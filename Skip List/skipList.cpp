#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Node
{
public:
    int data;
    vector<Node *> next;
    vector<Node *> prev;

    Node()
    {
        data = 0;
        next.resize(3);
        prev.resize(3);
    }

    Node(int _data)
    {
        data = _data;
        next.resize(3);
        prev.resize(3);
    }

    Node(const Node &n)
    {
        data = n.data;
        next = n.next;
        prev = n.prev;
    }

    void linkNodes(Node *_prev, Node *_next, int layer)
    {
        _prev->next.insert(_prev->next.begin() + layer, _next);
        _next->prev.insert(_next->prev.begin() + layer, _prev);
    }

    void printNode()
    {
        cout << "\n"
             << endl;
        cout << data << " " << endl;
        for (int i = 0; i < next.size(); i++)
        {
            if (next[i] != nullptr)
                cout << "Layer" << i << next[i]->data << " \n";
            else
                cout << "Layer" << i << "NULL ";
        }
        cout << endl;
        for (int i = 0; i < prev.size(); i++)
        {
            if (prev[i] != nullptr)
                cout << "Layer" << i << prev[i]->data << "\n ";
            else
                cout << "Layer" << i << "NULL ";
        }
    }

    bool findNode(Node *head, int data)
    {
        Node *current = head;
        int layer = head->next.size() - 1;
        while (layer >= 0)
        {
            if (current->data == data)
            {
                return true;
            }
            else if (current->next[layer] == NULL || current->next[layer]->data > data)
            {
                layer = layer - 1;
            }
            else
                current = current->next[layer];
        }
        return false;
    }

    void insertNode(Node *head, int data)
    {
        Node *current = head;
        int layer = head->next.size() - 1;

        while (layer >= 0)
        {
            if (current->next[layer] == NULL || current->next[layer]->data > data)
            {
                layer = layer - 1;
            }
            else if (current->next[layer]->data > data)
            {
                break;
            }
            else
            {
                current = current->next[layer];
            }
        }

        Node *newnode = new Node(data);
        newnode->linkNodes(current, newnode, 0);

        // find suitable forward node to link to
        int suitableLayer = 0;
        for (int i = 0; i < newnode->next.size(); i++)
        {
            if (current->next[i] == NULL)
            {
                continue;
            }
            else
            {
                suitableLayer = i;
            }
        }
        newnode->linkNodes(newnode, current->next[suitableLayer], 1);
    }
};
int main()
{

    Node head;
    Node first(1);
    Node second(2);
    Node third(3);
    Node seventh(7);

    head.linkNodes(&head, &first, 0);
    head.linkNodes(&first, &second, 0);
    head.linkNodes(&head, &third, 1);
    head.linkNodes(&third, &seventh, 1);

    // head.printNode();
    // first.printNode();
    // second.printNode();
    // third.printNode();
    // seventh.printNode();

    head.insertNode(&head, 4);
    third.printNode();
    seventh.printNode();
}