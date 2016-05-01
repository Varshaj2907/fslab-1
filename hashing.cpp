//============================================================================
// Name        : hash.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
using namespace std;
int hashalgo(string str,int prime)
{
	unsigned long hash = 5381;
	int c;
	int i=0;
	while(c=str[i++])
	{
		hash=((hash<<5)+hash)+c;
	}
	return hash%prime;
}
bool isprime(int n)
{
	if(n==2)
		return true;
	if((n%2)==0)
		return false;
	for(int i=3; i <= sqrt(n); i++ )
	{
		if((n%i)==0)
			return false;
	}
	return true;
}
int nearprime(int n)
{
    int i;
    if(n==1)
    	return 2;
    if(n==2)
    	return 2;
	if((n%2)==0)
		n++;
	for(i=n;isprime(i)==false;i++);
	return i;
}
class Student
{
	string name;
	string usn;
	int sem;
	string branch;
public:
	Student (string iname,string iusn,string ibranch,int isem)
	{
		name=iname;
		usn=iusn;
		sem=isem;
		branch=ibranch;
	}
	string getkey()
	{
		return name;
	}
	string pack(int n)
	{
		string s;
		stringstream ss;
		ss<<sem;
		s=name+"|"+usn+"|"+branch+"|"+ss.str();
		s.resize(n,'$');
		return s;
	}
	static Student unpack (string in)
	{
		stringstream ss;
		ss<<in;
		string name,usn,sem,branch;
		getline(ss,name,'|');
		getline(ss,usn,'|');
		getline(ss,branch,'|');
		getline(ss,sem,'$');
		return Student(name,usn,branch,atoi(sem.c_str()));
	}

	bool match (string key,string value)
	{
		return (key=="name"&&value==name) ||(key=="usn"&&value == usn)
				||(key=="sem"&&sem==atoi(value.c_str()))||(key=="branch"&&value==branch);
	}
};
class Hashfile {
	string filename;
	int buckets;
    int b_size;
	int rsize;
public:
	Hashfile(string fname, int no_of_buckets,int bucket_size, int recsize)
	{
		filename=fname;
		buckets=nearprime(no_of_buckets);
		b_size=bucket_size;
		rsize=recsize;
		string str;
		str.resize(rsize,'$');
		ofstream f(filename.c_str(),ios::out|ios::app);
		for(int i=0;i<(buckets*b_size*rsize);i+=rsize)
		{
			f<<str;
		}
		f.close();
	}
	int addrec(string s,string key)
		{
			int bucket_nos=hashalgo(key,buckets);
	        char buff[rsize];
	        fstream f(filename.c_str(),ios::in|ios::out);
			f.seekg(bucket_nos*b_size*rsize);
			for(int i=0;i<b_size;i++)
			{
	            int offset=f.tellg();
			    f.read(buff,rsize);
	            if(buff[0]=='$')
	            {
	            	f.seekp(offset);
	            	f<<s;
	                f.close();
	                return 0;
	             }
	         }
			f.close();
	        return -1;
	      }
	string search(string key,string value)
	{
		char buffer[rsize+1];
		fstream f(filename.c_str(),ios::in|ios::out);
		buffer[rsize] = '\0';
        int bucket_no = hashalgo(key,buckets);
		f.seekg(0,ios::beg);
		for(int i = 0; i < (buckets * b_size ); i++)
		{
			//cout<<"pos in file search :"<<f.tellp()<<endl;
		    f.read(buffer,rsize);
            if ( buffer[0] != '$' )
            {
            	//cout<<"buffer : "<<buffer<<endl<<endl;
            	Student s = Student::unpack(buffer);
            	if (s.match(key,value))
            	{
            		return buffer;
            	}
            }
		}
	return "";
 	}
};
int main()
{
	int n;
	char ch;
	string key;
	cout<<"Enter the Number of Buckets"<<endl;
	cin>>n;
	Hashfile f("data.txt",n,5,100);
	Student s1 ("a","b","c",1);
	Student s2 ("d","e","f",2);
	Student s3 ("g","h","i",3);
	Student s4 ("j","k","l",3);
	Student s5 ("m","n","p",3);
	f.addrec(s1.pack(100),s1.getkey());
	f.addrec(s2.pack(100),s2.getkey());
	f.addrec(s3.pack(100),s3.getkey());
	f.addrec(s4.pack(100),s4.getkey());
	f.addrec(s5.pack(100),s5.getkey());
	while(1)
	{
	cout<<"Do you want to search?(y/n)";
	cin>>ch;
	if(ch=='y'|| ch=='Y')
		{
		cout<<"Enter key to be searched : ";
		cin>>key;
		cout << f.search("name",key) << endl;
		}
	else
		break;
	}
	return 0;
}
