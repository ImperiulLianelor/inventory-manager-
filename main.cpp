#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
constexpr int MAX_NAME_LEN = 20;
constexpr int MAX_NUMBER_LEN = 20;
constexpr int MAX_PRODUCTS = 10001;

class Product {
private:
    std::string name;
    std::string exp;
    std::string id;
    std::string cat;
    std::string q;

public:
    // Default constructor
    Product() {}

    // Parameterized constructor
    Product(const std::string& productName, const std::string& expirationDate,
            const std::string& productId, const std::string& category,
            const std::string& quantity)
        : name(productName), exp(expirationDate), id(productId),
          cat(category), q(quantity) {}

    // Getter and setter methods for each member variable
    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    std::string getExpirationDate() const { return exp; }
    void setExpirationDate(const std::string& newExpDate) { exp = newExpDate; }

    std::string getId() const { return id; }
    void setId(const std::string& newId) { id = newId; }

    std::string getCategory() const { return cat; }
    void setCategory(const std::string& newCategory) { cat = newCategory; }

    std::string getQuantity() const { return q; }
    void setQuantity(const std::string& newQuantity) { q = newQuantity; }

};

Product v[MAX_PRODUCTS];
int count = 0;

void readProductsFromFile() {
    std::ifstream inputFile("products.csv");

    if (!inputFile) {
        std::cout << "Error: could not open file" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\n') {
            line.pop_back();
        }
        std::istringstream iss(line);

        std::string data;
        std::getline(iss, data, ' ');
        v[count].setName(data);
        std::getline(iss, data, ' ');
        v[count].setId(data);
        std::getline(iss, data, ' ');
        v[count].setExpirationDate(data);
        std::getline(iss, data, ' ');
        v[count].setCategory(data);
        std::getline(iss, data, ' ');
        v[count].setQuantity(data);

        count++;
    }

    inputFile.close();
}

void writeProductsToFile() {
    std::ofstream outputFile("products.csv", std::ofstream::out);
    if (!outputFile) {
        std::cout << "Error: could not open file" << std::endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        outputFile << v[i].getName() << ' ' << v[i].getId() << ' ' << v[i].getExpirationDate() << ' ' << v[i].getCategory() << ' ' << v[i].getQuantity() << '\n';
    }

    outputFile.close();
}

void searchProduct() {
    std::cout << "SEARCH PRODUCT" << std::endl;
    std::cout << "Enter product's unique code: ";
    std::string id;
    std::cin >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (v[i].getId() == id) {
            found = true;
            std::cout << std::left << std::setw(20) << "Name" << std::setw(20) << "ID" << std::setw(20) << "Expiration"
                      << std::setw(20) << "Category" << std::setw(20) << "Quantity" << std::endl;
            std::cout << std::setw(20) << v[i].getName() << std::setw(20) << v[i].getId() << std::setw(20) << v[i].getExpirationDate()
                      << std::setw(20) << v[i].getCategory() << std::setw(20) << v[i].getQuantity() << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "Product with code " << id << " not found" << std::endl;
    }

    std::cin.ignore();
    std::cin.get();
}


void displayInventory() {
    std::cout << "INVENTORY" << std::endl;
    std::cout << std::left << std::setw(20) << "Name" << std::setw(20) << "ID" << std::setw(20) << "Expiration"
              << std::setw(20) << "Category" << std::setw(20) << "Quantity" << std::endl;
    for (int i = 0; i < count; i++) {
        std::cout << std::setw(20) << v[i].getName() << std::setw(20) << v[i].getId() << std::setw(20) << v[i].getExpirationDate()
                  << std::setw(20) << v[i].getCategory() << std::setw(20) << v[i].getQuantity() << std::endl;
    }
    std::cin.ignore();
    std::cin.get();
}

void addProduct() {
    std::cout << "ADD PRODUCT" << std::endl;
    std::cout << "Product name: ";
    std::string name;
    std::cin >> name;
    std::cout << "Product's unique code: ";
    std::string id;
    std::cin >> id;

    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm* currentTime = std::localtime(&nowTime);

    // Input validation for expiration date
    std::string exp;
    bool validDate = false;
    while (!validDate) {
        std::cout << "Enter expiration date (format: DD/MM/YY): ";
        std::cin >> exp;

        // Convert the input to a std::tm object
        std::istringstream iss(exp);
        std::tm expTime = {};
        iss >> std::get_time(&expTime, "%m/%d/%Y");

        if (iss.fail()) {
            std::cout << "Error: Invalid date format. Please enter a valid expiration date." << std::endl;
        }
        else {
            // Check if the expiration date is in the future
            if (expTime.tm_year >= currentTime->tm_year && expTime.tm_mon >= currentTime->tm_mon && expTime.tm_mday > currentTime->tm_mday) {
                validDate = true;
            }
            else {
                std::cout << "Error: Expiration date must be in the future. Please enter a valid expiration date." << std::endl;
            }
        }
    }

    std::cout << "Enter category name: ";
    std::string cat;
    std::cin >> cat;
    std::cout << "Enter the quantity: ";
    std::string q;
    std::cin >> q;


    for (int i = 0; i < count; i++) {
        if (v[i].getId() == id) {
            std::cout << "Error: product with code " << id << " already exists" << std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        }
    }

    v[count].setName(name);
    v[count].setId(id);
    v[count].setExpirationDate(exp);
    v[count].setCategory(cat);
    v[count].setQuantity(q);
    count++;
    writeProductsToFile();
    std::cout << "The product has been successfully added" << std::endl;
    std::cin.ignore();
    std::cin.get();
}

void sellProduct() {
    std::cout << "SELL PRODUCT" << std::endl;
    std::cout << "Enter product code: ";
    std::string id;
    std::cin >> id;

    for (int i = 0; i < count; i++) {
        if (v[i].getId() == id) {
            std::cout << "Enter the quantity: ";
            int soldQuantity;
            std::cin >> soldQuantity;
            int inventoryQuantity = std::stoi(v[i].getQuantity());

            if (soldQuantity > inventoryQuantity) {
                std::cout << "Error: not enough stock available" << std::endl;
                std::cin.ignore();
                std::cin.get();
                return;
            } else {
                inventoryQuantity -= soldQuantity;
                v[i].setQuantity(std::to_string(inventoryQuantity));
                writeProductsToFile();
                std::cout << "Sale recorded successfully" << std::endl;
                std::cin.ignore();
                std::cin.get();
                return;
            }
        }
    }

    std::cout << "Error: product with code " << id << " not found" << std::endl;
    std::cin.ignore();
    std::cin.get();
}

int main() {
    std::cout << "STORE INVENTORY PROGRAM" << std::endl;
    readProductsFromFile();
    std::cout << "STORE INVENTORY PROGRAM" << std::endl;

    while (true) {
        system("cls");
        std::cout << "STORE INVENTORY PROGRAM" << std::endl;
        std::cout << "1. Display inventory" << std::endl;
        std::cout << "2. Add a new product" << std::endl;
        std::cout << "3. Sell a product" << std::endl;
        std::cout << "4. Search for a product" << std::endl;
        std::cout << "5. Exit program" << std::endl;
        std::cout << "Enter your choice (1-5): ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayInventory();
                break;
            case 2:
                addProduct();
                break;
            case 3:
                sellProduct();
                break;
            case 4:
                searchProduct();
                break;
            case 5:
                std::cout << "Exiting" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
                std::cin.ignore();
                std::cin.get();
                break;
        }
    }

    return 0;
}
