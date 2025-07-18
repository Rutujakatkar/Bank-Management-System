
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
 
 
class account
{
	int Account_No;
	char Account_Holder_Name[44];
	char type;
	int Deposit_Amount;
public:
	void Open_account();	//function to get data from user
	void Display_account() const;	//function to show data on screen
	void Update();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void Withdraw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int Return_Account_Number() const;	//function to return account number
	int Return_Deposit_Amount() const;	//function to return balance amount
	char Return_type() const;	//function to return type of account
};         
 
 
void account::Display_account() const
{
	cout<<"\nAccount No. : "<<Account_No;
	cout<<"\nAccount Holder Name : ";
	cout<<Account_Holder_Name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<Deposit_Amount;
}
void account::Open_account()
{
	cout<<"\n please Enter Your Require Details :-->";
    cout<<"\nPlease! Enter The account No. :";
	cin>>Account_No;
	cout<<"\nPlease! Enter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(Account_Holder_Name,44);
	cout<<"\nPlease! Enter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nPlease! Enter The Initial amount(>=440 for Saving and >=1000 for current ) : ";
	cin>>Deposit_Amount;
	cout<<"\n\nCongratulation!!! Your Has Been Created Successfully ...";
}
 
 
 
	
void account::dep(int x)
{
	Deposit_Amount+=x;
}
	
void account::Withdraw(int x)
{
	Deposit_Amount-=x;
}
	
void account::report() const
{
	cout<<Account_No<<setw(10)<<" "<<Account_Holder_Name<<setw(10)<<" "<<type<<setw(6)<<Deposit_Amount<<endl;
}
 
void account::Update()
{
	cout<<"\nAccount No. : "<<Account_No;
	cout<<"\nUpdate Account Holder Name : ";
	cin.ignore();
	cin.getline(Account_Holder_Name,44);
	cout<<"\nUpdate Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nUpdate Balance amount : ";
	cin>>Deposit_Amount;
}
	
int account::Return_Account_Number() const
{
	return Account_No;
}
 
 
char account::Return_type() const
{
	return type;
}
int account::Return_Deposit_Amount() const
{
	return Deposit_Amount;
}
 
//function declaration
 
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void Deposit_Amount_withWithdraw(int, int); // function to desposit/withWithdraw amount for given account
void intro();	//introductory screen function
void Update_account(int);	//function to Update record of file
//THE MAIN FUNCTION OF PROGRAM
 
int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\t\t-------------------------MAIN MENU-----------------------------------";
		cout<<"\n\t\t1. Create An ACCOUNT";
		cout<<"\n\t\t2. Deposit_Amount AMOUNT";
		cout<<"\n\t\t3. WITHWithdraw AMOUNT";
		cout<<"\n\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t7. Update AN ACCOUNT";
		cout<<"\n\t\t8. EXIT";
        cout<<"\n";
		cout<<"\n\t\tSelect Your Option (1-8):--> ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			Deposit_Amount_withWithdraw(num, 1);
			break;
		case '3':
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			Deposit_Amount_withWithdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			Update_account(num);
			break;
		case '8' :
			cout<<"n\t\t************ Thanks for using bank managemnt system *************";
			break;
		 default :cout<<"Invalid Choice";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

//function to write in file
 
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.Open_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}
 
//function to read specific record from file
 
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";
 
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\nAccount number does not exist";
}
 
 
//function to Update record of file
 
void Update_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			cout<<"\nPlease! Enter The New Details of account"<<endl;
			ac.Update();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\t\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n Record Not Found ";
}
 
//function to delete record of file
 
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.Return_Account_Number()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\t\tRecord Deleted ..";
}
 
//function to display all accounts Deposit_Amount list
 
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\t\tACCOUNT HOLDER LIST\n";
	cout<<"*************************\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"*************************\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}
 
//  	function to Deposit_Amount and withWithdraw amounts
 
 
void Deposit_Amount_withWithdraw(int n, int option)
{
	int Amount;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			if(option==1)
			{
				cout<<"\n\t\tTO Deposit_Amount AMOUNT ";
				cout<<"\nPlease! Enter The amount to be Deposit:";
				cin>>Amount;
				ac.dep(Amount);
			}
			if(option==2)
			{
				cout<<"\n\t\tTO WITHWithdraw AMOUNT ";
				cout<<"\nPlease! Enter The amount to be withWithdraw:";
				cin>>Amount;
				int bal=ac.Return_Deposit_Amount()-Amount;
				if((bal<440 && ac.Return_type()=='S') || (bal<1000 && ac.Return_type()=='C'))
					cout<<"Insufficience balance";
				else
					ac.Withdraw(Amount);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\t\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n Record Not Found ";
}
 
 
//INTRODUCTION FUNCTION
 
void intro()
{
	cout<<"\n\n\t                              !!!  WELCOME TO DHANLAXMI BANK  !!! ";
    //cout<<"\n\t           ------------------------------------------------";
    cout<<"\n\t                        ------------------------------------------------";
	cout<<"\n";
	//cout<<"\n\t\tMANAGEMENT";
	//cout<<"\n\t\t  SYSTEM";
	cout<<"\n\nMADE BY : Rutuja, Sukhada, Dipali";
    cout<<"\n";
	cout<<"\nINSTITUTE NAME : Soft Polynomials ";
    cout<<"\n\n";

    cout<<"\n*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*~~*";
    

	cin.get();
}
