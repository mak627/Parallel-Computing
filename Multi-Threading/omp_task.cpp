//Parallel Programming with OpenMP
#include <iostream>
#include <chrono>
#include <omp.h>

#define N 100000
#define STEP 100

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

#pragma omp for
for(int i=0;i<N;i+=STEP){
    //cout << "Executing from thread" << omp_get_thread_num() << "of " << omp_get_num_threads() << "total threads";
    #pragma omp task
    {
	for(int j=i;j<i+STEP;j++)	
	c[j] = a[j] + b[j];
    }
}

t2 = omp_get_wtime();
cout << (t2-t1)*1000 << "ms" << endl;
return 0;
}
