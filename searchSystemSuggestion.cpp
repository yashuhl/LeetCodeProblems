/*
1268. Search Suggestions System

You are given an array of strings products and a string searchWord.

Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.

Return a list of lists of the suggested products after each character of searchWord is typed.

 

Example 1:

Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"].
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"].
After typing mou, mous and mouse the system suggests ["mouse","mousepad"].
Example 2:

Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
Explanation: The only word "havana" will be always suggested while typing the search word.
 

Constraints:

1 <= products.length <= 1000
1 <= products[i].length <= 3000
1 <= sum(products[i].length) <= 2 * 104
All the strings of products are unique.
products[i] consists of lowercase English letters.
1 <= searchWord.length <= 1000
searchWord consists of lowercase English letters.

*/

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<map>
#include<set>
#include<math.h>
#include<iterator>
#include<algorithm>


using namespace std;

class Solution 
{
public:
    // time complexity O(n*m)
    // space complexity O(n)
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) 
    {
        vector<vector<string>> result;
        map<char,set<string>> mapProducts;
        for(size_t i=0; i<products.size(); i++)
        {
            mapProducts[products[i][0]].insert(products[i]);
        }

        
        cout<<"\n products inside map in ascending order "<<endl;
        cout<<" { "<<endl;
        for(auto i:mapProducts)
        {
            cout<<" First element "<<i.first<<"-->";
            for(auto j:i.second)
            {
                cout<<j<<" ";
            }
            cout<<endl;
        }
        cout<<" }"<<endl;
        
        string tempWord="";
        
        for(size_t i=0; i<searchWord.size(); i++)
        {
            tempWord=tempWord+searchWord[i];
            vector<string> tempSearchSuggestion;

            
            
            set<string>::iterator itr;
            for(itr=mapProducts[tempWord[0]].begin();itr != mapProducts[tempWord[0]].end(); itr++)
            {
                string temp=*itr;
                if(temp.substr(0,tempWord.size()) == tempWord)
                {
                    tempSearchSuggestion.push_back(*itr);
                }
                
                if(tempSearchSuggestion.size()==3)
                {
                    break;
                }
            }
            
            // or use lower_bound binary search inbuilt function
            /*
            auto itrLowerBound=mapProducts[tempWord[0]].lower_bound(tempWord);
            for(;itrLowerBound != mapProducts[tempWord[0]].end(); itrLowerBound++)
            {  
                tempSearchSuggestion.push_back(*itrLowerBound);
                if(tempSearchSuggestion.size()==3)
                {
                    break;
                }
            }
            */
            result.push_back(tempSearchSuggestion);
        }
        return result;
        
    }
};

int main()
{
    vector<string> products = { "mobile","mouse","moneypot","monitor","mousepad" };

    string searchWord = "mouse";

    Solution S;
    vector<vector<string>> output=S.suggestedProducts(products, searchWord);

    cout<<"\n Output of search system suggestion are "<<endl;
    cout<<"{ "<<endl;

    for(size_t i=0; i<output.size(); i++)
    {
        cout<<"{ ";
        for(size_t j=0; j<output[i].size(); j++)
        {
            cout<<output[i][j];
            if(j<output[i].size()-1)
            {
                cout<< " , ";
            }
        }
        cout<<" }"<<endl;
    }
    cout<<" }"<<endl;

}