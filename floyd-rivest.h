
#ifndef FLOYD_RIVEST_H
#define FLOYD_RIVEST_H

#define sgn(val) ((0 < val) - (val < 0))
#define defaultCompare(a,b) ((a < b) ? -1 : (a > b ? 1 : 0))
#define max(x,y) ((x<y)?y:x)
#define min(x,y) ((x<y)?x:y)
#define swap(x,y) ((tmp=x),(x=y),(y=tmp))

typedef int(*Func_int)(int,int);
typedef int(*Func_double)(double,double);

void ipartition(int array[],int left,int right,int k,Func_int cmp);
void dpartition(double array[],int left,int right,int k,Func_double cmp);
int inth(int array[],int k,int left,int right, Func_int cmp);
double dnth(double array[],int k,int left,int right, Func_double cmp);
  
#endif
