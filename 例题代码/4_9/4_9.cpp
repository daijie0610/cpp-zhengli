#include<iostream>
#include<cmath>
using namespace std;

class SavingsAccount{
public:
	SavingsAccount(int date,int id,double rate);
	int getId(){return id;}
	double getBalance(){return balance;}
	double getRate(){return rate;}
	void show();
	void deposit(int date,double amount);
	void withdraw(int date,double amount);
	void settle(int date);
private:
	int id;
	double balance,rate;
	int lastDate;
	double accumulation;
	void record(int date,double amount); //修改当前余额并将余额输出
	double accumulate(int date);
};
SavingsAccount::SavingsAccount(int date,int id,double rate):id(id),balance(0),rate(rate),lastDate(date),accumulation(0){
	cout<<date<<"\t#"<<id<<" is created"<<endl;
}
void SavingsAccount::show(){
	cout<<"#"<<id<<"\tBalance: "<<balance<<endl;
}
void SavingsAccount::deposit(int date,double amount){
	record(date,amount);
}
void SavingsAccount::withdraw(int date,double amount){
	if(amount>getBalance())
		cout<<"Error,not enough money \n";
	else
		record(date,-amount);
}
void SavingsAccount::settle(int date){ //计算年息
	double interest=accumulate(date)*rate/365;
	if(interest!=0)
		record(date,interest);
	accumulation=0;
}
void SavingsAccount::record(int date,double amount){
	accumulation=accumulate(date);
	lastDate=date;
	amount=floor(amount*100+0.5)/100;
	balance+=amount;
	cout<<date<<"\t#"<<id<<"\t"<<amount<<"\t"<<balance<<endl;
}
double SavingsAccount::accumulate(int date){
	return (static_cast<double>(date)- static_cast<double>(lastDate))*balance+accumulation;
}

int main(){
	SavingsAccount sa0(1,21325302,0.015);
	SavingsAccount sa1(1,58320212,0.015);

	sa0.deposit(5,5000);
	sa1.deposit(25,10000);
	sa0.deposit(45,5500);
	sa1.withdraw(60,4000);
	sa0.settle(90);
	sa1.settle(90);
	sa0.show();
	sa1.show();
	return 0;
}
