#include "floyd-rivest.h"


// left is the left index for the interval
// right is the right index for the interval
// k is the desired index value, where array[k] is the (k+1)th smallest element when left = 0
void ipartition(int array[],int left,int right,int k,Func_int cmp){
  int tmp;
  while (right > left) {
    // Use select recursively to sample a smaller set of size s
    // the arbitrary constants 600 and 0.5 are used in the original
    // version to minimize execution time.
    if (right - left > 600){
      int n = right - left + 1;
      int i = k - left + 1;
      double z = log(n);
      double s = 0.5 * exp(2 * z/3);
      double sd = 0.5 * sqrt(z * s * (n - s)/n) * sgn(i - n/2);
      int newLeft = max(left, int(k - i * s/n + sd));
      int newRight = min(right, int(k + (n - i) * s/n + sd));
      ipartition(array, newLeft, newRight, k,cmp);
    }
    // partition the elements between left and right around t
    int t = array[k] ;
    int i = left;
    int j = right;
    swap(array[left] , array[k]);
    if (array[right] > t) {
      swap (array[right] , array[left]);
    }
    while (i < j) {
      swap (array[i] , array[j]);
      ++i;
      --j;
      for (;cmp(array[i],t) < 0;++i);
      for (;cmp(array[j],t) > 0;--j);
      if (cmp(array[left] , t)==0) {
        swap (array[left] , array[j]);
      }
      else{
        ++j;
        swap (array[j] , array[right]);
      }
      // Adjust left and right towards the boundaries of the subset
      // containing the (k - left + 1)th smallest element.
      if (j <= k)
        left = j + 1;
      if (k <= j)
        right = j - 1;
    }
  }
}

// left is the left index for the interval
// right is the right index for the interval
// k is the desired index value, where array[k] is the (k+1)th smallest element when left = 0
void dpartition(double array[],int left,int right,int k,Func_double cmp){
  double tmp;
  while (right > left) {
    // Use select recursively to sample a smaller set of size s
    // the arbitrary constants 600 and 0.5 are used in the original
    // version to minimize execution time.
    if (right - left > 600){
      int n = right - left + 1;
      int i = k - left + 1;
      double z = log(n);
      double s = 0.5 * exp(2 * z/3);
      double sd = 0.5 * sqrt(z * s * (n - s)/n) * sgn(i - n/2);
      int newLeft = max(left, int(k - i * s/n + sd));
      int newRight = min(right, int(k + (n - i) * s/n + sd));
      dpartition(array, newLeft, newRight, k,cmp);
    }
    // partition the elements between left and right around t
    double t = array[k] ;
    int i = left;
    int j = right;
    swap(array[left] , array[k]);
    if (array[right] > t) {
      swap (array[right] , array[left]);
    }
    while (i < j) {
      swap (array[i] , array[j]);
      ++i;
      --j;
      for (;cmp(array[i],t) < 0;++i);
      for (;cmp(array[j],t) > 0;--j);
      if (cmp(array[left] , t)==0) {
        swap (array[left] , array[j]);
      }
      else{
        ++j;
        swap (array[j] , array[right]);
      }
      // Adjust left and right towards the boundaries of the subset
      // containing the (k - left + 1)th smallest element.
      if (j <= k)
        left = j + 1;
      if (k <= j)
        right = j - 1;
    }
  }
}

int inth(int array[],int k,int left,int right, Func_int cmp){
  ipartition(array,left,right,k,cmp);
  return array[k-left+1];
}
double dnth(double array[],int k,int left,int right, Func_double cmp){
  dpartition(array,left,right,k,cmp);
  return array[k-left+1];
}
