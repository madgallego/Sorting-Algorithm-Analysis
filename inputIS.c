/*b) Increasing Sequence 
• The program prompts the user to enter a starting value X (a positive number). 
• It generates an increasing sequence where: 
    • The first element is X, 
    • The second element is X+1, 
    • The third element is X+2, and so on, for N elements.*/

#include <stdio.h>

void increasingSequence(int array[], int N, int *X);

void main(){
    int i, N, X;

    printf("Enter num of values to be sorted: ");
    scanf("%d", &N);

    int array[N];

    printf("\nIncreasing Sequence\nEnter a positive starting value: ");
    scanf("%d", &X);

    increasingSequence(array, N, &X);

    for(i=0; i<N; i++) {
        printf("%d ", array[i]);
    }
    return;
}

void increasingSequence(int array[], int N, int *X) {
    int i;

    for(i=0; i<N; i++){
        array[i] = *X;
        (*X)++;
    }
    return;
}