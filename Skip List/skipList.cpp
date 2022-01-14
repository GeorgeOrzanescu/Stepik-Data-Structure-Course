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
        next.push_back(nullptr);
        prev.push_back(nullptr);
    }

    Node(int _data)
    {
        data = _data;
        next.push_back(nullptr);
        prev.push_back(nullptr);
    }

    // Node(const Node &n)
    // {
    //     data = n.data;
    //     next = n.next;
    //     prev = n.prev;
    // }

    void linkNodes(Node *_prev, Node *_next, int layer)
    {
        _prev->next.emplace(_prev->next.begin() + layer, _next);
        _next->prev.emplace(_next->prev.begin() + layer, _prev);
    }

    void printNode()
    {
        cout << "\n"
             << endl;
        cout << data << " " << endl;
        for (int i = 0; i < next.size(); i++)
        {
            if (next[i] != nullptr)
                cout << next[i]->data << " \n";
            else
                cout << "NULL ";
        }
        cout << endl;
        for (int i = 0; i < prev.size(); i++)
        {
            if (prev[i] != nullptr)
                cout << prev[i]->data << "\n ";
            else
                cout << "NULL ";
        }
    }
};

int main()
{

    Node head;
    Node first(1);
    Node second(2);
    Node third(3);

    head.linkNodes(&head, &first, -1);
    head.linkNodes(&head, &third, 1);

    head.printNode();
    first.printNode();
    third.printNode();
}