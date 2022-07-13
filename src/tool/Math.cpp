#include "tool/Math.hpp"

int Math::factorial(int n){
    if(n==0||n==1){
        return 1;

    }else{
        return factorial(n-1)*n;

    }

}

int Math::combinatorialNumber(int n,int m){
    return Math::factorial(n)/(Math::factorial(m)*Math::factorial(n-m));

}
