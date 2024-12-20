#Make an empty list for storing aliens 
aliens = []

#make 30 aliens 
for aliens_number in range(30):
    new_alien = {'color':'green','points':5,'speed':'slow'} #Dictionarie
    aliens.append(new_alien) #append in the list

for alien in aliens[:3]:
    if alien['color']=='green':
        alien['color']='yellow'
        alien['speed']='medium'
        alien['points']=10
        
#slow the first 5 aliens 
for alien in aliens[:5]:
    print(alien)
print("...")

#show how many aliens have been created
print(f"Total number of aliens : {len(alien)}")


