#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data; // This integer holds the actual data of the node
        Node* prev; // This pointer points to the next node in the dll
        Node* next; // This pointer points to the previous node in the dll
        // This is a full parameter constructor for node, which can takes the data value
        // pointer to the previous node, and pointer to the next node. However,
        // The p and n can also be left blank, as they are by deafult set to nullptr.
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head; // Pointer to the first node in the dll
    Node* tail; // Pointer to the last node in the dll

public:
    // Default constructor for the actual dll itself
    // Doesn't take any parameters, instead setting head and tail to null by default
    // Which means an empty dll
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // insert_after() inserts a node after the node in position n
    // parameters: int value    - the actual data to be held by the new node
    //             int position - the position of the node to be inserted after
    // returns: void
    void insert_after(int value, int position) {
        // Ofc you can't insert a node in a negative position\
        // So this is a guard clause
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        // Creates a new node and initializes it with value
        // But the head and tail pointers remain unitialized
        Node* newNode = new Node(value);
        if (!head) { // If the list is empty, aka head is null set both head and tail to the new node
            head = tail = newNode;
            return;
        }

        Node* temp = head; // set a temporary node to head so we can iterate
        // Iterate until either
        // a. We reach the position n, which means temp will hold the node before where we want to insert
        // b. temp points to null, meaning we've passed the tail
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next; // Go to next node

        if (!temp) { // If the temp is null, that means we've passed the tail node and so the position is invalid
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // delete to clean up memory
            return;
        }

        newNode->next = temp->next; // set the next of the newnode, to the next of the node before it
        // In other words, we're attatching the succeeding node to the newnode
        newNode->prev = temp; // set the previous of newnode to the the temp node, because we're inserting
        // newnode after temp, so logically temp is the preceeder of newnode.
        if (temp->next) // If the node following temp before the insertion exists, aka if temp is not tail
            temp->next->prev = newNode; // Set the previous of the node following temp to newnode
        else
            tail = newNode; // Otherwise, newnode becomes the new tail
        temp->next = newNode; // and set the next of temp to be newnode cus we inserted it after
    }

    // delete_val() deletes the node with value value from the dll
    // parameters: int value - the value held by the node to be deleted
    // returns: void
    void delete_val(int value) {
        if (!head) return; // If the list is empty we can't remove anything

        Node* temp = head; // Set a temporary node to the head for traversal
        
        // Traverse until temp is nullptr in which we have passed the tail
        // Or until the data held by temp matches the value we want to delete
        while (temp && temp->data != value)
            temp = temp->next;

        // If the temp is null we've passed the tail and the value isn't in the dll
        if (!temp) return; 

        // If the temp has a previous, aka not the head
        if (temp->prev)
            temp->prev->next = temp->next; // Set the next of the preceeding node to the next
            // of the current node, basically bypassing
        else
            head = temp->next;  // Otherwise the new head becomes the succeeding node

        // If the temp has a next, aka not the tail
        if (temp->next)
            temp->next->prev = temp->prev; // Set the prev of the succeeding node to the prev
            // of the current node, basically bypassing
        else
            tail = temp->prev;  // Otherwise the new tail becomes the preceeding node

        delete temp; // delete temp so no memory leaks
    }

    // delete_pos() deletes the node in position n
    // parameters: int pos - position of the node to be deleted
    // returns void
    void delete_pos(int pos) {
        if (!head) { // If the head is nullptr then the list is empty and we can't delete anythig
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) { // If position is 1 we're deleting the head node
            pop_front(); // so we just pop the front of the list
            return;
        }
    
        Node* temp = head; // Sets a temp node to head for traversal
    
        for (int i = 1; i < pos; i++){ // Traverse the dll starting from 1 to pos
            if (!temp) { // If temp is nullptr means we've passed the tail and position is out of bounds
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next; // otherwise set temp to the node suceeding temp
        }
        if (!temp) { // If temp is nullptr means we've passed thet ail and the position is out of bounds
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) { // If temp has no succeesor, we're deleting the tail node
            pop_back(); // so we just pop the back of the list
            return;
        }
    
        Node* tempPrev = temp->prev; // tempprev
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}