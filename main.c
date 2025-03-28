#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Algoritmos de ordenação

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int tmp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = tmp;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            }
        }
        int tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void countingSort(int arr[], int n) {
    if (n <= 0) return;
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    int range = max - min + 1;
    int *count = calloc(range, sizeof(int));
    int *output = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) count[arr[i] - min]++;
    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) output[--count[arr[i] - min]] = arr[i];
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(count);
    free(output);
}

// Funções utilitárias

void copyArray(int *source, int *dest, int n) {
    for (int i = 0; i < n; i++)
        dest[i] = source[i];
}

void fillRandom(int *arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;
}

void testSorts(int size) {
    printf("\n=== Testando com %d elementos ===\n", size);
    int *original = malloc(size * sizeof(int));
    fillRandom(original, size);
    int *arr = malloc(size * sizeof(int));
    clock_t start, end;

    // Bubble Sort
    copyArray(original, arr, size);
    start = clock();
    bubbleSort(arr, size);
    end = clock();
    printf("Bubble Sort: %.3fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Selection Sort
    copyArray(original, arr, size);
    start = clock();
    selectionSort(arr, size);
    end = clock();
    printf("Selection Sort: %.3fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Insertion Sort
    copyArray(original, arr, size);
    start = clock();
    insertionSort(arr, size);
    end = clock();
    printf("Insertion Sort: %.3fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Merge Sort
    copyArray(original, arr, size);
    start = clock();
    mergeSort(arr, 0, size - 1);
    end = clock();
    printf("Merge Sort: %.3fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Quick Sort
    copyArray(original, arr, size);
    start = clock();
    quickSort(arr, 0, size - 1);
    end = clock();
    printf("Quick Sort: %.3fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Counting Sort
    copyArray(original, arr, size);
    start = clock();
    countingSort(arr, size);
    end = clock();
    printf("Counting Sort: %.3fs\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(original);
    free(arr);
}

// Função principal

int main() {
    srand(time(NULL));
    int sizes[] = {100, 500, 1000, 5000, 30000, 80000, 100000, 150000, 200000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        testSorts(sizes[i]);
    }

    return 0;
}
