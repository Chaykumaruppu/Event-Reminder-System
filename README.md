# Event Reminder System

The **Event Reminder System** is a console-based C++ application developed as part of a summer training program at Cipher School. It allows users to manage events by adding, viewing, marking as done, deleting, and searching events using a trie data structure for efficient prefix-based title searches. The system includes file persistence to retain events between sessions, making it a robust tool for event management. This project is developed by Uppu Chaithanya Kumar, Lovely Professional University (Registration Number: 12113448).

## Features
- **Add Event**: Create events with a title, description, and date (YYYY-MM-DD format).
- **View Events**: Display all events with their details and completion status.
- **Remove Event**: Delete an event by its index.
- **Mark Event as Done**: Toggle an event's completion status.
- **View Completed Events**: Show only completed events.
- **Search by Title Prefix**: Perform case-insensitive searches for events using a trie data structure.
- **File Persistence**: Save events to `events.txt` and load them on program startup.

## Prerequisites
- C++ compiler (e.g., g++)

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/event-reminder-system.git
   ```
2. **Navigate to the Directory**:
   ```bash
   cd event-reminder-system
   ```
3. **Compile the Code**:
   ```bash
   g++ -o event_reminder main.cpp
   ```
4. **Run the Program**:
   ```bash
   ./event_reminder
   ```

## Usage
Run the program and select options from the menu:
1. **Add Event**: Enter title, description, and date (e.g., 2025-05-15).
2. **View Events**: See all events with their details.
3. **Remove Event**: View events, then enter the event number to delete.
4. **Mark Event as Done**: View events, then enter the event number to toggle status.
5. **View Completed Events**: Display only completed events.
6. **Search Events by Title Prefix**: Enter a title prefix (e.g., "birth") to find matching events.
7. **Exit**: Save events to `events.txt` and exit.

## Sample Output
```
Welcome to Event Reminder Management System
1. Add Event
2. View Events
3. Remove Event
4. Mark Event as Done
5. View Completed Events
6. Search Events by Title Prefix
7. Exit
Enter your choice: 1
Enter title: Birthday chaitu 13 sept
Enter description: chaithanya's birthday 13 september
Enter date (YYYY-MM-DD): 2025-09-13
```

## Data Structure Usage
- **Trie**: Implements efficient, case-insensitive prefix-based search for event titles, with a time complexity of O(p + n), where p is the prefix length and n is the number of matching events.
- **Vector**: Stores events for easy management and iteration.
- **File I/O**: Uses `fstream` for persistent storage in `events.txt` with `|` as a delimiter.

## Notes
- Dates must be in `YYYY-MM-DD` format.
- Title searches are case-insensitive (e.g., "birth" matches "Birthday chaitu").
- Events are saved to `events.txt` automatically on exit.

## Future Enhancements
- Add a Qt-based GUI for a user-friendly interface.
- Implement a background thread for real-time reminders.
- Sort events by date using a map for efficient retrieval.
- Add date format validation using regex.

## Author
- **Name**: Uppu Chaithanya Kumar
- **Institution**: Lovely Professional University
- **Registration Number**: 12113448
- **Training Organization**: Cipher School

## License
This project is licensed under the MIT License.
