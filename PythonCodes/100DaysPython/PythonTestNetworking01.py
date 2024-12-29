import requests

arduino_ip = "http://192.168.100.19"

#funcion para encender un LED
def turn_on_led(led_number):
    url = f"{arduino_ip}/ledon{led_number}"
    
    try:
        response = requests.get(url)
        if response.status_code == 200:
            print(f"LED {led_number} encendido")
        else:
            print(f"Error al encender LED{led_number}:{response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Error de conexión: {e}")
        
#funcion para apagar un led
def turn_off_led(led_number):
    url = f"{arduino_ip}/ledoff{led_number}"
    
    try:
        response = requests.get(url)
        if response.status_code == 200:
            print(f"LED {led_number} apagado")
        else:
            print(f"Error al apagar LED{led_number}:{response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Error de conexión: {e}")

#Menu para interactuar con el arduino 
    
def menu():
    while True:
        print("\n Control de LEDs")
        print("\n 1. Encender Led1")
        print("\n 2. Apagar LED1")
        print("\n 3. Encender LED2")
        print("\n 4. Apagar LED2")
        print("\n 5. Salir")
        
        choice = input("Selecciona una opcion")

        if choice == "1":
            turn_on_led(1)
        elif choice == "2":
            turn_off_led(1)
        elif choice == "3":
            turn_on_led(2)
        elif choice == "4":
            turn_off_led(2)
        elif choice == "5":
            print("Saliendo ... ")            
            break
        else:
            print("Opcion invalida , intenta de nuevo ")

menu()
            
            
        