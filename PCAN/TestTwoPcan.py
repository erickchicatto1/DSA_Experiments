import can
import json
import time
from collections import deque

# Configuración del bus CAN
bus = can.interface.Bus(
    interface='pcan',  # Usando Peak CAN
    channel='PCAN_USBBUS1',  # Canal configurado
    bitrate=500_000  # Debe coincidir con el bitrate del transmisor
)

# Almacenar valores CAN en un deque con tamaño máximo de 5
canValues = deque(maxlen=5)

GenerateJsonFlag = False  # Flag para generar JSON
CanFileName = 'CanValues.json'

# Clase para manejar los datos
class SaveData(object):
    """Clase para almacenar información CAN"""
    def __init__(self, data):
        self.data = data

    def show_response(self):
        """Muestra la respuesta almacenada"""
        print(self.data)

# Función para recibir mensajes
def receive_message():
    global GenerateJsonFlag  # Declarar el flag como global
    try:
        message = bus.recv(timeout=1.0)  # Tiempo de espera para recibir mensaje
        if message:
            print(f"Mensaje recibido: ID={hex(message.arbitration_id)}, Data={message.data}")
            canValues.append(message)
            # Validar mensaje
            if (message.arbitration_id == 0x0A and
                list(message.data) == [0, 1, 2, 3, 4, 5, 6, 7]):
                print("Mensaje válido recibido.")
                GenerateJsonFlag = True
    except Exception as e:
        print(f"Error al recibir mensaje: {e}")

# Función para escribir datos en JSON
def write_to_json():
    if GenerateJsonFlag:
        with open(CanFileName, 'w') as f:
            json.dump([msg.data.tolist() for msg in canValues if msg], f)
        print(f"Datos escritos en {CanFileName}")

# Bucle principal
while True:
    receive_message()
    #write_to_json()  # Activar escritura en JSON
    #time.sleep(1)  # Esperar 1 segundo antes de recibir el próximo mensaje
