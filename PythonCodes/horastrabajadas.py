#Preguntar al usuario por las horas trabajdas
horas_trabajadas = float(input("Introduce el numero de horas trabajadas  "))
#preguntar por el coste por hora 
coste_por_hora =  float(input("Introduce el coste por horas  "))
#calcular la paga 
paga = horas_trabajadas*coste_por_hora
print(f"La paga que te corresponde es: {paga:.2f}")