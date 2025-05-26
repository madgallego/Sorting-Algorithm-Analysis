//DESIGN AND ANALYSIS OF ALGORITHMS
//PROGRAMMING PROJECT

//GABARDA, YNO
//GALLEGO, MHARC ALEX
//JOLOC, JOHN LESTER
//NACARIO, CARL JOSEPH
//TABAYAG, XARIS JOY

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _POSIX_C_SOURCE 199309L


//make use of fucntion decalrations here, and function definitions in below the main function
void selection(int arr[], int n); //algorithm for sorting that finds the smallest element and swaps the position of the elements from the left
void insertion(int arr[], int n); //algorithm for sorting that traverses through the array and inserts the smallest elements to the left
void bubble(int arr[], int n); //algorithm for sorting that goes through the array multiple times and moves the largest element to the right
void mergesort(int arr[], int i, int j); //divides the array in half until there is only one element left before merging and sorting 
void merge(int arr[], int i1, int j1, int i2, int j2); //algorithm used after dividing the array to sort and merge the elements
int hoare(int arr[], int l, int h); //algorithm used after partition that uses a pivot as a guide to sort the array
void quickHoare(int arr[], int l, int h); //algorithm for sorting by partitioning and then sorting the array
void heapify(int arr[], int n, int i); //function to heapify the tree to get the maximum element
void heapSort(int arr[], int n); //algorithm for sorting using heap properties
void startQuick(int arr[], int n); //function to measure the run time of quick sort algorithm
void startHeap(int arr[], int n); //function to measure the run time of heap sort algorithm
void startMerge(int arr[], int n); //function to measure the run time of merge sort algorithm
void rng(int arr[], int n); //function that generates random numbers as elements in the array
void increasingSequence(int arr[], int N, int *X); //function to input elements in the array from x, x+1,..., x+n 
void printArr(int arr[], int n); //function to print the array


void main(){
    int i, N, X, choice, random_choice;
    
    printf("Enter num of values to be sorted: ");
    scanf("%d", &N);

    int *arr = malloc(sizeof(int) *N);//ensure that array is instantiated as a pointer(ex: int *arr = malloc(sizeof(int) * n))
    
    printf("Choose input type: \n");
    printf("1. Randomly Generated\n");
    printf("2. Increasing Sequence\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
    case 1: printf("Randomly Generated\n"); 
    rng(arr, N); 
    break;

    case 2: printf("Increasing Sequence\nEnter a positive starting value: "); 
    scanf("%d", &X); increasingSequence(arr, N, &X);
    break;

    default: printf("Invalid choice! Exiting program.\n");
    return;
    }
    
    while(1){
        printf("Choose one of the Options below:\n\n");
        printf(" 1 => Selection\n");
        printf(" 2 => Insertion\n");
        printf(" 3 => Bubble\n");
        printf(" 4 => Merge\n");
        printf(" 5 => Quicksort\n");
        printf(" 6 => Heap sort\n");
        printf("Enter your choice: ");
        scanf("%d", &random_choice);

        int i = 0;
        while(i < 5){
            switch(random_choice){
                    case 1:
                    selection(arr,N);
                    break;

                    case 2:
                    insertion(arr,N);
                    break;

                    case 3:
                    bubble(arr,N);
                    break;

                    case 4:
                    startMerge(arr,N);
                    break;
                    
                    case 5:
                    startQuick(arr,N); 
                    break;

                    case 6:
                    startHeap(arr,N);
                    break;

                    default: printf("Invalid choice! Exiting program.\n");
                    return;
                }
            printf("\n");
            //regenarate our array based on settings
            if(choice == 1)
                rng(arr, N);
            else
                increasingSequence(arr, N, &X);
            i++;

        }
    }
 free(arr);
}

//add the different sorting algorithms beyond this point
//selection
void selection(int arr[], int n){
    struct timespec start, end; //timespec struc used to store the time elapsed from start to end when the program runs
    clock_gettime( CLOCK_REALTIME, &start); //clock_gettime() function used for more accurate time measurements
    int temp;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++ ){
            //compare
            if(arr[j] < arr[i]){
                //swap
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    clock_gettime( CLOCK_REALTIME, &end);
    
    double elapsed = ((double) ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000.0)); 
    printf("Total: %.15f\n", elapsed);
}
//insertion
void insertion(int arr[], int n){
    struct timespec start, end;
    clock_gettime( CLOCK_REALTIME, &start);
    int temp;
    for(int i = 1; i < n; i++){
        for(int j = i; j > 0; j--){
            if(arr[j] < arr[j - 1]){
                temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
    clock_gettime( CLOCK_REALTIME, &end);
    
    double elapsed = ((double) ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000.0));
    printf("Total: %.15f\n", elapsed);
}
//bubble
void bubble(int arr[], int n){
    struct timespec start, end;
    clock_gettime( CLOCK_REALTIME, &start);
    int temp;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            if(arr[j] > arr[j + 1]){
                temp = arr[j];
                arr[j]= arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    clock_gettime( CLOCK_REALTIME, &end);
    
    double elapsed = ((double) ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000.0));
    printf("Total: %.15f\n", elapsed);
}

//merge
void mergesort(int arr[], int i, int j){
    if(i < j){
        int mid = (i + j)/2;
        mergesort(arr, i, mid);
        mergesort(arr, mid+1, j);
        merge(arr, i, mid, mid+1, j);
    }
}
//merge 2.0
void merge(int arr[], int i1, int j1, int i2, int j2){
    int start1 = i1;
    int start2 = i2;
    int end1 = j1;
    int end2 = j2;
    int k = 0;
    int *temp= malloc(sizeof(int) * (j2 - i1 + 1));
    while(start1 <= end1 && start2 <= end2){
        if(arr[start1] < arr[start2])
            temp[k++] = arr[start1++];
        else
            temp[k++] = arr[start2++];
    }

    //copy the rest
    while(start1 <= end1)
        temp[k++] = arr[start1++];
    while(start2 <= end2)
        temp[k++] = arr[start2++];

    //copy back to original
    for(int i = i1, k = 0; i <= j2; i++, k++)
        arr[i] = temp[k];
    free(temp);
}

//PARTIONING ALGO
int hoare(int arr[], int l, int h){
    int p;
    int i = l -1, j = h + 1, t;

    //finding median
    int max, min, med;
    int q = 0;
    max = arr[l];
    min = arr[l];
    med = arr[l];
    while(q <= h){  //find min and max
        if(arr[q] > max)
            max = arr[q];
        if(arr[q] < min)
            min = arr[q];
        q++;
    }
    med = (int) (max+min)/2;
    //finding number closest to med
    q = 0;
    p = arr[l];
    int diff = abs(med - p);
    while(q <= h){
        if(abs(med - arr[q]) < diff){
            p = arr[q];
            diff = abs(med - arr[q]);
        }
        q++;
    }
    

    while(1){
        do{
            i++;
        }
        while(arr[i] < p);
        do{
            j--;
        }
        while(arr[j] > p);

        if(i >=j){
            return j;
        }
        
        
        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

//BACK TO SORTING
void quickHoare(int arr[], int l, int h){
    if(l < h){
        int p = hoare(arr, l ,h);
        //left
        quickHoare(arr, l, p);
        //right
        quickHoare(arr, p + 1, h);
    }
}

void heapify(int arr[], int n, int i){
    int m = i;
    int l = 2* i + 1;
    int r = 2* i + 2;
    if(l < n && arr[l] > arr[m])
        m = l;
    
    if(r < n && arr[r] > arr[m])
        m = r;

    if(m != i){
        int temp = arr[i];
        arr[i] = arr[m];
        arr[m] = temp;

        heapify(arr, n , m);

    }

}

void heapSort(int arr[], int n){
    for(int i = n/2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }

    for(int i = n -1; i > 0; i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

//FOR RECURSIVE SORTS, USE THESE FUNCTION CALLS
void startQuick(int arr[], int n){
    struct timespec start, end;
    clock_gettime( CLOCK_REALTIME, &start);
    quickHoare(arr, 0, n-1);
    clock_gettime( CLOCK_REALTIME, &end);

    double elapsed = ((double) ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000.0));
    printf("Total: %.15f\n", elapsed);
    
}

void startHeap(int arr[], int n){
    struct timespec start, end;
    clock_gettime( CLOCK_REALTIME, &start);
    heapSort(arr, n);
    clock_gettime( CLOCK_REALTIME, &end);
    
    double elapsed = ((double) ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000.0));
    printf("Total: %.15f\n", elapsed);
}

void startMerge(int arr[], int n){
    struct timespec start, end;
    clock_gettime( CLOCK_REALTIME, &start);
    mergesort(arr, 0, n-1);
    clock_gettime( CLOCK_REALTIME, &end);
    
    double elapsed = ((double) ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1000000000.0));
    printf("Total: %.15f\n", elapsed);
}


void rng(int arr[], int n){
    for(int i = 0; i<n; i++)
        arr[i] = rand();
}

void increasingSequence(int arr[], int N, int *X) {
    int i;

    for(i=0; i<N; i++){
        arr[i] = *X;
        (*X)++;
    }
    return;
}

void printArr(int arr[], int n){
    printf("Array: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}