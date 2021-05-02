#!/bin/bash
echo "BLAS SOLVER"
./tema2_blas inputs/input_graphs

echo "NEOPT SOLVER"
./tema2_neopt inputs/input_graphs

echo "OPT SOLVER"
./tema2_opt_m inputs/input_graphs

