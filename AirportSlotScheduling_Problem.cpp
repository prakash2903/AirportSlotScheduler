
/** Airport Slot Scheduling **/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// GLOBAL VARIABLES :

// Lounge :
int totalLoungeSpace = 10400;
int totalCapacity = 6928;

// Passport Checkpoints :
int totalNumberOFPassportCounters = 132;

// Customs :
int totalCustomsDevices = 16;


// REQUIRED CLASSES :
class Flight
{
    public :
        string ID, gate;
        int numOfPassengers;
        int parked;

        // Parameterised Constructor :
        Flight(string id, int NP, int a)
        {
            this->ID = id;
            this->gate = "NIL";
            this->numOfPassengers = NP;
            this->parked = a;
        }
};

class Lounge
{
    public :
        string ID;  // Name of Lounge.
        int space;
        int capacity;
        int areaZone;
        bool assigned;

        // Default Constructor:
        Lounge()
        {
            ID = "";
            space = capacity = areaZone = 0;
            assigned = false;
        }

        // Parameterised Constructor :
        Lounge(string id, int S, int C, int A, bool a)
        {
            this->ID = id;
            this->space = S;
            this->capacity = C;
            this->areaZone = A;
            this->assigned = a;
        }
};

class Passport
{
    public :
        string ID, gate;
        int areazone;
        bool assigned;

        // Parameterised Constructor :
        Passport(string id, int A, int a)
        {
            this->ID = id;
            this->areazone = A;
            this->assigned = a;
            this->gate = "NIL";
        }
};

class Customs
{
    public :
        string ID,luggage;
        int areazone;
        bool assigned;

        // Parameterised Constructor :
        Customs(string id, int A, int a)
        {
            this->ID = id;
            this->areazone = A;
            this->assigned = a;
            this->luggage = "NIL";
        }
};

class Luggage
{
    public :
        string ID,counter;
        int areazone;
        bool assigned;

        // Parameterised Constructor :
        Luggage(string id, int A, bool a)
        {
            this->ID = id;
            this->areazone = A;
            this->assigned = a;
            this->counter = "NIL";
        }
};


/* ********* PRINTING  ********* */

void printFlight(vector<Flight> F)
{
    cout << "\nFlights :-" << endl;
    for(int i = 0;i < F.size();i++)
    {
        cout << "ID : " << F[i].ID << ", Passengers : " << F[i].numOfPassengers << ", Parked : " << F[i].parked << ", Gates : " << F[i].gate << endl;
    }
    cout << endl;
}

void printGate(vector<Lounge> G)
{
    cout << "\nGates :-" << endl;
    for(int i = 0;i < G.size();i++)
    {
        cout << "ID : " << G[i].ID << ", Capacity : " << G[i].capacity << ", Assigned : " << G[i].assigned << endl;
    }
    cout << endl;
}

void printPassport(vector<Passport> PC)
{
    cout << "\nPassport Counters :-" << endl;
    for(int i = 0;i < PC.size();i++)
    {
        cout << "ID : " << PC[i].ID << ", Gate : " << PC[i].gate << ", Assigned : " << PC[i].assigned << endl;
    }
    cout << endl;
}


void printLuggage(vector<Luggage> L)
{
    cout << "\nLuggages :-" << endl;
    for(int i = 0;i < L.size();i++)
    {
        cout << "ID : " << L[i].ID << ", Counter : " << L[i].counter << ", Assigned : " << L[i].assigned << endl;
    }
    cout << endl;
}


void printCustoms(vector<Customs> C)
{
    cout << "\nCustoms :-" << endl;
    for(int i = 0;i < C.size();i++)
    {
        cout << "ID : " << C[i].ID << ", Luggage : " << C[i].luggage << ", Assigned : " << C[i].assigned << endl;
    }
    cout << endl;
}

/* ********* PRINTING  ********* */


/******************** ALGORITHMS *************************/

/* =============================== 2 START =============================== */

//Function to find number of flights unassigned :
int numOfFlights(vector<Flight> F)
{
    int NoF = 0;
    for(int i = 0;i < F.size();i++)
    {
        if(F[i].parked == 0)
        {
            NoF += 1;
        }
    }
    return NoF;
}

// Function to return number of passengers in each flight :
vector<int> numOfPassengers(vector<Flight> F)
{
    vector<int> passengers;
    for(int i = 0;i < F.size();i++)
    {
        passengers.push_back(F[i].numOfPassengers);
    }
    return passengers;
}

// Comparator function to sort descending based on capacity :
bool sortByCapacity(Lounge &a, Lounge &b)
{
    return a.capacity > b.capacity;
}

// Function to assign gates to the planes :
string assignLounge(vector<Lounge> &G, int passengers, int PTg, vector<int> WR)
{
    // Sorting gates descending based on capacity.
    sort(G.begin(), G.end(), sortByCapacity);

    int minDiff = 1000, index = -1;

    // Finding minimum difference between capacity and passenger Count(Finding Best fit gate).
    for(int i = 0;i < G.size();i++)
    {
        if(G[i].assigned == false && minDiff > G[i].capacity - passengers && G[i].capacity - passengers >= 0)
        {
            minDiff = G[i].capacity - passengers;
            index = i;
        }
    }

    G[index].assigned = true;
    return G[index].ID;
}

// Comparator function to sort descending based on number of passengers :
bool sortByPassengers(Flight &a, Flight &b)
{
    return a.numOfPassengers > b.numOfPassengers;
}

// Function to guide passengers from AIRCRAFT to GATE LOUNGE :
void aircraftToGateLounge(vector<Flight> &F, vector<Lounge> &G, int t, int PTg, vector<int> WR)
{
    int NoF = numOfFlights(F);
    if(NoF > 0)
    {
        // Sorting Flights in descending based on passengers count.
        sort(F.begin(), F.end(), sortByPassengers);

        for(int i = 0;i < NoF;i++)
        {
            string gate = assignLounge(G, F[i].numOfPassengers, PTg, WR);

            // Removing flight from consideration:
            F[i].parked = -1;
            F[i].gate = gate;
        }
    }
}

/* =============================== 2 END =============================== */

/* =============================== 3 START =============================== */

// Number of lounges available(Lounges that contain people) :
int numOfGateLounges(vector<Lounge> G)
{
    int num = 0;
    for(int i = 0;i < G.size();i++)
    {
        if(G[i].assigned == true)
            num += 1;
    }
    return num;
}

// Function to assign a passport Counter :
void assign(vector<Lounge> &G, vector<Passport> &PC, int t, int PTp, int l)
{
    //sort(P.begin(), P.end(), sortByCounter);

    for(int i = 0;i < PC.size();i++)
    {
        if(PC[i].assigned == false)
        {
            PC[i].assigned = true;
            PC[i].gate = G[l].ID;
            break;
        }
    }

    // Removing gate from consideration.
    G[l].assigned = false;
}

/*
// Function to update assigned Lounges :
Lounge updateAssignedLounges(Lounge G1)
{

}
// Function to update Assigned Passport Counter :
Passport updateAssignedPassportCounter(Passport p)
{}*/


// Comparator Function to sort descending :
bool sortBySize(Lounge &a, Lounge &b)
{
    return a.capacity > b.capacity;  // Sort descending.
}

bool sortByAssign(Lounge &a, Lounge &b)
{
    return a.assigned == 1 && b.assigned == 0;
}

// Function to guide passengers from GATE LOUNGE to PASSPORT COUNTER :
void gateLoungeToPass(vector<Lounge> &G, vector<Passport> &PC, int t, int PTp)
{
    // Number of available gate lounges(Lounges that contain people).
    int NoG = numOfGateLounges(G);

    if(NoG > 0)
    {
        // Sort descending based on capacity.
        //sort(G.begin(), G.end(), sortBySize);

        // Sort based on availability.
        sort(G.begin(), G.end(), sortByAssign);

        for(int i = 0;i < NoG;i++)
        {
            assign(G, PC, t, PTp, i);
        }
    }
}

/* =============================== 3 END =============================== */



/* =============================== 4 START =============================== */

int numOfPassort(vector<Passport> PC)
{
    int NoP = 0;
    for(int i = 0;i < PC.size();i++)
    {
        if(PC[i].assigned == true)
            NoP += 1;
    }
    return NoP;
}

void assignBelt(vector<Passport> &PC, vector<Luggage> &L, int t, int LTD, int l)
{
    for(int i = 0;i < L.size();i++)
    {
        if(L[i].assigned == false)
        {
            L[i].assigned = true;
            L[i].counter = PC[l].ID;
            break;
        }
    }

    // Removing passport from consideration.
    PC[l].assigned = false;
}

bool sortByPassport(Passport &a , Passport &b)
{
    return a.assigned == 1 && b.assigned == 0;
}
void passToLuggage(vector<Passport> &PC, vector<Luggage> &L, int t, int LTD)
{
    int NoP = numOfPassort(PC);

    if(NoP > 0)
    {
        // sorting desc based on assigned passport counters
        sort(PC.begin(),PC.end(),sortByPassport);

        for(int i = 0;i < NoP;i++)
        {
            assignBelt(PC, L, t, LTD, i);
        }
    }
}

/* =============================== 4 END =============================== */



/* =============================== 5 START =============================== */

int numOfLuggage(vector<Luggage> L)
{
    int NoL = 0;
    for(int i=0;i<L.size();i++)
    {
        if(L[i].assigned == true)
            NoL+=1;
    }
    return NoL;
}

bool sortByLuggage(Luggage &a, Luggage &b)
{
    return a.assigned == 1 && b.assigned == 0;
}

void assignCustoms(vector<Luggage> &L, vector<Customs> &C, int t, int l)
{
    for(int i = 0;i < C.size();i++)
    {
        if(C[i].assigned == false)
        {
            C[i].assigned = true;
            C[i].luggage = L[l].ID;
            break;
        }
    }

    // Removing luggage from consideration.
    L[l].assigned = false;

}
void luggageToCustoms(vector<Luggage> &L,vector<Customs> &C, int t)
{
    int NoL = numOfLuggage(L);
    if(NoL>0)
    {
        sort(L.begin(),L.end(),sortByLuggage);
        for(int i = 0;i < NoL;i++)
        {
            assignCustoms(L, C, t, i);
        }
    }

}

/* =============================== 5 END =============================== */



/* =============================== 6 START =============================== */

int numOfCustoms(vector<Customs> C)
{
    int NoC = 0;
    for(int i = 0;i < C.size();i++)
    {
        if(C[i].assigned == true)
            NoC += 1;
    }
    return NoC;
}

bool sortByCustoms(Customs &a, Customs &b)
{
    return a.assigned == 1 && b.assigned == 0;
}

void assignPlaza(vector<Customs> &C, int &Z, int t, int l)
{
    // Removing customs from consideration.
    C[l].assigned = false;

    Z++;
}

void customsToPlaza(vector<Customs> &C, int &Z, int t)
{
    int NoC = numOfCustoms(C);

    if(NoC > 0)
    {
        sort(C.begin(), C.end(), sortByCustoms);

        for(int i = 0;i < NoC;i++)
        {
            assignPlaza(C, Z, t, i);
        }

    }
}

/* =============================== 6 END =============================== */


/* =============================== 1 START =============================== */

void flightSchedulingAlgo(int PTg, vector<int> WR, int PTp, int CDc)
{
    // List of Flights.
    vector<Flight> F = {Flight("F1", 500, 0), Flight("F2", 600, 0)};

    // List of Gate Lounges.
    vector<Lounge> G = {Lounge("G1", 800, 800, 1, false), Lounge("G2", 800, 900, 1, false)};

    // List of Passport Checkpoint counters.
    vector<Passport> PC = {Passport("PC1", 1, false), Passport("PC2", 1, false)};

    // List of Luggage area.
    vector<Luggage> L = {Luggage("L1", 1, false), Luggage("L2", 1, false)};

    // List of Custom Checkpoints.
    vector<Customs> C = {Customs("C1", 1, false), Customs("C2", 1, false)};

    // Number of planes arrived and passengers passed through the airport.
    int Z;

    int LTD = 10;

    cout << "\n###################  START ####################" << endl;
    for(int t = 1; t < 2;t++)
    {
        // Update Gate Lounges data.
        aircraftToGateLounge(F, G, t, PTg, WR);

        cout << "\nFlight ----- Gate :-" << endl;
        printFlight(F);
        printGate(G);


        // Update data for Gate Lounge and Passport Counters.
        gateLoungeToPass(G, PC, t, PTp);

        cout << "\nGate ----- Passport Counter :-" << endl;
        printGate(G);
        printPassport(PC);


        // Update data for Passport Counters and Luggage.
        passToLuggage(PC, L, t, LTD);

        cout << "\nPassport Counter ----- Luggage :-" << endl;
        printPassport(PC);
        printLuggage(L);


        // Update data for Luggage and Customs.
        luggageToCustoms(L, C, t);

        cout << "\nLuggage ----- Customs :-" << endl;
        printLuggage(L);
        printCustoms(C);

        // Update data for Customs and plaza.
        customsToPlaza(C, Z, t);

        cout << "\nCustoms ----- Plaza :-" << endl;
        printCustoms(C);
        cout << "Number of flights arrived so far = " << Z << endl << endl;
    }
}

/* =============================== 1 END =============================== */



// Main(Driver) Function :
int main()
{
    // Processing time at gates(Medication)(M) :
    int PTg = 1;

    // Number of workers at each gate(M) :
    vector<int> WR = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    //int WRg1 = 10,  WRg2 = 10,  WRg3 = 10,  WRg4 = 10,  WRg5 = 10,  WRg6 = 10,  WRg7 = 10,  WRg8 = 10,  WRg9 = 10;
    //int WRg10 = 10, WRg11 = 10, WRg12 = 10, WRg13 = 10, WRg14 = 10, WRg15 = 10, WRg16 = 10, WRg17 = 10, WRg18 = 10;

    //Processing time at Passport checkpoints(M) :
    int PTp = 1;

    /*// Number of passport Counters at each section(GIVEN) :
    Passport P1("c1", 1, false);
    Passport P2("c2a", 1, false);
    Passport P3("c2b", 1, false);
    Passport P4("c3a", 2, false);
    Passport P5("c3b", 2, false);
    Passport P6("c4", 2, false);

    vector<Passport> P = {P1, P2, P3, P4, P5, P6};
    //int P1 = 18, P2 = 32, P3 = 16, P4 = 32, P5 = 16, P6 = 18;*/

    // Number of Customs inspection devices :
    int CDc = 4; // DOUBT;


    flightSchedulingAlgo(PTg, WR, PTp, CDc);

    return 0;
}

