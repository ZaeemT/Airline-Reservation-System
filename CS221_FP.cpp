#include <iostream>
#include <queue>

using namespace std;

class FlightNode {
    public:
        int flightNum;
        int arrival;
        int departure;
        FlightNode* next;

        FlightNode (int num, int a, int d) {
            this->flightNum = num;
            this->arrival = a;
            this->departure = d;
            this->next = NULL;
        }
};

class Flights {
    public:
        FlightNode* fHead;

        Flights () {
            fHead = NULL;
        }

        void addFlight (int n, int a, int d) {
            FlightNode* newNode = new FlightNode(n, a, d);

            if (fHead == NULL) {
                fHead = newNode;
                return;
            }

            FlightNode* temp = fHead;

            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        void displayFlights () {
            cout << "Flight Number \t" << "Arrival \t" << "Departure \t" << endl;
            for(FlightNode *ptr = fHead; ptr != NULL; ptr = ptr->next){
                cout << "\t" << ptr->flightNum << "\t  " << ptr->arrival << "\t\t  " << ptr->departure << endl; 
            }
        }

        void displayFlightIDs(){
            cout << "1. KHI -> LHR" << endl;
            cout << "2. KHI -> ISL" << endl;
            cout << "3. LHR -> KHI" << endl;
            cout << "4. LHR -> ISL" << endl;
            cout << "5. ISL -> KHI" << endl;
            cout << "6. ISL -> RWP" << endl;
            cout << "7. RWP -> PEW" << endl;
            cout << "8. PEW -> ISL" << endl;
        }

        int flightRes(){
            int option = 0;
            cout << "\t Flight Reservation" << endl;
            cout << "---------------------------------" << endl;
            displayFlightIDs();
            cout << "-----------------------" << endl;
            cout << "Choose your flights: ";
            cin >> option;
            cout << endl;

            return option; 
        }

        void swap(FlightNode* p1, FlightNode* p2){
            int temp_fNum = p1->flightNum;
            int temp_arrival = p1->arrival;
            int temp_departure = p1->departure;


            p1->flightNum = p2->flightNum;
            p1->arrival = p2->arrival;
            p1->departure = p2->departure;
            

            p2->flightNum = temp_fNum;
            p2->arrival = temp_arrival;
            p2->departure = temp_departure;
        }

        void selectionSort_arrival(){
		    FlightNode *ptr = fHead;
		    FlightNode *min;
		    FlightNode *ptr2;
		
		    while(ptr != nullptr){
		        min = ptr;
		        ptr2 = ptr->next;
		
		        while (ptr2 != nullptr){
		            if (ptr2->arrival < min->arrival){
		                min = ptr2;
		            }
		            ptr2 = ptr2->next;
		        }
		        swap (min, ptr);
		        ptr = ptr->next;
		    }
		}

        void selectionSort_departure(){
            FlightNode* ptr = fHead;
            FlightNode* min;
            FlightNode* ptr2;

            while(ptr != nullptr){
                min = ptr;
                ptr2 = ptr->next;

                while (ptr2 != nullptr){
                    if (ptr2->departure < min->departure){
                        min = ptr2;
                    }
                    ptr2 = ptr2->next;
                }
                swap (min, ptr);
                ptr = ptr->next;
            }
        }
};

class PassengerNode {
    public:
        int id;
        string firstName;
        string lastName;
        //flight
        PassengerNode *next;

        PassengerNode (int i, string fName, string lName) {
            this->id = i;
            this->firstName = fName;
            this->lastName = lName;
            this->next = NULL;
        }
};

class Passengers {
    public:
        PassengerNode* pHead;

        Passengers () {
            pHead = NULL;
        }

        void addPassenger (int id, string fName, string lName) {
            PassengerNode* newNode = new PassengerNode(id, fName, lName);

            if (pHead == NULL) {
                pHead = newNode;
                return;
            }

            PassengerNode* temp = pHead;

            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        void removePassenger (int searchid) {
            PassengerNode* prev = pHead;
            PassengerNode* ptr;

            if (pHead->id == searchid) {
                ptr = pHead;
                pHead = prev->next;
                delete ptr;

                return;
            }

            for (ptr = prev->next; ptr != NULL; ptr = ptr->next) {
                if (ptr->id == searchid) {
                    prev->next = ptr->next;
                    delete ptr;
                }
                prev = prev->next;
            }
        }

        void Sort_lname(){
        	PassengerNode* temp = pHead;
        	
        	while (temp) {
				PassengerNode* min = temp;
				PassengerNode* ptr = temp->next;
		
				while (ptr) {
					if (min->lastName > ptr->lastName)
						min = ptr;

					ptr = ptr->next;
				}
				
				int ID = temp->id;			
				string firstname = temp->firstName;
				string lastname = temp->lastName;

				temp->id = min->id;
				temp->firstName = min->firstName;
				temp->lastName = min->lastName;
		
				min->id = ID;
				min->firstName = firstname;
				min->lastName = lastname;

				temp = temp->next;
			}
        }

        void display() {
            PassengerNode* temp = pHead;
            while (temp != NULL) {
                cout << temp->id << " " << temp->firstName << " " << temp->lastName << endl;
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
};

class ReservationNode {
    public:
        int passengerID;
        int flightID;
        ReservationNode* next;

        ReservationNode (int pi, int fi) {
            this->passengerID = pi;
            this->flightID = fi;
            this->next = NULL;
        }
};

class Reservations : public Flights, public Passengers{
    public:
        ReservationNode* rHead;

        Reservations () {
            rHead = NULL;
        }

        void makeReservation () {
            int passID, flightID;
            bool idSuccess;
            string fname, lname;
            
            cout << "Enter Passenger ID: ";
            cin >> passID;
            cout << "Enter Passenger First Name: ";
            cin >> fname;
            cout << "Enter Passenger Last Name: ";
            cin >> lname;

            cout << "Book Following Flight:" << endl;
            flightID = flightRes();

            ReservationNode* newNode = new ReservationNode(passID, flightID);
            addPassenger (passID, fname, lname);

            if (rHead == NULL) {
                rHead = newNode;
                return;
            }

            ReservationNode* temp = rHead;

            if (rHead == NULL) {
                rHead = newNode;
                return;
            }

            //ReservationNode* temp = rHead;

            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        void findReservation (int searchPassID) {
            ReservationNode* temp;
            bool passIDFound = false;
            int idFlight;

            for (temp = rHead; temp != NULL; temp = temp->next) {
                if (searchPassID == temp->passengerID) {
                    passIDFound = true;
                    idFlight = temp->flightID;
                    break;
                }
            }
            if (passIDFound == false) {
                cout << "No such passenger found." << endl;
                return;
            }

            PassengerNode* ptr1;
            FlightNode* ptr2;

            for (ptr1 = pHead; ptr1 != NULL; ptr1 = ptr1->next) {
                if (searchPassID == ptr1->id) {
                    cout << "Passenger ID:\t" << ptr1->id << endl;
                    cout << "Passenger First Name:\t" << ptr1->firstName << endl;
                    cout << "Passenger Last Name:\t" << ptr1->lastName << endl;
                    cout << "--" << endl;
                }
            }
            cout << "Flight No: " << idFlight << endl;
        }

        void deleteReservation (int pID, int fID) {
            ReservationNode* prev = rHead;
            ReservationNode* ptr;

            if (rHead->passengerID == pID && rHead->flightID == fID) {
                ptr = rHead;
                rHead = prev->next;
                delete ptr;

                return;
            }

            for (ptr = prev->next; ptr != NULL; ptr = ptr->next) {
                if (ptr->passengerID == pID && ptr->flightID == fID) {
                    prev->next = ptr->next;
                    delete ptr;
                }
                prev = prev->next;
            }
        }

        void passengerOnFlight (int searchFlightID) {
            Passengers* p = new Passengers;
            
            ReservationNode* temp = rHead;
            
            cout << "Passengers in flight:" << endl;
            for (temp = rHead; temp != NULL; temp = temp->next) {
                if (searchFlightID == temp->flightID) {
                    cout << temp->passengerID << endl;
                }
            }
        }
};

class DestNode{
    public:
        int dest_id;
        int duration;
        string dest_name;
        DestNode *next;

        DestNode (int id, int d, string name){
            this->dest_id = id;
            this->duration = d;
            this->dest_name = name;
            this->next = NULL;
        }
};

class Cities{
    public:
        int city_id;
        string city_name;
        DestNode *next;
        DestNode *last;

        // Default Constructor
        Cities(){   
            this->city_id = 0;
            this->city_name = "";
            this->next = NULL;
            this->last = NULL;
        }

        // Overloaded Constructor
        Cities (int id, string name){
            this->city_id = id;
            this->city_name = name;
            this->next = NULL;
            this->last = NULL;
        }
};

class Graph{
    public:
        int size;
        Cities *node;

        // Constructor
        Graph(int n, string city[]){
            this->size = n;
            this->node = new Cities[size];
            this->setData(city);
        }

        void setData(string city[]){
            if(size <= 0){
                cout << "ERROR: Empty graph!" << endl; 
            }
            else{
                for(int i = 0; i < size; i++){
                    this->node[i].city_id = i;
                    this->node[i].city_name = city[i];
                }
            }
        }

        //addEdge (source, city name, destination, destination name, flight duration)
        void addEdge (int src, string srcName, int dest, string destName, int dur) {
            if (src >= 0 && src < this->size && dest >= 0 && dest < this->size) {
                DestNode *destination = new DestNode(dest, dur, destName);

                if (this->node[src].next == NULL) {
                    this->node[src].next = destination;
                }
                else {
                    this->node[src].last->next = destination;
                }

                this->node[src].last = destination;
            }
            else {
                cout << "ERROR: Edge could not be added." << endl;
            }
        }

        void displayGraph (string city[]) {
            if (this->size > 0) {
                for (int i = 0; i < this->size; ++i) {
                    cout << "\nAdjency list of vertex " << i << " : " << city[i] << " -> ";

                    DestNode *temp = this->node[i].next;

                    while (temp != NULL) {
                        cout << " " << this->node[temp->dest_id].city_id << " : " << this->node[temp->dest_id].city_name << " -> ";
                        temp = temp->next;
                    }

                    cout << endl;
                }
            }
        }

        void displayCities (string city[]) {
            cout << "\nCities Serviced by Airline: " << endl;

            for (int i = 0; i < this->size; ++i) {
                cout << city[i] << endl;
            }
        }

        void reachAdjCity (int vertex, string city[]) {
            if (vertex > this->size || this->size <= 0) {
                cout << "ERROR: Vertex not found." << endl;
                return;
            }

            cout << "List of cities reached by " << vertex << " : " << city[vertex] << ": " << endl;

            DestNode *temp = this->node[vertex].next;

            if (temp == NULL) {
                cout << "No available flights from this city!" << endl;
            }

            while (temp != NULL) {
                cout << " " << this->node[temp->dest_id].city_id << " : " << this->node[temp->dest_id].city_name << " -> ";
                temp = temp->next;
            }
        }

        void dijkstra (string start, string city[], string dest) {
            string visited[5];
            int destIndex;
            int w[5];
            int index;
            
            for (int i=0; i<5; i++) {
                visited[i] = city[i];
                w[i] = 1000; //infinite

                if (start == city[i]) {
                    index = i; 
                }
                if (city[i] == dest) {
                    destIndex = i;
                }
            }
            
            w[index] = 0;
            
            while (visited[index] != "") {
        
                    string min = "";
                    int minIndex;
                    visited[index] = "";

                    DestNode* temp = node[index].next;
                    int min_w = 1000, min_v=1000;
                    while (temp != NULL) {
                        int indexNext;
                        string next;
                        
                        next = temp->dest_name;
                        indexNext = temp->dest_id;
                        
                        if(visited[temp->dest_id] != "" && w[index] + temp->duration < w[temp->dest_id]){
                            w[indexNext] = w[index] + temp->duration;

                            if(min_w > w[indexNext]){
                                
                                min_w = w[indexNext];
                                min = temp->dest_name;
                                minIndex = indexNext;
                            }
                        }
                        
                        temp = temp->next;
                    }

                    if (destIndex == index) {
                        break;
                    }

                    if (min != "") {
                        cout<<city[index]<<" ";
                        index = minIndex;
                    }

                    else {
                        index = 2;
                    }
                }

                for(int i=0; i<5; i++){
                    if(city[i] == dest){
                        cout<<city[i] << "  ; Duration: " << w[i] << " hours" <<endl;
                    }
                }
            }
};

int menu (){
    int option = 0;

	cout << "-------------------------------------------------  " << endl;
	cout << "1- Display list of cities serviced by the airline." << endl;
	cout << "2- Display list of flight departures sorted by departure time." << endl;
	cout << "3- Display list of flight arrivals sorted by arrival time." << endl;
	cout << "4- Display list of cities reached from a particular city." << endl;
	cout << "5- Display shortest path between two cities." << endl;
	cout << "6- Book flight reservation." << endl;
	cout << "7- Display passenger reservation schedule." << endl;
	cout << "8- Delete passenger reservation." << endl;
	cout << "9- Display List of passengers in particular flight." << endl;
    cout << "10- Exit System." << endl;

    cout << "Select option: ";
    cin >> option;
    cout << "----------------------------------------------------------------------" << endl;

    return option;
}

void initializeGraph (Graph* graph) {
    graph->addEdge(0, "KHI", 1, "LHR", 3);
    graph->addEdge(0, "KHI", 2, "ISL", 4);
    graph->addEdge(1, "LHR", 0, "KHI", 3);
    graph->addEdge(1, "LHR", 2, "ISL", 2);
    graph->addEdge(2, "ISL", 0, "KHI", 4);
    graph->addEdge(2, "ISL", 3, "RWP", 1);
    graph->addEdge(3, "RWP", 4, "PEW", 1);
    graph->addEdge(4, "PEW", 2, "ISL", 1);
}

void initializeFlights (Flights* flights) {
    flights->addFlight(1, 2, 5);
    flights->addFlight(2, 7, 11);
    flights->addFlight(3, 6, 9);
    flights->addFlight(4, 10, 12);
    flights->addFlight(5, 4, 8);
    flights->addFlight(6, 4, 5);
    flights->addFlight(7, 7, 8);
    flights->addFlight(8, 1, 2);
}

int main () {
    string city[5] = {"KHI", "LHR", "ISL", "RWP", "PEW"};

    Graph *graph = new Graph(5, city);
    Passengers* pass = new Passengers;
    Flights* flight = new Flights;
    Reservations* res = new Reservations;

    initializeGraph(graph);
    initializeFlights(flight);

    bool quit = false;
    int option, intOption;
    string strOption;

    cout << "-- AIRLINE MANAGEMENT SYSTEM --" << endl;

    do {
        option = menu();

        switch (option) {
            case 1: {
                graph->displayCities(city);

                break;
            }
            case 2: {
                flight->selectionSort_departure();
                flight->displayFlights();

                break;
            }
            case 3: {
                flight->selectionSort_arrival();
                flight->displayFlights();

                break;
            }
            case 4: {
                cout << "Enter city you want to search from: " << endl;
                cin >> strOption;

                int i;
                for (i = 0; i < 5; i++) {
                    if (strOption == city[i]) {
                        break;
                    }
                }

                graph->reachAdjCity(i, city);

                break;
            }
            case 5: {
                string source, destination;
                cout << "Enter the source city: ";
                cin >> source;
                cout << "Enter destination city: ";
                cin >> destination;

                graph->dijkstra(source, city, destination);
                
                break;
            }
            case 6: {
                res->makeReservation();

                break;
            }
            case 7: {
                int ID;

                cout << "Enter passenger ID to print his/her reservations: ";
                cin >> ID;

                res->findReservation(ID);

                /* Giving memory error */
                break;
            }
            case 8: {
                int fID, pID;

                cout << "Enter passenger ID to delete his/her reservations: ";
                cin >> pID;

                flight->displayFlightIDs();

                cout << "Enter flight ID to delete his/her reservations: ";
                cin >> fID;

                res->deleteReservation(pID, fID);

                break;
            }
            case 9: {
                int fID;

                flight->displayFlightIDs();
                cout << endl;

                cout << "Enter flight ID: ";
                cin >> fID;

                cout << endl;
                res->passengerOnFlight(fID);

                /* Not showing the last passenger */
                break;
            }
            case 10: {
                cout << "Thank you & Good Bye!" << endl;
                quit = true;

                break;
            }
            default: {
                cout << "Invalid Input!. Try Again!" << endl;

                break;
            }
        }
    } while (quit == false);
}