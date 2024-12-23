import can
import time

# Configuración del canal PCAN y la velocidad del bus
CHANNEL = "PCAN_USBBUS1"  # Cambia esto según tu configuración
BITRATE = 500000  # Velocidad del bus en bits por segundo

# Configura el bus CAN
try:
    bus = can.interface.Bus(bustype='pcan', channel=CHANNEL, bitrate=BITRATE)
    print("Conexión al bus CAN exitosa.")
except can.CanError as e:
    print(f"Error al conectar al bus CAN: {e}")
    exit(1)

# Lista para almacenar los mensajes recibidos
store = []

# Función para decodificar los mensajes recibidos
def decode_message(msg):
    if msg.is_extended_id:
        print(f"Mensaje extendido recibido: ID=0x{msg.arbitration_id:X}, Datos={msg.data.hex()}")
    else:
        print(f"Mensaje estándar recibido: ID=0x{msg.arbitration_id:X}, Datos={msg.data.hex()}")

# Función para almacenar los valores recibidos
def store_values(msg):
    store.append({
        "id": msg.arbitration_id,
        "data": msg.data.hex(),
        "timestamp": msg.timestamp
    })
    print(f"Mensaje almacenado: {store[-1]}")

# Lee mensajes continuamente
try:
    print("Esperando mensajes...")
    while True:
        message = bus.recv(timeout=1)  # Espera un mensaje (timeout en segundos)
        if message:
            decode_message(message)
            #store_values(message)
except KeyboardInterrupt:
    print("\nFinalizando la lectura de mensajes.")
finally:
    bus.shutdown()
