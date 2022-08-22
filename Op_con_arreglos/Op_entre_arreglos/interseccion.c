#include <stdio.h>
#include <stdbool.h>


#define MAX_ELEMENTOS 100

// Pre: tope debe ser mayor o igual a 0.
// Pos: Imprime por pantalla los elementos del vector.
void imprimir_vector(int* vector, int tope) {
	for (int i = 0; i < tope-1; i++) {
		printf("%i, ", vector[i]);
	}
	printf("%i\n", vector[tope-1]);
}


// Pre: vector1 y vector2 tienen que estar ordenados. tope1 y tope2 deben ser >= 0.
// Pos: Llena vector_resultado con los elementos que están en ambos vectores (sin repetir)
// 		y establece su tope
void intersectar_vectores(int vector1[MAX_ELEMENTOS], int tope1,
						  int vector2[MAX_ELEMENTOS], int tope2,
						  int vector_resultado[MAX_ELEMENTOS], int* tope_resultado) {
	int i = 0;
	int j = 0;
	*tope_resultado = 0;

	while (i < tope1 && i < tope2) {
		if (vector1[i] < vector2[j]) {
			i++;
		} else if (vector2[j] < vector1[i]) {
			j++;
		} else {
			vector_resultado[*tope_resultado] = vector1[i];
			(*tope_resultado)++;
			i++;
			j++;
		}
	}
}
