with open('tiempoSPI.txt') as f:
   lines=f.readlines() 
delta=[]

for i in range(1,len(lines)):
    delta.append((int(lines[i].strip())-int(lines[i-1].strip())))
 
#print(delta)

# Guardar la lista delta en un archivo
with open('deltaI2C.txt', 'w') as f:
    for item in delta:
        f.write("{}\n".format(item))
