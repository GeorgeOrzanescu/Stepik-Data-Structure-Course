#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define LAYER_MAX 4

using namespace std;

//  practice random value and layer generator
/*
The rand() function is used in C/C++
 to generate random numbers in the range (0, RAND_MAX). 
*/
int generateRandomLayer()
{
    srand((unsigned)time(NULL));
    return rand() % 2;
}

// practice create node for the linked list

class Node
{
public:
    int value;
    Node **next;
    Node(int level, int value)
    {
        this->value = value;
        next = new Node *[level + 1]; // create a new array of pointers as layers
        memset(next, 0, sizeof(Node *) * (level + 1));
    }

    Node operator=(Node &node)
    {
        this->value = node.value;
        this->next = node.next;

        return *this;
    }

    ~Node()
    {
        delete[] next;
    }

    void display()
    {
        cout << "value: " << value << endl;
        for (int i = 0; i < LAYER_MAX; i++)
        {
            cout << "next[" << i << "]: " << next[i] << endl;
        }
    }
};

class SkipList
{
public:
    Node *head;
    int value;
    int layer;

    SkipList()
    {
        // head layer
        head = new Node(LAYER_MAX, value);
        layer = 0;
    }
    ~SkipList()
    {
        delete head;
    }

    void insertNode(int);
    void displaySl();
};

int main()
{

    Node header(4, 1);

    SkipList sl;

    sl.insertNode(1);
    sl.insertNode(4);
    sl.insertNode(2);

    sl.displaySl();
    return 0;
}

void SkipList::insertNode(int value)
{
    Node *x = head;
    Node *update[LAYER_MAX + 1];

    memset(update, 0, sizeof(Node *) * (LAYER_MAX + 1));

    for (int i = layer; i >= 0; i--)
    {
        while (x->next[i] != NULL && x->next[i]->value < value)
        {
            x = x->next[i];
        }
        update[i] = x;
    }
    x = x->next[0];

    if (x == NULL || x->value != value)
    {
        int newLayer = 0;
        bool coinToss = true;
        while (coinToss)
        {
            int randGen = generateRandomLayer();
            cout << "randGen: " << randGen << endl;
            if (randGen < 1 && newLayer < LAYER_MAX)
            {
                newLayer++;
            }
            else if (randGen == 1)
            {
                coinToss = false;
            }
        }
        cout << newLayer;

        if (newLayer > layer)
        {
            for (int i = layer + 1; i <= newLayer; i++)
            {
                update[i] = head;
            }
            layer = newLayer;
        }

        x = new Node(newLayer, value);
        for (int i = 0; i <= newLayer; i++)
        {
            x->next[i] = update[i]->next[i];
            update[i]->next[i] = x;
        }
    }
}

void SkipList::displaySl()
{
    Node *x = head->next[0];
    while (x != NULL)
    {
        cout << x->value;
        x = x->next[0];
        if (x != NULL)
            cout << " - ";
    }
    cout << endl;
}