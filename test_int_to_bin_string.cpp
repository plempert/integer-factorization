#include<iostream>
#include<sstream>
#include "ttmath/ttmath.h"

template<typename NumTy>
std::string String(const NumTy& Num)
{
	std::stringstream StrStream;
	StrStream << Num;
	return(StrStream.str());
}

void reverse(std::string &s){
    for(int i = 0; i < s.length()/2; i++){
        std::swap(s[i],s[s.length()-1-i]);
    }
}

std::string toString(ttmath::UInt<5> x){
    std::string s;
    while (x > 0)
    {
        s += String< ttmath::UInt<5> >(x % 2);
        x /= 2;
    }
    reverse(s);
    return s;
}

int main(){
    // (pseudo-code)
    // String to BigInt
/*
    String s = ...;
    BigInt x = 0;

    while (!s.empty())
    {
        x *= 10;
        x += s[0] - '0';
        s.pop_front();
    }

    Output(x);
*/
    // (pseudo-code)
    // BigInt to String

    ttmath::UInt<5> temp="123456789";
/*
    BigInt x = ...;
    String s;

    while (x > 0)
    {
        s += '0' + x % 10;
        x /= 10;
    }

    Reverse(s);
    Output(s);*/

    std::cout <<  toString(temp);
    return 0;

}
