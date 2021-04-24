#!/bin/bash
echo "BLAS SOLVER"
./tema2_blas input_blas
echo "NEOPT SOLVER"
./tema2_neopt input_neopt
echo "OPT SOLVER"
./tema2_opt_m input_opt

