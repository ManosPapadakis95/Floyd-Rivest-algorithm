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
// k is the desired index value, where obj[k] is the (k+1)th smallest element when left = 0
template<typename T,typename Func = Compare<typename T::value_type>>
static void select_h(T &obj,int left,int right,int k, Func cmp = defaultCompare<typename T::value_type>){
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
      select_h<T>(obj, newLeft, newRight, k, cmp);
    }
    // partition the elements between left and right around t
    auto t = obj[k] ;
    auto i = left;
    auto j = right;
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

template<typename T,typename Func = Compare<typename T::value_type>>
typename T::value_type nth(T &obj,int k,int left=0,int right=0, Func cmp = defaultCompare<typename T::value_type>){
  select_h<T>(obj,left,right==0 ? obj.size()-1 : right,k,cmp);
  return obj[k-left+1];
}
template<typename T,typename VT,typename Func = Compare<VT>>
VT nth(T &obj,int k,int left=0,int right=0, Func cmp = defaultCompare<VT>){
  select_h<T>(obj,left,right==0 ? obj.size()-1 : right,k,cmp);
  return obj[k-left+1];
}
template<typename T,typename Func = Compare<typename T::value_type>>
typename T::value_type nth(T &obj,int k, Func cmp = defaultCompare<typename T::value_type>){
  select_h<T>(obj,0,obj.size()-1,k,cmp);
  return obj[k+1];
}
template<typename T,typename VT,typename Func = Compare<VT>>
VT nth(T &obj,int k, Func cmp = defaultCompare<VT>){
  select_h<T>(obj,0,obj.size()-1,k,cmp);
  return obj[k+1];
}

template<typename T,typename Func = Compare<typename T::value_type>>
void partition(T &obj,int k,int left=0,int right=0, Func cmp = defaultCompare<typename T::value_type>){
  select_h<T>(obj,left,right==0 ? obj.size()-1 : right,k,cmp);
}
template<typename T,typename VT,typename Func = Compare<VT>>
void partition(T &obj,int k,int left=0,int right=0, Func cmp = defaultCompare<VT>){
  select_h<T>(obj,left,right==0 ? obj.size()-1 : right,k,cmp);
}
template<typename T,typename Func = Compare<typename T::value_type>>
void partition(T &obj,int k, Func cmp = defaultCompare<typename T::value_type>){
  select_h<T>(obj,0,obj.size()-1,k,cmp);
}
template<typename T,typename VT,typename Func = Compare<VT>>
void partition(T &obj,int k, Func cmp = defaultCompare<VT>){
  select_h<T>(obj,0,obj.size()-1,k,cmp);
}
