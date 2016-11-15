#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

// initialize basic operation for brute force is zero
long int basic_operation_bruteforce = 0;

// brute force finding median algorithm
long BruteForceMedian(int a[], int n) {
    int k = ceil(float(n)/2);
    for(int i=0; i<n; i++) {
         int numsmaller = 0;
         int numequal = 0;
         for(int j=0; j<n; j++) {
            basic_operation_bruteforce++;
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
long basic_operation_median = 0;
int Partition(int a[], int l, int h) {
    int pivotval = a[l];
    int pivotloc = l;

    for(int j=l+1; j<=h; j++) {
        basic_operation_median++;
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
long Median(int a[], int n) {

    if(n == 1) {
        basic_operation_median++;
        return a[0];
    } else {
        Select(a, 0, ceil(float(n)/2), n-1);
    }
}


int main()
{
    srand(time(NULL));

    double START_B, END_B, START_P, END_P;
    int bruteForceMedian, jsMedian;

    long long bruteForceAvgBO = 0, bruteForceTotalBO = 0, medianAvgBO = 0, medianTotalBO = 0;

    double avgTime_BF, totalTime_BF, avgTime_MEDIAN, totalTime_MEDIAN;


    // create test cases loop to run same size of array many times
    int y = 100;
    for (int v=0; v<y; v++) {

        // create testing data loop to generate random number input
        int x = 1000;
        int a[x];
        int rand_vaule;
        for(int i=0; i<x; i++){
            rand_vaule = rand();
            a[i] = rand_vaule;
        }

        basic_operation_bruteforce = 0;
        basic_operation_median = 0;

        START_B = clock();
        bruteForceMedian = BruteForceMedian(a, sizeof(a)/sizeof(int));
        END_B = clock();

        bruteForceTotalBO += basic_operation_bruteforce;

        totalTime_BF += ((END_B - START_B)/CLOCKS_PER_SEC);

        START_P = clock();
        jsMedian = Median(a, sizeof(a)/sizeof(int));
        END_P = clock();

        medianTotalBO += basic_operation_median;

        totalTime_MEDIAN += ((END_P - START_P)/CLOCKS_PER_SEC);
    }

    // get average output for same array size in many times test cases
    bruteForceAvgBO = bruteForceTotalBO/y;
    avgTime_BF = totalTime_BF/y;

    medianAvgBO = medianTotalBO/y;
    avgTime_MEDIAN = totalTime_MEDIAN/y;

    cout << endl <<  std::fixed;
    cout <<"Brute Force Total Time: " << totalTime_BF << endl;
    cout <<"Brute Force Average Time: " << avgTime_BF << endl;

    cout << endl;
    cout <<"Brute Force Total Basic Operations: " << bruteForceTotalBO << endl;
    cout <<"Brute Force Average Basic Operations: " << bruteForceAvgBO << endl;

    cout << endl;
    cout <<"Median Total Time: " << totalTime_MEDIAN << endl;
    cout <<"Median Average Time: " << avgTime_MEDIAN << endl;

    cout << endl;
    cout <<"Median Total Basic Operations: " << medianTotalBO << endl;
    cout <<"Median Average Basic Operations: " << medianAvgBO << endl;

    return 0;
}
