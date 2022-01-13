#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node *prev;

    Node()
    {
        data = 0; // TAIL will always be 0
        next = nullptr;
        prev = nullptr;
    }

    void printList(Node *head)
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void InsertFront(Node *&head, Node *&tail, int data)
    {
        Node *newNode = new Node();
        newNode->data = data;

        if (head->next == NULL)
        {
            cout << "Insert front if list is empty" << endl;

            head = newNode;
            head->next = tail;
            tail->prev = head;
        }
        else
        {
            cout << "Insert front if list is NOT empty" << endl;

            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void InsertBack(Node *&head, Node *&tail, int data)
    {
        Node *newNode = new Node();
        newNode->data = data;

        if (tail->prev == NULL)
        {
            cout << "Insert back if list is empty" << endl;

            head = newNode;
            head->next = tail;
            tail->prev = head;
        }
        else
        {
            cout << "Insert back if list is NOT empty" << endl;
            newNode->prev = tail->prev;
            tail->prev->next = newNode;

            tail->prev = newNode;
            newNode->next = tail;
        }
    }
};

int main()
{
    Node *head = new Node();
    Node *tail = new Node();

    head->InsertBack(head, tail, 10);
    head->InsertFront(head, tail, 1);
    head->InsertFront(head, tail, 3);

    head->printList(head);
    cout << "Tail data" << tail->data << endl;

    head->InsertBack(head, tail, 20);
    cout << tail->data << endl;
    cout << tail->prev->data << endl;
    head->InsertBack(head, tail, 30);

    head->printList(head);

    return 0;
}