#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordoptions(const std::set<std::string>& dict, const std::string& in, const std::string& floating, int length, int position, std::string& current, std::set<std::string>& options, int numfloating);
int countletters(const std::string& in);
int findfloaters(const std::string& in, int numletters, const std::string& floating);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int lengthofword = countletters(in);
    int numfloating = countletters(floating);

   int position = 0;
   std::set<std::string> options;
   std::string current = "";
   wordoptions(dict, in, floating,lengthofword, position, current, options, numfloating);
   return options;

}

// Define any helper functions here
int countletters(const std::string& in){
   int numletters = 0;
   while(in[numletters] != '\0'){
     ++numletters;
   }
   return numletters;
}


int findfloaters(const std::string& in, int numletters, const std::string& floating){
    int numfloats = 0;
    std::map<char, int> frequencies;
    for(char c : floating){
        frequencies[c]++;
        // if(frequencies.find(c) == frequencies.end()){
        //     frequencies.insert({c, 1});
        // }else{
        //     ++frequencies.find(c)->second;
        // }
    }
    for(char c:in){
        if(frequencies.find(c)!=frequencies.end() &&(frequencies.find(c)->second>0) ){
          ++numfloats;
           --frequencies.find(c)->second;
        }
    }
    return numfloats;

}


void wordoptions(const std::set<std::string>& dict, const std::string& in, const std::string& floating, int length, int position, std::string& current, std::set<std::string>& options, int numfloating){
   if(position == length){
       int numletters = countletters(current);
       int numfloaters = findfloaters(current, numletters, floating);
       if(numfloaters == numfloating && dict.count(current)){
           //if (dict.find(current)!= dict.end()){
           options.insert(current);
           // }
           //options.insert(current);
       }
       return;
   }else{
       int numletters = countletters(current);
       int numfloaters = findfloaters(current, numletters, floating);
       if((length-numletters)<(numfloating-numfloaters)){
           return;
       }
       if(dict.lower_bound(current) == dict.end() || dict.lower_bound(current)->compare(0, numletters, current) != 0){
           return;
       }
   }
   if(in[position] != '-'){
       current.push_back(in[position]);
       wordoptions(dict, in, floating, length, position+1, current, options, numfloating);
       current.pop_back();
   }else{
       for(char c='a'; c <= 'z'; c++){
           current.push_back(c);
           wordoptions(dict, in, floating, length, position+1, current, options, numfloating);
           current.pop_back();
       }
   }
}
