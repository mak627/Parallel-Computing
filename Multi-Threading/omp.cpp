//Parallel Programming with OpenMP
#include <iostream>
#include <chrono>
#include <omp.h>

#define N 100000

using namespace std;
using namespace std::chrono;

int main() {

int a[N],b[N],c[N];
double t1,t2;
for(int i=0;i<N;i++){
	a[i] = 1;
	b[i] = 2;
}
//auto start = high_resolution_clock::now();
t1 = omp_get_wtime();

#pragma omp parallel for
for(int i=0;i<N;i++){
	c[i] = a[i] + b[i];
}

t2 = omp_get_wtime();
//auto stop = high_resolution_clock::now();
//auto time_diff = stop - start;
//cout << "Tot_Exec_Time:" << duration<double,micro> (time_diff).count() << "us" << endl;
cout << (t2-t1)*1000000 << "ms" << endl;
return 0;
}
