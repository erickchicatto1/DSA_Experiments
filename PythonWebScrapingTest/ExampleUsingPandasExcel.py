import pandas as pd

#Create an dictionary of data 
data = {
    "Nombre":["Juan","Maria","Carlos"],
    "Edad" : [25,30,35],
    "Ciudad":["Madrid","Lima","Bogota"]
}

#Convert to data frame
df = pd.DataFrame(data)

df.to_excel("PandasFile.xlsx",index = False)
print("File saved like 'PandasFile.xlsx' ")