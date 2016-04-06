//============================================================================
// Name        : lab8.cpp
// Author      : Varsha Jain
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
string merge(vector<string>fname,int left,int right)
	{
	if(left==right)
		return fname[left];
	else if((right-left)==1)
		{
		ifstream if1(fname[left].c_str());
		ifstream if2(fname[right].c_str());
		ofstream of((fname[left]+"a").c_str());
		string s1,s2;
		getline(if1,s1);
		getline(if2,s2);
		while(!(if1.eof()) && !(if2.eof()))
			{
			if(s1==s2)
				{
				if(s1!="")
					of<<s1<<endl;
				getline(if1,s1);
				getline(if2,s2);
				}
			else if(s1<s2)
				{
				if(s1!="")
					of<<s1<<endl;
				getline(if1,s1);
				}
			else
				{
				if(s2!="")
					of<<s2<<endl;
				getline(if2,s2);
				}
			}
		while(!if1.eof())
			{ 
			if(s1!="")
				of<<s1<<endl;
			getline(if1,s1);
			}
		while(!if2.eof())
			{
			if(s2!="")
   				of<<s2<<endl;
    			getline(if2,s2);
			}
		if1.close();
		if2.close();
		of.close();
		return fname[left]+"a";
		}
	else
		{
		int mid=(left+right)/2;
		string f1,f2;
		f1=merge(fname,left,mid);
		f2=merge(fname,mid+1,right);
		vector<string>str;
		str.push_back(f1);
		str.push_back(f2);
		return merge(str,0,1);
		}
	}
int main()
	{
	vector<string>v;
	v.push_back("f0.txt");
	v.push_back("f1.txt");
	v.push_back("f2.txt");
	v.push_back("f3.txt");
	v.push_back("f4.txt");
	v.push_back("f5.txt");
	v.push_back("f6.txt");    
	v.push_back("f7.txt");
	cout<<"Resulting file is "<<merge(v,0,7)<<endl;
	}
