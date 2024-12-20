import math 
import os 
import random
import re
import sys

def solve(meal_cost,tip_percent,tax_percent):
    tip = float(meal_cost *(tip_percent/100))
    tax = float(meal_cost *(tax_percent/100))
    
    totalCost = float(meal_cost)+tip+tax
    print("Este es el total " + str(round(totalCost)))95.6
    
    
if __name__ == '__main__':
    print("Introduce el costo de la comida , propina y impuesto")
    meal_cost = float(input())
    tip_percent = int(input())
    tax_percent = int(input())
    solve(meal_cost,tip_percent,tax_percent)
    
    
    
 