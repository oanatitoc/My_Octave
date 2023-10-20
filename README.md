Titoc Oana Alexandra
313CA
Tema 2

    Pentru aceasta problema am ales sa lucrez cu un vector care stocheaza
matrici (triplu pointer) pe care l-am numit big_array. De asemenea, pentru a
stoca numarul de linii si de coloane a fiecarei matrici din vector am folosit
structura mat si am definit un pointer la aceasta structura, numit a, pe care
il voi apela mereu cu a[i].rows / a[i].colls.
    In main am alocat initial memorie pointerului de tip structura a si
pointerului triplu big_array verificand daca s-a alocat memorie de fiecare data
(programare defensiva). Am inceput sa citesc litere pana la intalnirea
caracterului Q care semnifica inchiderea programului si eliberarea totala a
memoriei.
    Pentru fiecare comanda (una din literele L, D, P, C, M, O, T, R, F) am ales sa
fac o singura functie pentru o lizibilitate mai buna a codului. Pentru litera L
am implementat functia "build_array" care aloca de fiecare data numarul de
linii si de coloane pentru noua matrice care se citeste. In plus, are
grija sa realoce memorie intregului pointer triplu si a pointerului de 
dimensiuni a in cazul in care numarul de matrici citite a ajuns sa fie multiplu
de 10 (define-ul ADD). Dupa fiecare citire am crescut nr_matrix, adica numarul
de matrici citite.
    Pentru comanda D am facut functia print_dim care printeaza liniile si
coloanele unei matrice a carui index il citim. Acestea sunt stocate in
pointerul de tip structura a.
    De asemenea, pentru comanda P am facut functia print_matrix care afiseaza
intreaga matrice aflata pe pozitia index in vectorul big_array.
    Pentru comanda C de redimensionare a unei matrici am apelat big_array cu 4
stelute deoarece in interiorul acestei functii matricea de la acel index isi
schimba dimensiunile, deci trebuie realocata. Am avut nevoie de 2 vectori
auxiliari pe care i-am alocat dinamic, in care am stocat liniile, respectiv
coloanele dupa care se face redimensionarea. M-am folosit de functia
build_matrix_red care construieste o matrice auxiliara redimensionata.
Dupa ce am sters matricea initiala de la index din big_array, am atribuit
lui big_array[index] matricea creata in functia anterioara. Am avut grija la
final sa dau free la tot ce a fost auxiliar si alocat dinamic.
    La introducerea comenzii "M" (inmultirea a doua matrici), dupa setul de
verificari legat de indecsi, a trebuit sa verificam daca numarul nr_matrix de
matrici alocate pana atunci este multiplu de ADD (10), adica daca trebuie
facuta o realocare. Apoi am alocat pe ultima pozitie din big_array, liniile
de la prima matrice si coloanele de la a doua si am facut inmultirea matricelor
dupa algoritmul matematic. Si aici big_array a fost apelat cu 4 stelute in
antetul functiei, respectiv in main cu &, deoarece a fost nevoie de modificarea
lui. (la fel si pointerul la structura cu 2 stelute). La final am crescut
nr_matrix ca dovada a introducerii in big_array a unei noi matrici.
    Pentru sortarea matricelor (comanda O) am facut functia care parcurge
cu doua for-uri tot big_array-ul si interschimba atat matricile, cat si
vectorul la structura cu liniile si coloanele matricilor astfel incat acestea
sa fie sortate crescator dupa suma elementelor.
    Pentru comanda T care inlocuieste o matrice din vector cu transpusa sa,
am luat o matrice auxiliara pe care am alocat-o cu numarul de linii = cu nr
de coloane a vechii matrice si numarul de coloane = cu numarul de linii a
vechii matrice. Am construit acea matrice prin intermediul functiei
build_matrix_tr. Am realocat memorie pentru big_array[index] si cu functia
build_array_tr am reconstruit noua matrice din big_array. La final am dat free
de matricea auxiliara.
    Pentru ridicarea la putere (comanda R) am alocat o matrice auxiliara
"matrix" careia i-am atribuit valorile matricei din big_array care trebuie
ridicata la putere. Am alocat o alta matrice auxiliara "aux" pe care am facut-o
matrice unitate (functia make_identity_matrix). Am implementat un algoritm
iterativ de ridicare la putere in timp logaritmic folosindu-ma de cele doua
matrici auxiliare iar rezultatul ramanea in matricea aux. La final in big_array
de index am pus valorile din aux si am dealocat memoria celor doua matrici
auxiliare.
    Pentru comanda F de stergere a unei matrici din memorie a fost nevoie de
implementarea mai multor functii, principala fiind "rebuild_array". In aceasta
functie am adus pe pozitia i, matricea de la pozitia i+1. Aceasta operatie a
fost facuta cu functia "link_matrix". In aceasta functie am facut urmatoarele
operatii: am dealocat memoria matricei ce urmeaza sa fie inlocuita (matricea
de la indexul i), am realocat numarul de linii si de coloane pentru matricea abia
stearsa cu liniile si coloanele corespunzator matricei de la pozitia i+1, am
atribuit noii matrice alocate, valorile din matricea de la i+1. Toata functia
"link_matrix" este creeata cu index1 si index2 in loc de i si i+1 ceea ce ii da
o functionalitate mai generala pentru inlocuirea la un moment dat a unei
matrici cu o matrice de la orice alt index, nu doar i+1. La final, am dat free
de ultima matrice aflata in big_array si am scazut numarul de matrici totale
existente in big_array (nr_matrix).
    Atunci cand in main se iese din while-ul principal, adica atunci cand am
dat comanda Q, se face free de tot vectorul big_array si bineinteles, de
pointerul de strucuri a (funcita "free_all").
    Am avut grija ca de fiecare data cand aloc un pointer dinamic sa fac si
verificarea daca s-a alocat spatiu corect ceea ce tine de etica programarii
defensive.



