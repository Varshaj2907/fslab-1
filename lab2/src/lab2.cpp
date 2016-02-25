//============================================================================
// Name        : lab2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : B3-lab2.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<fstream>
#include <iostream>
#include<string>
#include<sstream>
#define max 100
using namespace std;
class Student
{
	string name,USN,branch;
	int sem;
public :
	string buffer;
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
		cout<<"\nUSN : "<<USN;
		cout<<"\nName : "<<name;
		cout<<"\nBranch : "<<branch;
		cout<<"\nSemester : "<<sem<<endl;
		pack();
	}
	void pack()
	{
		int i;
		string temp,sem1;
		stringstream out;
		out<<sem;
		sem1=out.str();
		temp=USN+'|'+name+'|'+branch+'|'+sem1;
		for(i=temp.size();i<max;i++)
		{
			temp+='$';
		}
		cout<<temp;
		buffer=temp;
	}
	void write()
	{
		fstream fp1;
		fp1.open("data1.txt",ios::out|ios::app);
		fp1<<buffer;
		fp1<<endl;
		fp1.close();
	}
	int search(string key)
	{
		fstream fp1;
		int pos;
		fp1.open("data1.txt",ios::in);
		while(!fp1.eof())
		{
			getline(fp1,buffer);
			pos=fp1.tellp();
			unpack();
			if(USN==key)
			{
				cout<<"USN : "<<USN;
				cout<<"\nName : "<<name;
				cout<<"\nBranch : "<<branch;
				cout<<"\nSemester : "<<sem<<endl;
				fp1.close();
				return pos;
			}
		}
		return 0;
	}
	void unpack()
	{
		int i=0;
		USN.erase();
		while(buffer[i]!='|')
			USN+=buffer[i++];
		i++;
		name.erase();
		while(buffer[i]!='|')
			name+=buffer[i++];
		i++;
		branch.erase();
		while(buffer[i]!='|')
			branch+=buffer[i++];
		i++;
		string sem1;
		stringstream out;
		out<<sem;
		sem1=out.str();
		sem1.erase();
		while(buffer[i]!='|')
			sem1+=buffer[i++];
		i++;

	}

	void modify(string key)
	{
		int choice;
		search(key);
		del(key);
		cout<<"Enter choice : \n1.USN\n2.name\n3.Branch\n4.Sem\n";
		cin>>choice;
		switch(choice)
			{
				case 1: cout<<"Enter USN :"<<endl;
						cin>>USN;
						break;
				case 2: cin.clear();
						cin.ignore(255,'\n');
						cout<<"Enter name :"<<endl;
						getline(cin,name);
						break;
				case 3: cin.clear();
						cin.ignore(255,'\n');
						cout<<"Enter branch : "<<endl;
						getline(cin,branch);
						break;
				case 4: cout<<"Enter semester : "<<endl;
						cin>>sem;
						break;
			}
		pack();
		write();
	}
	int del(string key)
	{
		fstream fp1;
		int pos=search(key);
		pos=pos-100;
		fp1.open("data1.txt",ios::out|ios::app);
		seek("data1.txt",pos);
		fp2.put('*');
		fp1.close();
		return pos;

	}
};
int main()
{
	int choice,i;
	Student S;
	char ch;
	string key;
	while(1)
	{
	cout<<"Enter choice : \n1.Insert\n2.Search\n3.Delete\n4.Modify\n";
	cin>>choice;
	switch(choice)
		{
			case 1: S.ReadStudentFromConsole();
				    S.write();
				    break;
			case 2: cout<<"Enter key : ";
					cin>>key;
				    i=S.search(key);
				    if(i!=0)
				    	cout<<"Found at "<<i-100<<endl;
				    else
				    	cout<<"Not found\n";
				    break;
			case 3: cout<<"Enter key : ";
					cin>>key;
					S.modify(key);
					break;
		}
	cout<<"\nDo you want to continue? (Y/N)";
	cin>>ch;
	if(ch=='Y' || ch=='y')
		continue;
	else
		break;
	}
	return 0;
}
