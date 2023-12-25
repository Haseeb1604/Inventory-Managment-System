# Inventory Management System Documentation

## Overview:

The Inventory Management System is a C++ application designed to efficiently manage and organize information about food items in a stock inventory. The system employs file handling techniques to read and write data to a CSV file, ensuring persistent storage and retrieval of inventory details.

## Key Features:

### 1. **Real-Time Data Handling:**
   - **FileManagment Class:** Manages the reading and writing of inventory data to a CSV file.
   - **CSV Format:** Data is stored in a CSV format for easy human readability and manipulation.

### 2. **Efficient Data Storage:**
   - **FoodItem Class:** Represents individual food items with attributes such as name, category, quantity, barcode, and expiry date.
   - **Time Handling:** Utilizes the `time_t` data structure for storing and comparing date and time information.

### 3. **User Interaction:**
   - **Menu-Driven Interface:** The main.cpp file provides a user-friendly menu-driven interface for interacting with the inventory system.
   - **Input Validation:** Ensures valid input for critical operations like barcode entry.

### 4. **CRUD Operations:**
   - **Add Food Items:** Enables the addition of new food items to the inventory.
   - **Edit Food Items:** Allows for the modification of existing food item details based on barcode.
   - **Delete Food Items:** Permits the removal of food items from the inventory using the barcode.
   - **Display Inventory:** Shows a comprehensive list of all items in the inventory.

### 5. **Date Handling:**
   - **Date Conversion Functions:** Includes functions to convert strings to `time_t` format and vice versa for efficient date handling.
   - **Expiry Warnings:** Displays warnings for expired or soon-to-expire items.

### 6. **Sorting:**
   - **Prioritize Inventory:** Utilizes the `sort` function to prioritize inventory items based on expiry dates.

## Code Structure:

### 1. **Inventory Class:**
   - Manages the overall inventory, including reading and writing data to the CSV file.
   - Implements core operations such as adding, editing, and deleting food items.

### 2. **FileManagment Class:**
   - Handles file-related operations, including reading data from and writing data to the CSV file.

### 3. **FoodItem Class:**
   - Represents individual food items with attributes and includes methods for checking expiration and imminent expiry.

## Usage:

1. **Add Food Items:**
   - Enter the name, category, barcode, quantity, and expiry date to add a new item to the inventory.

2. **Edit Food Items:**
   - Modify the details of an existing item using its barcode.

3. **Delete Food Items:**
   - Remove items from the inventory based on their barcode.

4. **Display Warnings:**
   - View a list of items that are either expired or nearing expiry.

5. **Display Inventory:**
   - See a comprehensive list of all items in the inventory.

6. **Search Food Item:**
   - Find and display specific items based on their barcode.

7. **Prioritize Inventory:**
   - Sort the inventory based on expiry dates.

8. **Exit:**
   - Safely exit the application, ensuring that the data is saved to the CSV file.

## Conclusion:

The Inventory Management System provides a robust and user-friendly solution for businesses or individuals to keep track of their stock. With features like real-time data handling, efficient storage, and user interaction, it offers a reliable and practical tool for managing inventory effectively.
