#pragma once
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
using Compare = int(*)(T,T);

template <typename T> static int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

template<typename T>
int defaultCompare(T a,T b) {
    return a < b ? -1 : (a > b ? 1 : 0); 
}

// left is the left index for the interval
// right is the right index for the interval
// k is the desired index value, where array[k] is the (k+1)th smallest element when left = 0
template<typename T,typename Func = Compare<typename T::value_type>>
static void select_h(T &array,int left,int right,int k, Func cmp = defaultCompare<typename T::value_type>){
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
      select_h<T>(array, newLeft, newRight, k, cmp);
    }
    // partition the elements between left and right around t
    auto t = array[k] ;
    auto i = left;
    auto j = right;
    swap(array[left] , array[k]);
    if (array[right] > t) {
      swap (array[right] , array[left]);
    }
    while (i < j) {
      swap (array[i] , array[j]);
      ++i;
      --j;
      for (;defaultCompare(array[i],t) < 0;++i);
      for (;defaultCompare(array[j],t) > 0;--j);
      if (defaultCompare(array[left] , t)==0) {
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

template<typename T,typename Func = Compare<typename T::value_type>>
double nth(T &array,int k,int left=0,int right=0, Func cmp = defaultCompare<typename T::value_type>){
  select_h<T>(array,left,right==0 ? array.size()-1 : right,k,cmp);
  return array[k-left+1];
}
template<typename T,typename VT,typename Func = Compare<VT>>
double nth(T &array,int k,int left=0,int right=0, Func cmp = defaultCompare<VT>){
  select_h<T>(array,left,right==0 ? array.size()-1 : right,k,cmp);
  return array[k-left+1];
}
template<typename T,typename Func = Compare<typename T::value_type>>
double nth(T &array,int k, Func cmp = defaultCompare<typename T::value_type>){
  select_h<T>(array,0,array.size()-1,k,cmp);
  return array[k+1];
}
template<typename T,typename VT,typename Func = Compare<VT>>
double nth(T &array,int k, Func cmp = defaultCompare<VT>){
  select_h<T>(array,0,array.size()-1,k,cmp);
  return array[k+1];
}

template<typename T,typename Func = Compare<typename T::value_type>>
T partition(T &array,int k,int left=0,int right=0, Func cmp = defaultCompare<typename T::value_type>){
  select_h<T>(array,left,right==0 ? array.size()-1 : right,k,cmp);
  return array;
}
template<typename T,typename VT,typename Func = Compare<VT>>
T partition(T &array,int k,int left=0,int right=0, Func cmp = defaultCompare<VT>){
  select_h<T>(array,left,right==0 ? array.size()-1 : right,k,cmp);
  return array;
}
template<typename T,typename Func = Compare<typename T::value_type>>
T partition(T &array,int k, Func cmp = defaultCompare<typename T::value_type>){
  select_h<T>(array,0,array.size()-1,k,cmp);
  return array;
}
template<typename T,typename VT,typename Func = Compare<VT>>
T partition(T &array,int k, Func cmp = defaultCompare<VT>){
  select_h<T>(array,0,array.size()-1,k,cmp);
  return array;
}
