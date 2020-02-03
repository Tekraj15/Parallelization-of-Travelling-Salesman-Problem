#include<stdio.h>
#include<omp.h>
#include<time.h>
#include<unistd.h>


int main()
{

clock_t begin = clock();

int n;
printf("Enter No Of Vertices : ");
scanf( "%d" , &n );
int a[n][n];
int nv[n];
int v[n];
int i , j , k;
int over = 0;
int min = 1000000;
int vertex;
int mstCost = 0;
for( i = 0 ; i < n ; i++ )
{
for( j = 0 ; j < n ; j++ )
{
printf( "Enter Edge Weight ( %d , %d ) : " , i , j );
scanf( "%d" , &a[i][j] );
}
nv[i] = i;
v[i] = -1;
printf( "nv[i]=%d \n",nv[i]);
}
if( n > 0 )
{
v[0] = nv[0];
nv[0] = -1;
}
//-1 indicates node is visited
while( over == 0 )
{
omp_set_num_threads(4);
#pragma omp parallel for
for( i = 0 ; i < n ; i++ )
{
if( v[i] != -1 )
{
for( j = 0 ; j < n ; j++ ){
if( nv[j] != -1 )
{
if( min > a[v[i]][nv[j]] && a[v[i]][nv[j]] != 0 )
{
min = a[v[i]][nv[j]];
vertex = nv[j];
k = j; //for indicates visit
}
}
}
}
}
printf( "min=%d \n",min);
mstCost += min;
min = 1000000;
nv[k] = -1; //visited
for( i = 0 ; i < n ; i++ )
{
if( v[i] == -1 )
{
v[i] = vertex;
break;
}
}
over = 1;
for( i = 0 ; i < n ; i++ )
{
if( nv[i] != -1 )
{
over = 0;
break;
}
}
}
printf( "MST COST : %d \n" , mstCost);

clock_t end = clock();
double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
printf("Time spent: %lf\n", time_spent);



return 0;
}
