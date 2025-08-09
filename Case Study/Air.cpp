//Air traffic control system
#include<iostream>
using namespace std;

//inner list
//For flight
struct Flight {
    string flightNo;
    string destination;
    Flight *next;
};

//outer list
//For airport
struct Airport {
    string airportCode;
    Flight *flightHead; //head of flight linked list
    Airport *next;
};

class ATC {
private:
    Airport *airportHead;
    
public:
    ATC() {
        airportHead = NULL;
    }
    
    //add airport
    void addAirport(string code) {
        Airport *newAirport = new Airport{code, NULL, NULL};
        
        if(!airportHead) {
            airportHead = newAirport;
        }
        else {
            Airport *temp = airportHead;
            while(temp->next)
                temp = temp->next;
            temp->next = newAirport;
        }
        
        cout<<"Airport "<<code<<" added.\n";
    }
    
    //add flight to airport
    void addFlight(string code, string flightNum, string dest) {
        Airport *airport = findAirport(code);
        
        if(!airport) {
            cout<<"Airport not found.\n";
            return;
        }
        
        Flight *newFlight = new Flight{flightNum, dest, NULL};
        if(!airport->flightHead) {
            airport->flightHead = newFlight;
        }
        else {
            Flight *temp = airport->flightHead;
            while(temp->next)
                temp = temp->next;
            temp->next = newFlight;
        }
        
        cout<<"Flight "<<flightNum<<" to "<<dest<<" added to "<<code<<".\n";
    }
    
    //display airports and flights
    void display() {
        Airport *aTemp = airportHead;
        while(aTemp) {
            cout<<"Airport: "<<aTemp->airportCode<<"\n";
            Flight *fTemp = aTemp->flightHead;
            if(!fTemp) {
                cout<<"No flights scheduled.\n";
            }
            else {
                while(fTemp) {
                    cout<<"Flight: "<<fTemp->flightNo<<" -> "<<fTemp->destination<<"\n";
                    fTemp = fTemp->next;
                }
            }
            aTemp = aTemp->next;
        }
    }
    
    //find airport by code
    Airport *findAirport(string code) {
        Airport *temp = airportHead;
        while(temp) {
            if(temp->airportCode == code)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }
    
    ~ATC() {
        while(airportHead) {
            Airport *aTemp = airportHead;
            airportHead = airportHead->next;
            
            while(aTemp->flightHead) {
                Flight *fTemp = aTemp->flightHead;
                aTemp->flightHead = aTemp->flightHead->next;
                delete fTemp;
            }
            delete aTemp;
        }
    }
};

int main() {
    ATC control;
    control.addAirport("ABC");
    control.addAirport("XYZ");
    control.addFlight("ABC", "KD102", "India");
    control.addFlight("ABC", "JG315", "Tokyo");
    control.addFlight("XYZ", "DS100", "Paris");
    
    cout<<"\n--Air traffic control--\n";
    control.display();
    
    return 0;
}
