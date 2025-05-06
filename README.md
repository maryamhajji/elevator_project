# Elevator Request Management System

A simple C++ program that simulates an elevator request system with time-based access control. Users submit elevator ride requests, and the system checks if the destination floor is open at the requested time.

---

## 1. Project Description

This project is designed to handle and process elevator ride requests using a *queue-based data structure*. The system simulates time-based restrictions on certain floors like the gym, library, swimming pool, and restaurant.

Key features:
- Add user requests (with time, source, and destination)
- Check floor access permissions based on time
- Process requests in the order they were received
- Maintain a request history
- Clean terminal menu-based interaction

---

## 2. Installation Instructions

1. Clone this repository:
   ```bash
   git clone https://github.com/YOUR_USERNAME/elevator-system.git
   cd elevator-system

---

## 3. How to Run the Code

Once compiled, run the program using:
./elevator

You’ll see a menu with the following options:
	1.	Add Request
	2.	Process Requests
	3.	Show History
	4.	Exit

 ---
 
 ## 4. Usage Example

Input:

1. Add Request
Name: Sarah
From floor: 1
To floor: 3
Hour: 7

processing: 

Processing: Sarah from 1 to 3 at 7:30
Access granted.

History output:

Request History:
Sarah -> Floor 3 at 7:30 Minute: 30

---

## 5. Notes
•	All time inputs must be in 24-hour format.
•	Requests are stored and processed in order using a queue.
•	History is retained even after requests are processed.
•	This program demonstrates fundamental data structures in C++.
