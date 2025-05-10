#include <iostream>
#include <string>
using namespace std;

// Structure to store elevator request details
struct Request {
    int number;       // Unique request number
    int from, to;     // Origin and destination floors
    int hour, minute; // Request time (24-hour format)
    Request* next;    // Pointer to the next request in a linked list
};

// Queue using linked list to manage elevator requests
struct Queue {
    Request* front = NULL;  // Points to front request
    Request* rear = NULL;   // Points to last request

    // Check if the queue is empty
    bool isEmpty() {
        return front == NULL;
    }

    // Add a request to the queue
    void enqueue(Request* r) {
        r->next = NULL;
        if (rear == NULL) {
            // If empty, both front and rear point to new request
            front = rear = r;
        } else {
            // Add to end of list and move rear pointer
            rear->next = r;
            rear = r;
        }
    }

    // Remove and return the front request
    Request* dequeue() {
        if (isEmpty()) return NULL;
        Request* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL; // Queue is now empty
        return temp;
    }
};

// Elevator system logic
struct ElevatorSystem {
    Queue q;                   // Queue of pending requests
    Request* history = NULL;   // Linked list of all past requests

    // Add a new request to system
    void addRequest(int num, int from, int to, int hour, int minute) {
        Request* r = new Request{num, from, to, hour, minute, NULL};

        // Append to history linked list
        if (history == NULL) {
            history = r;
        } else {
            Request* temp = history;
            while (temp->next) temp = temp->next;
            temp->next = r;
        }

        // Enqueue the request for processing
        q.enqueue(r);
    }

    // Determine if access to the requested floor is allowed
    bool allowed(Request* r) {
        int time = r->hour * 60 + r->minute; // Convert time to total minutes

        switch (r->to) {
            case 2: // GYM: 6:00 AM – 11:00 PM
                return time >= 360 && time <= 1380;
            case 3: // Restaurant: Breakfast, Lunch, Dinner
                return (time >= 360 && time <= 660) || 
                       (time >= 720 && time <= 900) ||
                       (time >= 1080 && time <= 1260);
            case 4: // Library: 8:00 AM – 8:00 PM
                return time >= 480 && time <= 1200;
            case 10: // Swimming Pool: 9:00 AM – 10:00 PM
                return time >= 540 && time <= 1320;
            // All other floors are accessible 24/7
            case 1: case 5: case 6: case 7: case 8: case 9:
                return true;
            default: // Invalid floor
                return false;
        }
    }

    // Process all requests in the queue
    void process() {
        while (!q.isEmpty()) {
            Request* r = q.dequeue();

            // Show request being processed
            cout << "\nProcessing: " << r->number << " from floor " << r->from
                 << " to floor " << r->to << " at " << r->hour << ":"
                 << (r->minute < 10 ? "0" : "") << r->minute << endl;

            // Check access rules
            if (allowed(r))
                cout << "Access granted.\n";
            else
                cout << "Access denied. Floor closed.\n";
        }
    }

    // Display history of all submitted requests
    void showHistory() {
        cout << "\nRequest History:\n";
        Request* temp = history;
        while (temp) {
            cout << temp->number << " -> Floor " << temp->to << " at "
                 << temp->hour << ":" << (temp->minute < 10 ? "0" : "") << temp->minute << endl;
            temp = temp->next;
        }
    }

    // Display the access rules for special floors
    void showFloorRules() {
        cout << "\n--- Special Floor Access Rules ---\n";
        cout << "Lobby           Floor 1\n";
        cout << "GYM             Floor 2     6:00 AM - 11:00 PM\n";
        cout << "Restaurant      Floor 3     6:00 AM - 11:00 AM (Breakfast)\n";
        cout << "                            12:00 PM - 3:00 PM (Lunch)\n";
        cout << "                            6:00 PM - 9:00 PM (Dinner)\n";
        cout << "Library         Floor 4     8:00 AM - 8:00 PM\n";
        cout << "Rooms           Floor 5 - 9\n";
        cout << "Swimming Pool   Floor 10    9:00 AM - 10:00 PM\n";
        cout << "-------------------------------\n";
    }
};

// Entry point of the program
int main() {
    ElevatorSystem e;
    int choice;

    // Show access schedule at program start
    e.showFloorRules();

    // Main menu loop
    do {
        cout << "\n1. Add Request\n2. Process Requests\n3. Show History\n4. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Gather input and create request
                int num, from, to, h, m;
                cout << "Number: "; cin >> num;
                cout << "From floor: "; cin >> from;
                cout << "To floor: "; cin >> to;
                cout << "Hour: "; cin >> h;
                cout << "Minute: "; cin >> m;
                e.addRequest(num, from, to, h, m);
                break;
            }
            case 2:
                // Handle and respond to requests
                e.process(); 
                break;
            case 3:
                // Review all requests made
                e.showHistory(); 
                break;
            case 4:
                // Exit program
                cout << "Exiting.\n";
                break;
            default:
                // Handle invalid input
                cout << "Invalid.\n";
        }
    } while (choice != 4);

    return 0;
}
