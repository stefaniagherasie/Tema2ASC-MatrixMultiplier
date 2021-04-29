printf "\ndiff BLAS - NEOPT\n"
./compare outputs/out1_blas outputs/out1_neopt 0.01
./compare outputs/out2_blas outputs/out2_neopt 0.01
./compare outputs/out3_blas outputs/out3_neopt 0.01


printf "\ndiff BLAS - OPT\n"
./compare outputs/out1_blas outputs/out1_opt 0.01
./compare outputs/out2_blas outputs/out2_opt 0.01
./compare outputs/out3_blas outputs/out3_opt 0.01


printf "\ndiff NEOPT - OPT\n"
./compare outputs/out1_neopt outputs/out1_opt 0.01
./compare outputs/out2_neopt outputs/out2_opt 0.01
./compare outputs/out3_neopt outputs/out3_opt 0.01


