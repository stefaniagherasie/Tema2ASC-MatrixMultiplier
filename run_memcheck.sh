#!/bin/bash
printf "\nValgrind BLAS\n"
valgrind --tool=memcheck --leak-check=full ./tema2_blas inputs/input_valgrind >> results/blas.memory 2>&1

printf "\n\n\nValgrind NEOPT\n"
valgrind --tool=memcheck --leak-check=full ./tema2_neopt inputs/input_valgrind >> results/neopt.memory 2>&1

printf "\n\n\nValgrind OPT\n"
valgrind --tool=memcheck --leak-check=full ./tema2_opt_m inputs/input_valgrind >> results/opt_m.memory 2>&1


