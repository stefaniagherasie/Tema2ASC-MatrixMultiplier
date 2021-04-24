printf "\ndiff BLAS - NEOPT\n"
./compare out1_blas out1_neopt 0.01
./compare out2_blas out2_neopt 0.01
./compare out3_blas out3_neopt 0.01


printf "\ndiff BLAS - OPT\n"
./compare out1_blas out1_opt 0.01
./compare out2_blas out2_opt 0.01
./compare out3_blas out3_opt 0.01


printf "\ndiff NEOPT - OPT\n"
./compare out1_neopt out1_opt 0.01
./compare out2_neopt out2_opt 0.01
./compare out3_neopt out3_opt 0.01


