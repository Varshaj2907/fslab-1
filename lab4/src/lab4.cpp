//============================================================================
// Name        : lab4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;
class student
{
		string name,USN,branch;
		int sem;
public: string buffer;
		void ReadStudentFromConsole()
		{
			cin.clear();
			cin.ignore(255,'\n');
			cout<<"Enter name :"<<endl;
			getline(cin,name);
			cout<<"Enter USN :"<<endl;
			cin>>USN;
			cin.clear();
			cin.ignore(255,'\n');
			cout<<"Enter branch : "<<endl;
			getline(cin,branch);
			cout<<"Enter semester : "<<endl;
			cin>>sem;
			Show();
		}
		void Show()
		{
			cout<<"USN : "<<USN;
			cout<<"\nName : "<<name;
			cout<<"\nBranch : "<<branch;
			cout<<"\nSemester : "<<sem;
			pack();
		}
		void pack();
		void unpack(int);
}S;
int rrn[100],count = 0;
fstream fp;
void find_rrn();
void search();
void error(int);
void find_rrn()
{
	int pos;
	string buffer;
	fp.open("data.txt",ios::in);
	if(!fp)
		error(1);
	while(fp)
	{
		pos = fp.tellg();
		getline(fp,buffer);
		if(buffer.length()==0)
			continue;
		rrn[++count]=pos;
	}
	fp.close();
}

void student::pack()
{
	int pos = fp.tellg();
	string sem1;
	stringstream out;
	out<<sem;
	sem1=out.str();
	string buffer=USN+'|'+name +'|'+branch +'|'+sem1+'$';
	fp<<buffer<<endl;
	cout<<endl<<buffer;
	rrn[++count]=pos;
}
void student::unpack(int pos)
{
	string sem1;
	fp.seekg(pos, ios::beg);
	getline(fp, USN, '|');
	getline(fp, name, '|');
	getline(fp, branch, '|');
	getline(fp, sem1, '$');
	stringstream convert(sem1);
	convert>>sem;
}
void search()
{
	int rrn_srch, pos;
	cout<<"Enter the RRN of the record to be found:\n";
	cin>>rrn_srch;
	if(rrn_srch>count||rrn_srch<1)
	{
		error(2);
		return;
	}
	cout<<"Record Found at position ";
	pos=rrn[rrn_srch];
	cout<<pos<<endl;
	fp.open("data.txt", ios::in);
	if(!fp)
		error(1);
	S.unpack(pos);
	fp.close();
	S.Show();
}
void error(int error)
{
	switch(error)
	{
	case 1: cout<<"Unable to open the record File\n";
			exit(0);
	case 2:	cout<<"Invalid RRN\n";
			return;
	}
}
int main()
{
	int choice;
	char ch;
	fp.open("data.txt",ios::out|ios::app);
	fp.close();
	find_rrn();
	while(1)
	{
		cout<<"1.Insert a record\n2.Search for record using RRN\n3.Exit\nEnter Choice : ";
		cin>>choice;
		switch(choice)
		{
		case 1: S.ReadStudentFromConsole();
			    fp.open("data.txt",ios::out|ios::app);
			    if(!fp)
			    	error(1);
			    S.pack();
			    fp.close();
			    break;
		case 2: search();
				break;
		default: exit(0);
		}
	cout<<"\nDo you want to continue? (Y/N)";
	cin>>ch;
	if(ch=='Y' || ch=='y')
		continue;
	else
		break;
	}
}
