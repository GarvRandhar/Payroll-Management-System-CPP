#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct Employee {
    string firstname;
    string lastname;
    int eno;
    float grossPay;
    float netPay;
};

void displaySystemTitle() {
    cout << "|-------------------------------------------------------|" << endl;
    cout << "|       WELCOME TO THE PAYROLL MANAGEMENT SYSTEM        |" << endl;
    cout << "|-------------------------------------------------------|" << endl;
}

float calculateGrossPay(float rate, int hour, int day, float over, float overh) {
    return (rate * hour * day) + (over * overh);
}

float calculateNetPay(float grossPay, float taxRate) {
    return grossPay - (grossPay * taxRate);
}

void displayPayslip(const Employee& emp) {
    cout << "\n|--------------------------------------------------|" << endl;
    cout << "|      :::::::::: Employee Payslip ::::::::::      |" << endl;
    cout << "|--------------------------------------------------|" << endl;
    cout << "Employee Name: \t\t" << emp.firstname << " " << emp.lastname << endl;
    cout << "Employee Number: \t\t" << emp.eno << endl;
    cout << fixed << setprecision(2);
    cout << "Gross Pay: \t\t\tPhp " << emp.grossPay << endl;
    cout << "Net Pay (after tax): \tPhp " << emp.netPay << endl;
    cout << "|--------------------------------------------------|\n" << endl;
}

void savePayslipToFile(const Employee& emp) {
    ofstream file("payslips.txt", ios::app);
    if (file.is_open()) {
        file << "|--------------------------------------------------|\n";
        file << "|      :::::::::: Employee Payslip ::::::::::      |\n";
        file << "|--------------------------------------------------|\n";
        file << "Employee Name: \t\t" << emp.firstname << " " << emp.lastname << "\n";
        file << "Employee Number: \t\t" << emp.eno << "\n";
        file << fixed << setprecision(2);
        file << "Gross Pay: \t\t\tPhp " << emp.grossPay << "\n";
        file << "Net Pay (after tax): \tPhp " << emp.netPay << "\n";
        file << "|--------------------------------------------------|\n\n";
        file.close();
    } else {
        cout << "Error: Unable to open file to save payslip.\n";
    }
}

int main() {
    vector<Employee> employees;
    char choice;
    const float taxRate = 0.10f; 

    displaySystemTitle();

    do {
        string firstname, lastname;
        int eno, hour, day;
        float rate, over, overh;

        cout << "\nEnter Employee's First Name: ";
        cin >> firstname;
        cout << "Enter Employee's Last Name: ";
        cin >> lastname;
        cout << "Enter Employee Number: ";
        cin >> eno;

        cout << "Enter Basic Rate Per Hour: ";
        cin >> rate;
        if (rate < 0) {
            cout << "Error: Rate cannot be negative.\n";
            continue;
        }

        cout << "Enter Number of Hours Worked Per Day: ";
        cin >> hour;
        if (hour < 0) {
            cout << "Error: Hours cannot be negative.\n";
            continue;
        }

        cout << "Enter Number of Days Worked: ";
        cin >> day;
        if (day < 0) {
            cout << "Error: Days cannot be negative.\n";
            continue;
        }

        cout << "Enter Overtime Rate Per Hour: ";
        cin >> over;
        if (over < 0) {
            cout << "Error: Overtime rate cannot be negative.\n";
            continue;
        }

        cout << "Enter Number of Overtime Hours: ";
        cin >> overh;
        if (overh < 0) {
            cout << "Error: Overtime hours cannot be negative.\n";
            continue;
        }

        float grossPay = calculateGrossPay(rate, hour, day, over, overh);
        float netPay = calculateNetPay(grossPay, taxRate);

        Employee emp = {firstname, lastname, eno, grossPay, netPay};
        employees.push_back(emp);

        displayPayslip(emp);
        savePayslipToFile(emp);

        cout << "Enter 'C' to input another employee or any other key to exit: ";
        cin >> choice;

    } while (choice == 'C' || choice == 'c');

    cout << "\nThank you for using the Payroll Management System!\n";
    return 0;
}
