import math
import os
import random
import re
import sys


def solve(meal_cost,tip_percent,tax_percent):
    tip = float(meal_cost *(tip_percent/100))
    tax = float(meal_cost *(tax_percent/100))
    
    totalCost = float(meal_cost)+tip+tax
    print("Este es el total"+str(round(totalCost)))
    
def use_math_module(number):
    print("\n--- Uso del módulo math ---")
    print(f"Redondeo hacia abajo: {math.floor(number)}")
    print(f"Raíz cuadrada: {math.sqrt(number)}")
    print(f"Número elevado al cubo: {math.pow(number, 3)}")
    
def use_os_module():
    print("\n--- Uso del módulo os ---")
    print(f"Nombre del sistema operativo: {os.name}")
    print(f"Directorio actual: {os.getcwd()}")
    
def use_random_module():
   print("\n--- Uso del módulo random ---")
   random_number = random.randint(1,100)
   print(f"Número aleatorio generado: {random_number}")
   return random_number

def use_re_module(string):
    print("\n--- Uso del módulo re ---")
    if re.match(r"^\d+\.\d+$", string):
        print("La cadena es un número decimal válido.")
    else:
        print("La cadena no es un número decimal válido.")

def use_sys_module():
    print("\n--- Uso del módulo sys ---")
    print(f"Argumentos de línea de comandos: {sys.argv}")
    print(f"Tamaño máximo de un entero: {sys.maxsize}")

if __name__ == '__main__':
    # Entrada de datos
    print("Introduce el costo de la comida, propina y impuesto:")
    meal_cost = float(input())
    tip_percent = int(input())
    tax_percent = int(input())
    
    # Resolver el cálculo principal
    solve(meal_cost, tip_percent, tax_percent)
    
    # Uso adicional de los módulos
    use_math_module(meal_cost)
    use_os_module()
    random_number = use_random_module()
    use_re_module(str(meal_cost))
    use_sys_module()
    
    









if __name__ == '__main__':
    