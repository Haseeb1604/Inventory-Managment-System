// PROJECT_C++.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define _CRT_SECURE_NO_WARNINGS


#include "Inventory.h"
#include <iostream>
// fstream is used for filehandling
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
// algorithm is imported for sort function that is used in prioritize function of inventory class
#include <algorithm>
// sstream is used for string stream operation
#include <sstream>


using namespace std;


int main()
{
    Inventory inventory;

    bool isExit = false;

    while (!isExit) {
        system("cls");
        cout << "Menu\n";
        cout << " 1) Add Food Items\n";
        cout << " 2) Edit Food Items\n";
        cout << " 3) Delete Food Items\n";
        cout << " 4) Display Warnings\n";
        cout << " 5) Display Inventory\n";
        cout << " 6) Search Food Item\n";
        cout << " 7) Prioritise Inventory\n";
        cout << " 0) Exit\n";
        cout << " Choice : ";
        // to automit the system change the hard coding to soft coding.
        int choice;
        cin >> choice;

        string name, category,barcode,expiryDate;
        int quantity, index;
        switch (choice) {
        case 1:
            cout << "Add Food Items\n";
            cout << "Enter Name : ";     cin >> name;
            cout << "Enter Category : "; cin >> category;
            cout << "Enter Barcode (6 Digit) : ";
            cin >> barcode;
            cout << "Enter Quantity : ";
            cin >> quantity;
            cout << "Enter ExpiryDate (YYYY-MM-DD) : ";
            cin >> expiryDate;
            inventory.addFoodItems(name, category, quantity, barcode, convertStringtoTime(expiryDate));
            system("pause");
            break;
        case 2:
            cout << "Edit Food Items\n";
            cout << "Enter Barcode : ";    cin >> barcode;
            if(barcode.length() !=6){
            	cout<<"Barcode is not valid\n";
			}else{
				cout << "Enter Name : ";     cin >> name;
                cout << "Enter Category : "; cin >> category;
                cout << "Enter Quantity : "; cin >> quantity;
                cout << "Enter ExpiryDate (YYYY-MM-DD) : ";
                cin >> expiryDate;
                inventory.editFoodItems(barcode, name, category, quantity, convertStringtoTime(expiryDate));	
			}
            system("pause");
            break;
        case 3:
            cout << "Deleting Food Item\n";
            cout << "Enter Barcode (6 Digit)s : ";
            cin >> barcode;
            inventory.deleteFoodItems(barcode);
            system("pause");
            break;
        case 4:
            inventory.DisplayWornings();
            system("pause");
            break;
        case 5:
            inventory.Display();
            system("pause");
            break;
        case 6:
            cout << "Search Food Item\n";
            cout << "enter Barcode of The Food Item\n";
            cin >> barcode;
            inventory.SearchItems(barcode);
            system("pause");
            break;
        case 7:
            inventory.Prioritise();
            system("pause");
            break;
        case 0:
            isExit = true;
            break;
        default:
            cout << "Invalid Option\n";
        }
    }

}
