//Copyright Oana-Alexandra Titoc 313CAb 2022-2023

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD 10
#define MODULO 10007

struct mat {
	int rows;
	int colls;
};

//se realoca spatiu pentru vectorul de matrici
int ***realloc_big_array(int ***big_array, int size)
{
	big_array = (int ***)realloc(big_array, sizeof(int **) * size);
	if (!big_array) {
		printf("alocare esuata");
		exit(-1);
	}
	return big_array;
}

//se realoca spatiu pentru vectorul in care sunt stocate liniile si coloanele
struct mat *realloc_vector_size(struct mat *a, int size)
{
	a = (struct mat *) realloc(a, sizeof(struct mat *) * size);
	if (!a) {
		printf("alocare esuata");
		exit(1);
	}
	return a;
}

//se construieste vectorul(comanda L)
void build_array(int ****big_array, struct mat **a, int *nr_matrix, int *size)
{
	int m, n;
	scanf("%d%d", &m, &n);
	if (*nr_matrix % ADD == 0) {
		*size += ADD;
		*big_array = realloc_big_array(*big_array, *size);
		*a = realloc_vector_size(*a, *size);
	}
	(*a)[*nr_matrix].rows = m;
	(*a)[*nr_matrix].colls = n;
	(*big_array)[*nr_matrix] = (int **)malloc(m * sizeof(int *));
	if (!(*big_array)[*nr_matrix]) {
		printf("alocare esuata2");
		exit(-1);
	}
	for (int i = 0; i < m; i++) {
		(*big_array)[*nr_matrix][i] = (int *)malloc(n * sizeof(int));
		if (!(*big_array)[*nr_matrix][i]) {
			printf("alocare esuata2");
			exit(-1);
		}
	}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &((*big_array)[*nr_matrix][i][j]));
	(*nr_matrix)++;
}

//se afiseaza dimensiunile unei matrici din vectorul mare(comanda D)
void print_dim(int nr_matrix, struct mat *a)
{
	int index;
	scanf("%d", &index);
	if (index >= nr_matrix || index < 0)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", a[index].rows, a[index].colls);
}

//afisarea matricii(comanda P)
void print_matrix(int ***big_array, struct mat *a, int nr_matrix)
{
	int index;
	scanf("%d", &index);
	if (index >= nr_matrix || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		for (int i = 0; i < a[index].rows; i++) {
			for (int j = 0; j < a[index].colls; j++)
				printf("%d ", big_array[index][i][j]);
			printf("\n");
		}
	}
}

//construieste matricea auxiliara redimensionata
void build_matrix_red(int  ***big_array, int ***matrix, int index,
					  int l, int c, int *vect_l, int *vect_c)
{
	for (int i = 0; i < l; i++)
		for (int j = 0; j < c; j++)
			(*matrix)[i][j] = big_array[index][vect_l[i]][vect_c[j]];
}

//se atribuie vectorului de matrici valoarea matricei auxiliare
//comanda C + T + F
void build_array_tr(int ***big_array, int **matrix, struct mat *a, int index)
{
	for (int i = 0; i < a[index].rows; i++)
		for (int j = 0; j < a[index].colls; j++)
			big_array[index][i][j] = matrix[i][j];
}

//functia de redimensionare a unei matrici (comanda C)
void redimension_matrix(int ****big_array, struct mat *a, int nr_matrix)
{
	int index, l, c;
	int *vect_l, *vect_c;
	scanf("%d", &index);
	scanf("%d", &l);
	vect_l = (int *)malloc(l * sizeof(int));
	if (!vect_l) {
		printf("alocare esuata2");
		exit(-1);
	}
	for (int i = 0; i < l; i++)
		scanf("%d", &vect_l[i]);
	scanf("%d", &c);
	vect_c = (int *)malloc(c * sizeof(int));
	if (!vect_c) {
		printf("alocare esuata2");
		exit(-1);
	}
	for (int i = 0; i < c; i++)
		scanf("%d", &vect_c[i]);
	if (index >= nr_matrix || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		int r_init = a[index].rows;
		a[index].colls = c;
		a[index].rows = l;
		int **matrix = (int **)malloc(a[index].rows * sizeof(int *));
		if (!matrix) {
			printf("alocare esuata2");
			exit(-1);
		}
		for (int i = 0; i < a[index].rows; i++) {
			matrix[i] = (int *)malloc(a[index].colls * sizeof(int));
			if (!matrix[i]) {
				printf("alocare esuata2");
				exit(-1);
			}
		}
		build_matrix_red(*big_array, &matrix, index, l, c, vect_l, vect_c);
		for (int i = 0; i < r_init; i++)
			free((*big_array)[index][i]);
		free((*big_array)[index]);
		(*big_array)[index] = (int **)malloc(a[index].rows * sizeof(int *));
		if (!(*big_array)[index]) {
			printf("alocare esuata2");
			exit(-1);
		}
		for (int i = 0; i < a[index].rows; i++) {
			(*big_array)[index][i] = (int *)malloc(a[index].colls *
															sizeof(int));
			if (!matrix) {
				printf("alocare esuata2");
				exit(-1);
			}
		}
		build_array_tr(*big_array, matrix, a, index);
		for (int i = 0; i < a[index].rows; i++)
			free(matrix[i]);
		free(matrix);
	}
	free(vect_l);
	free(vect_c);
}

//face inmultirea a doua matrici +verificari
//comanda M
void multiply_matrix(int ****big_array, struct mat **a, int *nr_matrix,
					 int *size)
{
	int index1, index2;
	scanf("%d%d", &index1, &index2);
	if (index1 >= *nr_matrix || index2 >= *nr_matrix || index1 < 0 ||
		index2 < 0) {
		printf("No matrix with the given index\n");
	} else {
		if ((*a)[index1].colls != (*a)[index2].rows) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			if (*nr_matrix % ADD == 0) {
				*size += ADD;
				*big_array = realloc_big_array(*big_array, *size);
				*a = realloc_vector_size(*a, *size);
			}
		(*a)[*nr_matrix].rows = (*a)[index1].rows;
		(*a)[*nr_matrix].colls = (*a)[index2].colls;
		(*big_array)[*nr_matrix] = (int **)malloc((*a)[*nr_matrix].rows *
		 sizeof(int *));
		if (!(*big_array)[*nr_matrix]) {
			printf("alocare esuata2");
			exit(-1);
		}
		for (int i = 0; i < (*a)[*nr_matrix].rows; i++) {
			(*big_array)[*nr_matrix][i] = (int *)malloc((*a)[*nr_matrix].colls
			 * sizeof(int));
			if (!(*big_array)[*nr_matrix][i]) {
				printf("alocare esuata2");
				exit(-1);
			}
		}
		for (int i = 0; i < (*a)[index1].rows; i++)
			for (int j = 0; j < (*a)[index2].colls; j++) {
				(*big_array)[*nr_matrix][i][j] = 0;
				for (int k = 0; k < (*a)[index1].colls; k++) {
					(*big_array)[*nr_matrix][i][j] +=
					 ((*big_array)[index1][i][k] * (*big_array)[index2][k][j]) %
					  MODULO;
					(*big_array)[*nr_matrix][i][j] %= MODULO;
					if ((*big_array)[*nr_matrix][i][j] < 0)
						(*big_array)[*nr_matrix][i][j] += MODULO;
				}
			}
		(*nr_matrix)++;
		}
	}
}

//suma elementelor dintr-o matrice
//pentru comanda O
int sum_matrix(int **matrix, int index, struct mat *a)
{
	int s = 0;
	for (int i = 0; i < a[index].rows; i++)
		for (int j = 0; j < a[index].colls; j++) {
			s += matrix[i][j];
			s %= MODULO;
			if (s < 0)
				s += MODULO;
		}
	return s;
}

//sortarea matricilor din vectorul de matrici
//comanda O
void bubble_sort_matrix(int ***big_array, int nr_matrix, struct mat *a)
{
	for (int i = 0; i < nr_matrix - 1; i++)
		for (int j = i + 1; j < nr_matrix; j++)
			if (sum_matrix(big_array[i], i, a) >
				sum_matrix(big_array[j], j, a)) {
				int **aux = big_array[i];
				big_array[i] = big_array[j];
				big_array[j] = aux;
				int aux2 = a[i].rows;
				a[i].rows = a[j].rows;
				a[j].rows = aux2;
				int aux3 = a[i].colls;
				a[i].colls = a[j]. colls;
				a[j].colls = aux3;
			}
}

//se construiete matricea transpusa intr-o matrice auxiliara
//pentru comanda T
void build_matrix_tr(int  ***big_array, int ***matrix, int index, int r, int c)
{
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			(*matrix)[j][i] = big_array[index][i][j];
}

//functia care inlocuieste o matrice cu transpusa sa
//comanda T
void transpose_matrix(int ****big_array, struct mat *a, int nr_matrix)
{
	int index;
	scanf("%d", &index);
	if (index >= nr_matrix || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		int r = a[index].rows, c = a[index].colls;
		a[index].colls = r;
		a[index].rows = c;
		int **matrix = (int **)malloc(a[index].rows * sizeof(int *));
		if (!matrix) {
			printf("alocare esuata2");
			exit(-1);
		}
		for (int i = 0; i < a[index].rows; i++) {
			matrix[i] = (int *)malloc(a[index].colls * sizeof(int));
			if (!matrix) {
				printf("alocare esuata2");
				exit(-1);
			}
		}
		build_matrix_tr(*big_array, &matrix, index, r, c);
		for (int i = 0; i < r; i++)
			free((*big_array)[index][i]);
		free((*big_array)[index]);
		(*big_array)[index] = (int **)malloc(a[index].rows * sizeof(int *));
		if (!(*big_array)[index]) {
			printf("alocare esuata2");
			exit(-1);
		}
		for (int i = 0; i < a[index].rows; i++) {
			(*big_array)[index][i] = (int *)malloc(a[index].colls *
			 sizeof(int));
			if (!(*big_array)[index][i]) {
				printf("alocare esuata2");
				exit(-1);
			}
		}
		build_array_tr(*big_array, matrix, a, index);
		for (int i = 0; i < a[index].rows; i++)
			free(matrix[i]);
		free(matrix);
	}
}

//inmultirea a doua matrici patratice a, b de dimensiuni n (comanda R)
//matricea a va deveni a*b;
void multiply(int **a, int **b, int n)
{
	//aux=matrice auxiliara in care punem rezultatul a*b
	int **aux = (int **)malloc(n * sizeof(int *));
	if (!aux) {
		printf("alocare esuata2");
		exit(-1);
	}
	for (int i = 0; i < n; i++) {
		aux[i] = (int *)malloc(n * sizeof(int));
		if (!aux[i]) {
			printf("alocare esuata2");
			exit(-1);
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			aux[i][j] = 0;
			for (int k = 0; k < n; k++) {
				aux[i][j] += (a[i][k] * b[k][j]) % MODULO;
				aux[i][j] %= MODULO;
				if (aux[i][j] < 0)
					aux[i][j] += MODULO;
			}
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = aux[i][j];
	for (int i = 0; i < n; i++)
		free(aux[i]);
	free(aux);
}

void make_identity_matrix(int **aux, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j)
				aux[i][j] = 1;
			else
				aux[i][j] = 0;
		}
}

//ridicarea la putere in timp logaritmic (comanda R)
void power_matrix(int ***big_array, struct mat *a, int nr_matrix)
{
	int index, power;
	scanf("%d%d", &index, &power);
	if (index >= nr_matrix || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		if (power < 0) {
			printf("Power should be positive\n");
		} else {
			if (a[index].rows != a[index].colls) {
				printf("Cannot perform matrix multiplication\n");
			} else {
				int **matrix = (int **)malloc(a[index].rows * sizeof(int *));
				if (!matrix) {
					printf("alocare esuata2");
					exit(-1);
				}
				for (int i = 0; i < a[index].rows; i++) {
					matrix[i] = (int *)malloc(a[index].colls * sizeof(int));
					if (!matrix[i]) {
						printf("alocare esuata2");
						exit(-1);
					}
				}
				for (int i = 0; i < a[index].rows; i++)
					for (int j = 0; j < a[index].colls; j++)
						matrix[i][j] = big_array[index][i][j];
				int **aux = (int **)malloc(a[index].rows * sizeof(int *));
				if (!aux) {
					printf("alocare esuata2");
					exit(-1);
				}
				for (int i = 0; i < a[index].rows; i++) {
					aux[i] = (int *)malloc(a[index].colls * sizeof(int));
					if (!aux[i]) {
						printf("alocare esuata2");
						exit(-1);
					}
				}
				make_identity_matrix(aux, a[index].rows);
				while (power) {
					if (power % 2 == 1)
						multiply(aux, matrix, a[index].rows);
					multiply(matrix, matrix, a[index].rows);
					power /= 2;
				}
				for (int i = 0; i < a[index].rows; i++)
					for (int j = 0; j < a[index].colls; j++)
						big_array[index][i][j] = aux[i][j];
				for (int i = 0; i < a[index].rows; i++) {
					free(aux[i]);
					free(matrix[i]);
				}
				free(aux);
				free(matrix);
			}
		}
	}
}

//functie care elibereaza memoria de la matricea care urmeaza sa fie inlocuita
//cu matricea de la indexul i+1 (comanda F)
void free_matrix_from_array(int ***big_array, int r, int index)
{
	for (int i = 0; i < r; i++)
		free(big_array[index][i]);
	free(big_array[index]);
}

void link_matrix(int ****big_array, struct mat *a, int index1, int index2)
{
	for (int i = 0; i < a[index1].rows; i++)
		free((*big_array)[index1][i]);
	free((*big_array)[index1]);
	(*big_array)[index1] = (int **)malloc(a[index2].rows * sizeof(int *));
	if (!(*big_array)[index1]) {
		printf("alocare esuata2");
		exit(-1);
	}
	for (int i = 0; i < a[index2].rows; i++) {
		(*big_array)[index1][i] = (int *)malloc(a[index2].colls * sizeof(int));
		if (!(*big_array)[index1][i]) {
			printf("alocare esuata2");
			exit(-1);
		}
	}
	a[index1].rows = a[index2].rows;
	a[index1].colls = a[index2].colls;
	build_array_tr(*big_array, (*big_array)[index2], a, index1);
}

//functie care reface vectorul de matrici dupa ce s-a sters o matrice din el
//comanda F
void rebuild_array(int ****big_array, int *nr_matrix, struct mat *a)
{
	int index;
	scanf("%d", &index);
	if (index >= (*nr_matrix) || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		for (int i = index; i < (*nr_matrix) - 1; i++)
			link_matrix(big_array, a, i, i + 1);
		free_matrix_from_array(*big_array, a[(*nr_matrix) - 1].rows,
							   (*nr_matrix) - 1);
		(*nr_matrix)--;
	}
}

//functia care elibereaza memoria total
void free_all(int ***big_array, int nr_matrix, struct mat *a)
{
	for (int i = 0; i < nr_matrix; i++) {
		for (int j = 0; j < a[i].rows; j++)
			free(big_array[i][j]);
		free(big_array[i]);
	}
	free(big_array);
	free(a);
}

int main(void)
{
	int nr_matrix = 0, size = 1;
	//a-pointer la struct mat care retine liniile si coloanele matricilor
	struct mat *a = (struct mat *)malloc(sizeof(struct mat));
	if (!a) {
		printf("alocare esuata2");
		exit(-5);
	}
	int ***big_array = (int ***)malloc(sizeof(int **));
	if (!big_array) {
		printf("alocare esuata1");
		exit(-4);
	}
	char command, string[11] = "LDPCMOTRFQ";
	scanf("%c", &command);
	while (command != 'Q') {
		if (strchr(string, command) == 0)
			printf("Unrecognized command\n");
		if (command == 'L')
			build_array(&big_array, &a, &nr_matrix, &size);
		if (command == 'D')
			print_dim(nr_matrix, a);
		if (command == 'P')
			print_matrix(big_array, a, nr_matrix);
		if (command == 'C')
			redimension_matrix(&big_array, a, nr_matrix);
		if (command == 'M')
			multiply_matrix(&big_array, &a, &nr_matrix, &size);
		if (command == 'O')
			bubble_sort_matrix(big_array, nr_matrix, a);
		if (command == 'T')
			transpose_matrix(&big_array, a, nr_matrix);
		if (command == 'R')
		    power_matrix(big_array, a, nr_matrix);
		if (command == 'F')
			rebuild_array(&big_array, &nr_matrix, a);
		scanf("\n%c", &command);
	}
	free_all(big_array, nr_matrix, a);
}
