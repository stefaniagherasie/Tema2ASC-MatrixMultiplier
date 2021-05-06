# Tema2ASC-MatrixMultiplier
[Tema2 - Arhitectura Sistemelor de Calcul] <br>
Tema presupune realizarea unei operatii de inmultire de matrici in 3 moduri.
> Enuntul se gaseste [aici](https://ocw.cs.pub.ro/courses/asc/teme/tema2). <br>
> Scheletul de cod se gaseste [aici](https://ocw.cs.pub.ro/courses/_media/asc/tema2/skel.zip).

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
- `graphs`, `results` - foldere cu rezultatele obtinute

## Rulare si Testare
Rularea si testarea se realizeaza pe **cluster** (username@fep.grid.pub.ro), pe coada `ibm-nehalem.q`.

În urma rulării comenzii `make` vor rezulta 3 fișiere binare: `tema2_blas`, `tema2_neopt` si `tema2_opt_m`.
```shell
    ./tema2_<mod> <input_file> 
```

Testarea se face folosind utilitarul `compare`.
```shell
    ./compare  out1  /export/asc/tema2/out1  <tolerance>
```

**Fișierul de input** este structurat astfel:
- pe prima linie numărul de teste.
- pe următoarele linii descrierea fiecarui test:
   - valoarea lui N.
   - seed-ul folosit la generarea datelor.
   - calea către fișierul de ieșire ce conține matricea rezultat.
 

## Implementare

#### ► Metoda BLAS

Am folosit functiile BLAS Atlas pentru a realiza eficient inmultirea matricilor. Am implementat functia `make_copy` care intoarce o copie a unei matrice, folosita pentru rezultate intermediare ale functiilor BLAS.

Deoarece A este o matrice superior triunghiulara, am folosit pentru inmultirea `M = A x B` functia [cblas_dtrmm].
Pentru inmultirea `P = At x A` am folosit aceeasi functie, schimband un parametru care calculeaza transpusa matricei A, care este inferior triunghiulara.

Pentru operatia `M x Bt + P` se foloseste functia [cblas_dgemm] care realizeaza inmultirea dintre 2 matrici
oarecare si adunarea cu o a treia matrice in acelasi timp, astfel obtinand rezultatul operatiei cerute. 



Timpii aproximativi de rulare sunt:
>    Run=./tema2_blas: N=400: Time=0.058715 <br>
>    Run=./tema2_blas: N=800: Time=0.272988 <br>
>    Run=./tema2_blas: N=1200: Time=0.848344 <br>
<br>

#### ► Metoda NEOPTIMIZATA

Se folosesc inmultirile normale de matrice, fara vreo imbunatatire care sa optimizeze timpul. Operatia se
realizeaza tinand cont ca matricea A este superior triunghiulara, avand functii separate pentru inmultirea cu
matricea triunghilara.
- `add_matrix` - aduna 2 matrici
- `transpose_matrix` si `transpose_upper_matrix` - obtine transpusa unei matrici normale/superior triunghiulare
- `multiply_matrix` - inmulteste 2 matrici oarecare
- `multiply_upper_matrix` si `multiply_lower_matrix` - restange conditiile din bucle pentru a diminua calculele 
cand matricea din stanga e superior/inferior triunghiulara

Timpii aproximativi de rulare sunt:
>    Run=./tema2_neopt: N=400: Time=1.157325 <br>
>    Run=./tema2_neopt: N=800: Time=9.290556 <br>
>    Run=./tema2_neopt: N=1200: Time=32.165798
<br>

#### ► Metoda OPTIMIZATA

Se aduc imbunatatiri codului de la varianta neoptimizata pentru obtinerea unor timpi radical mai buni, avand
insa aceeasi complexitate. Imbunatatirile se fac in principal prin optimizarea constantelor si al accesului 
la vectori si prin optimizarea buclelor. 
- Rezultatul din `result[i][j]` se calculeaza in constanta `sum` pentru a reduce numarul de accesari la memorie.
- Accesul la matrice se face folosind pointeri pentru a realiza mai rapid operatia de inmultire, renuntandu-se la 
deferentiere. 
- Am folosit `register` pentru a utiliza optim acea resursa.
- Pentru functia `multiply_matrix` se foloseste si optimizarea prin folosirea unei bucle `k-i-j`, care acceseaza memoria intr-un mod mai eficient si aduce performante mai bune. 

Timpii aproximativi de rulare sunt:
>    Run=./tema2_opt_m: N=400: Time=0.352998 <br>
>    Run=./tema2_opt_m: N=800: Time=2.780238 <br>
>    Run=./tema2_opt_m: N=1200: Time=9.409059 <br>
<br>

## Compararea Rezultatelor
Graficele se afla in folderul `graphs` si contin interpretarea valorilor lui N din intervalul
[400, 800, 1000, 1200, 1400, 1600].  Am ales sa reprezint grafic diferenta dintre timpii de rulare obtinuti (`graph_compare`).
Am realizat si grafice individuale cu timpii pentru fiecare metoda, pentru a observa ca timpii tind
sa creasca in acelasi mod pe masura ce creste N, indiferent de metoda folosita.

- Se observa ca metoda cu BLAS este cea mai avantajoasa, folosind functii specializate in lucrul cu operatii pe matrici. De exemplu, pentru N=1200, se obtine
blas=0.85s si opt_m=9.4s, deci un timp de 11 ori mai bun in cazul BLAS. Graficul metodei BLAS
este aproape o dreapta comparativ cu celelalte.

- Fata de varianta neoptimizata, metoda optimizata este de aproximativ 70% mai buna pentru valori mari ale lui N.
De exemplu, pentru N=1200, se obtine neopt=32s si opt_m=9.4s. Prin urmare, folosirea pointerilor,
accesul direct la memorie si ordonarea buclelor permit o optimizare radicala a rezultatelor.


## Bibliografie
1. http://www.netlib.org/blas/
2. https://ocw.cs.pub.ro/courses/asc/laboratoare/05
3. http://www.netlib.org/lapack/explore-html/d5/db0/cblas__dtrmm_8c_acbf40f4eac3fa3e2cdcafa5a1f1cf6da.html
4. http://www.netlib.org/lapack/explore-html/dc/d18/cblas__dgemm_8c_ad07ba707cc7a6b23df8576123fac3e0d.html#ad07ba707cc7a6b23df8576123fac3e0d
6. https://ocw.cs.pub.ro/courses/asc/laboratoare/04


[BLAS Atlas]: http://www.netlib.org/blas/
[cblas_dtrmm]: http://www.netlib.org/lapack/explore-html/d5/db0/cblas__dtrmm_8c_acbf40f4eac3fa3e2cdcafa5a1f1cf6da.html
[cblas_dgemm]: http://www.netlib.org/lapack/explore-html/dc/d18/cblas__dgemm_8c_ad07ba707cc7a6b23df8576123fac3e0d.html#ad07ba707cc7a6b23df8576123fac3e0d
