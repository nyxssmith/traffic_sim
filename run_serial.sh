#!/bin/bash

#on SC done have make in here
echo "Running make"
make
#once mpi is added chancge this to mpi excec bit
echo "Running ./main_s.cx"
./main_s.cx || echo "If segfault was the size too big?"
#once on SC make gif runner not run and instead make a zip of all .speed and .grid files
echo "Running gif.py"
python gif.py || echo "Check that the length and height are the same in the gif.py and main.c"
echo "Gif made, running make clean"
make clean
echo "Done!"
