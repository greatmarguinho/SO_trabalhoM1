import threading
import time
from datetime import datetime

var_sensor = 0
var_total = 0
var_global = 0  # numero total de itens (vai até 500)
mutex = threading.Semaphore()

def verifica():
    global var_sensor, var_total, var_global
    if var_global >= 500:
        var_total = var_sensor
        var_global = 0
        end = datetime.now()
        elapsed_time = (end - start).total_seconds()
        print(var_total)
        print("Tempo decorrido:", elapsed_time, "segundos")
        input("Pressione Enter para continuar...")

def thread_sensor_1():
    global var_sensor, var_total, var_global
    var_local = 5
    while True:
        with mutex:
            var_sensor += var_local
            print("Peso total a cada 500:", var_total, ". Sensor th1:", var_local)
            var_global += 1
            verifica()
        time.sleep(2)


def thread_sensor_2():
    global var_sensor, var_total, var_global
    var_local = 2
    while True:
        with mutex:
            var_sensor += var_local
            print("Peso total a cada 500:", var_total, ". Sensor th2:", var_local)
            var_global += 1
            verifica()
        time.sleep(1)


# Iniciar threads
thread1 = threading.Thread(target=thread_sensor_1)
thread2 = threading.Thread(target=thread_sensor_2)
thread1.start()
thread2.start()
start = datetime.now()

# Aguardar threads terminarem
thread1.join()
thread2.join()
