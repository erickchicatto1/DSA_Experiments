import ctypes

#cargar la libreria compartida
# Ruta de la DLL
dll_path = r"D:\Ing_Software\1.stm32\DSA_Experiments\PythonCodes\mylib.dll"

# Cargar la DLL
lib = ctypes.CDLL(dll_path)
#llamar a la funcion hello_fromC
lib.hello_fromC()
# Definir los tipos de retorno y argumentos de las funciones
lib.add.restype = ctypes.c_int
lib.substract.restype = ctypes.c_int
lib.multiply.restype = ctypes.c_int
lib.divide.restype = ctypes.c_float
lib.is_event.restype = ctypes.c_int

#ejemplos de uso 
a = 5
b = 5


# Sumar
result_add = lib.add(a, b)
print(f"The result of {a} + {b} is {result_add}.")

# Restar
result_subtract = lib.substract(a, b)
print(f"The result of {a} - {b} is {result_subtract}.")

# Multiplicar
result_multiply = lib.multiply(a, b)
print(f"The result of {a} * {b} is {result_multiply}.")

# Dividir
result_divide = lib.divide(a, b)
print(f"The result of {a} / {b} is {result_divide:.2f}.")

# Verificar si un número es par
number = 4
if lib.is_event(number):
    print(f"{number} is even.")
else:
    print(f"{number} is odd.")
