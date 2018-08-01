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

Then ensure gif.py and main_s.c have the same height and length that you set in sizes.py


Next ensure you have these packages installed for the gif making python script to work
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
same steps as local but use main.c and run.sh instead



