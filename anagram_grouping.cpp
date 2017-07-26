/*
Author: Ashish Jindal
Title: Group all the anagrams together and return set of anagrams
*/

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

/*structure to store strings and their original indexes*/
struct myStruct
{
    string str;
    int index;
};

/*Comparator function for quick sort*/
bool compStr(struct myStruct a, struct myStruct b)
{
    return (strcmp(a.str.c_str(), b.str.c_str()) <= 0);
}

/*Actual method which groups the anagrams together and put them into a set. Finally the vector of sets of anagrams is returned.*/
vector<set<string> > doGrouping(const vector<string>&words)
{
    vector<set<string> >ans;
    ans.clear();
    set<string>mySet;
    mySet.clear();

    vector<struct myStruct>myarr;
    struct myStruct temp;
    myarr.clear();
    int n=words.size();

    for(int i=0; i<n; i++)
    {
        temp.str = words[i];
        temp.index = i;
        myarr.push_back(temp);
    }

    for(int i=0; i<n; i++)
    {
        sort(myarr[i].str.begin(), myarr[i].str.end());
    }

    sort(myarr.begin(), myarr.end(), compStr);

    string t1=myarr[0].str;
    for(int i=0; i<n; )
    {
        if(t1==myarr[i].str)
        {
            mySet.insert(words[myarr[i].index]);
            i++;
        }
        else
        {
            t1=myarr[i].str;
            ans.push_back(mySet);
            mySet.clear();
        }
    }
    ans.push_back(mySet);

    return ans;
}

int main()
{
    vector<set<string> >result;
    result.clear();
    set<string>::iterator it;

    vector<string>words; 
    //can input more words here
    words.push_back("cat");
    words.push_back("dog");
    words.push_back("god");
    words.push_back("act");

    result = doGrouping(words);

    for(int i=0; i<result.size(); i++)
    {
        for(it=result[i].begin(); it!=result[i].end(); it++)
        {
            cout<<*it<<" ";
        }
        cout<<"\n";
    }

    return 0;
}
