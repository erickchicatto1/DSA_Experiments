#This code is for experiment about the PCAN and try to make an automation

#1. Understand how connect pcan with python 

import can 

bus = can.interface.Bus(
    bustype = 'pcan', # Se usa Peak Can
    channel = 'PCAN_USBBUS1', #Nombre del canal 
    bitrate = 500_000
)

#Enviar un mensaje 
message = can.Message(arbitration_id=0x123, data=[0x11, 0x22, 0x33, 0x44], is_extended_id=False)

#
try:
    bus.send(message)
    print(f"Mensaje enviado")
except can.CanError:
    print("Error al enviar el mensaje.")
    
#Escuchar mensajes
for msg in bus:
    print(f"ID: {msg.arbitration_id}, Data: {msg.data}")
    