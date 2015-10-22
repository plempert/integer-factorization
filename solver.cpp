#include<iostream>
#include<bitset>
#include<cmath>
#include<cstdlib>
#include<vector>
#include <ctime>
#include "ttmath/ttmath.h"

//typedef ttmath::Big<10,10> MyBig;

typedef signed short BIT;
typedef ttmath::UInt<10> BigInt;
const clock_t begin_time = clock();


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

std::string toString(BigInt x){
    std::string s;
    while (x > 0)
    {
        s += String< BigInt >(x % 2);
        x /= 2;
    }
    reverse(s);
    return s;
}

void trim(std::string &binary){
    binary = binary.substr( binary.find('1') );
}

void printPrime(BIT p[], int n){
    for(int i = 0; i < n; i++){
        std::cout << p[i];
    }
    std::cout << "\n";
}

void printPrime(std::vector<BIT> p){
    for(int i = 0; i < p.size(); i++){
        std::cout << p[i];
    }
    std::cout << "\n";
}

void init(BIT p1[], BIT p2[], BIT z[], int n){
    p1[n-1] = -1; p1[0] = 1;
    for(int i = 0; i < n; i++){
        z[i] = 0;
    }
    for(int i = 0; i < n; i++){
        if(i == 0 || i == n-1){

            p2[i] = 1;
        } else{
            p1[i] = -1;
            p2[i] = -1;
        }
    }
    //printPrime(p1,n);
    //printPrime(p2,n);
    //printPrime(z,n);
}

void trim(std::vector<BIT> &p){
    for(int i = p.size()-1; i>=0; i--){
        if(p[i] == 0) p.pop_back();
        else break;
    }
}

void reverse(BIT p[], int n){
    for(int i = 0; i < n/2; i++){
        std::swap(p[i],p[n-1-i]);
    }
}

void reverse(std::vector<BIT> &p){
    for(int i = 0; i < p.size()/2; i++){
        std::swap(p[i],p[p.size()-1-i]);
    }
}

void multiply(BIT p1[], BIT p2[], std::vector<BIT> &product, int n){    //n is number of bits in p1,p2
    BIT carry = 0;
    //int product_index = 0;
    int sum = 0;
    int p1_i;
    for(int p1_start = 0; p1_start < n; p1_start++){
            p1_i = p1_start;
        for(int terms = 1; terms <= p1_start+1; terms++){
            sum += p1[p1_i] * p2[terms-1];
            //std::cout << p1[p1_i] << " * " << p2[terms-1] << " + ";
            p1_i--;
        }

        sum += carry;
        //std::cout << carry << " = ";
        product.push_back(sum % 2);
        carry = sum / 2;
        //std::cout << sum << " " << product[product.size()-1] << " " << carry << "\n";
       // product_index++;
        sum = 0;
    }
    //std::cout << "\n";
    int p1_start = n-1;
    int p2_i;
    for(int p2_start = 1; p2_start < n; p2_start++){
            p2_i = p2_start;
            p1_i = n-1;
        for(int terms = n-p2_start; terms >= 1; terms--){
            sum += p1[p1_i] * p2[p2_i];
            //std::cout << p1[p1_i] << " * " << p2[p2_i] << " + ";
            p1_i--;
            p2_i++;
        }
        sum += carry;
        //std::cout << carry << " = ";
        product.push_back(sum % 2);
        carry = sum / 2;
        //std::cout << sum << " " << product[product.size()-1] << " "<< carry << "\n";
        //product_index++;
        sum = 0;
    }
    if(carry==1)product.push_back(carry);
}

bool areEqual(std::vector<BIT> product, BIT sp[], int n){    //n is number of bits in sp, product
    if(n!=product.size()) return false;
    for(int i = 0; i < n; i++){
        if(product[i] != sp[i]) return false;
    }
    return true;
}

void solve(BIT sp[], BIT p1[], BIT p2[], BIT z[], int &n, int current_position, BIT carry, int &sp_n){    //n is number of bits in p1,p2
    //if(current_position == 0) solve(sp, p1, p2, z, n, current_position+1, 0);
    //std::cout << sp_cp << "\n";
    //std::string pause; getline(std::cin, pause);
    //reverse(p1, n);printPrime(p1,n);reverse(p1, n);
    //reverse(p2, n);printPrime(p2,n);reverse(p2, n);
    //std::cout << "current pos: " << current_position << "\n";
    if(current_position == n){
        std::vector<BIT> product;
        multiply(p1,p2,product,n);
        trim(product);
/*
        std::cout << "p1\n";
        reverse(p1, n);printPrime(p1,n);reverse(p1, n);
        std::cout << "p2\n";
        reverse(p2, n);printPrime(p2,n);reverse(p2, n);
        std::cout << "p1*p2\n";
        reverse(product);printPrime(product);reverse(product);
        std::cout << "sp\n";
        reverse(sp,sp_n);printPrime(sp,sp_n);reverse(sp,sp_n);
*/
        if( areEqual(product,sp,sp_n) ){
            reverse(p1, n);
            reverse(p2, n);
            reverse(product);
            reverse(sp,sp_n);
            std::cout << "Hooray!\n";
            printPrime(p1,n);
            printPrime(p2,n);
            printPrime(product);
            printPrime(sp,sp_n);
            std::cout << "------\n";
            std::cout << "TIME: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "\n";
            exit(0);
        }
        return;
    }
    BIT sum_of_carry_and_known = carry;
    for(int i = 1; i < current_position; i++){
        sum_of_carry_and_known += p2[i]*p1[current_position-i];
    }
    //std::cout << sum_of_carry_and_known << "\n";
    //std::cout << sp[current_position] << "\n";

    if(sp[current_position] == 0){
        if(sum_of_carry_and_known % 2 == 0){
            p1[current_position] = 0;    p2[current_position] = 0;    carry = (sum_of_carry_and_known+p1[current_position]+p2[current_position])/2;
            solve(sp,p1,p2,z,n,current_position+1,carry,sp_n);
            p1[current_position] = 1;    p2[current_position] = 1;    carry = (sum_of_carry_and_known+p1[current_position]+p2[current_position])/2;
            solve(sp,p1,p2,z,n,current_position+1,carry,sp_n);
        } else if(sum_of_carry_and_known % 2 == 1){
            p1[current_position] = 0;    p2[current_position] = 1;    carry = (sum_of_carry_and_known+p1[current_position]+p2[current_position])/2;
            solve(sp,p1,p2,z,n,current_position+1,carry,sp_n);
            p1[current_position] = 1;    p2[current_position] = 0;    carry = (sum_of_carry_and_known+p1[current_position]+p2[current_position])/2;
            solve(sp,p1,p2,z,n,current_position+1,carry,sp_n);
        }
    }else if(sp[current_position] == 1){
        if(sum_of_carry_and_known % 2 == 0){
            p1[current_position] = 0;    p2[current_position] = 1;    carry = (sum_of_carry_and_known+p1[current_position]+p2[current_position])/2;
            solve(sp,p1,p2,z,n,current_position+1,carry,sp_n);
            p1[current_position] = 1;    p2[current_position] = 0;    carry = (sum_of_carry_and_known+p1[current_position]+p2[current_position])/2;
            solve(sp,p1,p2,z,n,current_position+1,carry,sp_n);
        } else if(sum_of_carry_and_known % 2 == 1){
            p1[current_position] = 0;    p2[current_position] = 0;    carry = (sum_of_carry_and_known+p1[current_position]+p2[current_position])/2;
            solve(sp,p1,p2,z,n,current_position+1,carry,sp_n);
            p1[current_position] = 1;    p2[current_position] = 1;    carry = (sum_of_carry_and_known+p1[current_position]+p2[current_position])/2;
            solve(sp,p1,p2,z,n,current_position+1,carry,sp_n);
        }
    }
}


int main(int argc, char **argv){

    //MyBig semiprime;
    /*
    unsigned long long semiprime;
    std::cout << "enter semiprime: ";
    std::cin >> semiprime;
    std::string semiprime_binary;
    semiprime_binary = std::bitset<512>(semiprime).to_string();
    */

    BigInt semiprime = argv[1];
    //std::cout << "enter semiprime: ";
    //std::cin >> semiprime;
    std::string semiprime_binary = toString(semiprime);



    //semiprime.ToString(semiprime_binary, 2); //std::bitset<128>(semiprime).to_string();
    trim(semiprime_binary);
    std::cout << semiprime_binary << "\n";
    int size_of_primes = std::ceil( semiprime_binary.length()/2 + 1);


    BIT sp[semiprime_binary.length()];
    int sp_n = semiprime_binary.length();
    for(int i = 0; i < sp_n; i++){
        sp[i] = semiprime_binary[i] - '0';    //convert string to BIT array
    }
    //printPrime(sp,semiprime_binary.length());

    BIT prime1[size_of_primes];
    BIT prime2[size_of_primes];
    BIT zero[size_of_primes];
    init(prime1, prime2, zero, size_of_primes);
    //std::cout << size_of_primes << "\n";


    reverse(sp,sp_n);
    solve(sp, prime1, prime2, zero, size_of_primes, 1, 0, sp_n);
    //std::cout << "test\n";
    return 0;
}
