 #!/bin/bash


gcc -g -c 2048.c
gcc -g -c griglia.c
gcc -g -c linea.c
gcc -g -c classifica.c
gcc -o 2048 2048.o linea.o griglia.o classifica.o
