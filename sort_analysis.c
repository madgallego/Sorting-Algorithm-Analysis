#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//make use of fucntion decalrations here, and function definitions in below the main function



void main() {
    //user inputs will also occur here
        //ensure that array is instantiated as a pointer(ex: int *arr = malloc(sizeof(int) * n))
    printf("Enter number of elements: ");
    int n;
    scanf(" %d", &n);
    int *arr = malloc(sizeof(int) * n);
    rng(arr, n, 100);
    printArr(arr, n);


    //add the calls here
    //use swtich case



    free(arr);



}


//add the different sorting algorithms beyond this point
//selection
void selection(int arr[], int n){
    clock_t start = clock();
    clock_t end;
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
    end = clock();
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total: %f\n", elapsed);
}
//insertion
void insertion(int arr[], int n){
    clock_t start = clock();
    clock_t end;
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
    end = clock();
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total: %f\n", elapsed);
}
//bubble
void bubble(int arr[], int n){
    clock_t start = clock();
    clock_t end;
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
    end = clock();
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total: %f\n", elapsed);
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
    int p = arr[l];
    int i = l -1, j = h + 1, t;

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
    clock_t start = clock();
    clock_t end;
    quickHoare(arr, 0, n-1);
    end = clock();
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total: %f\n", elapsed);
    
}

void startHeap(int arr[], int n){
    clock_t start = clock();
    clock_t end;
    heapSort(arr, n);
    end = clock();
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total: %f\n", elapsed);
}

void startMerge(int arr[], int n){
    clock_t start = clock();
    clock_t end;
    mergesort(arr, 0, n-1);
    end = clock();
    double elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total: %f\n", elapsed);
}


void rng(int arr[], int length, int min){
    int newRand;
    int unique = 0;

    for (int i = 0; i < length; i++){
        
        do{
            newRand = (rand() % (length - min + 1)) + min;
            unique = 1;
            for(int j = 0; j < i; j++){
                if(arr[j] == newRand)
                    unique = 0;
            }
        }while(unique != 1);

        arr[i] = newRand;
    }
}

void printArr(int arr[], int n){
    printf("Array: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}