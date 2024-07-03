/*
You have a keypad with 9 buttons, numbered from 1 to 9, each mapped to lowercase English letters. You can choose which characters each button is matched to as long as:

All 26 lowercase English letters are mapped to.
Each character is mapped to by exactly 1 button.
Each button maps to at most 3 characters.
To type the first character matched to a button, you press the button once. To type the second character, you press the button twice, and so on.

Given a string s, return the minimum number of keypresses needed to type s using your keypad.

Note that the characters mapped to by each button, and the order they are mapped in cannot be changed.

 

Example 1:


Input: s = "apple"
Output: 5
Explanation: One optimal way to setup your keypad is shown above.
Type 'a' by pressing button 1 once.
Type 'p' by pressing button 6 once.
Type 'p' by pressing button 6 once.
Type 'l' by pressing button 5 once.
Type 'e' by pressing button 3 once.
A total of 5 button presses are needed, so return 5.
Example 2:


Input: s = "abcdefghijkl"
Output: 15
Explanation: One optimal way to setup your keypad is shown above.
The letters 'a' to 'i' can each be typed by pressing a button once.
Type 'j' by pressing button 1 twice.
Type 'k' by pressing button 2 twice.
Type 'l' by pressing button 3 twice.
A total of 15 button presses are needed, so return 15.
 

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters.

*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<map>
#include<unordered_map>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    //create hash map of individual 26 character small english letter
    // map<char,int> char hold english small letter,int holds itr repetetion in order.
    string s="apple";

    std::map<char,int> mapString;

    for(size_t i=0; i<s.size(); i++)
    {
        mapString[s[i]]++;
    }

    // auto it is same as map<char,int>::iterator it, it is a pointer
    cout<< "Using sorted map as per key i.e small letters "<<endl;
    for(auto it=mapString.begin(); it !=mapString.end(); it++)
    {
        cout <<"key is = " << it->first << "\t";
        cout <<"value is = "<< it->second << endl;

    }

    // unordered_map<char,int> char hold english small letter,int holds itr repetetion in un order.
    unordered_map<char,int> unMapString;
    for(size_t i=0; i<s.size(); i++)
    {
        unMapString[s[i]]++;
    }

    // using iterator 
    cout<< "Using un sorted map as per key i.e small letters "<<endl;
    for(std::unordered_map<char,int>::iterator it=unMapString.begin(); it !=unMapString.end(); it++)
    {
        cout <<"key is = " << it->first << "\t";
        cout <<"value is = "<< it->second << endl;

    }

    // pair of char and int in vector to store unordered_map 
    vector<pair<char,int>> pairs;

    for(auto it:unMapString)
    {
        pairs.push_back(it);

    }


    //sort map as per descending order of its value
    
    sort(pairs.begin(), pairs.end(),
    [] (auto& a, auto& b)
    {
        return a.second>b.second;
    });

   cout<< "Using vector pair containing un ordered map as per key i.e small letters "<<endl;
   vector<int> countLetters;
   for(auto& pair:pairs)
   {
        cout <<"key is = " << pair.first << "\t";
        cout <<"value is = "<< pair.second << endl;
        countLetters.push_back(pair.second);
   }

   int count=0;
   for(size_t i=0; i<countLetters.size(); i++)
   {
        if(i<9)
        {
            count=count+countLetters[i];
        }
        if(i<18 && i>=9)
        {
            count=count+2*countLetters[i];
        }
        if(i>=18)
        {
            count=count+3*countLetters[i];
        }
   }

   cout << "Total buttons pressed are " << count <<endl;
   return 0;
}