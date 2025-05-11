#include <iostream>
#include <string>

using namespace std;

// Structure to store elevator request details
struct Request {
    int number;       // Request number
    int from, to;      // Floor numbers: from (origin), to (destination)
    int hour, minute;  // Time of request
    Request* next;     // Pointer to the next request (for linked list)
    Request* prev;	   // Pointer to the previous request (for linked list)
};

// Simple queue using singly-linked list
struct Queue {
    Request* front = NULL;  // Pointer to front of queue
    Request* rear = NULL;   // Pointer to rear of queue

    // Check if the queue is empty
    bool isEmpty() {
        return front == NULL;
    }

    // Add a request to the queue
    void enqueue(Request* r) {
        r->next = NULL;
        if (rear == NULL) {
        	// If the queue is empty, front and rear are the same
            front = rear = r;
        } else {
        	// Add new request to the end and update rear
            rear->next = r;
            rear = r;
        }
    }
    
	// Remove and return the front request from the queue
    Request* dequeue() {
        if (isEmpty()) return NULL;
        Request* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL; // If queue becomes empty
        temp->next = NULL;
        return temp;
    }
};

// Class to handle the elevator system
struct ElevatorSystem {
    Queue q;                   // Queue to store pending requests
    Request* historyHead = NULL;   // Linked list to keep history of all requests from head
    Request* historyTail = NULL;   // Linked list to keep history of all requests from tail
    int requestCounter = 1;   // An automatic counter for every request

    // Add a new request to the system
    void addRequest(int from, int to, int hour, int minute) {
        // Create request for queue
        Request* rq = new Request{requestCounter, from, to, hour, minute, NULL, NULL};
        q.enqueue(rq);

        // Create a copy for history in doubly linked list
        Request* hist = new Request{requestCounter++, from, to, hour, minute, NULL, NULL};
        if (historyHead == NULL) {
            historyHead = historyTail = hist;
        } else {
            historyTail->next = hist;
            hist->prev = historyTail;
            historyTail = hist;
        }
    }

    // Check if a request is allowed based on floor rules and time
    bool allowed(Request* r) {
        int time = r->hour * 60 + r->minute; // Convert to total minutes since midnight

        // Access control logic based on floor and time
        switch (r->to) {
            case 2:  // GYM: 6:00 AM - 11:00 PM
                return time >= 360 && time <= 1380;
            case 3:  // Restaurant: Breakfast: 6:00 AM - 11:00 AM
					// Lunch: 12:00 PM - 3:00 PM
					// Dinner times: 6:00 PM - 9:00 PM
                return (time >= 360 && time <= 660) || 
                       (time >= 720 && time <= 900) ||
                       (time >= 1080 && time <= 1260);
            case 4:  // Library: 8:00 AM - 8:00 PM
                return time >= 480 && time <= 1200;
            case 10: // Swimming Pool: 9:00 AM - 10:00 PM
                return time >= 540 && time <= 1320;
            // Floors with unrestricted access
            case 1: case 5: case 6: case 7: case 8: case 9: 
                return true;
            default: 
                return false;
        }
    }

    void process() {
        if (q.isEmpty()) {		//Check if the list is empty
            cout << "No request available right now\n";
            return;
        }

        while (!q.isEmpty()) {
            Request* r = q.dequeue(); // Get the next request

            // Display request details            
            cout << "\nProcessing request #" << r->number
                 << " from floor " << r->from << " to floor " << r->to
                 << " at " << r->hour << ":" << (r->minute < 10 ? "0" : "") << r->minute << endl;
 
            // Check if access is allowed
            if (allowed(r))
                cout << "Access granted.\n";
            else
                cout << "Access denied. Floor closed.\n";

            delete r; //  delete request from the memory
        }
    }
	
	// Display the history of all requests
    void showHistory() {
        cout << "\nRequest History:\n";
        Request* temp = historyHead;
        while (temp) {
            cout << "Request #" << temp->number << ": from floor " << temp->from
                 << " to floor " << temp->to << " at " << temp->hour << ":"
                 << (temp->minute < 10 ? "0" : "") << temp->minute << endl;
            temp = temp->next;
        }
    }

	// Function to search and display a request in the history by its number
	void searchHistory(int number) {
	    Request* temp = historyHead; // Start from the beginning of the history list
	
	    // Traverse the doubly-linked list of request history
	    while (temp != NULL) {
	        // If the request number matches the search number
	        if (temp->number == number) {
	            // Display the details of the found request
	            cout << "\nFound request #" << temp->number << ": from floor " << temp->from
	                 << " to floor " << temp->to << " at " << temp->hour << ":"
	                 << (temp->minute < 10 ? "0" : "") << temp->minute << endl;
	            return; // Exit after finding the request
	        }
	        temp = temp->next; // Move to the next request in history
	    }
	
	    // If the request wasn't found in the list
	    cout << "Request #" << number << " not found in history.\n";
	}

	// Show access rules for each floor
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
    ElevatorSystem e;
    int choice;

	// Show the floor access rules once at the beginning
    e.showFloorRules();

	// Main menu loop
    do {
        cout << "\n1. Add Request\n2. Process Requests\n3. Show History\n4. Search Request\n5. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
            	// Take input and add new request
                int from, to, h, m;
                cout << "From floor: "; cin >> from;
                cout << "To floor: "; cin >> to;
                cout << "Hour: "; cin >> h;
                cout << "Minute: "; cin >> m;
                e.addRequest(from, to, h, m);
                break;
            }
            case 2:
            	// Process all requests
                e.process();
                break;
            case 3:
            	// Show request history
                e.showHistory();
                break;
            case 4: {
            	// Take input and search request 
                int searchNum;
                cout << "Enter request number to search: ";
                cin >> searchNum;
                e.searchHistory(searchNum);
                break;
            }
            case 5:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid.\n";
        }
    } while (choice != 5);

    return 0;
}
