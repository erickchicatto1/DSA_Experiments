import random 

rock = '''
    _______
---'   ____)
      (_____)
      (_____)
      (____)
---.__(___)
'''

paper = '''
    _______
---'   ____)____
          ______)
          _______)
         _______)
---.__________)
'''

scissors = '''
    _______
---'   ____)____
          ______)
       __________)
      (____)
---.__(___)
'''


games_images = [rock,paper,scissors]

user_choice = int(input("What do you choose? Type 0 for Rock, 1 for Paper or 2 for Scissors.\n"))
print(games_images[user_choice])

computer_choice = random.randint(0,2)
print("Computer Choice : ")
print(games_images[computer_choice])

if user_choice >= 3 or user_choice < 0: 
  print("You typed an invalid number, you lose!") 
elif user_choice == 0 and computer_choice == 2:
  print("You win!")
elif computer_choice == 0 and user_choice == 2:
  print("You lose")
elif computer_choice > user_choice:
  print("You lose")
elif user_choice > computer_choice:
  print("You win!")
elif computer_choice == user_choice:
  print("It's a draw")
  
'''
// mylib.c
#include <stdio.h>

// Función que imprime un saludo
void hello_from_c() {
    printf("Hello from C!\n");
}

// Función que suma dos enteros
int add(int a, int b) {
    return a + b;
}

// Función que resta dos enteros
int subtract(int a, int b) {
    return a - b;
}

// Función que multiplica dos enteros
int multiply(int a, int b) {
    return a * b;
}

// Función que divide dos enteros (con manejo de división por cero)
float divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero!\n");
        return 0; // O un valor especial que definas
    }
    return (float)a / b;
}

// Función que verifica si un número es par
int is_even(int n) {
    return n % 2 == 0; // Retorna 1 (true) si es par, 0 (false) si es impar
}


gcc -shared -o mylib.so -fPIC mylib.c  # En Linux/Mac
# o
gcc -shared -o mylib.dll mylib.c  # En Windows
import ctypes

# Cargar la biblioteca compartida
lib = ctypes.CDLL('./mylib.so')  # o './mylib.dll' en Windows

# Llamar a la función hello_from_c
lib.hello_from_c()

# Definir los tipos de retorno y argumentos de las funciones
lib.add.restype = ctypes.c_int
lib.subtract.restype = ctypes.c_int
lib.multiply.restype = ctypes.c_int
lib.divide.restype = ctypes.c_float
lib.is_even.restype = ctypes.c_int

# Ejemplos de uso
a = 5
b = 3

# Sumar
result_add = lib.add(a, b)
print(f"The result of {a} + {b} is {result_add}.")

# Restar
result_subtract = lib.subtract(a, b)
print(f"The result of {a} - {b} is {result_subtract}.")

# Multiplicar
result_multiply = lib.multiply(a, b)
print(f"The result of {a} * {b} is {result_multiply}.")

# Dividir
result_divide = lib.divide(a, b)
print(f"The result of {a} / {b} is {result_divide:.2f}.")

# Verificar si un número es par
number = 4
if lib.is_even(number):
    print(f"{number} is even.")
else:
    print(f"{number} is odd.")




'''