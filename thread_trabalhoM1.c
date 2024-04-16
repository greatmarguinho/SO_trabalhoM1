#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>

char linha[80]; // só para poder usar fgets e o programa pausa quando atinge 500 produtos
int var_sensor = 0;
int var_total = 0;
int var_global = 0; // numero total de itens(vai até 500)
struct timeval start, end;
double elapsed_time;

pthread_mutex_t exclusao_mutua = PTHREAD_MUTEX_INITIALIZER;
sem_t mutex;

void verifica(){
    if(var_global >= 500){
        var_total = var_sensor;
        var_global = 0;
        gettimeofday(&end, NULL);
            elapsed_time = (end.tv_sec - start.tv_sec) +
                   (end.tv_usec - start.tv_usec) / 1e6;
            printf("%d\n",var_total);
            printf("Tempo decorrido: %.6f segundos\n", elapsed_time);
        fgets(linha, sizeof(linha), stdin); // para parar o terminal
    }
}

void *thread_sensor_1(void *param){
   int var_local = 5;
   while(1){
      //pthread_mutex_lock(&exclusao_mutua);
      sem_wait(&mutex);
      var_sensor = var_sensor + var_local;
      printf("Peso total a cada 500: %d .Sensor th1: %d\n", var_total, var_local);
      var_global++;
      verifica();
      //pthread_mutex_unlock(&exclusao_mutua);
      sem_post(&mutex);
      usleep(2000000); //sleep for 2 ms
   }
}

void *thread_sensor_2(void *param){
   int var_local = 2;
   while(1){
      //pthread_mutex_lock(&exclusao_mutua);
      sem_wait(&mutex);
      var_sensor = var_sensor + var_local;
      printf("Peso total a cada 500: %d .Sensor th2: %d\n", var_total, var_local);
      var_global++;
      verifica();
      //pthread_mutex_unlock(&exclusao_mutua);
      sem_post(&mutex);
      usleep(1000000); //sleep for 1 s
   }
}


void main(){
   //declarar variáveis e tipos para threads
   pthread_t tid_1, tid_2;
   pthread_attr_t attr;
   
   sem_init(&mutex, 0, 1);
   
   pthread_attr_init(&attr);
   //criar thread 1
   pthread_create(&tid_1,&attr,thread_sensor_1,NULL);
   
   //criar thread 2
   pthread_create(&tid_2,&attr,thread_sensor_2,NULL);

    gettimeofday(&start, NULL);
   //join thread
   pthread_join(tid_1, NULL);
   pthread_join(tid_2, NULL);
   sem_destroy(&mutex);
}