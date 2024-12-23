#In this code I would like to experiment how to use excel and pcan apis
import random
import pandas as pd
import can 


#1. Configure the can channel 
bus = can.interface.Bus(
    interface = 'pcan', # Se usa Peak Can
    channel = 'PCAN_USBBUS1', #Nombre del canal 
    bitrate = 500_000 # The bitrate to send a value
)

i = 0

def receive_message():
    """Receive the message and append in a list """
    message = bus.recv()
    if message is not None:
        print("Received Message :{}".format(message))
        

#Create the frame  , using a dictionary
data = {
    'MessageCan':'message',
       }

while i<=10:
    receive_message()
    i = i + 1 
    
df = pd.DataFrame(data)
#Save in the excel 
df.to_excel('datosCan.xlsx',index=False)


    

    

    
    
    

