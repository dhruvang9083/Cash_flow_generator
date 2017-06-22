#include "stdafx.h" // 
#include <iostream> // for fetching input output stream
#include <conio.h> // for console input output
#include <vector> // for using vectors
#include <iomanip> // 

using namespace std; // namespace includes standard functions like cin and cout

class PaymentDetail //create a class with name PaymentDetail
{
	// class member variables, are private by default
	int monthNumber;		 
	double interestAmount; 
	double principalAmount;
	double remainingAmount;

	//public functions is class paymentdetail
public:
	PaymentDetail(int month, double interest, double principal, double remAmount) // constructor
	{
		monthNumber = month;
		interestAmount = interest;
		principalAmount = principal;
		remainingAmount = remAmount;
	}

	double round2decimals(double val) // round up to 2 decimals value provided
	{
		return roundf(val * 100) / 100;
	}

	void Print() // for printing
	{
		cout << monthNumber << std::setw(15);
		cout << round2decimals(interestAmount) << std::setw(15);
		cout << round2decimals(principalAmount) << std::setw(15);
		cout << round2decimals(remainingAmount) << std::setw(15);
		cout << '\n';
	}

	void PaymentDetail_Join(PaymentDetail& src)
	{
		monthNumber = src.monthNumber;
		interestAmount += src.getInterestAmount();
		principalAmount += src.getPrincipalAmount();
		remainingAmount += src.getRemainingAmount();
	}

	//getters and setters/accessors and mutators
public:
	int PaymentDetail::getMonthNumber() const {
		return (monthNumber);
	}

	double PaymentDetail::getInterestAmount() const {
		return (interestAmount);

	}

	double PaymentDetail::getPrincipalAmount() const {
		return (principalAmount);
	}

	double PaymentDetail::getRemainingAmount() const {
		return (remainingAmount);
	}
};



class Loan // class with name Loan
{
	Loan() {}    //private constructor to prevent object creation using this method
	
	//class member variables
	int loanid;
	double amountLoaned;
	double rate;
	int months;

public:
	Loan(int id) { loanid = id; } //default constructor as one with no parameters is made private

	//getters and setters/accessors and mutators
	int getloanid() { return loanid; }

	void Loan::setAmountLoaned(double mountLoaned) {     
		this->amountLoaned = mountLoaned;
	}

	void Loan::setMonths(int months) {    
		this->months = months;
	}

	void Loan::setRate(double rate) {     
		this->rate = rate;
	}

public:

	double Loan::getAmountLoaned() const {
		return (amountLoaned);
	}

	int Loan::getMonths() const {
		return (months);
	}

	double Loan::getRate() const {
		return (rate);
	}
};


class Calculator//class with name calculator for doing all the calculations
{
	std::vector<PaymentDetail> PaymentDetails; // vector variable for storing all the payment details
	int loanid; // class member variable

	//default constructor
public:
	Calculator() {
	}

	//prints payment all details to console one by one
	void Print()
	{
		cout << "Month" << std::setw(15);
		cout << "Interest($)" << std::setw(15);
		cout << "Principal($)" << std::setw(15);
		cout << "Balance($)" << std::setw(15);
		cout << '\n';

		for (int i = 0; i < PaymentDetails.size(); i++)
		{
			PaymentDetails[i].Print();
		}
	}
	//getters and setters/accessors and mutators
	std::vector<PaymentDetail>& GetPaymentDetails() { return PaymentDetails; }

	double GetMonthlyPayment(Loan& loan)
	{
		double amount = loan.getAmountLoaned();
		double rate = loan.getRate() / 1200.0;
		int months = loan.getMonths();
		double payment = (amount) * (rate) / (1.0 - ::pow(1.0 + rate, -months));
		return payment;
	}

	//calculate all payment details for given loan
	void Calculate(Loan& loan)
	{
		this->loanid = loan.getloanid();
		PaymentDetail pd(0, 0, 0, loan.getAmountLoaned());
		PaymentDetails.push_back(pd);

		int i = 0;
		double rembal = loan.getAmountLoaned();
		double pmt = GetMonthlyPayment(loan);
		while (i < loan.getMonths() && rembal > 0)
		{
			double interest = loan.getRate() / 1200.0 * rembal;
			double principal = pmt - interest;
			rembal = rembal - principal;

			PaymentDetail pd(i + 1, interest, principal, rembal);
			PaymentDetails.push_back(pd);
			i++;
		}
	}

	void Join(Calculator& source)
	{
		//source = calc2
		//srcpmtdetails = cacl2(payment details)

		//poolcalc//
		//PaymentDetails = poolcalc(paymentdetails)

		std::vector<PaymentDetail>& srcpmtdetails = source.GetPaymentDetails();
		for (int i = 0; i < srcpmtdetails.size(); i++)
		{
			PaymentDetail* pd = 0;
			if (i < PaymentDetails.size())
				pd = &PaymentDetails.at(i);
			// pd = paykentdetail at i(payemntdetail iof calc1 )
			else
			{
				PaymentDetails.push_back(PaymentDetail(0, 0, 0, 0));
				pd = &PaymentDetails.back();
			}


			
			pd->PaymentDetail_Join(srcpmtdetails[i]);
		}
	}

};

//

int main()
{
	
	std::vector<Loan> loans; // declare a vector varibale named loans for storing all the loans given as input

	int n;//number of loans
	cout << " enter total loan n ";
	cin >> n;
	
	for (int i = 0; i < n;i++) { // iterating for all loans

		Loan loan1(i+1); //setting loan id to i+1 as i starts from 0 and loan id start from 1
		cout << "Enter Loan Amount " << endl;
		int loanAmount;
		cin >> loanAmount; // getting laonAmount input
		loan1.setAmountLoaned(loanAmount);

		cout << "Enter Rate " << endl;
		int rate;
		cin >> rate; //getting rate input
		loan1.setRate(rate);

		cout << "Enter Months " << endl;
		int months;
		cin >> months; //getting months input
		loan1.setMonths(months);

		loans.push_back(loan1); //storing each loan in loans vector
			
	}
	
	

	std::vector<Calculator> Calculators; // a vactor variable named vCalculators for storing all the calculations
	Calculator poolcalc; // single calculator variable
	for (int i = 0; i < loans.size(); i++) // iterating through all loans
	{
		Calculator calc;
		calc.Calculate(loans[i]);    //calculate payment details for loan[i]

		cout << std::endl << "Loan Number-" << loans[i].getloanid() << std::endl;
		calc.Print();                //print payment details

		poolcalc.Join(calc);
		Calculators.push_back(calc);
	}

	cout << std::endl << "Pool Loan Payment Details" << std::endl;
	poolcalc.Print();    //print pool payment details

	cout << "Press any key to exit";
	_getch();
	return 0;
}