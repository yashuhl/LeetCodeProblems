/*
2288. Apply Discount to Prices

A sentence is a string of single-space separated words where each word can contain digits, lowercase letters, and the dollar sign '$'. A word represents a price if it is a sequence of digits preceded by a dollar sign.

For example, "$100", "$23", and "$6" represent prices while "100", "$", and "$1e5" do not.
You are given a string sentence representing a sentence and an integer discount. For each word representing a price, apply a discount of discount% on the price and update the word in the sentence. All updated prices should be represented with exactly two decimal places.

Return a string representing the modified sentence.

Note that all prices will contain at most 10 digits.

 

Example 1:

Input: sentence = "there are $1 $2 and 5$ candies in the shop", discount = 50
Output: "there are $0.50 $1.00 and 5$ candies in the shop"
Explanation: 
The words which represent prices are "$1" and "$2". 
- A 50% discount on "$1" yields "$0.50", so "$1" is replaced by "$0.50".
- A 50% discount on "$2" yields "$1". Since we need to have exactly 2 decimal places after a price, we replace "$2" with "$1.00".
Example 2:

Input: sentence = "1 2 $3 4 $5 $6 7 8$ $9 $10$", discount = 100
Output: "1 2 $0.00 4 $0.00 $0.00 7 8$ $0.00 $10$"
Explanation: 
Applying a 100% discount on any price will result in 0.
The words representing prices are "$3", "$5", "$6", and "$9".
Each of them is replaced by "$0.00".
 

Constraints:

1 <= sentence.length <= 105
sentence consists of lowercase English letters, digits, ' ', and '$'.
sentence does not have leading or trailing spaces.
All words in sentence are separated by a single space.
All prices will be positive numbers without leading zeros.
All prices will have at most 10 digits.
0 <= discount <= 100

*/

#include<iostream>
#include<string>
#include<stdio.h>
#include<vector>

using namespace std;

string discountPrices(string &sentence, int discount) 
{
    // put every string into vector of string , check for space to divide array elements
    vector<string> tempArray;
    string temp="";
    for(size_t i=0; i<sentence.size(); i++)
    {
        if(sentence[i] == ' ')
        {
            tempArray.push_back(temp);
            temp="";

        }
        else
        {
            temp=temp+sentence[i];
        }
    }
    if(temp.size() != 0)
    {
        tempArray.push_back(temp);
    }

    //print array content
    for(size_t j=0; j<tempArray.size(); j++)
    {
        cout << tempArray[j] << " ";
    }
    cout << endl;

    for(size_t j=0; j<tempArray.size(); j++)
    {
        string help=tempArray[j];
        bool found =false;

        string num="";
        for(size_t k=0; k<help.size(); k++)
        {
            //check if first char of each array element is $
            if( (k==0) && (help[k]=='$') )
            {
                found=true;
            }
            // collect the number if present after array starting with $
            else if(found == true)
            {
                if(help[k] >='0' && help[k]<='9')
                {
                    num=num+help[k];
                }
                else
                {
                    // set found bool back to false and come out of loop if $ is followed by any other format
                    found = false;
                    break;
                }
            }
        }

        if(found && num.size() >0 )
        {
            // convert string number to float, apply discount and convert float to string with $
            float number=stof(num);
            float disPrice=(number*(100-discount))/100.0 ;
            string arr = "$"+to_string(disPrice);
            //remove last 4 decimal units
            int pres = 4;
            while(pres--)
            {
                arr.pop_back();
            }
                
            tempArray[j]=arr;
        }
    }

    // put the sliced array back
    string ans="";
    for(auto it:tempArray)
    {
        ans=ans+it+" ";

    }
    // remove the last trailing space.
    ans.pop_back();
    return ans;
}

int main()
{
    string sentence = "there are $1 $2 and 5$ candies in the shop";
    int discount=50;
    string output = discountPrices(sentence, discount);

    // Output the result 
    cout << "Original: " << sentence << endl; 
    cout << "Modified: " << output << endl;

    return 0;
}