#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Flight node structure
struct Flight {
    string flightNo;
    string destination;
    string status;
    Flight *next;
};

// Airport node structure
struct Airport {
    string airportCode;
    Flight *flightHead;
    int flightCount;
    Airport *next;
};

// Air Traffic Control system
class ATC {
private:
    Airport *airportHead;
    const int MAX_FLIGHTS = 10;

    // Helper function to check if flight exists in given airport
    bool flightExists(Airport* airport, const string& flightNum) {
        Flight* current = airport->flightHead;
        while (current) {
            if (current->flightNo == flightNum)
                return true;
            current = current->next;
        }
        return false;
    }

    void addFlight_FromLoad(string code, string flightnum, string dest, string status) {
        Airport *airport = findAirport(code);
        if (!airport) return;

        if (flightExists(airport, flightnum)) {
            cout << "Duplicate flight " << flightnum << " in " << code << " skipped during load.\n";
            return;
        }

        Flight *f_new = new Flight{flightnum, dest, status, NULL};
        if (!airport->flightHead) {
            airport->flightHead = f_new;
        } else {
            Flight *temp = airport->flightHead;
            while (temp->next)
                temp = temp->next;
            temp->next = f_new;
        }
        airport->flightCount++;
    }

public:
    ATC() {
        airportHead = NULL;
    }

    void addAirport(string code) {
        if (findAirport(code)) {
            cout << "Airport with code " << code << " already exists.\n";
            return;
        }

        Airport *newAirport = new Airport{code, NULL, 0, NULL};
        if (!airportHead) {
            airportHead = newAirport;
        } else {
            Airport *temp = airportHead;
            while (temp->next)
                temp = temp->next;
            temp->next = newAirport;
        }
        cout << "Airport " << code << " added.\n";
    }

    void removeAirport(string code) {
        Airport *cu = airportHead, *pr = NULL;
        while (cu) {
            if (cu->airportCode == code) {
                if (pr)
                    pr->next = cu->next;
                else
                    airportHead = cu->next;

                while (cu->flightHead) {
                    Flight *fTemp = cu->flightHead;
                    cu->flightHead = fTemp->next;
                    delete fTemp;
                }
                delete cu;
                cout << "Airport " << code << " removed.\n";
                return;
            }
            pr = cu;
            cu = cu->next;
        }
        cout << "Airport not found!\n";
    }

    void addFlight(string code, string flightNum, string dest) {
        Airport *airport = findAirport(code);
        if (!airport) {
            cout << "Airport not found.\n";
            return;
        }

        if (airport->flightCount >= MAX_FLIGHTS) {
            cout << "Cannot add more flights to " << code << ". Maximum limit of " << MAX_FLIGHTS << " reached.\n";
            return;
        }

        if (flightExists(airport, flightNum)) {
            cout << "Flight " << flightNum << " already exists in " << code << ".\n";
            return;
        }

        Flight *newFlight = new Flight{flightNum, dest, "On Time", NULL};
        if (!airport->flightHead) {
            airport->flightHead = newFlight;
        } else {
            Flight *temp = airport->flightHead;
            while (temp->next)
                temp = temp->next;
            temp->next = newFlight;
        }

        airport->flightCount++;
        cout << "Flight " << flightNum << " to " << dest << " added to " << code << ".\n";
    }

    void deleteFlight(string code, string flightNum) {
        Airport *airport = findAirport(code);
        if (!airport) {
            cout << "Airport not found!\n";
            return;
        }

        Flight *cu = airport->flightHead;
        Flight *pr = NULL;

        while (cu) {
            if (cu->flightNo == flightNum) {
                if (pr)
                    pr->next = cu->next;
                else
                    airport->flightHead = cu->next;
                delete cu;
                airport->flightCount--;
                cout << "Flight " << flightNum << " deleted from " << code << ".\n";
                return;
            }
            pr = cu;
            cu = cu->next;
        }
        cout << "Flight not found!\n";
    }

    void updateFlight(string code, string flightNum, string newDest) {
        Airport *airport = findAirport(code);
        if (!airport) {
            cout << "Airport not found!\n";
            return;
        }
        Flight *flight = airport->flightHead;
        while (flight) {
            if (flight->flightNo == flightNum) {
                flight->destination = newDest;
                cout << "Flight " << flightNum << " updated.\n";
                return;
            }
            flight = flight->next;
        }
        cout << "Flight not found!\n";
    }

    void display() {
        Airport *aTemp = airportHead;
        while (aTemp) {
            cout << "\nAirport: " << aTemp->airportCode
                 << " | Total Flights: " << aTemp->flightCount << "\n";

            Flight *fTemp = aTemp->flightHead;
            if (!fTemp) {
                cout << "  No flights scheduled.\n";
            } else {
                while (fTemp) {
                    cout << "  Flight: " << fTemp->flightNo
                         << " -> " << fTemp->destination
                         << " | Status: " << fTemp->status << "\n";
                    fTemp = fTemp->next;
                }
            }
            aTemp = aTemp->next;
        }
    }

    void saveTofile(const string& filename) {
        ofstream outfile(filename);
        if (!outfile.is_open()) {
            cout << "Error opening file for saving\n";
            return;
        }

        Airport *currentAirport = airportHead;
        while (currentAirport) {
            outfile << "============================================================\n";
            outfile << "Airport Code: " << currentAirport->airportCode << "\n";
            outfile << "Total Flights: " << currentAirport->flightCount << "\n";
            outfile << "------------------------------------------------------------\n";
            outfile << left << setw(15) << "Flight No"
                    << setw(25) << "Destination"
                    << setw(15) << "Status" << "\n";
            outfile << "------------------------------------------------------------\n";

            Flight *currentFlight = currentAirport->flightHead;
            if (!currentFlight) {
                outfile << "No flights scheduled.\n";
            } else {
                while (currentFlight) {
                    outfile << left << setw(15) << currentFlight->flightNo
                            << setw(25) << currentFlight->destination
                            << setw(15) << currentFlight->status << "\n";
                    currentFlight = currentFlight->next;
                }
            }

            outfile << "============================================================\n\n";
            currentAirport = currentAirport->next;
        }

        outfile.close();
        cout << "Data successfully saved to: " << filename << endl;
    }


    void loadFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile.is_open()) {
            cout << "No saved data is found / file is not available\n";
            return;
        }

        // Clear existing data
        while (airportHead) {
            Airport *atemp = airportHead;
            airportHead = atemp->next;
            while (atemp->flightHead) {
                Flight *ftemp = atemp->flightHead;
                atemp->flightHead = ftemp->next;
                delete ftemp;
            }
            delete atemp;
        }

        airportHead = NULL;

        string line, code, flightnum, dest, status;
        int flightcount;

        // Modified parsing logic to read file format generated by saveTofile
        while (getline(infile, line)) {
            if (line.find("Airport Code:") != string::npos) {
                code = line.substr(line.find(":") + 2);

                getline(infile, line); // Total Flights: X
                flightcount = stoi(line.substr(line.find(":") + 2));

                // Skip separator lines and headers
                getline(infile, line); // separator
                getline(infile, line); // headers
                getline(infile, line); // separator

                addAirport(code);

                if (flightcount > 0) {
                    for (int i = 0; i < flightcount; i++) {
                        if (!getline(infile, line)) break;

                        if (line == "No flights scheduled.") {
                            break;  // No flights here
                        }

                        // Parsing flight info lines - flightNo, destination, status by fixed widths
                        string flightNo = line.substr(0,15);
                        string destination = line.substr(15,25);
                        string status = line.substr(40);

                        // Trim trailing spaces
                        flightNo.erase(flightNo.find_last_not_of(" \n\r\t")+1);
                        destination.erase(destination.find_last_not_of(" \n\r\t")+1);
                        status.erase(status.find_last_not_of(" \n\r\t")+1);

                        addFlight_FromLoad(code, flightNo, destination, status);
                    }
                }
            }
        }

        infile.close();
        cout << "Data successfully loaded from " << filename << "\n";
    }

    Airport *findAirport(string code) {
        Airport *temp = airportHead;
        while (temp) {
            if (temp->airportCode == code)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }

    ~ATC() {
        while (airportHead) {
            Airport *aTemp = airportHead;
            airportHead = airportHead->next;

            while (aTemp->flightHead) {
                Flight *fTemp = aTemp->flightHead;
                aTemp->flightHead = fTemp->next;
                delete fTemp;
            }
            delete aTemp;
        }
    }
};

// Main function
int main() {
    ATC control;
    int choice;
    string code, flightNum, dest;
    string filename = "atc_data.txt";

    do {
        cout << "\n--- Air Control Menu ---\n";
        cout << "1. Add Airport\n";
        cout << "2. Remove Airport\n";
        cout << "3. Arriving Flight\n";
        cout << "4. Departing Flight\n";
        cout << "5. Update Flight\n";
        cout << "6. Display All\n";
        cout << "7. Save to file\n";
        cout << "8. Load from file\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter airport code: ";
                cin >> code;
                control.addAirport(code);
                break;
            case 2:
                cout << "Enter airport code to remove: ";
                cin >> code;
                control.removeAirport(code);
                break;
            case 3:
                cout << "Enter airport code: ";
                cin >> code;
                cout << "Enter flight number: ";
                cin >> flightNum;
                cout << "Enter destination: ";
                cin >> dest;
                control.addFlight(code, flightNum, dest);
                break;
            case 4:
                cout << "Enter airport code: ";
                cin >> code;
                cout << "Enter flight number to delete: ";
                cin >> flightNum;
                control.deleteFlight(code, flightNum);
                break;
            case 5:
                cout << "Enter airport code: ";
                cin >> code;
                cout << "Enter flight number to update: ";
                cin >> flightNum;
                cout << "Enter new destination: ";
                cin >> dest;
                control.updateFlight(code, flightNum, dest);
                break;
            case 6:
                control.display();
                break;
            case 7:
                control.saveTofile(filename);
                break;
            case 8:
                control.loadFromFile(filename);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
