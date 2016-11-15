#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

// brute force finding median algorithm
int BruteForceMedian(int a[], int n) {
    int k = ceil(float(n)/2);
    for(int i=0; i<n; i++) {
         int numsmaller = 0;
         int numequal = 0;
         for(int j=0; j<n; j++) {
            if(a[j] < a[i]){
                numsmaller++;
            } else {
                 if(a[j] == a[i]){
                    numequal++;
                 }
            }
         }
         if((numsmaller < k) && (k<=(numsmaller+numequal))) {
             return a[i];
         }
     }
}

// initialize basic operation for median of partition algorithm which will partially sort the array
int Partition(int a[], int l, int h) {
    int pivotval = a[l];
    int pivotloc = l;

    for(int j=l+1; j<=h; j++) {
        if(a[j] < pivotval) {
            pivotloc++;
            swap(a[pivotloc], a[j]);
        }
    }
    swap(a[l], a[pivotloc]);
    return pivotloc;
}

// initialize basic operation for median of select algorithm which is finding the median after using partition algorithm
int Select(int a[], int l, int m, int h) {
    int pos;
    pos = Partition(a, l, h);

    if(pos == m)
        return a[pos];
    if(pos > m)
        return Select(a, l, m, pos-1);
    if(pos < m)
        return Select(a, pos+1, m, h);
}

// special case for if array size is 1, then return median. Or go to select algorithm
int Median(int a[], int n) {

    if(n == 1) {
        return a[0];
    } else {
        Select(a, 0, floor(double(n)/2), n-1);
    }
}

int main()
{
    //Founction testing different array size
//    int b = 10;
//    int a[b] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
//    int c = 10;
//    int a[c] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
//    int d = 7;
//    int a[d] = {3, 2, 4, 5, 6, 7, 8};
    int e = 10;
    int a[e] = {3, 5, 2, 4, 6, 7, 8, 9, 7, 1};


    int bruteForceMedian = BruteForceMedian(a, sizeof(a)/sizeof(int));


    cout << "The median from Brute Force median is found:" << bruteForceMedian << endl;


    int median = Median(a, sizeof(a)/sizeof(int));


    cout << "The median from Median is found:" << median << endl;



    return 0;
}
