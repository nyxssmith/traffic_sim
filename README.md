# traffic_sim
straight line traffic sim in C

# Setup (local)
Setting cycles and output
Open main_s.c and set the cycles to do to be how many cycles you want set and any other variables you wish to change as well
```C //how many cycles should be simulated
int cycles_to_do = 5000;

int do_output_grid = 1;
```
If do_output_grid is set to 1, then you must also follow the gif making steps as well

Setting the size of the grid
Open sizes.py
set the length and height to what you want the grid size to be
run
```sh
$ python sizes.py
```
this will output 4 lines like these
```sh
int number_of_rows_to_start_barriers = 3;
int rows_to_start_barriers[3] = {0, 25, 50};
int number_of_cells_to_start_spawners = 48;
int cells_to_start_spawners[48] = {1861, 2792, 3723, 4654, 5585, 6516, 7447, 8378, 9309, 10240, 11171, 12102, 13033, 13964, 14895, 15826, 16757, 17688, 18619, 19550, 20481, 21412, 22343, 23274, 24206, 25137, 26068, 26999, 27930, 28861, 29792, 30723, 31654, 32585, 33516, 34447, 35378, 36309, 37240, 38171, 39102, 40033, 40964, 41895, 42826, 43757, 44688, 45619}; 
```
to the console
Copy and overwrite the same lines in main_s.c
they are towards the top of the file

Then ensure gif.py and main_s.c have the same height and length and target speed that you set in sizes.py
```py
length = 931
height = 51
target_speed = 65
```
```C
int length = 931;
int height = 51;
int target_speed = 65;
```

Next ensure you have these packages installed for the gif making python script to work (it is python3)
(you can skip this step if do_output_grid = 0)
```sh
$ pip3 install numpy imageio pillow
```

# Running (local)
```sh
$ chmod +x run_serial.sh
$ ./run_serial.sh
```
This can take some time depending on how many cycles were set to run and size of grid
there will now be an output.gif


# Using on Supercomputer

First ensure there is also a directory called "files"
if not, make one
```sh
mkdir files
```
this is where the .grid and .speed files will go

Setup: same as local.
To run, use
```sh
qsub pbs_Traffic
```
this will make a file similar to
```sh
traffic_run.o34714
```
and now the files directory will be populated

scp the files dir back to you local machine and either
1: copy gif.py to it and run gif.py
2: copy all the .grid and .speed files to the same dir as gif.py and run it

# Other changeable values

Length and height of the grid (covered above)
```C
int length = 931;
int height = 51;

//is calc'd on init
int total_cells;
```

Indices of cells to start as cars that drive to the left by default
```C
int number_of_cells_to_start_cars = 0;
int cells_to_start_cars[0] = {}; 
```
Barrier and spawner definition
Covered above via copy/paste section
defines cell indices that should start as spawners and rows to start barriers
```C
int number_of_rows_to_start_barriers = 3;
int rows_to_start_barriers[3] = {0, 8, 16};
int number_of_cells_to_start_spawners = 14;
int cells_to_start_spawners[14] = {499, 749, 999, 1249, 1499, 1749, 1999, 2250, 2500, 2750, 3000, 3250, 3500, 3750}; 
```

The lenth a cell is in feet, used for distance traveled simulation
kept as 10ft as that is avg length of car
```C
int cell_size = 10;//how long/tall is each cell in ft,
```

How many cycles should be simulated
Covered above
```C
int cycles_to_do = 5000;
```

Should the C code ouput files for gif creaion
```C
int do_output_grid = 1;
```

Vehicle parameters

What speed should cars spawn at
```C
int starting_speed = 65;
```

Speed limit of the road
```C
int target_speed = 65;
```

Speed change rates
```C
double braking_rate = 8;//breaking rate in 1mph
double accel_rate = .4;//in 1 mph
```

Default vehicle direction
0,1,2,3 for left,right,up,down
```C
int default_direction = 0;
```

ID of each vehicle counter for unique IDs
```C
int uuid_counter = 1;
```

World parameters

How much time a cycle simulates
```C
double time_step_duration_sec = .1;
```

Spawning rate control
0-100 higher = less
```C
int spawning_threshold = 75;
```

Threshold to randomly change lanes without reason
0-100 is higher it is the less likely it is to randomly change lanes
less than 0 will try to change lanes every cycle
above 100 will never randomaly change lanes unless to pass or avoid crash
```C
int lane_transfer_threshold = 101;
```

How long in minutes a crashed cell lasts for before becoming empty
is set really small to avoid huge pileups
```C
double crash_duration = .04;
```

Not needed to be set, is used by the program to tell how long its run
```C
int run_counter = 0;
```
