#!/bin/bash
printf "\nCachegrind BLAS\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_blas inputs/input_valgrind

printf "\n\n\nCachegrind NEOPT\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_neopt inputs/input_valgrind

printf "\n\n\ncachegrind OPT\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_opt_m inputs/input_valgrind

rm -rf cachegrind*

