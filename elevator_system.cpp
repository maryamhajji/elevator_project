#include <iostream>
#include <string>
using namespace std;

// Structure representing a user's elevator request
struct Request {
    string name;       // Name of the user making the request
    int from, to;      // Starting floor and destination floor
    int hour, minute;  // Time the request was made
    Request* next;     // Pointer to the next request (for linked list)
};

// Queue structure to manage requests in FIFO order
struct Queue {
    Request* front = NULL; // Pointer to the first request
    Request* rear = NULL;  // Pointer to the last request

    // Checks if the queue is empty
    bool isEmpty() {
        return front == NULL;
    }

    // Adds a new request to the end of the queue
    void enqueue(Request* r) {
        r->next = NULL;
        if (rear == NULL) {
            // If queue is empty, set both front and rear to the new request
            front = rear = r;
        } else {
            // Otherwise, add to the end and update rear
            rear->next = r;
            rear = r;
        }
    }

    // Removes and returns the request at the front of the queue
    Request* dequeue() {
        if (isEmpty()) return NULL;
        Request* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL; // If queue becomes empty
        return temp;
    }
};

// ElevatorSystem manages requests, enforces rules, and keeps history
struct ElevatorSystem {
    Queue q;                  // Queue to store current pending requests
    Request* history = NULL;  // Linked list to store full request history

    // Adds a new elevator request to the system
    void addRequest(string name, int from, int to, int hour, int minute) {
        // Create a new request
        Request* r = new Request{name, from, to, hour, minute, NULL};

        // Add request to history linked list
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

    // Determines if a request is allowed based on floor-specific time rules
    bool allowed(Request* r) {
        int time = r->hour * 60 + r->minute; // Convert time to minutes

        switch (r->to) {
            case 2: // Gym: 6:00 AM - 11:00 PM
                return time >= 360 && time <= 1380;
            case 3: // Restaurant: breakfast/lunch/dinner time slots
                return (time >= 360 && time <= 660) || // 6:00 - 11:00
                       (time >= 720 && time <= 900) || // 12:00 - 15:00
                       (time >= 1080 && time <= 1260); // 18:00 - 21:00
            case 4: // Library: 8:00 AM - 8:00 PM
                return time >= 480 && time <= 1200;
            case 10: // Pool: 9:00 AM - 10:00 PM
                return time >= 540 && time <= 1320;
            // Other floors have 24/7 access
            case 1: case 5: case 6: case 7: case 8: case 9:
                return true;
            default:
                return true;
        }
    }

    // Processes all pending requests in the queue
    void process() {
        while (!q.isEmpty()) {
            Request* r = q.dequeue();
            // Output request info
            cout << "\nProcessing: " << r->name << " from " << r->from
                 << " to " << r->to << " at " << r->hour << ":"
                 << (r->minute < 10 ? "0" : "") << r->minute << endl;

            // Check if access is allowed based on rules
            if (allowed(r))
                cout << "Access granted.\n";
            else
                cout << "Access denied. Floor closed.\n";
        }
    }

    // Displays the complete history of all requests ever made
    void showHistory() {
        cout << "\nRequest History:\n";
        Request* temp = history;
        while (temp) {
            cout << temp->name << " -> Floor " << temp->to << " at "
                 << temp->hour << ":" << (temp->minute < 10 ? "0" : "") << temp->minute << endl;
            temp = temp->next;
        }
    }

    // Displays access time rules for each special floor
    void showFloorRules() {
        cout << "\n--- Special Floor Access Rules ---\n";
        cout << "Lobby           Floor 1\n";
        cout << "GYM             Floor 2     6:00 AM - 11:00 PM\n";
        cout << "Restaurant      Floor 3     6:00 AM - 11:00 AM (Breakfast)\n";
        cout << "                            12:00 PM - 3:00 PM (Lunch)\n";
        cout << "                            6:00 PM - 9:00 PM (Dinner)\n";
        cout << "Library         Floor 4     8:00 AM - 8:00 PM\n";
        cout << "Rooms           Floor 5\n";
        cout << "Rooms           Floor 6\n";
        cout << "Rooms           Floor 7\n";
        cout << "Rooms           Floor 8\n";
        cout << "Rooms           Floor 9\n";
        cout << "Swimming Pool   Floor 10    9:00 AM - 10:00 PM\n";
        cout << "-------------------------------\n";
    }
};

int main() {
    ElevatorSystem e; // Create an instance of the system
    int choice;

    e.showFloorRules(); // Display access rules before starting

    do {
        // Menu
        cout << "\n1. Add Request\n2. Process Requests\n3. Show History\n4. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Gather request info from the user
                string name;
                int from, to, h, m;
                cout << "Name: "; cin >> name;
                cout << "From floor: "; cin >> from;
                cout << "To floor: "; cin >> to;
                cout << "Hour: "; cin >> h;
                cout << "Minute: "; cin >> m;
                e.addRequest(name, from, to, h, m); // Add the request
                break;
            }
            case 2:
                e.process(); // Process all queued requests
                break;
            case 3:
                e.showHistory(); // Display full history
                break;
            case 4:
                cout << "Exiting.\n"; // Exit program
                break;
            default:
                cout << "Invalid.\n"; // Invalid choice handling
        }
    } while (choice != 4); // Continue until user chooses to exit

    return 0;
}
