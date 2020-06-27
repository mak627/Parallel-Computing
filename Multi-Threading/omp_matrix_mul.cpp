//matrix multiplication with OpenMP
#include <iostream>
#include <omp.h>

#define n 500

using namespace std;

int main() {

int a[n][n],b[n][n],c[n][n];
int i,j,k;
double t1,t2;

t1 = omp_get_wtime();
#pragma omp parallel shared(a,b,c) private(i,j,k)
{
  #pragma omp for
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
	a[i][j] = 1;
	b[i][j] = 2;
    }
  }
  //compute matrix multiply
  #pragma omp for
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
	//c[i][j] = 0;
	for(k=0;k<n;k++){
	  c[i][j] += ((a[i][k]) * (b[k][j]));
	}
    }
  }
}

t2 = omp_get_wtime();
cout << (t2-t1)*1000 << "ms" << endl;
return 0;
}
