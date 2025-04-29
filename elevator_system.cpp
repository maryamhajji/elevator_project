
#include <iostream>
#include <string>

using namespace std;

// Structure representing a request made by a user
struct Request {
    string name;
    int fromFloor;
    int toFloor;
    int hour;
    int minute;
    Request* next; // Pointer to the next request (used in linked list or queue)
};

// Simple linked list-based queue for managing elevator requests
struct RequestQueue {
    Request* front = nullptr;
    Request* rear = nullptr;

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Request* req) {
        req->next = nullptr;
        if (rear == nullptr) {
            front = rear = req;
        } else {
            rear->next = req;
            rear = req;
        }
    }

    Request* dequeue() {
        if (isEmpty()) return nullptr;
        Request* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        return temp;
    }
};

// Elevator system managing requests and access rules
struct ElevatorSystem {
    RequestQueue requestQueue; // Queue for pending requests
    Request* requestListHead = nullptr; // Linked list for request history

    // Adds a new request to the history and queue
    void addRequest(string name, int fromFloor, int toFloor, int hour, int minute) {
        Request* newReq = new Request{name, fromFloor, toFloor, hour, minute, nullptr};

        // Add to linked list (history)
        if (!requestListHead) {
            requestListHead = newReq;
        } else {
            Request* temp = requestListHead;
            while (temp->next) temp = temp->next;
            temp->next = newReq;
        }

        // Add to queue
        requestQueue.enqueue(newReq);
    }

    // Checks if a request is allowed based on access rules
    bool checkAccess(Request* req) {
        int time = req->hour * 60 + req->minute;

        if (req->toFloor == 3 && time > 540) return false;       // After 9:00 AM
        if (req->toFloor == 2 && time < 300) return false;       // Before 5:00 AM
        if (req->toFloor == 5 && req->name != "admin") return false; // Staff only

        return true;
    }

    // Processes all requests in the queue
    void processRequests() {
        while (!requestQueue.isEmpty()) {
            Request* req = requestQueue.dequeue();

            cout << "\nProcessing request for " << req->name << ": "
                 << "From Floor " << req->fromFloor
                 << " to Floor " << req->toFloor
                 << " at " << req->hour << ":"
                 << (req->minute < 10 ? "0" : "") << req->minute << endl;

            if (checkAccess(req)) {
                cout << "Access granted. Elevator moving...\n";
            } else {
                cout << "Access denied due to hotel rules.\n";
            }
        }
    }

    // Displays all requests made (history)
    void showAllRequests() {
        cout << "\nAll Requests:\n";
        Request* temp = requestListHead;
        while (temp) {
            cout << temp->name << " requested Floor " << temp->toFloor
                 << " at " << temp->hour << ":"
                 << (temp->minute < 10 ? "0" : "") << temp->minute << endl;
            temp = temp->next;
        }
    }
};

// Main function to demonstrate system functionality
int main() {
    ElevatorSystem system;

    system.addRequest("John", 1, 3, 9, 5);     // Should be denied
    system.addRequest("Emily", 2, 2, 6, 0);    // Should be allowed
    system.addRequest("admin", 1, 5, 10, 0);   // Admin access allowed
    system.addRequest("Guest", 1, 5, 10, 0);   // Guest denied

    system.processRequests();
    system.showAllRequests();

    return 0;
}
