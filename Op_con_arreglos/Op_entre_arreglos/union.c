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

//Maximo tope posible ---> tope1+tope2 = tope_final
//Mínimo tope posible ---> tope1 = tope2 = tope_final



// Pre: vector1 y vector2 tienen que estar ordenados y no deben tener elementos repetidos
// 		dentro del mismo vector. tope1 y tope2 deben ser >= 0.
// Pos: Llena vector_resultado con la unión de ambos vectores (sin repetidos) y establece su tope.
void unir_vectores(int vector1[MAX_ELEMENTOS], int tope1,
				   int vector2[MAX_ELEMENTOS], int tope2,
				   int vector_resultado[2*MAX_ELEMENTOS], int* tope_resultado) {
	int i = 0;
	int j = 0;
	*tope_resultado = 0;

	while (i < tope1 && j < tope2) {
		if (vector1[i] < vector2[j]) {
			vector_resultado[*tope_resultado] = vector1[i];
			i++;
		} else if (vector2[j] < vector1[i]) {
			vector_resultado[*tope_resultado] = vector2[j];
			j++;
		} else {
			vector_resultado[*tope_resultado] = vector1[i];
			i++;
			j++;
		}
		(*tope_resultado)++;
	}

	while (i < tope1) {
		vector_resultado[*tope_resultado] = vector1[i];
		(*tope_resultado)++;
		i++;
	}

	while (j < tope2) {
		vector_resultado[*tope_resultado] = vector2[j];
		(*tope_resultado)++;
		j++;
	}
}
