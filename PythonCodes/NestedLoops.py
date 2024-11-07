#one example code
i = 1

while i<=2:
    j=1
    while j<=3:
        print('*',end='')
        j += 1
    print()
    i += 1
    
#second example code
numbers = [12,5,3]

i = 0 
for n in numbers:
    while i < n:
        print(i,end="")
        i += 2
    i = 0
    print()
    
