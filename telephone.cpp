#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
using namespace std;
class PhoneBook{
	char name[20];
	long int phn;
public:
	void getInput();
	void showOutput();
	void fileWrite();
	void fileRead();
	void searchNumber();
	void searchName();
	void updateNumber();
};
void PhoneBook::getInput()
{
	cout<<"Enter Name:";
	cin>>name;
	cout<<"Enter Phone Number";
	cin>>phn;
}
void PhoneBook::showOutput()
{
	cout<<setw(20)<<name<<setw(20)<<phn<<endl;
}
void PhoneBook::fileWrite()
{
	fstream fout;
	fout.open("phonebook.dat",ios::out|ios::app|ios::binary);
	fout.write((char*)this,sizeof(*this));
	fout.close();
}
void PhoneBook::fileRead()
{
	fstream fin;
	fin.open("phonebook.dat",ios::in|ios::binary);
	cout<<setw(20)<<"name"<<setw(12)<<"phone"<<endl;
	while(fin.read((char*)this,sizeof(*this))){
		this->showOutput();
	}
	fin.close();
}
void PhoneBook::searchName()
{
	fstream fp;
	long phone;
	int ps,i,offset;
	ps=-1,i=0;
	bool flag=false;
	cout<<"Enter the phone number you want to search";
	cin>>phone;
	fp.open("phonebook.dat",ios::in|ios::binary);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)this,sizeof(*this))){
		if(this->phn==phone)
		{
			ps=i;
			flag=true;
			break;
		}
		i++;
	}
	if(flag)
	{
	offset=ps*sizeof(*this);
	fp.seekp(offset);
	fp.read((char*)this,sizeof(*this));
	cout<<"\nRecord Found!,The Name is"<<this->name;	
	}
	else{
		cout<<"Number doesnt exist";
	}
	fp.close();	
}
void PhoneBook::searchNumber()
{
fstream fp;
	char nm[20];
	int ps,i,offset;
	ps=-1,i=0;
	bool flag=false;
	cout<<"Enter the name you want to search";
	cin>>nm;
	fp.open("phonebook.dat",ios::in|ios::binary);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)this,sizeof(*this))){
		if(strcmp(this->name,nm)==0)
		{
			ps=i;
			flag=true;
			break;
		}
		i++;
	}
	if(flag)
	{
	offset=ps*sizeof(*this);
	fp.seekp(offset);
	fp.read((char*)this,sizeof(*this));
	cout<<"\nRecord Found!,The Number is"<<this->phn;	
	}
	else{
		cout<<"Name doesnt exist";
	}
	fp.close();	
}
void PhoneBook::updateNumber()
{
	fstream fp;
	char nm[20];
	int ps,i,offset;
	ps=-1,i=0;
	long phone;
	bool flag=false;
	cout<<"Enter the name you want to search";
	cin>>nm;
	fp.open("phonebook.dat",ios::in|ios::out|ios::ate|ios::binary);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)this,sizeof(*this))){
		if(strcmp(this->name,nm)==0)
		{
			ps=i;
			flag=true;
			break;
		}
		i++;
	}
	if(flag)
	{
	offset=ps*sizeof(*this);
	fp.seekp(offset);
	cout<<"\nRecord Found!,The current  Number is"<<this->phn;
	cout<<"Enter new Phone number";
	cin>>phone;
	this->phn=phone;
	fp.write((char*)this,sizeof(*this))<<flush;
	cout<<"Record Updated! The updated content is \n";
	while(fp.read((char*)this,sizeof(*this)))
	{
		this->showOutput();
			
	}
}
	else{
		cout<<"Name doesnt exist";
	}
	fp.close();	
}
int main()
{
	PhoneBook pb;
	int choice;
	while(true)
	{
		cout<<"\nFILE MENU\n"
		    <<"1.Write Record\n"
		    <<"2.Read Record\n"
		    <<"3.Search Name\n"
		    <<"4.Search Number\n"
		    <<"5.Update Number\n"
		    <<"6.Exit\n"
		    <<"Enter your choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				pb.getInput();
				pb.fileWrite();
				break;
			case 2:
				pb.fileRead();
				break;
			case 3:
				pb.searchName();
				break;
			case 4:
				pb.searchNumber();
				break;
			case 5:
				pb.updateNumber();
				break;
			case 6:
				exit(0);
				break;
			default:
				cout<<"Invalid Choice";			
		}
	}
	return 0;
}
