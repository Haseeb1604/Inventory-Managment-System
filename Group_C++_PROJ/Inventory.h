#pragma once
#ifndef INNEMTORY_H_
#define INNEMTORY_H_

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

time_t convertStringtoTime(string str);

string convertTimetoString(time_t time);

class FoodItem {
public:
    string name;
    string category;
    int quantity;
    string barcode;
    // time_t is not the default data structure/variable type so we have to use a library in header file i.e. #include <ctime>
    // time_t is to store date and time 
    time_t expiryDate;

    // Constructor will initialize values
    FoodItem(string name, string category, int quantity, string barcode, time_t expiryDate);

    // This function will compare the expiryDate with todays data and will return true if date already has passed
    bool isExpired();

    // This function will use threshold date which will be the limit set to check for expiring dates and will compare it 
    // with that threshold date and will return true if the threshold date is higher than expiryDate
    bool isExpiring(int date);
};


class FileManagment {
private:
    string filename;
    vector <FoodItem> items;

public:
    FileManagment(string filename);

    vector<FoodItem> ReadCSV();

    void WriteCSV(vector<FoodItem> items);
};

class Inventory {
private:
    vector<FoodItem> items;
    FileManagment* FM; // Pointer to FileManagment instance/class

public:
	// Inventory() this is Constructor which will be called when the object of this class in created
    Inventory();

	// ~Inventory() is a Destructor which will be called when the object is closed 
    ~Inventory();

    void addFoodItems(string name, string category, int quantity, string barcode, time_t expiryDate);

    void editFoodItems(string barcode, string name, string category, int quantity, time_t expiryDate);

    void deleteFoodItems(string Barcode);

    void SearchItems(string Barcode);

    void DisplayWornings();

    void Display();

    void Prioritise();

};

#endif
