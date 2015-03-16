//
//  main.cpp
//  Find the Seed
//
//  Created by Yunfan Jin on 3/14/15.
//  Copyright (c) 2015 yunfan.jin. All rights reserved.
//

#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
using namespace std;

const long SP = 1000000007;

long inverse(long number){
    assert(number != 0);
    long long prod = 1, tmp;
    while (number != 1) {
        tmp = SP / number + 1;
        prod = prod * tmp % SP;
        number = number * tmp % SP;
    }
    return prod;
}

void run(const vector<long> &C, deque<long> &F,
         const int &N, const long &inverseFactor){
    long long sum = F[0];
    for (int i=1; i<N; i++) {
        sum = (sum - F[i] * C[i-1]) % SP;
    }
    if (sum < 0) {
        sum += SP;
    }
    if (sum % C[N-1] == 0) {
        F.push_back(sum / C[N-1]);
    }else{
        F.push_back(sum * inverseFactor % SP);
    }
    F.pop_front();
}

int main(int argc, const char * argv[]) {
    
    int N;
    long K, tmp;
    deque<long> F;
    vector<long> C;
    cin >> N >> K;
    for (int i=0; i<N; i++) {
        cin >> tmp;
        F.push_back(tmp);
    }
    for (int i=0; i<N; i++) {
        cin >> tmp;
        C.push_back(tmp);
    }
    
    while (C.back() == 0) {
        C.pop_back();
        F.pop_back();
        N --;
    }
    
    long inverseFactor = inverse(C[N-1]);
    for (long i = 0; i <= K - N; i ++) {
        run(C, F, N, inverseFactor);
    }
    
    cout << F[0];
    for (int i=1; i<N; i++) {
        cout << " " << F[i];
    }
    cout << endl;
    
    return 0;
}
