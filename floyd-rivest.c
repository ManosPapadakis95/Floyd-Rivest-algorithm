#include "floyd-rivest.h"


// left is the left index for the interval
// right is the right index for the interval
// k is the desired index value, where obj[k] is the (k+1)th smallest element when left = 0
void ipartition(int obj[],int left,int right,int k,Func_int cmp){
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
      ipartition(obj, newLeft, newRight, k,cmp);
    }
    // partition the elements between left and right around t
    int t = obj[k] ;
    int i = left;
    int j = right;
    swap(obj[left] , obj[k]);
    if (obj[right] > t) {
      swap (obj[right] , obj[left]);
    }
    while (i < j) {
      swap (obj[i] , obj[j]);
      ++i;
      --j;
      for (;cmp(obj[i],t) < 0;++i);
      for (;cmp(obj[j],t) > 0;--j);
      if (cmp(obj[left] , t)==0) {
        swap (obj[left] , obj[j]);
      }
      else{
        ++j;
        swap (obj[j] , obj[right]);
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
// k is the desired index value, where obj[k] is the (k+1)th smallest element when left = 0
void dpartition(double obj[],int left,int right,int k,Func_double cmp){
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
      dpartition(obj, newLeft, newRight, k,cmp);
    }
    // partition the elements between left and right around t
    double t = obj[k] ;
    int i = left;
    int j = right;
    swap(obj[left] , obj[k]);
    if (obj[right] > t) {
      swap (obj[right] , obj[left]);
    }
    while (i < j) {
      swap (obj[i] , obj[j]);
      ++i;
      --j;
      for (;cmp(obj[i],t) < 0;++i);
      for (;cmp(obj[j],t) > 0;--j);
      if (cmp(obj[left] , t)==0) {
        swap (obj[left] , obj[j]);
      }
      else{
        ++j;
        swap (obj[j] , obj[right]);
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

int inth(int obj[],int k,int left,int right, Func_int cmp){
  ipartition(obj,left,right,k,cmp);
  return obj[k-left+1];
}
double dnth(double obj[],int k,int left,int right, Func_double cmp){
  dpartition(obj,left,right,k,cmp);
  return obj[k-left+1];
}
