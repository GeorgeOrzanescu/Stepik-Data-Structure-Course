#include <iostream>
#include <vector>
using namespace std;
/*
we will think of arrays specifically in the context 
of using them to store contiguous lists of elements: an Array List. 
In other words, we'll assume that there are no empty cells between elements in the array 
(even though an array in general has no such restriction).
*/

// Finding an element takes O(n) time in an arbitrary array list.
bool findElement(vector<int> myVector, int element)
{
    for (int i = 0; i < myVector.size(); i++)
    {
        if (myVector[i] == element)
        {
            return true;
        }
    }
    return false;
};

// removing an element by value takes O(n) time in an arbitrary array list.
// !! must pass as reference to actually remove the element from the vector
void removeElementValue(vector<int> &myVector, int element)
{
    for (int i = 0; i < myVector.size(); i++)
    {
        if (myVector[i] == element)
        {
            myVector.erase(myVector.begin() + i);
        }
    }
};
// removing and element takes O(1) constant time in an array list if u use the index.
void removeElementbyIndex(vector<int> &myVector, int index)
{
    myVector.erase(myVector.begin() + index);
};

// adding an element to the back or front takes O(1) time in an array list.
void insertElementBack(vector<int> &myVector, int element)
{
    myVector.push_back(element);
};

// IF THE ELEMENTS IN THE ARRAY LIST ARE SORTED
// finding an element takes O(log n) time.

bool findElementBinarySearch(vector<int> myVector, int element)
{
    int low = 0;
    int high = myVector.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (myVector[mid] == element)
        {
            return true;
        }
        else if (myVector[mid] < element)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return false;
};

int main()
{

    vector<int> myVector = {1, 2, 4, 5, 6, 8, 3, 9, 10, 7, 11};
    vector<int> myVectorSorted = {1, 2, 4, 5, 6, 8, 9, 10, 11};

    int arrayList[] = {1, 2, 4, 5, 6, 8, 3, 9, 10, 7, 11};

    cout << findElement(myVector, 43) << endl;

    removeElementValue(myVector, 7);

    insertElementBack(myVector, 7);

    for (int i = 0; i < myVector.size(); i++)
    {
        cout << myVector[i] << " ";
    }

    cout << "\n"
         << findElementBinarySearch(myVector, 7)
         << findElementBinarySearch(myVector, 8);

    return 0;
}