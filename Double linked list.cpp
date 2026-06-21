#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int listSize = 0;

public:
    // Destructor to ensure clean memory release when object scope terminates
    ~DoublyLinkedList() {
        clear();
    }

    void insertAtHead(T value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }

    void insertAtTail(T value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }

    void insertAt(T value, int position) {
        if (position < 1 || position > listSize + 1) {
            std::cout << "Invalid Position Input\n";
            return;
        }
        if (position == 1) {
            insertAtHead(value);
            return;
        }
        if (position == listSize + 1) {
            insertAtTail(value);
            return;
        }

        Node* newNode = new Node(value);
        Node* temp = head;
        for (int i = 1; i < position - 1; ++i) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
        listSize++;
    }

    void removeAtHead() {
        if (!head) {
            std::cout << "List Is Empty\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        listSize--;
    }

    void removeAtTail() {
        if (!tail) {
            std::cout << "List Is Already Empty\n";
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
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
        if (position == listSize) {
            removeAtTail();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position; ++i) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        delete temp;
        listSize--;
    }

    T retrieveAt(int position) {
        if (position < 1 || position > listSize) {
            std::cout << "Invalid Position Input or Exceeded End of List\n";
            return T();
        }
        Node* temp = head;
        for (int i = 1; i < position; ++i) {
            temp = temp->next;
        }
        std::cout << "Item At Position (" << position << ") = ";
        return temp->data;
    }

    void replaceAt(T newData, int position) {
        if (position < 1 || position > listSize) {
            std::cout << "Invalid Position Input or Exceeded End of List\n";
            return;
        }
        Node* temp = head;
        for (int i = 1; i < position; ++i) {
            temp = temp->next;
        }
        temp->data = newData;
    }

    bool isExist(T value) {
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

    bool isItemAtEqual(T value, int position) {
        if (position < 1 || position > listSize) {
            std::cout << "Position Exceeded The End Of List\n";
            return false;
        }
        Node* temp = head;
        for (int i = 1; i < position; ++i) {
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
            std::cout << "Invalid Position Input or Exceeded End of List\n";
            return;
        }
        if (position1 == position2) {
            std::cout << "Can't Swap The Same Positions\n";
            return;
        }

        Node* curr1 = head;
        for (int i = 1; i < position1; ++i) curr1 = curr1->next;

        Node* curr2 = head;
        for (int i = 1; i < position2; ++i) curr2 = curr2->next;

        // Fortified structural swapping routines to manage adjacency maps safely
        if (curr1->next == curr2) {
            curr1->next = curr2->next;
            curr2->prev = curr1->prev;
            if (curr1->prev) curr1->prev->next = curr2; else head = curr2;
            if (curr2->next) curr2->next->prev = curr1; else tail = curr1;
            curr2->next = curr1;
            curr1->prev = curr2;
        } else if (curr2->next == curr1) {
            curr2->next = curr1->next;
            curr1->prev = curr2->prev;
            if (curr2->prev) curr2->prev->next = curr1; else head = curr1;
            if (curr1->next) curr1->next->prev = curr2; else tail = curr2;
            curr1->next = curr2;
            curr2->prev = curr1;
        } else {
            Node* p1 = curr1->prev;
            Node* n1 = curr1->next;
            Node* p2 = curr2->prev;
            Node* n2 = curr2->next;

            if (p1) p1->next = curr2; else head = curr2;
            if (n1) n1->prev = curr2; else tail = curr2;
            if (p2) p2->next = curr1; else head = curr1;
            if (n2) n2->prev = curr1; else tail = curr1;

            curr1->prev = p2; curr1->next = n2;
            curr2->prev = p1; curr2->next = n1;
        }
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
        return listSize;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
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
    DoublyLinkedList<int> list;

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