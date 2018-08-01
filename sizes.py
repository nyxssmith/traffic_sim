"""
int length = 23;
int height = 9;
//is calc'd on init
int total_cells;

//These are used to init the grid with borders as rows, as well as starting spawners and cars
int number_of_cells_to_start_cars = 0;
int cells_to_start_cars[0] = {}; 

int number_of_rows_to_start_barriers = 3;
int rows_to_start_barriers[3] = {0,4,8}; 

int number_of_cells_to_start_spawners = 6;
int cells_to_start_spawners[6] = {45,68,91,115,138,161}; 
"""

length = 931
height = 51

number_of_rows_to_start_barriers = 3
rows_to_start_barriers = [0]
halfway = int(height/2)
rows_to_start_barriers.append(halfway)
rows_to_start_barriers.append(height-1)


#rows_to_start_barriers = [0,4,8] 
print("int number_of_rows_to_start_barriers = "+str(len(rows_to_start_barriers))+";")
print("int rows_to_start_barriers["+str(len(rows_to_start_barriers))+"] = {"+str(rows_to_start_barriers).replace("[","").replace("]","")+"};" )


number_of_cells_to_start_spawners = height-3;
print("int number_of_cells_to_start_spawners = "+str(number_of_cells_to_start_spawners)+";")

cells_to_start_spawners = []

first_half = True
counter = 0
row_counter = 0;
for i in range(0,height*length):
    #print(i)
    add = False
    increment_row = False
    if counter == length-1:
        #print("ding!",i,first_half,row_counter)
        counter = 0
        add = True
        increment_row = True
    else:
        counter += 1
    if row_counter >= halfway:
        first_half = False
    
    if (row_counter in rows_to_start_barriers) and first_half:
        add = False
    
    if (row_counter+1 in rows_to_start_barriers) and not first_half:
        add = False
    
    if row_counter == height-1:
        add = False
    
    if add:
        if first_half:
            cells_to_start_spawners.append(i)
        else:
            cells_to_start_spawners.append(i+1)
    if increment_row:
        row_counter+=1
    
print("int cells_to_start_spawners["+str(number_of_cells_to_start_spawners)+"] = {"+str(cells_to_start_spawners).replace("[","").replace("]","")+"}; ")
