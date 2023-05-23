/*
#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int low, int mid, int high) {
    // Create arrays of left and right partititons
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];
    
    // Copy all left elements
    for (int i = 0; i < n1; i++) left[i] = arr[low + i];
    
    // Copy all right elements
    for (int j = 0; j < n2; j++) right[j] = arr[mid + 1 + j];
    
    // Compare and place elements
    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        } 
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // If any elements are left out
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void parallelMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections num_threads(10) {
            #pragma omp section
            parallelMergeSort(arr, low, mid);
            #pragma omp section
            parallelMergeSort(arr, mid + 1, high);
        }
        #pragma omp taskwait
        merge(arr, low, mid, high);
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int n = 1e5;
    int arr[n];
    double start_time, end_time;

    // Create an array with numbers starting from n to 1.
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
    
    // Measure Sequential Time
    start_time = omp_get_wtime(); 
    mergeSort(arr, 0, n - 1);
    end_time = omp_get_wtime(); 
    cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds\n";
    // Reset the array
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
    
    //Measure Parallel time
    start_time = omp_get_wtime(); 
    parallelMergeSort(arr, 0, n - 1);
    end_time = omp_get_wtime(); 
    cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds";
    
    return 0;
}
*/


#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void merge(vector <int> & a, int l, int mid, int r) {
    int n1 = mid - l + 1, n2 = r - mid;
    vector <int> left, right;
    for(int i = 0; i < n1; i++) left.push_back(a[l + i]);
    for(int i = 0; i < n1; i++) right.push_back(a[mid + i + 1]);
    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2) {
        if(left[i] < right[j])
            a[k++] = left[i++];
        else 
            a[k++] = right[j++];
    }
    while(i < n1) a[k++] = left[i++];
    while(j < n2) a[k++] = right[j++];
}

void pMergeSort(vector <int> & a, int l, int r) {
    if(r <= l) return;
    int mid = (l + r) / 2;
    #pragma omp parallel sections 
        #pragma omp section 
            pMergeSort(a, l, mid);
        
        #pragma omp section 
            pMergeSort(a, mid + 1, r);
    merge(a, l, mid, r);
}

void print(vector <int> a) {
    for(int x : a) cout << x << " ";
    cout << endl;
}

void mergeSort(vector <int> & a, int l, int r) {
    if(r <= l) return;
    int mid = (l + r) / 2;
    // cout << l << ", " << mid << ", " << r << endl;
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    merge(a, l, mid, r);
}

int main() {
    int n = 1000;
    vector <int> a(n);
    for(int i = 0; i < n; i++) a[i] = n - i;
    double st = omp_get_wtime();
    // mergeSort(a, 0, n - 1);
    pMergeSort(a, 0, n - 1);
    double end = omp_get_wtime();
    cout << end - st;
    // print(a);
}
