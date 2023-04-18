#include <iostream>

#include <string.h>
#include <cmath>
using namespace std;

class ATM
{ private:
    char acc_name[200];
    char card_no[10];
    float amount=0;
public:
 void create_new_acc(char name[],  char acc_no[] );
 void deposit(char acc_no[],float value );
 void withdrawal(char acc_no[] , float value );
 void transfer(ATM &rec_account, float value);
 void print_acc_data();
 char* get();



};
bool check_float(char c[]) // we entered the value to be deposited or withdrawn as an array of character so that we can check if it is a float number without any letter or symbol.
{
    int i = 0;
    while(c[i])
    {
        if (!((c[i] >= '0' && c[i] <= '9') || c[i] == '.'))
            return 0;
        i++;
    }
    return 1;
}

bool char_to_float(char c[], float &value) //this function is to transform the value from an array of character to float
{
    if (!check_float(c))
        return false;

    int i = 0;
    while(c[i] != '.' && c[i])
        i++;

    float ten_power = pow(10, i - 1);
    i = 0;
    value = 0;
    while(c[i])
    {
        if (c[i] != '.')
        {
            value += ten_power * (c[i] - '0');
            ten_power /= 10;
        }
        i++;
    }
    return true;
}
bool enter_value(char c[], float &value)
{
    char_to_float(c, value);
    if (!char_to_float(c, value))
        return false;
    return true;
}
int checkname(char name[]) //Checks if the account name does not have any numbers or symbols
    {
        for (int i = 0; name[i]; i++)
            {
                if ((name[i] >='a' && name[i] <= 'z')|| (name[i]>='A'&& name[i]<='Z') || (name[i]==' ')) //if the character only have letters or space we will continue to the next iteration
                  {
                      continue;
                  }
                  else return 0;


            }

        return 1;}

int checkdigit(char acc[]) //Checks if the account number doesn't have any letters or symbols
    {
        for (int i = 0; acc[i]; i++)
            {
                if (!(acc[i] >='0' && acc[i] <= '9'))//if the character is not a number we will return zero and let the user enter another account number that is valid

                    return 0;}

        return 1;}

int checksamedigit(char acc[]) //checks if the account number is not 10 repeated number
  { int counter =0;
      for (int i =1; acc[i]; i++)
      {
          if (acc[0]==acc[i])// compares the first number to the rest of the array and increments the counter
            counter ++;
      }
      if (counter ==9) //here if the counter is equal to 9 then it means that the user entered 10 repeated number so it return zero and let the user enter a valid number after sending the right message
        return 0;
      return 1;
  }


char* ATM :: get ()// gets the card number from private to the main
{
    return card_no;
}

void ATM :: print_acc_data()
{
cout << "name : "<<acc_name<<endl;
cout<< "card number : "<<card_no<<endl;
cout<< "amount : "<<amount<<endl;
}

void ATM :: create_new_acc(char name[],char acc_no[])
{
   strcpy(acc_name,name);
     strcpy(card_no,acc_no);
     do
     {
cout << "Please enter the account name: ";
 cin.getline(acc_name,200);
 cout<<endl;
  if (!checkname(acc_name))
    cout << "error! name cannot contain numbers or symbols , ";
    if (strlen(acc_name)>100)
        cout<< "you cannot enter more than 100 characters , ";
    if (strlen(acc_name)<3) //we don't want the name to be less than 3 letters or greater than 100 letters
        cout<<"not enough characters , ";

     }
while ((!checkname(acc_name)) || strlen(acc_name)>100 || strlen(acc_name)<3); //we check if the account name is correct according to the instructions

 do{
 cout << "Please enter the account number (10 numbers ): ";
 cin>>card_no;
 cout<<endl;

if(!checkdigit(card_no))
    cout<< "error! don't use characters ,";
    if(strlen(card_no)!=10)
    {
        cout<< " the account must contain 10 positive integers , ";
    }
    if (!checksamedigit(card_no))
        cout << "account number is too weak!, ";
 }
 while (strlen(card_no)!=10 || !(checkdigit(card_no)) || !(checksamedigit(card_no)) );// checks if the account number is correct according to the instruction (doesn't have characters , exactly 10 number and not 10 repeated number )

}

void ATM :: deposit(char acc_no[] ,float value)
{
    strcpy(card_no,acc_no);
    while (true)
    {
        cout << "please enter the amount to be deposited: ";
        cin.ignore();
        cin.clear();
        char temp_value[100];
        cin>>temp_value;
        bool flag = enter_value(temp_value, value);
        if (!flag)
        {
            cout << "Value has to be a number" << endl;
            continue;
        }
        break;
    }
 cout<<endl;
 amount+=0.01*value+value ; // the value is deposited with a extra 1% of the deposited amount to be added to the account
print_acc_data();
}

void ATM :: withdrawal(char acc_no[],float value)
{ int flag1=0;
    strcpy(card_no,acc_no);
while (!flag1)
    {
        cin.clear();
     while (true)
    {
        cout << "please enter the amount to be withdrawn: ";
        char temp_value[100];
        cin>>temp_value;
        bool flag = enter_value(temp_value, value);
        if (!flag)
        {
            cout << "Value has to be a number" << endl;
            continue;
        }
        break;
    }

 if ((value+value*0.03)<amount) // we check if the value to be withdrawn is available in the account
 {flag1=1; }
 if (!flag1)
   {
       cout<< "you only have "<< amount << " in your account, please enter another amount"<<endl<<endl;// if the value is not available in the account we print a message to the user telling him/her the amount available in their account and then repeat the withdrawal process
     flag1=0;
   }
    }

 amount -=(value + 0.03*value);
 print_acc_data();


}


void ATM :: transfer (ATM &rec_account, float value)
{do{
    cin.clear();
   while (true)
    {
        cout << "please enter the amount to be transferred: ";
        char temp_value[100];
        cin>>temp_value;
        bool flag = enter_value(temp_value, value);
        if (!flag)
        {
            cout << "Value has to be a number" << endl;
            continue;
        }
        break;
    }
  cout<<endl;

  if ((value+value*0.015)>amount)
    cout << " the sending account only has "<<amount<<endl; // prints the available amount the user have in their account


    }
      while ((value+value*0.015)>amount) ; //   to make sure the amount transferred is less than the amount in the sending account


  amount-=(value + value*0.015);
  rec_account.amount+=(value-value*0.015);
  cout << "sending account : "<<endl; // prints both the receiving and the sending account data
  cout<< "name :"<<acc_name<<endl;
  cout<< "card number : "<<card_no<<endl;
  cout<< "amount : "<<amount<<endl;
  cout<< "receiving account : "<<endl;
  cout << "name : "<<rec_account.acc_name<<endl;
  cout<< "card number : "<<rec_account.card_no<<endl;
  cout<< "amount : "<<rec_account.amount<<endl;

}
char acc_number [10]; float value;  char operation_no[100];  char name[100]; // global variables
int account_counter=0; int flag=0; ATM accounts[100];

void display() //display the main screen
{
cout<< "1----Create new account"<<endl;
cout<< "2----Deposit"<<endl;
cout<< "3----transfer to another account"<<endl;
cout<< "4----withdrawal"<<endl;
cout<< "5----exit"<<endl;
}



void getaccount(int &a,int &b) // function to get the account number, checks if it's exactly 10 numbers and no characters and links the object to its card number
    {
         while (!flag && b<3) // 2 attempts to enter right account number
    {
      do
      {
       cout << "Please enter the account number (10 numbers): ";
       cin>>acc_number ;
       cout<<endl;
int flag2 = checkdigit(acc_number);
if (flag2==0)
    cout<< "error! don't use characters ,";


      }
       while (strlen(acc_number )!=10 || !(checkdigit(acc_number))) ;

       for( a=0; a<account_counter ;a++)
            {
              if (strcmp(accounts[a].get(),acc_number )==0) // compares the entered account number and all the account numbers in the existing objects
                 {flag=1;
                  break;
                 }
            }

    if (!flag)
        {cout << " account number doesn't exist , attempt number "<<b<<endl;
                  b++;}
     }
    }
void sendingacc(int &a,int &b) //the sending account to the transfer process
{
  while (!flag && b<3) // 2 attempts to enter right account number
    {
      do
      {
       cout << "Please enter the sending account (10 numbers): ";
       cin>>acc_number ;
       cout<<endl;
       int flag2 = checkdigit(acc_number);
if (flag2==0)
    cout<< "error! don't use characters ,";


      }
       while (strlen(acc_number )!=10 || !(checkdigit(acc_number))) ;

       for( a=0; a<account_counter ;a++)
            {
              if (strcmp(accounts[a].get(),acc_number )==0) // compares the entered account number and all the account numbers in the existing objects
                 {flag=1;
                  break;
                 }
            }

    if (!flag)
        {cout << " account number doesn't exist , attempt number "<<b<<endl<<endl;
                  b++;}

     }
}
void receivingacc(int &c,int &d) //the receiving account in the transfer process
{
     while (!flag && d<3) // 2 attempts to enter right account number
    {
      do
      {
       cout << "Please enter the receiving account (10 numbers): ";
       cin>>acc_number ;
       cout<<endl;
       int flag2 = checkdigit(acc_number);
if (flag2==0)
    cout<< "error! don't use characters ,";


      }
       while (strlen(acc_number )!=10 || !(checkdigit(acc_number))) ;

       for( c=0; c<account_counter ;c++)
            {
              if (strcmp(accounts[c].get(),acc_number )==0)
                 {flag=1;
                  break;
                 }
            }

    if (!flag)
        {cout << " account number doesn't exist , attempt number "<<d<<endl<<endl;
                  d++;}

     }
}
int check_operation_no(char x[]) //Checks if the operation number doesn't have any letters or symbols, x is the operation number
    {


                if (!(x[0] >='1' && x[0] <= '5' ))
                    return 0;

        return 1;
    }



int main()
{

while (1)
{
 display();

 while(true)
 {
    cout<<"please enter the number of operation: ";
    cin.getline(operation_no, 100);
    cin.clear();
    cout<<endl;

    if (strlen(operation_no) == 1 && check_operation_no(operation_no))
        break;
    cout << "Error! enter a number from 1 to 5." << endl;
 }



 if (operation_no[0]=='1') // to create a new account.
   {accounts[account_counter].create_new_acc(name,acc_number );

   for (int i=0; i<account_counter ; i++)
   {
       if (strcmp(accounts[i].get(),accounts[account_counter].get() )==0) // compares the entered account number and all the account numbers in the existing objects
       {
           cout <<"this account already exists, please enter another account data: "<<endl;
           accounts[account_counter].create_new_acc(name,acc_number );
       }

   }

    accounts[account_counter].print_acc_data();
    account_counter++;
   }
  else if (operation_no[0]=='2') // to deposit money from your account.
  { int i; int j=1;
   getaccount(i,j);

    if (j!=3)
      accounts[i].deposit(acc_number ,value);
      flag=0;
      j=0;
  }

  else if (operation_no[0]=='4')// the withdrawal operation.
   { int i,j=1;
      getaccount(i,j);
      cin.ignore();

    if (j!=3)
      accounts[i].withdrawal(acc_number ,value);
      flag=0;
      j=0;
  }

else if (operation_no[0]=='3') // the transfer operation.
{ int i, j=1;
sendingacc(i,j); flag=0;
int k , z=1;
receivingacc(k,z);
int flag3=0; int m;
while (!flag3)
{  for ( m=1; m<3 ; m++) // 2 attempts to enter a correct receiving account until directed to the main menu
    {if (!strcmp(accounts[i].get(),accounts[k].get() ))
       {
        cout <<"you cannot transfer to the same account , attempt  "<< m<< " out of 2" <<endl;

      flag=0;
    receivingacc(k,z);
        flag3=1;
       } else break;

    }
    flag3=1;//to get out of the while loop
}

    if (z!=3&& j!=3&& m!=3)
     accounts[i].transfer(accounts[k], value);

      flag=0;
      z=0; j=0;

}


  else if (operation_no[0]=='5')
    break;
    cin.ignore();
    } // end of while true.
}
