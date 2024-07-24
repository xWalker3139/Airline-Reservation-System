// Including header files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Base Class
class Person {
protected:
    string username;
    string password;
public:
    Person(const string& user, const string& pass) : username(user), password(pass) {}
    virtual void display() const = 0;

    string getUsername() const { return username; }
    string getPassword() const { return password; }
};

class Passenger : public Person {
private:
    string passengerID;
public:
    Passenger(const string& user, const string& pass, const string& id) : Person(user, pass), passengerID(id) {}
    void display() const override {
        cout << "Passenger ID: " << passengerID << "\nUsername: " << username << endl;
    }

    string getPassengerID() const { return passengerID; }
};

class Admin : public Person {
public:
    Admin(const string& user, const string& pass) : Person(user, pass) {}
    void display() const override {
        cout << "Admin Username: " << username << endl;
    }
};

// Flight Class
class Flight {
private:
    string flightID;
    string origin;
    string destination;
    int availableSeats;
public:
    Flight(const string& id, const string& orig, const string& dest, int seats) 
        : flightID(id), origin(orig), destination(dest), availableSeats(seats) {}

    void displayFlightDetails() const {
        cout << "Flight ID: " << flightID 
             << "\nOrigin: " << origin 
             << "\nDestination: " << destination 
             << "\nAvailable Seats: " << availableSeats << endl;
    }

    string getFlightID() const { return flightID; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    int getAvailableSeats() const { return availableSeats; }
};

void showDetails(const Person* person) {
    person->display();
}

void savePassenger(const Passenger& p) {
    ofstream outFile("passengers.txt", ios::app);
    outFile << p.getUsername() << " " << p.getPassword() << " " << p.getPassengerID() << endl;
    outFile.close();
}

void loadPassengers(vector<Passenger>& passengers) {
    ifstream inFile("passengers.txt");
    string user, pass, id;
    while (inFile >> user >> pass >> id) {
        passengers.emplace_back(user, pass, id);
    }
    inFile.close();
}

bool authenticateUser(const string& username, const string& password, const vector<Passenger>& passengers) {
    for (const auto& p : passengers) {
        if (p.getUsername() == username && p.getPassword() == password) {
            return true;
        }
    }
    return false;
}

void saveFlight(const Flight& f) {
    ofstream outFile("flights.txt", ios::app);
    outFile << f.getFlightID() << " " << f.getOrigin() << " " << f.getDestination() << " " << f.getAvailableSeats() << endl;
    outFile.close();
}

void loadFlights(vector<Flight>& flights) {
    ifstream inFile("flights.txt");
    string id, orig, dest;
    int seats;
    while (inFile >> id >> orig >> dest >> seats) {
        flights.emplace_back(id, orig, dest, seats);
    }
    inFile.close();
}

int main() {
    vector<Passenger> passengers;
    loadPassengers(passengers);

    string user, pass;
    cout << "Enter username: ";
    cin >> user;
    cout << "Enter password: ";
    cin >> pass;

    if (authenticateUser(user, pass, passengers)) {
        cout << "Login successful!" << endl;
    } else {
        cout << "Login failed!" << endl;
    }

    // Right here I create a sample data
    Passenger p1("passenger1", "pass123", "P001");
    Admin a1("admin1", "admin123");
    Flight f1("F001", "New York", "London", 150);

    showDetails(&p1);
    showDetails(&a1);
    f1.displayFlightDetails();

    savePassenger(p1);
    saveFlight(f1);

    return 0;
}
