
# Elevator Request Management System

## Project Description
This project simulates a simple elevator request management system for a hotel using a queue and linked list structure. It processes guest requests to move between floors while enforcing hotel-specific access policies.

## Installation Instructions
1. Make sure you have a C++ compiler installed (e.g., g++, clang++).
2. Clone or download this repository to your local machine.

## How to Run the Code
1. Open a terminal or command prompt.
2. Navigate to the project directory.
3. Compile the code using:
   ```bash
   g++ elevator_system.cpp -o elevator_system
   ```
4. Run the compiled program:
   ```bash
   ./elevator_system
   ```

## Usage Examples
- `John` attempts to access floor 3 after 9:00 AM and is denied.
- `Emily` successfully requests a move within allowed floors and times.
- Only an `admin` user can access the staff-only 5th floor.

## Notes
- The system enforces specific access rules based on the guest name, floor number, and request time.
- All requests are logged and displayed after processing.
