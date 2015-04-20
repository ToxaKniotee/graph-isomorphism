/* Copyright 2015 ToxaKniotee */
#include <iostream>
#include <math.h>

/* Funciones complementarias */

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int *permutation(const int *matrix, int size, int a, int b) {
    /* Cambia de lugar tanto las filas por las columnas para pode ëfectuar una
     * permutación */
    /* Creamos las variables */
    int *tempMatrix = new int[size * size];
    int *rowBackUp = new int[size];

    /* Copiamos la matriz a la nueva matriz */
    memcpy(tempMatrix, matrix, size * size * sizeof(int));

    /* Si a y b son iguales regresamos la nueva matriz sin ningun cambio */
    if (a == b)
        return tempMatrix;

    /* si no fueron iguales entonces ntercambiamos las columnas */
    for (int i = 0; i < size; i++) {
        tempMatrix[i * size + a] = matrix[i * size + b];
        tempMatrix[i * size + b] = matrix[i * size + a];
    }

    /* Respaldamos la columna a, de esta forma nada mas tenemos que copiar la
     * columna b a la a y despues copiar el respaldo a la columna b */
    memcpy(rowBackUp, tempMatrix + a * size, size * sizeof(int));

    /* Copiamos la columna b a la columa a */
    memcpy(tempMatrix + a * size, tempMatrix + b * size, size * sizeof(int));

    /* Copiamos de nuevo el respaldo de a, a b */
    memcpy(tempMatrix + b * size, rowBackUp, size * sizeof(int));

    /* Regresamos la nueva matriz */
    return tempMatrix;
}

bool equal(const int * matrixA, const int * matrixB, int size) {
    /* Regresa true si ambas matrices son iguales, de lo contrario regresa
     * false */
    /* Para cada fila y columna */

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            /* Si encuentra una diferencia entonces regresa false y termina la
             * función */
            if (matrixA[i * size + j] != matrixB[i * size + j])
                return false;
        }
    }

    /* Si recorrio ambas matrices y no encontro ninguna diferencia entonces
     * regresamos true */
    return true;
}

/* isomorfismo */
bool isomorphism(const int *originalGraph, const int *permutedGraph, int size,
        int level, int *permutations, int maxPermutations,
        int *actualPermutations) {
    /* Funcion que recorremos recursivamente para ver si alguna de todas las
     * recursiones posibles da como resultado un isomorfo */
    /* Checamos si con la permutación actual ya se logro un isomorfismo */
    if (equal(originalGraph, permutedGraph, size))
        return true;

    /* Recursivamente vamos probando todas las opciones de esta iteracion */
    for (int i = level; i < size; i++) {
        /* Cambiamos de lugar los nodos en el arreglo 'permutations', para tener
         * un orden de que nodos se cambiaron */
        int temp = permutations[i];
        permutations[i] = permutations[level];
        permutations[level] = temp;

        /* Mandamos a ejecutar las siguientes permutaciones */
        if (isomorphism(originalGraph, permutation(permutedGraph, size, level,
                i), size, level + 1, permutations, maxPermutations,
                ++actualPermutations))
            return true;

        /* En el caso de que la permutación no dio como resultado un isomorfo
         * entonces regresamos el cambio que hicimos en el arreglo de
         * permutaciones */
        permutations[level] = permutations[i];
        permutations[i] = temp;
    }

    /* Si en los subarboles no se encontro ninguna permutación que cumpliera
     * con la condición de igualar las matrices, entonces tenemos regresamos false */
    return false;
}

void isomorphism(const int * originalGraph, const int * permutedGraph,
        int size) {
    /* Función que se encarga de manejar la función recursiva e implementar el
     * resultado */
    /* Creamos las variables */
    int *permutations = new int[size];
    int maxPermutations = factorial(size);
    int actualPermutations = 1;

    /* Llenamos el arreglo de permutaciones, que nos servira para saber cuales
     * son las permutaciones en caso de que sea un grafo isomorfico */
    for (int i = 0; i < size; i++)
        permutations[i] = i + 1;

    /* Mandamos a llamar a la función recursiva */
    if (isomorphism(originalGraph, permutedGraph, size, 0, permutations,
            maxPermutations, actualPermutations)) {
        /* Si es isomorfico entonces mostramos cual es la relación entre los
         * nodos */
        std::cout << "Ambos grafos son isomorficos, con las siguientes" <<
            " permutaciones\n\n";

        for (int i = 0; i < size; i++)
            std::cout << "  " << i + 1 << " -> " << permutations[i] <<
                std::endl;
        std::cout << std::endl;
    } else {
        /* En el caso de que no haya sido isomorfismo simplemente mostramos que
         * no ha sido isomórfico */
        std::cout << "Los grafos no son isomorfos\n";
    }
}

/* Main */
int main(int argc, char *argv[]) {
    /* Los dos grafos presentados son los de la pag http://math.stackexchange.
     * com/questions/393416/are-these-2-graphs-isomorphic.html */
    int size = 7;

    int graphA[] = {
        1, 0, 1, 1, 0, 1, 1,
        0, 1, 0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0, 0,
        1, 1, 0, 1, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0,
        1, 0, 1, 0, 1, 0, 1,
        0, 1, 0, 1, 0, 1, 0
    };

    int graphB[] = {
        0, 0, 0, 1, 1, 1, 1,
        0, 1, 0, 0, 0, 0, 1,
        1, 1, 1, 0, 0, 1, 0,
        0, 0, 0, 1, 0, 0, 0,
        1, 1, 1, 0, 0, 0, 0,
        1, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0
    };

    isomorphism(graphA, graphB, size);
    system("pause");
    return 0;
}
