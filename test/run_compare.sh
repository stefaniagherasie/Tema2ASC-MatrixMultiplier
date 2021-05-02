printf "\ndiff BLAS\n"
./compare outputs/out1_blas /export/asc/tema2/out1 0.0001
./compare outputs/out2_blas /export/asc/tema2/out2 0.0001
./compare outputs/out3_blas /export/asc/tema2/out3 0.0001


printf "\ndiff OPT\n"
./compare /export/asc/tema2/out1 outputs/out1_opt 0.0001
./compare /export/asc/tema2/out2 outputs/out2_opt 0.0001
./compare /export/asc/tema2/out3 outputs/out3_opt 0.0001


printf "\ndiff NEOPT\n"
./compare outputs/out1_neopt /export/asc/tema2/out1 0.0001
./compare outputs/out2_neopt /export/asc/tema2/out2 0.0001
./compare outputs/out3_neopt /export/asc/tema2/out3 0.0001


