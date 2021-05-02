#!/bin/bash
printf "\nCachegrind BLAS\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_blas inputs/input_valgrind >> results/blas.cache 2>&1

printf "\n\n\nCachegrind NEOPT\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_neopt inputs/input_valgrind >> results/neopt.cache 2>&1

printf "\n\n\ncachegrind OPT\n"
valgrind --tool=cachegrind --branch-sim=yes ./tema2_opt_m inputs/input_valgrind >> results/opt_m.cache 2>&1

rm -rf cachegrind*

