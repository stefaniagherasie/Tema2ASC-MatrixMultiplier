#!/bin/bash
printf "\nValgrind BLAS\n"
valgrind --tool=memcheck --leak-check=full ./tema2_blas inputs/input_valgrind

printf "\n\n\nValgrind NEOPT\n"
valgrind --tool=memcheck --leak-check=full ./tema2_neopt inputs/input_valgrind

printf "\n\n\nValgrind OPT\n"
valgrind --tool=memcheck --leak-check=full ./tema2_opt_m inputs/input_valgrind


