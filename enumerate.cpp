/*Author:Ali Khatai June 2020
Constructing Order 2 Carmichael numbers*/
// function to enumerate all divisors of a value given its prime facotrs

#include <algorithm>
#include<iostream>
#include <vector>
#include"print.h"

using namespace std;

// declare function
vector<int> divisors(vector<int>& factors) {
   
    // declare vector for the result
    vector<int> div;
   
    // get the size of the list of factors
    int size = factors.size();
    // if the size is one then the result is 1 and the number itself. So append that to the result vector "div".
    if (size == 1) {
        div.push_back(1);
        div.push_back(factors.front());
        return div;
    }
    else {
        // get the head of the input vector and the tail by removing the first element
        int head = factors.back();
        factors.pop_back();
        vector<int> divtail = divisors(factors);
        vector<int> mult;
        for (int i = 0; i < divtail.size(); i++) {
            int x = divtail[i] * head;
            
                mult.push_back(x);
        }
        //vector<int>div;
       
        // sort the two vectore and resize the result vector which is required for set union
        div.resize(divtail.size() + mult.size());
        sort(divtail.begin(), divtail.end());
        sort(mult.begin(), mult.end());
        
        // use set union to get the union to the two vectors
        set_union(divtail.begin(), divtail.end() , mult.begin(), mult.end() , div.begin());
        
        // remove trailing and leading zeros and return the divisors
        Rzeros(div);
        return div;
    }

}
