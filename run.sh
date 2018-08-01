#!/bin/bash

#once mpi is added chancge this to mpi excec bit
echo "Running ./main.cx"
./main.cx || echo "If segfault was the size too big?"
#once on SC make gif runner not run and instead make a zip of all .speed and .grid files
echo "TODO make zip of all .speed and .gif files for making gif on local machines"

make clean
echo "Done!"
