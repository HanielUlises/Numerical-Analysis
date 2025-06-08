#include "bits/stdc++.h"

float maximo(){
    float Xo = 5;
    float err = 0.001;
   
    const float lambda = 50;
    
    for(int i = 0; i < 500; i++){
        Xo = Xo + lambda* (Xo* (2*cos(Xo)-Xo*sin(Xo))-1) /1500;
        std::cout<<i + 1 <<')' <<Xo <<std::endl;
    }

    float dx = ((std::pow(Xo, 2) * cos(Xo) - Xo)/1500) + 4;
    return dx;
}

float minimo(){
    float Xo = 5;
    float err = 0.001;
   
    const float lambda = 50;
    
    for(int i = 0; i < 500; i++){
        Xo = Xo - lambda* (Xo* (2*cos(Xo)-Xo*sin(Xo))-1) /1500;
        std::cout<<i + 1 <<')' <<Xo <<std::endl;
    }

    float dx = ((std::pow(Xo, 2) * cos(Xo) - Xo)/1500) + 4;
    return dx;
}


int main (){
    float max = maximo();
    std::cout<<"Valor max "<< max<<std::endl;
    float min = minimo();
    std::cout<<"Valor min "<< min<<std::endl;
    
}