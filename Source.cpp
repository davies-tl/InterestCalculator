/*
Analysis: Given an input file of data and deposits for a group of people, calculate and print the amount of interest with details.
          Terminate the program when the end of file is reached, and make sure to use good variable names.
Design
   A) Input:
      - Prompt user for name of input file. File will include the following information.
      - Account Holder's Full Name
      - Amount Deposited in Dollars
      - Number of Years/Time on Deposit (used to calculate Interest Rate)
      - Code (used to determine the number of times compound interest is calculated and paid per year)
      - Verify that the file was opened properly; terminate the program if not.
      - Verify that the file has contents (no need to verify specific data); terminate the program if there are no contents.
      - Use File Stream to assign contents to individual variables. 
   B) Process:
      - Calculate Interest Rate using the given schedule:
         Time on Deposit                 Interest Rate
         >= 5 years                          4.5%
         Less than 5 and >=4 years           4%
         Less than 4 and >=3 years           3.5%
         Less than 3 and >=2 years           2.5%
         Less than 2 and >=1 years           2%
         Less than 1 year                    1.5%
      - Determine the number of times compound interest is calculated and paid per year, using the code given and the following chart:
         Code        Number of times calculated
         A                 4
         B                 2
         C                 1
         D                 12
         E                 365
      - Compute the interest using the formula: A = P(1+ r/n)^nt
         P = principal amount (the initial amount you borrow or deposit)
         r  = annual rate of interest (as a decimal)
         t  = number of years the amount is deposited or borrowed for.
         A = amount of money accumulated after n years, including interest.
         n  =  number of times the interest is compounded per year
      - Must have at least four functions.
      - Will need to use a loop to process new data for each person (loop will call to the other functions).
   C) Output: Display an organized chart including the following information:
      - Header
      - Name
      - Years
      - Original Deposit
      - Interest Earned
      - New Balance (with interested)
      - Make sure to display the decimal point with two digits after the decimal; also display the dollar sign for monetary values.
Implementation (Below):
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

double YearsToInterestRate(int numYears) {
    double interestRateDecimal;
    if (numYears < 1) {
        interestRateDecimal = 0.015;
    }
    else if (numYears < 2) {
        interestRateDecimal = 0.020;
    }
    else if (numYears < 3) {
        interestRateDecimal = 0.025;
    }
    else if (numYears < 4) {
        interestRateDecimal = 0.035;
    }
    else if (numYears < 5) {
        interestRateDecimal = 0.040;
    }
    else {
        interestRateDecimal = 0.045;
    }
    return interestRateDecimal;
}

int CodeToCompoundInterest(char compoundInterestCode) {
    int numTimesCompoundPerYear;
    switch (compoundInterestCode) {
        case 'A':
        case 'a':
            numTimesCompoundPerYear = 4;
            break;
        case 'B':
        case 'b':
            numTimesCompoundPerYear = 2;
            break;
        case 'C':
        case 'c':
            numTimesCompoundPerYear = 1;
            break;
        case 'D':
        case 'd':
            numTimesCompoundPerYear = 12;
            break;
        case 'E':
        case 'e':
            numTimesCompoundPerYear = 365;
            break;
        default:
            cout << "Code entered is not valid.  Program terminated." << endl;
            exit(0);
    }
    return numTimesCompoundPerYear;
}

double CalculateDepositWithInterest(double initialAmount, double interestRateDecimal, int numYears, int numCompoundPerYear) {
    double amountAfterInterest = initialAmount * pow((1.0 + (interestRateDecimal / (double)numCompoundPerYear)), ((double)numCompoundPerYear * (double)numYears));
    return amountAfterInterest;
}

void ProcessDataFile(string inputFileName) {
    ifstream inFS;
    string userName;
    double depositAmount, interestRate, interestDollarAmount;
    int yearsDeposited, numCompound;
    char compoundCode;
    double amountWithInterest;

    inFS.open(inputFileName);

    if (!inFS.is_open()) {
        cout << "Could not open file.  Program terminated." << endl;
        exit(0);
    }
    
    getline(inFS, userName);
    if (inFS.fail()) {
        cout << "There was no data in the file.  Program terminated." << endl;
        exit(0);
    }
    
    cout << left << fixed << showpoint << setprecision(2);
    cout << setw(25) << "Name" << setw(10) << "Years" << setw(16) << "Deposit Amount" << setw(16) << "Interest Earned" << setw(16) << "Total" << endl << endl;
        
    do {
        inFS >> depositAmount;
        inFS >> yearsDeposited;
        inFS>> compoundCode;

        interestRate = YearsToInterestRate(yearsDeposited);
        numCompound = CodeToCompoundInterest(compoundCode);
        amountWithInterest = CalculateDepositWithInterest(depositAmount, interestRate, yearsDeposited, numCompound);
        interestDollarAmount = amountWithInterest - depositAmount;

        cout << setw(25) << userName << setw(10) << (double)yearsDeposited << "$" << setw(15) << depositAmount << "$" << setw(15) << interestDollarAmount << "$" << setw(15) << amountWithInterest << endl;
        
        inFS.ignore(10, '\n');
    } while (getline(inFS, userName));

    inFS.close();
}

int main() {
    string depositsFileName;

    cout << "Enter File name: ";
    getline(cin, depositsFileName);
    cout << endl;

    ProcessDataFile(depositsFileName);

    cout << endl << "Thank you for using the interest calculation program.  Have a nice day." << endl;

    exit(0);
}
