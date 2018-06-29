#include <stdio.h>
//size of the grid
int length = 23;
int height = 5;
//is calc'd on init
int total_cells;
int starting_speed = 50;
int target_speed = 65;//target "moving" value to get
//how long does each time step act as
double time_step_duration_sec = .1;//how many seconds is each time step acting as

//speed change rates
double braking_rate = 1;//breaking rate in 1mph
double accel_rate = 1;//in 1 mph
//so to calc the new movement speed at a time step,
//future_moving (speed) = moving - (accel/braking_rate * time_step_duration)

int number_of_cells_to_start_cars = 2;
int cells_to_start_cars[2] = {1,2}; 

//TODO 
//rows_to_be_barriers

//TODO cells to start spawners   

//uuid is for vehicles only, set to 0 for all other cells
int uuid_counter = 1;//uuids are assigned as 1, then uuid is incremented


int cell_size = 10;//how long/tall is each cell in ft,
// to be used for speed calc and so each cell=1 car length

//TODO perhaps make this row based, so 2/bi-drectional road could be made in future
int default_direction = 0;//default move to the right



struct Cell
{
    
    int is_populated;//is the cell populated, if so, change all the other values to make it a valid vehcivle or border
    int future_is_populated;
    
    double moving;//speed 0-100 0 for stop
    double future_moving;//next time step state of moving
    
    int neighbors[8];//neighbors TODO increase size to 5x5
    int future_neighbors[8];
    
    int number;//index in array current
    int future_number;//future location
    
    //directions 0 1 2 3 are right, left, up, down
    int direction;//which direction to move
    int future_direction;//which direction will it be moving
    
    //TODO set speeding value on init from 0-40
    int speeding_value;//20 for target = target  0 for -20 under and 40 for 20 over
    int future_speeding_value;//20 for target = target  0 for -20 under and 40 for 20 over
    
    int self_target;//on init this should be set to the golbal target +/- the speeding target
    int future_self_target;//on init this should be set to the golbal target +/- the speeding target
    
    
    
    //how far has it traveled through this cell
    double percent_through_current_cell;
    double future_percent_through_current_cell;
    
    int time_until_moving_again;//if crashed, how long will it act as a barrier
    int future_time_until_moving_again;//if crashed, how long will it act as a barrier
    
    //TODO
    int id;//uniquie vehchle id
    int future_id;//for when a cell moves
    
    
    //This section doesnt need a future, as these values are either non-vechile or non-moving cells
    
    int todo;//is cell processed yet

    //TODO init to define roadways by setting cells to borders
    int is_road_border;//to tell if the cell is a road boarder, if so, then set moving to -1 and not process this cell
    //TODO set spawning cells that will always be a new vehcile if possible
    int is_spawn_cell;
    int spawn_target_cell;//the target of a spawner to spawn new vehcicle
    
    int modified_by_count;//how many other cells are looking to occupy in the future
    
};

void n_random_cells_to_start_cars(){
    int size = length*height;
    printf("size %i\ns",size);
    for(int i = 0;i<number_of_cells_to_start_cars;i++){
        cells_to_start_cars[i] = rand() % (size) + 1;
    }
}


int main()
{
    //make  a grid based on l x w size and populate with cells
    total_cells = length*height;
    struct Cell grid[total_cells];

    //n_random_cells_to_start_cars();
    init_grid(grid,total_cells,cells_to_start_cars);
    
    
    //Print the grid as numbers for reference
    for(int i = 0; i < total_cells;i++){
        if(i<9){
            printf("[0%i]",i);
        }else{
            printf("[%i]",i);
        }
        if(((i+1)%length)==0){
            printf("\n");
        }
    }
    
    
    print_grid(grid);
    printf("\n\n\n");
    
    //print_cell_info(grid,20);
    
    //print_cell_info(grid,17);
    while(1){
        
        char str[20];
        printf("\nPush Enter to cycle (ctrl+c to quit)");
        gets(str);
        do_cycle(grid);
        print_grid(grid);
        printf("\n===========end===========\n");
        //print_cell_info(grid,21);

    }
    
    
    return 0;
}


//takes a cells current status and does its actions
void set_vehicle_future(struct Cell grid[],int cell){
    
}

void do_vehicle(struct Cell grid[],int cell){

}

// do a cycle

//could pe parallized
int do_cycle(struct Cell grid[])
{   
    
    //First for all vehicles, calc future values
    //(cell 1 has future value of 2 and such now)
        //set moving speed 1st TODO how should accel and braking work
        //then use that speed and the length of time step to calc distence traveled in that time step

    //TODO spawner logic
    //For each spawner, tell if the future values of the spawn_target
    //cell is 0, then set it to be a new spawn
    
    //look at all cells future values, for all of them that have moved out of their current cells
    //then set their future cells to thier values. each cell has a modified_by counter,
    // if a cell is modified by >1 others, set it to a crash
    
    //then set all other cells to their future values if modified by >0
    
    //then reset todo on all cells and modified by to 0 for next cycle
    
    
    
    
    
    
    
    
    /*
    //TODO make section that sets all future states correctly
    
    
    
    
    //currently just does the fwd action on a cell
    //this section is for setting all the futures to current
    for(int i = 0; i < total_cells;i++){
        //if a cell is a vehcile
        if(grid[i].is_populated && (grid[i].is_road_border==0) && (grid[i].is_spawn_cell==0) && grid[i].todo){
            //printf("\n %i \n",i);//TODO detect if cell is at end of row
            int is_edge = ((i+1)%length==0);
            
            //if not on end of row, do nromal, else kill
            if(!is_edge){
                //set_vehicle_future(grid,i);
            }else{
                grid[i].is_populated = 0;
            }
        }
        //TODO also do a spawn cell cycle
    }
    */
    
    //set todo back to 1, as now all cells acted upon
    //and none have been modified yet by other cells
    for(int i = 0; i < total_cells;i++){
        grid[i].todo = 1;
        grid[i].modified_by_count = 0;
    }
    
    
    
    return 0;
}


//TODO rules



//init the grid
void init_vehicle(struct Cell grid[],int i){
    grid[i].is_populated = 1;
    
    grid[i].moving = starting_speed;//speed 0-100 0 for stop
    //TODO make a rule to determine next speed
    grid[i].future_moving = grid[i].moving;//next time step state of moving
    
    //TODO make a rule to decide which direction to go, up, down,left or right
    grid[i].future_number = grid[i].number+1;//future location
    grid[i].direction = default_direction;//which direction to move
    grid[i].future_direction = default_direction;//which direction will it be moving
    
    //TODO make way to decide how much to speed by
    grid[i].speeding_value = 20;//20 for target = target  0 for -20 under and 40 for 20 over
    grid[i].self_target = target_speed;//on init this should be set to the golbal target +/- the speeding target
    
    grid[i].is_road_border = 0;//to tell if the cell is a road boarder, if so, then set moving to -1 and not process this cell
    
    grid[i].is_spawn_cell = 0;
    
    grid[i].percent_through_current_cell = 0;
    grid[i].time_until_moving_again = 0;//if crashed, how long will it act as a barrier
    grid[i].todo = 1;
}




//could be parallized
int init_grid(struct Cell grid[],int total_cells,int cells_to_start_cars[])
{
    //init the grid cells to their starting state
    for(int i = 0; i < total_cells;i++){
        
        //set the cells number
        grid[i].number = i;

        
        if(is_value_in_array(i,cells_to_start_cars,number_of_cells_to_start_cars))
        {
            //if value is a car
            init_vehicle(grid,i);
            //grid[i].is_populated = 1;
            
        }
        else//TODO make way to make rows into barriers
        {
            grid[i].is_populated = 0;
        }
        //TODO make a way for spawn_cells to have a target they have on init
        
        //set_neighbors(grid,i);
    }
    return 0;
}

/*
//sets and prints neighbors
int set_neighbors(struct Cell grid[],int cell)
{
    //set the cell to left andright of it to be neighbors
    grid[cell].neighbors[0] = cell;
    grid[cell].neighbors[1] = cell+2;
    //same for the next row down below cell, and left/right of that
    grid[cell].neighbors[2] = cell+2+length;
    grid[cell].neighbors[3] = cell+1+length;
    grid[cell].neighbors[4] = cell+length;
    //and same for above
    grid[cell].neighbors[5] = cell+2-length;
    grid[cell].neighbors[6] = cell+1-length;
    grid[cell].neighbors[7] = cell-length;
    
    //set all invalid neighbors (off grid ones) to -1
    trim_neighbors(grid,cell);
    
    //TODO check all neighbors, if any look invalid, then set to -1
    //print_cell_info(grid,cell);
    return  0;
}

//can be paralleized ?
int trim_neighbors(struct Cell grid[],int cell)
{
    //for all neighbors
    for(int i = 0; i < 8;i++){
        //printf("%i ",grid[cell].neighbors[i]);
        //make suer neighbor isnt out of bound total
        if(!(grid[cell].neighbors[i]>0 && grid[cell].neighbors[i]<=total_cells)){
            grid[cell].neighbors[i] = -1;
        }
        //then also make sure the neighbor isnt out of row
        int row = find_row_from_cell_and_row_length(grid[cell].neighbors[i],length);
        int row_upper_end = row*length;
        int row_lower_end = (row*length)-length+1;
        //printf("\nrow:%i upper:%i lower:%i",row,row_upper_end,row_lower_end);
        if(!(grid[cell].neighbors[i]>=row_lower_end && grid[cell].neighbors[i] <= row_upper_end)){
            grid[cell].neighbors[i] = -1;
        }
        
    }
    //printf("\n");
    
    return 0;
}

*/

int find_row_from_cell_and_row_length(int cell,int length)
{
    if(cell%length==0){
        cell--;
    }
    int temp = cell;
    int row = 0;
    while(1){
        row++;
        temp = temp - length;
        //printf("temp %i\n",temp);
        if(temp<0){
            break;
        }
    }
    return row;
}

//printing/debug

//print cell info by index
int print_cell_info(struct Cell grid[],int cell)
{
    //printf("cell index: %i cell number: %i  alive:%i ",cell,grid[cell].number,grid[cell].is_populated);
    //print_neighbors(grid,cell);
    
    printf("is_populated %i \nmoving %i \nfuture_moving %i \nnumber %i \nfuture_number %i \ndirection %i \nfuture_direction %i \nspeeding_value %i \nself_target %i \nis_road_border %i \nis_spawn_cell %i \npercent_through_current_cell %i \ntime_until_moving_again %i",
    grid[cell].is_populated
    ,grid[cell].moving
    ,grid[cell].future_moving
    ,grid[cell].number
    ,grid[cell].future_number
    ,grid[cell].direction
    ,grid[cell].future_direction
    ,grid[cell].speeding_value
    ,grid[cell].self_target
    ,grid[cell].is_road_border
    ,grid[cell].is_spawn_cell
    ,grid[cell].percent_through_current_cell
    ,grid[cell].time_until_moving_again);
    
    
    return 0;
}

//print neighbors of cell by index
int print_neighbors(struct Cell grid[],int cell)
{   
    printf("neighbors: ");
    for(int i = 0; i < 8;i++){
        printf("%i ",grid[cell].neighbors[i]);
    }
    printf("\n");
}

//Print the grid with the alive values shown in the cells
int print_grid(struct Cell grid[])
{
    printf("\n");
    for(int i = 0; i < total_cells;i++){
        
        printf("[%i]",grid[i].is_populated);
        if(((i+1)%length)==0){
            printf("\n");
        }
    }
    return 0;
}

//other 

//Could be parallelized
int is_value_in_array(int val, int *arr, int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return 1;
    }
    return 0;
}


