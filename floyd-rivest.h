
#ifndef FLOYD_RIVEST_H
#define FLOYD_RIVEST_H

#define sgn(val) ((0 < val) - (val < 0))
#define defaultCompare(a,b) ((a < b) ? -1 : (a > b ? 1 : 0))
#define max(x,y) ((x<y)?y:x)
#define min(x,y) ((x<y)?x:y)
#define swap(x,y) ((tmp=x),(x=y),(y=tmp))

typedef int(*Func_int)(int,int);
typedef int(*Func_double)(double,double);

void ipartition(int[],int,int,int,Func_int);
void dpartition(double[],int,int,int,Func_double);
int inth(int[],int,int,int,Func_int);
double dnth(double[],int,int,int,Func_double);
  
#endif
