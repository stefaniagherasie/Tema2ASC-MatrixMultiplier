# Tema2ASC-MatrixMultiplier
[Tema2 - Arhitectura Sistemelor de Calcul] 
Optimizarea unei operatii de inmultire de matrici in 3 moduri. <br>
Enuntul se gaseste [aici](https://ocw.cs.pub.ro/courses/asc/teme/tema2).

## Descriere 
Se dă următoarea operație cu matrice, unde A si B sunt matrice patratice NxN, iar A este matrice **superior triunghiulara**:
> C = A × B × B<sup>t</sup> + A<sup>t</sup> × A

Se dorește implementarea operației de mai sus in C/C++ în 3 moduri:
- `blas` - o variantă care folosește una sau mai multe functii din [BLAS Atlas] pentru realizarea operatiilor de inmultire si adunare.
- `neopt` - o variantă “de mână” fără îmbunătățiri.
- `opt_m` - o variantă îmbunătățită a versiunii neopt.

## Organizare
Tema are urmatoarea organizare:
- `main.c` - conține funcția main, precum și alte funcții folosite pentru citirea fișierului cu descrierea testelor, scrierea matricei rezultat într-un fișier, generarea datelor de intrare și rularea unui test.
- `Makefile`
- `utils.h`
- `solver_blas.c` - implementarea variantei blas
- `solver_neopt.c` - implementarea variantei neopt.
- `solver_opt.c` - implementarea variantei opt_m.
- `compare.c` - utilitar ce poate fi folosit pentru a compara doua fisiere rezultat

## Rulare si Testare
În urma rulării comenzii `make` vor rezulta 3 fișere binare: `tema2_blas`, `tema2_neopt` si `tema2_opt_m`.
```shell
    ./tema2_<mod> <input_file> 
```
**Fișierul de input** este structurat astfel:
- pe prima linie numărul de teste.
- pe următoarele linii descrierea fiecarui test:
    - valoarea lui N.
    - seed-ul folosit la generarea datelor.
    - calea către fișierul de ieșire ce conține matricea rezultat.



## Bibliografie
1. http://www.netlib.org/blas/


[BLAS Atlas]: http://www.netlib.org/blas/
