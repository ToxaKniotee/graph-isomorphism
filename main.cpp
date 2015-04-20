#include <iostream>
#include <math.h>

/* Funciones complementarias */

int factorial(int n){

    return ( n == 1 || n == 0 ) ? 1 : factorial( n - 1 ) * n;

}

int * permutation( const int * matrix, int size, int a, int b ){

    /* Cambia de lugar tanto las filas por las columnas para pode ëfectuar una permutación */

    /* Creamos las variables */

    int * tempMatrix = new int[ size * size ];
    int * rowBackUp = new int[ size ];

    /* Copiamos la matriz a la nueva matriz */

    memcpy( tempMatrix, matrix, size * size * sizeof(int) );

    /* Si a y b son iguales regresamos la nueva matriz sin ningun cambio */

    if( a == b )
        return tempMatrix;

    /* si no fueron iguales entonces ntercambiamos las columnas */

    for( int i = 0; i < size; i++ ){

        tempMatrix[ i * size + a ] = matrix[ i * size + b ];
        tempMatrix[ i * size + b ] = matrix[ i * size + a ];

    }

    /* Respaldamos la columna a, de esta forma nada mas tenemos que copiar la columna b a la a y despues copiar el respaldo a la columna b */

    memcpy( rowBackUp, tempMatrix + a * size, size * sizeof(int) );

    /* Copiamos la columna b a la columa a */

    memcpy( tempMatrix + a * size, tempMatrix + b * size, size * sizeof(int) );

    /* Copiamos de nuevo el respaldo de a, a b */

    memcpy( tempMatrix + b * size, rowBackUp, size * sizeof(int) );

    /* Regresamos la nueva matriz */

    return tempMatrix;

}

bool equal( const int * matrixA, const int * matrixB, int size ){

    /* Regresa true si ambas matrices son iguales, de lo contrario regresa false */

    /* Para cada fila y columna */

    for( int i = 0; i < size; i++ ){

        for( int j = 0; j < size; j++ ){

            /* Si encuentra una diferencia entonces regresa false y termina la función */

            if( matrixA[ i * size + j ] != matrixB[ i * size + j ] )
                return false;

        }

    }

    /* Si recorrio ambas matrices y no encontro ninguna diferencia entonces regresamos true */

    return true;

}

/* isomorfismo */

bool isomorphism( const int * originalGraph, const int * permutedGraph, int size, int level, int * permutations, int maxPermutations, int & actualPermutations ){

    /* Funcion que recorremos recursivamente para ver si alguna de todas las recursiones posibles da como resultado un isomorfo */

    /* Marcamos el progreso total */

    //if( actualPermutations % 1000 == 0 ){

    //  system( "cls" );
    //  std::cout << actualPermutations << " / " << maxPermutations << std::endl;

    //}
    

    /* Checamos si con la permutación actual ya se logro un isomorfismo */

    if( equal( originalGraph, permutedGraph, size ) )
        return true;

    /* Recursivamente vamos probando todas las opciones de esta iteracion */

    for( int i = level; i < size; i++ ){

        /* Cambiamos de lugar los nodos en el arreglo 'permutations', para tener un orden de que nodos se cambiaron */

        int temp = permutations[i];
        permutations[i] = permutations[level];
        permutations[level] = temp;


        /* Mandamos a ejecutar las siguientes permutaciones */

        if( isomorphism( originalGraph, permutation( permutedGraph, size, level, i ), size, level + 1, permutations, maxPermutations, ++actualPermutations ) )
            return true;

        /* En el caso de que la permutación no dio como resultado un isomorfo entonces regresamos el cambio que hicimos en el arreglo de permutaciones */

        permutations[level] = permutations[i];
        permutations[i] = temp;

    }

    /* Si en los subarboles no se encontro ninguna permutación que cumpliera con la condición de igualar las matrices, entonces tenemos regresamos false */

    return false;

}

void isomorphism( const int * originalGraph, const int * permutedGraph, int size ){

    /* Función que se encarga de manejar la función recursiva e implementar el resultado */

    /* Creamos las variables */

    int * permutations = new int[ size ];
    int maxPermutations = factorial( size );
    int actualPermutations = 1;

    /* Llenamos el arreglo de permutaciones, que nos servira para saber cuales son las permutaciones en caso de que sea un grafo isomorfico */

    for( int i = 0; i < size; i++ )
        permutations[i] = i + 1;

    /* Mandamos a llamar a la función recursiva */

    if( isomorphism( originalGraph, permutedGraph, size, 0, permutations, maxPermutations, actualPermutations ) ){

        /* Si es isomorfico entonces mostramos cual es la relación entre los nodos */

        std::cout << "Ambos grafos son isomorficos, con las siguientes permutaciones\n\n";

        for( int i = 0; i < size; i++ )
            std::cout << "  " << i + 1 << " -> " << permutations[i] << std::endl;

        std::cout << std::endl;

    }else{

        /* En el caso de que no haya sido isomorfismo simplemente mostramos que no ha sido isomórfico */

        std::cout << "Los grafos no son isomorfos\n";

    }

}

/* Main */

int main(){

    /* Los dos grafos presentados son los de la pag http://math.stackexchange.com/questions/393416/are-these-2-graphs-isomorphic.html */

    int size = 7;
    //int graphA[] = {
    //  0, 1, 1, 1, 0, 0, 0,
    //  1, 0, 0, 0, 1, 0, 0,
    //  1, 0, 0, 0, 0, 1, 0,
    //  1, 0, 0, 0, 1, 0, 1,
    //  0, 1, 0, 1, 0, 0, 1,
    //  0, 0, 1, 0, 0, 0, 1,
    //  0, 0, 0, 1, 1, 1, 0
    //};

    //int graphB[] = {
    //  0, 1, 0, 0, 1, 1, 0,
    //  1, 0, 1, 0, 0, 0, 0,
    //  0, 1, 0, 0, 0, 0, 1,
    //  0, 0, 0, 0, 1, 0, 1,
    //  1, 0, 0, 1, 0, 1, 0,
    //  1, 0, 0, 0, 1, 0, 1,
    //  0, 0, 1, 1, 0, 1, 1
    //};

    /*int graphA[] = {
    1,  8, 16, 12, 14, 18,  2,  4, 20,  4,  6,  7,  3, 18,  6,
    13,  9,  6,  9, 14,  8,  8, 10,  2, 13, 17,  8,  4,  2, 16,
    7,  6, 14,  1,  7, 19,  6, 17, 16,  8, 15,  7, 20,  8, 12,
    12,  8,  8, 11, 17, 20,  3, 11, 13, 10,  3, 19, 14, 14, 15,
    12,  3, 16, 12,  7,  7, 17, 11,  4,  5, 15, 15, 18, 19, 18,
    18, 18,  8,  8, 17,  5,  8,  9,  9,  3,  5, 19, 15,  2,  7,
    15, 18, 17, 17, 19,  5, 15, 11, 12,  7, 10, 11,  3, 19,  9,
    14,  4,  1, 10, 11, 14, 12,  8,  6,  5, 10,  3, 14,  6, 10,
    2,  4, 19, 10, 15, 14,  2, 15, 19,  9,  2, 12, 10,  2, 15,
    20,  3,  1, 17, 19, 12,  6,  4, 20, 17, 14, 15,  3, 16,  4,
    15,  4, 13, 19, 10, 12, 11,  7, 20,  7, 19, 10, 10,  3, 18,
    1, 14, 15, 14,  2, 15, 20, 17,  3, 19,  3, 18,  4, 10,  5,
    18, 14,  8,  8,  9, 10, 15, 16,  6, 14, 11,  8, 12,  4,  4,
    2, 16, 18, 15,  5,  7, 15, 12,  1, 10, 10, 16, 17, 13, 14,
    17,  1,  2,  3, 20, 18, 13, 17,  9,  3, 14,  5, 11, 10, 13
    };

    int graphB[] = {
    13, 16, 18, 15, 17,  7, 15, 12,  1, 10, 10, 16,  5,  2, 14,
    2,  9,  6,  8,  4,  8,  9, 10,  2, 13, 17,  8, 14, 13, 16,
    8,  6, 14,  6, 20, 19,  1, 17, 16,  8, 15,  7,  7,  7, 12,
    19, 18, 17, 15,  3,  5, 17, 11, 12,  7, 10, 11, 19, 15,  9,
    4, 14,  8, 15, 12, 10,  8, 16,  6, 14, 11,  8,  9, 18,  4,
    2, 18,  8,  8, 15,  5,  8,  9,  9,  3,  5, 19, 17, 18,  7,
    14,  8,  8,  3, 14, 20, 11, 11, 13, 10,  3, 19, 17, 12, 15,
    6,  4,  1, 12, 14, 14, 10,  8,  6,  5, 10,  3, 11, 14, 10,
    2,  4, 19,  2, 10, 14, 10, 15, 19,  9,  2, 12, 15,  2, 15,
    16,  3,  1,  6,  3, 12, 17,  4, 20, 17, 14, 15, 19, 20,  4,
    3,  4, 13, 11, 10, 12, 19,  7, 20,  7, 19, 10, 10, 15, 18,
    10, 14, 15, 20,  4, 15, 14, 17,  3, 19,  3, 18,  2,  1,  5,
    19,  3, 16, 17, 18,  7, 12, 11,  4,  5, 15, 15,  7, 12, 18,
    18,  8, 16,  2,  3, 18, 12,  4, 20,  4,  6,  7, 14,  1,  6,
    10,  1,  2, 13, 11, 18,  3, 17,  9,  3, 14,  5, 20, 17, 13
    };*/

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

    isomorphism( graphA, graphB, size );

    system("pause");

    return 0;

}
