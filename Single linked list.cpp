#include <iostream>

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {} // Constructor for cleaner allocation
    };

    Node* head = nullptr;
    int listSize = 0;

public:
    // Destructor automatically safely clears memory when the object goes out of scope
    ~LinkedList() {
        clear();
    }

    void insertAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    void insertAtTail(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        listSize++;
    }

    void insertAt(int value, int position) {
        if (position < 1 || position > listSize + 1) {
            std::cout << "Invalid Position Input\n";
            return;
        }
        if (position == 1) {
            insertAtHead(value);
            return;
        }

        Node* newNode = new Node(value);
        Node* temp = head;
        for (int i = 1; i < position - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        listSize++;
    }

    void removeAtHead() {
        if (!head) {
            std::cout << "List Is Already Empty\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp; // Fixed memory leak
        listSize--;
    }

    void removeAtTail() {
        if (!head) {
            std::cout << "List Is Already Empty\n";
            return;
        }
        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
        listSize--;
    }

    void removeAt(int position) {
        if (position < 1 || position > listSize) {
            std::cout << "Invalid Position Input or Exceeded End of List\n";
            return;
        }
        if (position == 1) {
            removeAtHead();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position - 1; i++) {
            temp = temp->next;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        listSize--;
    }

    int retrieveAt(int position) {
        if (position < 1 || position > listSize) {
            std::cout << "Invalid Position Input or Exceeded End of List\n";
            return -1;
        }
        Node* temp = head;
        for (int i = 1; i < position; i++) {
            temp = temp->next;
        }
        std::cout << "Item At Position (" << position << ") = ";
        return temp->data;
    }

    void replaceAt(int newData, int position) {
        if (position < 1 || position > listSize) {
            std::cout << "Invalid Position Input or Exceeded End of List\n";
            return;
        }
        Node* temp = head;
        for (int i = 1; i < position; i++) {
            temp = temp->next;
        }
        temp->data = newData;
    }

    bool isExist(int value) {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) {
                std::cout << "Element Is Found\n";
                return true;
            }
            temp = temp->next;
        }
        std::cout << "Element Is Not Found\n";
        return false;
    }

    bool isItemAtEqual(int value, int position) {
        if (position < 1 || position > listSize) {
            std::cout << "Position Exceeded The End Of List\n";
            return false;
        }
        Node* temp = head;
        for (int i = 1; i < position; i++) {
            temp = temp->next;
        }
        if (temp->data == value) {
            std::cout << "YES, Item Is Found In This Position\n";
            return true;
        }
        std::cout << "NO, Item Is Not Found In This Position\n";
        return false;
    }

    void swapNodes(int position1, int position2) {
        if (position1 < 1 || position2 < 1 || position1 > listSize || position2 > listSize) {
            std::cout << "Invalid Position Input\n";
            return;
        }
        if (position1 == position2) {
            std::cout << "Can't Swap The Same Positions\n";
            return;
        }

        Node *prev1 = nullptr, *curr1 = head;
        for (int i = 1; i < position1; i++) {
            prev1 = curr1;
            curr1 = curr1->next;
        }

        Node *prev2 = nullptr, *curr2 = head;
        for (int i = 1; i < position2; i++) {
            prev2 = curr2;
            curr2 = curr2->next;
        }

        if (prev1) prev1->next = curr2;
        else head = curr2;

        if (prev2) prev2->next = curr1;
        else head = curr1;

        Node* temp = curr2->next;
        curr2->next = curr1->next;
        curr1->next = temp;
    }

    bool isEmpty() const {
        if (!head) {
            std::cout << "List Is Empty\n";
            return true;
        }
        std::cout << "List Is Not Empty\n";
        return false;
    }

    int linkedListSize() const {
        std::cout << "Linked List Size = ";
        return listSize; // O(1) performance optimization
    }

    void clear() {
        if (!head) {
            std::cout << "List Is Already Empty\n";
            return;
        }
        // Fixed memory leak: properly traversing and freeing node blocks
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }

    void PrintList() const {
        if (!head) {
            std::cout << "List Is Empty\n";
            return;
        }
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }
};

int main() {
    LinkedList list;

    std::cout << "Inserting Values at the Tail of the Linked List \n";
    list.insertAtTail(6);
    list.insertAtTail(48);
    list.insertAtTail(51);
    list.insertAtTail(8);
    list.insertAtTail(19);
    std::cout << "List after inserting at Tail: \n";
    list.PrintList();
    std::cout << list.linkedListSize() << "\n\n";

    std::cout << "Inserting Values at the Head of the Linked List \n";
    list.insertAtHead(16);
    list.insertAtHead(2);
    list.insertAtHead(12);
    list.insertAtHead(80);
    list.insertAtHead(1);
    std::cout << "List after inserting at Head: \n";
    list.PrintList();
    std::cout << list.linkedListSize() << "\n\n";

    std::cout << "Inserting Values (10,3) at Positions (3,7) of the Linked List \n";
    list.insertAt(10, 3);
    list.insertAt(3, 7);
    std::cout << "List after inserting Values at different Positions: \n";
    list.PrintList();
    std::cout << list.linkedListSize() << "\n\n";

    std::cout << "Removing two values from the Head of the linked list \n";
    list.removeAtHead();
    list.removeAtHead();
    std::cout << "List after removing the values: \n";
    list.PrintList();
    std::cout << list.linkedListSize() << "\n\n";

    std::cout << "Removing two values from the Tail of the linked list \n";
    list.removeAtTail();
    list.removeAtTail();
    std::cout << "List after removing the values: \n";
    list.PrintList();
    std::cout << list.linkedListSize() << "\n\n";

    std::cout << "Removing the value of Position (5) from the Linked List \n";
    list.removeAt(5);
    std::cout << "List after removing the value: \n";
    list.PrintList();
    std::cout << list.linkedListSize() << "\n\n";

    std::cout << "Retrieving the value of Position (4) from the Linked List \n";
    std::cout << list.retrieveAt(4) << "\n\n";

    std::cout << "Replacing the Data of Position (3) with Value (100) in the Linked List \n";
    list.replaceAt(100, 3);
    std::cout << "List after replacing the Data: \n";
    list.PrintList();
    std::cout << list.linkedListSize() << "\n\n";

    std::cout << "Checking if the value (16) exists in the Linked List or Not \n";
    list.isExist(16);
    std::cout << "Checking if the value (166) exists in the Linked List or Not \n";
    list.isExist(166);
    std::cout << "\n";

    std::cout << "Linked list Elements: ";
    list.PrintList();
    std::cout << "Checking if the value (16) is at the Position (3) in the Linked List or Not \n";
    list.isItemAtEqual(16, 3);
    std::cout << "Checking if the value (16) is at the Position (4) in the Linked List or Not \n";
    list.isItemAtEqual(16, 4);
    std::cout << "\n";

    std::cout << "Linked list before swapping: ";
    list.PrintList();
    std::cout << "Linked list after swapping the nodes of Position (1) and (5): ";
    list.swapNodes(1, 5);
    list.PrintList();
    std::cout << "\n";

    std::cout << "Checking if the Linked List is empty or Not \n";
    list.isEmpty();
    std::cout << "Clearing the linked list \n";
    list.clear();
    std::cout << "Checking if the Linked List is empty or Not \n";
    list.isEmpty();
    std::cout << "Checking the Linked List and the Size \n";
    list.PrintList();
    std::cout << list.linkedListSize() << "\n";

    return 0;
}