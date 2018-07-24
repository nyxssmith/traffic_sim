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
height = 9
target_speed = 65

#get .dat files
d = os.listdir(".")
#print(d)

grids = []
speeds = []
for f in d:
    if ".grid" in f:
        grids.append(f)

    if ".speed" in f:
        speeds.append(f)


s_grids = sorted(grids,key=lambda x: int(os.path.splitext(x)[0]))
grids=s_grids

s_speeds = sorted(speeds,key=lambda x: int(os.path.splitext(x)[0]))
speeds=s_speeds

#make big list of grids
b_mat_g = []
b_mat_s = []

for grid in grids:

    temp_mat = []
    with open(grid,"r") as f:
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
    b_mat_g.append(temp_mat)
    #print("temp mat",temp_mat)
    
    

for speed in speeds:

    temp_mat = []
    with open(speed,"r") as f:
        raw_speeds = f.readlines()
        #print(raw_speeds)
        speed_list = []
        for s in raw_speeds:
            speed_list.append(int(s.replace("\n","")))
        #print(speed_list)
        count = 0
        temp =[]
        for part in speed_list:
            temp.append(part)
            count+=1
            if count==length:
                count = 0
                temp_mat.append(temp)
                temp=[]
        temp_mat.append(temp)
    b_mat_s.append(temp_mat)
        
#print("grids",b_mat_g)
#print("speeds",b_mat_s)
#print(len(b_mat_g))
#print(len(b_mat_s))


#for each .dat matrix over time make a png
m_counter = 0;
for mat in b_mat_g:

    array = np.zeros([height, length, 3], dtype=np.uint8)
    
    r_counter = 0
    for row in mat:
        c_counter = 0
        #print(mat[r_counter])
        #print(array[r_counter])
        for item in mat[r_counter]:
            #print("mat r,c",mat[r_counter][c_counter])
            #print("r,c",r_counter,c_counter)
            num = int(mat[r_counter][c_counter])
            #print(array[r_counter][c_counter])
            if(num==0):
                array[r_counter][c_counter] = [255,255,255]
            elif(num==1):
                #print("found vehcilce, calc color from speed",r_counter,c_counter)
                #print("speed is ",b_mat_s[m_counter][r_counter][c_counter])
                speed = b_mat_s[m_counter][r_counter][c_counter]
                if speed >target_speed:
                    array[r_counter][c_counter] = [0,255,0]
                elif speed <target_speed :
                    #the red and green values
                    color = [0,0]
                    #print("speed",speed)
                    speed_as_level = 0
                    greater_than_half = bool(speed>(.5*target_speed))
                    #print("green? ",greater_than_half)
                    per = speed/target_speed
                    #print("percent",per)
                    #print("per*500",per*500)
                    if greater_than_half:
                        color[1] = 255
                        color[0] = int(per*500)-255
                    else:
                        color[0] = 255
                        color[1] = int(per*500)-255
                        
                    array[r_counter][c_counter] = [color[0],color[1],0]
                
                
            elif(num==2):
                array[r_counter][c_counter] = [0,0,255]
            else:
                array[r_counter][c_counter] = [0,0,0]
    
            #print("X: "+str(c_counter)+" Y: "+str(r_counter)+" is "+str(num))        
            c_counter+=1
            
        r_counter+=1
        
    m_counter+=1
    
    img = Image.fromarray(array)
    name = str(b_mat_g.index(mat))+".png"
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
#print(s_images)


import imageio
images = []
for image in s_images:
    images.append(imageio.imread(image))
imageio.mimsave('output.gif', images)

print("ouput.gif created\nuse 'make clean' to clean all .speed, .grid, .png files")






