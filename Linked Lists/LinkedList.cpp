#include <iostream>
#include <vector>
using namespace std;

/*
A Linked List is a data structure composed of nodes: containers that each hold a single element. 
These nodes are "linked" to one another via pointers. 
Typically, we maintain one global head pointer (i.e., a pointer to the first node in the Linked List) 
and one global tail pointer (i.e., a pointer to the last node in a Linked List). 
These are the only two nodes to which we have direct access, 
and all other nodes can only be accessed by traversing pointers starting at either the head or the tail node.

*/

class Node
{
public:
    int data;
    Node *next;
    Node(int data, Node *next)
    {
        this->data = data;
        this->next = next;
    }

    void setNext(Node *next)
    {
        this->next = next;
    }
};

// find an element in a linked list takes O(n) time.
bool findElement(Node *head, int element)
{
    Node *current = head;
    while (current != NULL)
    {
        if (current->data == element)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// inserting an element into a linked list takes O(n) time.
// with the exception of the first element and last, which takes O(1) time.

void insertElement(Node *&head, Node *newNode, int position)
{
    Node *current = head;
    // for adding at the beginning
    if (position == 0)
    {
        newNode->next = current;
        head = newNode;
        return;
    }

    // for adding at the end  BECAUSE IS NOT A DOUBLE LINKED LIST time complexity is O(n)
    if (position == -1)
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
        return;
    }

    for (int i = 0; i < position - 1; i++)
    // -1 because we want to position just before the index we want to insert at
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void removeElement(Node *&head, int position)
{
    Node *current = head;
    // for removing at the beginning
    if (position == 0)
    {
        head = current->next;
        delete current;
        return;
    }

    // for removing at the end
    if (position == -1)
    {
        while (current->next->next != NULL)
        {
            current = current->next; // current is the element before the last element
        }
        delete current->next;
        current->next = NULL;
        return;
    }

    for (int i = 0; i < position - 1; i++)
    // -1 because we want to position just before the index we want to delete at
    {
        current = current->next;
    }

    Node *temp = current->next; // temp is the element we want to delete
    current->next = temp->next; // link the divided elements
    delete temp;                // delete the element we want to delete
}

int main()
{

    Node *head = new Node(1, NULL);
    Node *second = new Node(2, NULL);
    head->setNext(second);
    Node *third = new Node(3, NULL);
    second->setNext(third);
    Node *fourth = new Node(4, NULL);
    third->setNext(fourth);
    Node *tail = new Node(5, NULL);
    fourth->setNext(tail);

    // vector<Node *> myVector = {head, second, third, tail};

    Node *newNode = new Node(6, NULL);
    Node *newNode2 = new Node(7, NULL);
    insertElement(head, newNode, 3);
    insertElement(head, newNode2, -1);

    removeElement(head, 3);
    removeElement(head, -1);

    for (Node *current = head; current != NULL; current = current->next)
    {
        cout << current->data << " ";
    }

    cout << findElement(head, 5) << endl;

    return 0;
}