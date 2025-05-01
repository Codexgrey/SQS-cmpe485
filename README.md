# SQS-cmpe485 - Objectives
- Simple Queueing Systems
- Numerical solution techniques to Closed Form Queueing Equations.


# List of files
- sim.c         : source code for sim
- sim.exe       : compiled code
- Makefile      : config to help compile, test, clean (working dir) and run codes
- test.sh       : simple script to test codes and report errors
- *.txt files   : program results


# How-To Guide > LINUX, BASH
- Clone repo via ssh (git clone https://github.com/Codexgrey/SQS-cmpe485)
- Depending on your environment, use Makefile as follows;

## To compile and test the program
- $ `mingw32-make test`
- OR
- $ `make test`

## To run simulation and print the results
- $ `mingw32-make run` 
- OR
- $ `make run`

## To clean working directory (remove results and all .exe files)
- $ `mingw32-make clean` 
- OR
- $ `make clean`

## To clean working directory and recompile :
- mingw32-make rebuild
- OR
- make rebuild


# Have a nice day...
