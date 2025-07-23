#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm> // For transform and tolower

using namespace std;

// Event class to store event details
class Event {
private:
    string title;
    string description;
    string date;
    bool isCompleted;

public:
    Event(string t, string d, string dt) : title(t), description(d), date(dt), isCompleted(false) {}

    string getTitle() const { return title; }
    string getDescription() const { return description; }
    string getDate() const { return date; }
    bool getStatus() const { return isCompleted; }
    void changeStatus() { isCompleted = !isCompleted; }
    void setStatus(bool s) { isCompleted = s; }
};

// Trie Node for search functionality
struct TrieNode {
    map<char, TrieNode*> children;
    bool isEndOfWord;
    size_t eventIndex;

    TrieNode() : isEndOfWord(false), eventIndex(-1) {}
};

// Trie class for efficient title search
class Trie {
private:
    TrieNode* root;

    void collectIndices(TrieNode* node, vector<size_t>& indices) {
        if (node->isEndOfWord) {
            indices.push_back(node->eventIndex);
        }
        for (auto& child : node->children) {
            collectIndices(child.second, indices);
        }
    }

    string toLowerCase(string str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

public:
    Trie() { root = new TrieNode(); }

    void insert(string key, size_t index) {
        key = toLowerCase(key); // Convert to lowercase for case-insensitive search
        TrieNode* current = root;
        for (char c : key) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
        current->eventIndex = index;
    }

    void remove(string key, size_t index) {
        key = toLowerCase(key); // Convert to lowercase for consistency
        TrieNode* current = root;
        for (char c : key) {
            if (current->children.find(c) == current->children.end()) return;
            current = current->children[c];
        }
        if (current->isEndOfWord && current->eventIndex == index) {
            current->isEndOfWord = false;
            current->eventIndex = -1;
        }
    }

    vector<size_t> searchPrefix(string prefix) {
        prefix = toLowerCase(prefix); // Convert to lowercase for search
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return vector<size_t>();
            }
            current = current->children[c];
        }
        vector<size_t> indices;
        collectIndices(current, indices);
        return indices;
    }
};

// ReminderManager class to manage events
class ReminderManager {
private:
    vector<Event> events;
    Trie titleTrie;

public:
    void addEvent(Event e) {
        events.push_back(e);
        titleTrie.insert(e.getTitle(), events.size() - 1);
    }

    void viewEvents() {
        if (events.empty()) {
            cout << "No events to view." << endl;
        } else {
            for (size_t i = 0; i < events.size(); ++i) {
                cout << "Event " << i + 1 << ":" << endl;
                cout << "Title: " << events[i].getTitle() << endl;
                cout << "Description: " << events[i].getDescription() << endl;
                cout << "Date: " << events[i].getDate() << endl;
                cout << "Status: " << (events[i].getStatus() ? "Completed" : "Pending") << endl;
                cout << endl;
            }
        }
    }

    void markEventAsDone(int index) {
        if (index < 0 || index >= events.size()) {
            cout << "Invalid index." << endl;
            return;
        }
        events[index].changeStatus();
    }

    void removeEvent(int index) {
        if (index < 0 || index >= events.size()) {
            cout << "Invalid index." << endl;
            return;
        }
        titleTrie.remove(events[index].getTitle(), index);
        events.erase(events.begin() + index);
    }

    void viewCompletedEvents() {
        bool hasCompleted = false;
        for (size_t i = 0; i < events.size(); ++i) {
            if (events[i].getStatus()) {
                cout << "Event " << i + 1 << ":" << endl;
                cout << "Title: " << events[i].getTitle() << endl;
                cout << "Description: " << events[i].getDescription() << endl;
                cout << "Date: " << events[i].getDate() << endl;
                cout << "Status: Completed" << endl;
                cout << endl;
                hasCompleted = true;
            }
        }
        if (!hasCompleted) {
            cout << "No completed events." << endl;
        }
    }

    void searchEventsByPrefix(string prefix) {
        vector<size_t> indices = titleTrie.searchPrefix(prefix);
        if (indices.empty()) {
            cout << "No events found with prefix '" << prefix << "'." << endl;
        } else {
            for (size_t idx : indices) {
                if (idx < events.size()) {
                    cout << "Event " << idx + 1 << ":" << endl;
                    cout << "Title: " << events[idx].getTitle() << endl;
                    cout << "Description: " << events[idx].getDescription() << endl;
                    cout << "Date: " << events[idx].getDate() << endl;
                    cout << "Status: " << (events[idx].getStatus() ? "Completed" : "Pending") << endl;
                    cout << endl;
                }
            }
        }
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, desc, date, statusStr;
            getline(ss, title, '|');
            getline(ss, desc, '|');
            getline(ss, date, '|');
            getline(ss, statusStr, '|');
            bool status = (statusStr == "1");
            Event e(title, desc, date);
            e.setStatus(status);
            addEvent(e);
        }
        file.close();
    }

    void saveToFile(string filename) {
        ofstream file(filename);
        if (!file.is_open()) return;
        for (const auto& e : events) {
            file << e.getTitle() << "|" << e.getDescription() << "|" << e.getDate() << "|" << (e.getStatus() ? "1" : "0") << endl;
        }
        file.close();
    }

    size_t getEventCount() const { return events.size(); }
};

// Main executor
int main() {
    ReminderManager rm;
    rm.loadFromFile("events.txt");

    int choice;
    do {
        cout << "Welcome to Event Reminder Management System" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. View Events" << endl;
        cout << "3. Remove Event" << endl;
        cout << "4. Mark Event as Done" << endl;
        cout << "5. View Completed Events" << endl;
        cout << "6. Search Events by Title Prefix" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        if (choice == 1) {
            string title, desc, date;
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter description: ";
            getline(cin, desc);
            cout << "Enter date (YYYY-MM-DD): ";
            getline(cin, date);
            Event e(title, desc, date);
            rm.addEvent(e);
        } else if (choice == 2) {
            rm.viewEvents();
        } else if (choice == 3) {
            if (rm.getEventCount() == 0) {
                cout << "No events to remove." << endl;
            } else {
                rm.viewEvents();
                int index;
                cout << "Enter the event number to remove: ";
                cin >> index;
                cin.ignore();
                if (index >= 1 && index <= rm.getEventCount()) {
                    rm.removeEvent(index - 1);
                } else {
                    cout << "Invalid index." << endl;
                }
            }
        } else if (choice == 4) {
            if (rm.getEventCount() == 0) {
                cout << "No events to mark as done." << endl;
            } else {
                rm.viewEvents();
                int index;
                cout << "Enter the event number to mark as done: ";
                cin >> index;
                cin.ignore();
                if (index >= 1 && index <= rm.getEventCount()) {
                    rm.markEventAsDone(index - 1);
                } else {
                    cout << "Invalid index." << endl;
                }
            }
        } else if (choice == 5) {
            rm.viewCompletedEvents();
        } else if (choice == 6) {
            string prefix;
            cout << "Enter title prefix to search: ";
            getline(cin, prefix);
            rm.searchEventsByPrefix(prefix);
        } else if (choice == 7) {
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    rm.saveToFile("events.txt");
    return 0;
}