#include<iostream>
#include<istream>
#include<stdlib.h>
#include<fstream>
#include<stdio.h>
using namespace std;

class Student
{
	int roll_No;
	char name[50];
	char gender;
	char section;
	float CGPA;

public:
	void getData();
	void showData();
	int getRoll(){ return roll_No;}
}s;

ofstream put;
ifstream get;
fstream file;

void Student :: getData(){
	cout<<"Enter Roll no of student :: ";
	cin>>roll_No;
	cout<<"Enter name of student    :: ";
	cin.ignore();
	cin.getline(name,30);
	cout<<"Enter gender (M/F) of student  :: ";
	cin>>gender;
	cout<<"Enter Section of student :: ";
	cin>>section;
	cout<<"Enter Grade of student   :: ";
	cin>>CGPA;
	cout<<endl;
}

void Student :: showData(){
	cout<<"\t----------------------------------------------------------------------------------"<<endl;
	cout<<"\t|Roll No |"<<"\t\tName\t\t\t"<<"| Gender "<<"| Section "<<"| Grade(CGPA) |"<<endl;
	cout<<"\t|--------|--------------------------------------|--------|---------|-------------|"<<endl;
	cout<<"\t|   "<<roll_No<<"\t | "<<name<<"\t\t\t|    "<<gender<<"\t |    "<<section<<"\t   |     "<<CGPA<<"\t |"<<endl;
	cout<<"\t----------------------------------------------------------------------------------"<<endl;
}

void addData(){
	put.open("Student.txt",ios::app | ios::out);
	cout<<"\n=========================================================================================\n";
	cout<<"\t\t\t\t:: ENTER STUDENT DETAILS :: "<<endl;
	cout<<"==========================================================================================\n"<<endl;
	char ch;
	do{
	s.getData();
	put.write((char*)&s,sizeof(s));
	cout<<"\nDo you want to add more Record(Y/N) :: ";
	cin>>ch;
	cout<<endl;
	}while(ch=='Y' || ch=='y');
	put.close();
	cout<<"Data Successfully Saved to file ...\n\n"<<endl;
}

void displayData(){
	get.open("Student.txt",ios::in);
	cout<<"\n==========================================================================================\n";
	cout<<"\t\t\t\t :: STUDENT DETAILS :: "<<endl;
	cout<<"===========================================================================================\n";
	while(get.read((char*)&s,sizeof(s)))
	{
		s.showData();
		cout<<endl;
	}
	get.close();
}

void searchData(){
	int n,flag=0;
	get.open("Student.txt",ios::in);
	cout<<"\nEnter the Roll No you want to search :: ";
	cin>>n;
	
	while(get.read((char*)&s,sizeof(s)))
	{
		if(n == s.getRoll())
		{
		cout<<"\n=======================================================================================\n";
		cout<<"\t\t\t\t :: STUDENT DETAILS :: ";
		cout<<"\n=======================================================================================\n";
			s.showData();
			flag++;
		}
	}
	if(flag==0)
		cout<<"\n   Sorry!!!  Record not found ..."<<endl;
	
	get.close();
}

void updateData(){
	int n,flag=0,pos;
	file.open("Student.txt",ios::in | ios::out);
	cout<<"\nEnter the Roll No you want to Modify :: ";
	cin>>n;
	
	while(file.read((char*)&s,sizeof(s)))
	{
		pos=file.tellg();
		if(n==s.getRoll())
		{
			cout<<"\n=======================================================================================\n";
			cout<<"\t\t\t\t :: DETAILS OF STUDENT :: "<<endl;
			cout<<"\n=======================================================================================\n";
			s.showData();
			
			cout<<"\n=======================================================================================\n";
			cout<<"\t\t\t ENTER THE NEW DETAILS OF STUDENT"<<endl;
			cout<<"\n=======================================================================================\n";
			s.getData();
			file.seekg(pos-sizeof(s));
			file.write((char*)&s,sizeof(s));
			cout<<"\n  Data update Successfully...."<<endl;
			flag++;
		}
	}
	file.close();
	
	if(flag==0)
		cout<<"\n   Sorry!!! Record not Found"<<endl<<"Please, Input Vaild Roll No"<<endl;	
}

void deleteData()
	{
	
	fstream f1("Student.txt",ios::in);
	fstream f2("Delete.txt",ios::out);
	int flag=0,n;
	char ch='n';
	cout<<"\nEnter the Roll No yout want to Delete :: ";
	cin>>n;
	while(f1.read((char*)&s,sizeof(s)))
	{
		if(s.getRoll()==n)
		{
			flag=1;
			cout<<"\nPreparing record to delete ...."<<endl;
			s.showData();
			cout<<"\nAre you sure to delete a record (Y/N) :: ";
			cin>>ch;
		}				
		if(ch=='y' | ch=='Y')
		{
			if(s.getRoll()!=n){
			f2.write((char*)&s,sizeof(s));
			f1.close();
			f2.close();
			remove("Student.txt");
			rename("Delete.txt","Student.txt");
			}
		}
	}
		if(flag==0)
		{
			f1.close();
			f2.close();
			cout<<"\n   Sorry!!! Record is not Found ..."<<endl;
		}	
	}

void work()
{
	int ch;
	do{
		system("cls");	
		cout<<"=======================================================================================\n";
		cout<<"............................. STUDENT MANAGEMENT SYSTEM ...............................\n";
		cout<<"=======================================================================================\n";
		cout<<"0. Exit from System"<<endl;
		cout<<"1. ADD Recorde in Database"<<endl;
		cout<<"2. SEARCH Data from Database"<<endl;
		cout<<"3. MODIFY Data in Database"<<endl;
		cout<<"4. DELETE Data from Database"<<endl;
		cout<<"5. SHOW Data form Database"<<endl;
		
		cout<<"\nEnter your choise :: ";
		cin>>ch;
		cout<<endl;
		switch(ch)
		{
			case 1:addData(); break;
			case 2:searchData(); break;
			case 3:updateData(); break;
			case 4:deleteData(); break;
			case 5:displayData(); break;
		}
		system("\npause");	
		}while(ch);
}

int main()
{		
	work();
	return 0;
}
