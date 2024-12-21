#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Base User class
class User {
protected:
    string name;
    string email;

public:
    User(string name, string email) : name(name), email(email) {}
    virtual void displayDetails() {
        cout << "Name: " << name << "\nEmail: " << email << endl;
    }
};

// Customer class inheriting User
class Customer : public User {
private:
    vector<string> orderHistory;

public:
    Customer(string name, string email) : User(name, email) {}

    void placeOrder(string order) {
        orderHistory.push_back(order);
        cout << name << " placed an order: " << order << endl;
    }

    void viewOrderHistory() {
        cout << "Order History for " << name << ":\n";
        for (const string &order : orderHistory) {
            cout << "- " << order << endl;
        }
    }
};

// Restaurant class
class Restaurant {
private:
    string name;
    map<string, double> menu;

public:
    Restaurant(string name) : name(name) {}

    void addMenuItem(string item, double price) {
        menu[item] = price;
    }

    void displayMenu() {
        cout << "Menu for " << name << ":\n";
        for (const auto &item : menu) {
            cout << item.first << " - $" << item.second << endl;
        }
    }

    double getItemPrice(string item) {
        return menu.count(item) ? menu[item] : -1;
    }
};

// Delivery Person class inheriting User
class DeliveryPerson : public User {
private:
    string currentOrder;

public:
    DeliveryPerson(string name, string email) : User(name, email), currentOrder("") {}

    void assignOrder(string order) {
        currentOrder = order;
        cout << name << " assigned to deliver order: " << order << endl;
    }

    void completeOrder() {
        cout << name << " completed delivery of: " << currentOrder << endl;
        currentOrder = "";
    }
};

// Main System class
class FoodOrderingSystem {
private:
    vector<Customer> customers;
    vector<Restaurant> restaurants;
    vector<DeliveryPerson> deliveryPersons;

public:
    void addCustomer(string name, string email) {
        customers.emplace_back(name, email);
    }

    void addRestaurant(string name) {
        restaurants.emplace_back(name);
    }

    void addDeliveryPerson(string name, string email) {
        deliveryPersons.emplace_back(name, email);
    }

    void showRestaurants() {
        cout << "Available Restaurants:\n";
        for (size_t i = 0; i < restaurants.size(); ++i) {
            cout << i + 1 << ". " << restaurants[i].name << endl;
        }
    }

    void placeOrder(size_t customerId, size_t restaurantId, string item) {
        if (customerId >= customers.size() || restaurantId >= restaurants.size()) {
            cout << "Invalid customer or restaurant ID.\n";
            return;
        }

        double price = restaurants[restaurantId].getItemPrice(item);
        if (price == -1) {
            cout << "Item not available at the selected restaurant.\n";
            return;
        }

        customers[customerId].placeOrder(item);

        if (!deliveryPersons.empty()) {
            deliveryPersons[0].assignOrder(item); // Assign to the first available delivery person
        } else {
            cout << "No delivery person available currently.\n";
        }
    }
};

int main() {
    FoodOrderingSystem system;

    // Add sample restaurants and menu items
    system.addRestaurant("Pizza Palace");
    system.addRestaurant("Burger Bistro");

    system.restaurants[0].addMenuItem("Pepperoni Pizza", 12.99);
    system.restaurants[0].addMenuItem("Cheese Pizza", 10.99);
    system.restaurants[1].addMenuItem("Classic Burger", 8.99);
    system.restaurants[1].addMenuItem("Veggie Burger", 7.99);

    // Add customers and delivery personnel
    system.addCustomer("Alice", "alice@example.com");
    system.addCustomer("Bob", "bob@example.com");
    system.addDeliveryPerson("Eve", "eve@example.com");

    // Simulation
    system.showRestaurants();
    system.placeOrder(0, 0, "Pepperoni Pizza"); // Alice orders from Pizza Palace

    return 0;
}
