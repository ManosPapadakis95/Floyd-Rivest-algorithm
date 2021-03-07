# Floyd-Rivest-algorithm
Floyd–Rivest algorithm is a selection algorithm developed by Robert W. Floyd and Ronald L. Rivest. https://en.wikipedia.org/wiki/Floyd%E2%80%93Rivest_algorithm

In this repository you can find the Floyd–Rivest algorithm in different programming languages.

<h1>C++</h1
    
There are 2 different template implementations,
    
    1) nth: find the nth smallest number (like C++'s nth_element)
    2) partition: partitions the given array (like C++'s partition)

Both of them accepts the arguments:

    1) obj: of any type that 
        a) overloads operator()
        b) has a public static field value_type that holds the type of each element (like std::vector). You can give any type through template arguments.
        c) has a public function called size that returns the number of the elements inside obj. (like std::vector size)
    2) left: indicates the beggining of the sequence to be partitioned. By default 0.
    3) right: indicates the end of the sequence to be partitioned. By default obj.size()-1.
    4) Func: a function - lambda function to compare the elements of the object. Accepts 2 argument of type value_type and returns an integer. By default defaultCompare.


    #include "floyrd-rivest.hpp"
    #include <numeric>
    #include <vector>
    using namespace std;
  
    int main(){
      vector<double> array(100);
      std::random_device rd;
      std::mt19937 g(rd());
      iota(array.begin(),array.end(),0);
      shuffle(array.begin(),array.end(),g);
      
      partition<vector<double>>(array,k,[&](double a,double b){return a < b ? -1 : (a > b ? 1 : 0);});
  
      nth<vector<double>>(array,k);
    }
