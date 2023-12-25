#define _CRT_SECURE_NO_WARNINGS
#include "Inventory.h"

using namespace std;

time_t convertStringtoTime(string str) {
    // Declaring tm struct and initializes it to zeros 
    // tm is a C++ struct that represents a broken-down time
    // tm struct in present in ctime header file 
    tm tm = {}; 
    // istringstream is a special type of input stream that reads from a string
    istringstream ss(str);
    // get_time extracts values from a stream using a specified format, and stores them in a provided tm struct.
    // 2023-04-26
	//    >> extract data from stringstream
	//    << store data in stringstream
    ss >> get_time(&tm, "%Y-%m-%d");
    // mktime() function takes a pointer to a tm struct, and returns a time_t value 
    // representing the corresponding time in seconds since the Unix epoch
    time_t time = mktime(&tm);
    return time;
}


string convertTimetoString(time_t time) {
    // The localtime() function is used to convert time_t value to a broken-down time representation in the tm struct.
    tm* date = localtime(&time);
    // This array will be used to store the string representation of the date
    char output[11];
    // strftime() function to format the tm struct pointed to by date into a string according to the specified format string
    strftime(output, sizeof(output), "%Y-%m-%d", date);
    return output;
}

FileManagment::FileManagment(string filename){
	// storing file name in filename variable
    this->filename = filename;
}

vector<FoodItem> FileManagment::ReadCSV() {
	// ifstream is a class in fstream header file
    ifstream file(filename);
    
    // Checking whether the file already exist or not
    if (file.good()) {
        string fileData, name, category, barcode;
        int quantity;
        time_t date;

        // Extracting line by line data from file and storing it in fileData
        // each line from file will be stored in fileData
        while (getline(file, fileData)) {
        	// fileData is a string Variable which will contain only one line data
        	// mango, fruit, 5, #b1234, 2023-03-03
        	
        	// stringstream is a class in sstream header file
            stringstream ss(fileData); // Each line contains different data seperated by `,`
            vector<string> tokens; 
            string token;

            // Extracting each variable data seperated by `,` and storing it in tokens 
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            name = tokens[0];
            category = tokens[1];
            quantity = stoi(tokens[2]); // converting string to int
            barcode = tokens[3];
            date = convertStringtoTime(tokens[4]); // conversion to time_t format
            
            items.emplace_back(name, category, quantity, barcode, date); // pushing data to a vector of FoodItems
        }
    }

    file.close();

    return items;
}

void FileManagment::WriteCSV(vector<FoodItem> items) {
    ofstream file(filename);
    // Saving each item data seperated by `,` 
    for (auto item : items) {
    	// << store data to stream
    	// >> extract data from stream
        file << item.name << "," << item.category << "," << item.quantity << "," << item.barcode << "," << convertTimetoString(item.expiryDate) << endl;
    }
    file.close();
}

FoodItem::FoodItem(string name, string category, int quantity, string barcode, time_t expiryDate) {
	// this-> is an arrow method to tell the class which variable is class attribute and which one is parameter to contrustor
    this->name = name;
    this->category = category;
    this->quantity = quantity;
    this->expiryDate = expiryDate;
    this->barcode = barcode;
}

bool FoodItem::isExpired() {
	// utilizating time function from ctime library 
	// passing NULL to time function this will return the current time 
    time_t now = time(NULL);
    return expiryDate < now;
}

bool FoodItem::isExpiring(int date = 1) {
    time_t now = time(NULL);
    time_t Threshold = now + date * 24 * 60 * 60; // threshold = Todays day+ 1 day
    return expiryDate < Threshold;
}

Inventory::Inventory() {
    FM = new FileManagment("Inventory.csv");
    // We are using arrow method to access function of class since FM is a pointer to FileManagment class
    items = FM->ReadCSV();
}

Inventory::~Inventory() {
	// when we exit our program the destructor of Inventory Class will call and in this destructor we are passing our vector of Food Items i.e. items to
	// a function of class FileManagment which is WriteCSV that will save data to our csv file
	// we are using arrow operator to access the function since FM is pointer to FileManagment class
    FM->WriteCSV(items);
}

void Inventory::addFoodItems(string name, string category, int quantity, string barcode, time_t expiryDate) {
	// storing data in vector of Food Items i.e. items
    items.emplace_back(name, category, quantity, barcode, expiryDate);
}

// editing data based on barcode
void Inventory::editFoodItems(string barcode, string name, string category, int quantity, time_t expiryDate) {
    int index = 0;
	for (auto item : items) {
		// find method will compare barcode with barcode of every item if it matchs we will update data based on passed variables
		if (item.barcode.find(barcode) != string::npos) {
			items[index].name = name;
	        items[index].category = category;
	        items[index].quantity = quantity;
	        items[index].barcode = barcode;
	        items[index].expiryDate = expiryDate;
	        cout << "Successfully Edited the Volme at the defined index\n";
		}
		index++;
    }
}

void Inventory::deleteFoodItems(string Barcode) {
    int index = 0;
    if (Barcode.length() == 6) {
        for (auto item : items) {
            // find method matchs the string it will return 1 if the its match else 
            // the function will return value equal to string::npos. It is a special value that represents 
            // the "not found" condition in string searching functions.
            if (item.barcode.find(Barcode) != string::npos) {
            	// begin() will show the memory location from where the vector starts
                items.erase(items.begin() + index);
                cout << "Successfuly deleted that Food Item(s)\n";
            }
            index++;
        }
    }
    else {
        cout << "Invalid Barcode!\n";
    }
    
}
void Inventory::SearchItems(string Barcode) {
    cout << setw(15) << left << " Name" << setw(15) << left << "Category" << setw(15) << left << "Barcode" << setw(15) << left << "ExpiryDate" << endl;
    for (auto item :items) {
        // #b1234 | #b123
        if (item.barcode.find(Barcode) != string::npos) {
            cout << setw(15) << left <<item.name<< setw(15) << left << item.category << setw(15) << left <<item.barcode<<setw(15)<<left<< convertTimetoString(item.expiryDate) << endl;
        }
    }
}
void Inventory::Prioritise() {
    // Sort function will sort the items based on the lambda function passed
    // In Lambda function we will pass references to two of the items in vector of Food Item
    // After that it will check both items expiry dates and will sort it accordingly
    sort(items.begin(), items.end(), [](const FoodItem& a, const FoodItem& b) {
        return a.expiryDate < b.expiryDate;
     });

}

void Inventory::DisplayWornings() {
    cout << "Warning! These food item(s) is/are expired or expiring soon, please deal with it " << endl;
    cout << setw(15) << left << "Index" << setw(15) << left << "Name" << setw(15) << left << "Barcode" << setw(15) << left
        << "Status" << setw(15) << left << "Expiry Date" << endl;
    int index = 0;
    for (auto item : items) {
        if (item.isExpired()) {
            cout << setw(15) << left << index+1 << setw(15) << left << item.name << setw(15) << left << item.barcode
                << setw(15) << left << "Expired" << left << convertTimetoString(item.expiryDate) << endl;
        }
        else
            if (item.isExpiring()) {
                cout << setw(15) << left << index+1 << setw(15) << left << item.name << setw(15) << left << item.barcode
                    << setw(15) << left << "Expiring" << left << convertTimetoString(item.expiryDate) << endl;
            }
        index++;

    }
}

void Inventory::Display() {
    cout << "Our stock Balance is \n";
    // setw is a function used to control the output formatting of data. It sets the width of the next output field
    cout << setw(15) << left << " Index" << setw(15) << left << " Name" << setw(15) << left << "Category" << setw(15) << left << "Quantity" << setw(15) << left << "Barcode" << setw(15) << left
        << "Expiry Date" << endl;
    int index = 0;
    for (auto item : items) {
        // Using convertTimetoString function to display the time in user understandable format
        cout << setw(15) << left << index+1 << setw(15) << left << item.name << setw(15) << left << item.category << setw(15) << left << item.quantity << setw(15) << left << item.barcode
            << setw(15) << left << convertTimetoString(item.expiryDate) << endl;
        index++;
    }
}
