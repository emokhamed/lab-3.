#include <iostream>
#include <string>
using namespace std;

struct Node {
    string flightNumber;
    string departureDate;
    string destination;
    string passenger;
    Node* left;
    Node* right;

    Node(string number, string date, string dest, string name) {
        flightNumber = number;
        departureDate = date;
        destination = dest;
        passenger = name;
        left = nullptr;
        right = nullptr;
    }
};

class TicketRequests {
private:
    Node* root;

public:
    TicketRequests() {
        root = nullptr;
    }

    void addRequest(string flightNumber, string departureDate, string destination, string passenger) {
        Node* newNode = new Node(flightNumber, departureDate, destination, passenger);
        if (root == nullptr) {
            root = newNode;
        }
        else {
            addRecursive(root, newNode);
        }
    }

    void addRecursive(Node* currentNode, Node* newNode) {
        if (newNode->flightNumber < currentNode->flightNumber) {
            if (currentNode->left == nullptr) {
                currentNode->left = newNode;
            }
            else {
                addRecursive(currentNode->left, newNode);
            }
        }
        else {
            if (currentNode->right == nullptr) {
                currentNode->right = newNode;
            }
            else {
                addRecursive(currentNode->right, newNode);
            }
        }
    }

    void removeRequests(string flightNumber, string departureDate) {
        root = removeRecursive(root, flightNumber, departureDate);
    }

    Node* removeRecursive(Node* currentNode, string flightNumber, string departureDate) {
        if (currentNode == nullptr) {
            return nullptr;
        }
        if (flightNumber < currentNode->flightNumber) {
            currentNode->left = removeRecursive(currentNode->left, flightNumber, departureDate);
        }
        else if (flightNumber > currentNode->flightNumber) {
            currentNode->right = removeRecursive(currentNode->right, flightNumber, departureDate);
        }
        else {
            if (departureDate == currentNode->departureDate) {
                if (currentNode->left == nullptr && currentNode->right == nullptr) {
                    delete currentNode;
                    return nullptr;
                }
                else if (currentNode->left == nullptr) {
                    Node* temp = currentNode->right;
                    delete currentNode;
                    return temp;
                }
                else if (currentNode->right == nullptr) {
                    Node* temp = currentNode->left;
                    delete currentNode;
                    return temp;
                }
                else {
                    Node* minNode = findMin(currentNode->right);
                    currentNode->flightNumber = minNode->flightNumber;
                    currentNode->departureDate = minNode->departureDate;
                    currentNode->destination = minNode->destination;
                    currentNode->passenger = minNode->passenger;
                    currentNode->right = removeRecursive(currentNode->right, minNode->flightNumber, minNode->departureDate);
                }
            }
            else {
                currentNode->right = removeRecursive(currentNode->right, flightNumber, departureDate);
            }
        }
        return currentNode;
    }

    Node* findMin(Node* currentNode) {
        while (currentNode->left != nullptr) {
            currentNode = currentNode->left;
        }
        return currentNode;
    }

    void printRequests() {
        printRecursive(root);
    }

    void printRecursive(Node* currentNode) {
        if (currentNode != nullptr) {
            printRecursive(currentNode->left);
            cout << "Flight: " << currentNode->flightNumber << endl;
            cout << "Departure Date: " << currentNode->departureDate << endl;
            cout << "Destination: " << currentNode->destination << endl;
            cout << "Passenger: " << currentNode->passenger << endl;
            cout << endl;
            printRecursive(currentNode->right);
        }
    }
};

int main() {
    TicketRequests requests;

    // Добавление заявок
    requests.addRequest("FL123", "2024-01-01", "Moscow", "Mohamed Esam");
    requests.addRequest("FL456", "2024-03-02", "London", "Abdoo");
    requests.addRequest("FL789", "2024-02-02", "Paris", "Burhan");

    // Вывод всех заявок
    cout << "All requests:" << endl;
    requests.printRequests();
    cout << endl;

    // Удаление заявки по номеру рейса и дате вылета
    requests.removeRequests("FL456", "2024-03-02");

    // Вывод всех заявок после удаления
    cout << "Requests after removal:" << endl;
    requests.printRequests();

    return 0;
}
