#HOW TO USE
#run python3 gif.py after changing length and height to match the C code
#run the c code with output grid turned on
#this will make output.gif and a bunch of other pngs

#requires numpy, imageio and PIL
#pip3 install numpy imageio pillow

import os

import numpy as np
from PIL import Image


length = 23
height = 5

#get .dat files
d = os.listdir(".")
print(d)

dats = []
for f in d:
    if ".dat" in f:
        dats.append(f)

print(dats)
s_dats = sorted(dats,key=lambda x: int(os.path.splitext(x)[0]))
dats=s_dats

#make big list of grids
b_mat = []

for dat in dats:
    print(dat.replace(".dat",""))
    
    temp_mat = []
    with open(dat,"r") as f:
        raw_grid = f.read()
        #print(raw_grid)
        grid_list = list(raw_grid)
        #print(grid_list)
        count = 0
        temp =[]
        for part in grid_list:
            temp.append(part)
            count+=1
            if count==length:
                count = 0
                temp_mat.append(temp)
                temp=[]
        temp_mat.append(temp)
    b_mat.append(temp_mat)
    #print("temp mat",temp_mat)
    
    
    

#for each .dat matrix over time make a png
for mat in b_mat:

    array = np.zeros([height, length, 3], dtype=np.uint8)
    
    r_counter = 0
    for row in mat:
        c_counter = 0
        #print(mat[r_counter])
        #print(array[r_counter])
        for item in mat[r_counter]:
            #print(mat[r_counter][c_counter])
            num = int(mat[r_counter][c_counter])
            #print(array[r_counter][c_counter])
            if(num==0):
                array[r_counter][c_counter] = [255,255,255]
            elif(num==1):
                array[r_counter][c_counter] = [0,200,0]
            elif(num==2):
                array[r_counter][c_counter] = [0,0,255]
            else:
                array[r_counter][c_counter] = [0,0,0]
    
            #print("X: "+str(c_counter)+" Y: "+str(r_counter)+" is "+str(num))        
            c_counter+=1
            
        r_counter+=1

    
    img = Image.fromarray(array)
    name = str(b_mat.index(mat))+".png"
    img.save(name)


#make all pngs into gif

d = os.listdir(".")
images = []
for f in d:
    if ".png" in f:
        images.append(f)
try:
    images.remove("scopes.png")
except:
    pass
s_images = sorted(images,key=lambda x: int(os.path.splitext(x)[0]))
print(s_images)


import imageio
images = []
for image in s_images:
    images.append(imageio.imread(image))
imageio.mimsave('output.gif', images)







