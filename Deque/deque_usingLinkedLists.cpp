#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

class Deque
{

    Node *head;
    Node *tail;
    int size;

public:
    Deque()
    {
        head = tail = nullptr;
        size = 0;
    }

    void push_back(int data)
    {
        Node *newNode = new Node();
        newNode->data = data;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void push_front(int data)
    {
        Node *newNode = new Node();
        newNode->data = data;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void pop_back()
    {
        if (tail == nullptr)
        {
            cout << "Deque is empty" << endl;
            return;
        }
        else
        {
            Node *temp = tail; // so we don't leave tail dangling
            tail = tail->prev;
            tail->next = nullptr;
            delete temp; // delete the tangling tail
            size--;
        }
    }

    void pop_front()
    {
        if (head == nullptr)
        {
            cout << "Deque is empty" << endl;
            return;
        }
        else
        {
            Node *temp = head; // so we don't leave head dangling
            head = head->next;
            head->prev = nullptr;
            delete temp; // delete the tangling head
            size--;
        }
    }

    void printDeque()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main()
{

    Deque d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_front(0);
    d.push_front(-1);

    d.pop_back();
    d.pop_front();
    d.printDeque();

    return 0;
}