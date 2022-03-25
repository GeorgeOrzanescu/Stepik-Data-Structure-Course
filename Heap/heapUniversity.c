#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>


typedef struct 
{
    int priority;
    char *callerName;
     
} EmergencyCall;


typedef struct
{
    EmergencyCall *vector;
    int numElem;
} heap;


void bubbleUp(heap h,int index){
    int indexMax = index; // root node
    int indexLeft = 2 * index + 1; // left children
    int indexRight = 2 * index + 2;// right children

    if(indexLeft < h.numElem && h.vector[indexLeft].priority > h.vector[indexMax].priority)
    {
        indexMax = indexLeft;
    }
    if(indexRight < h.numElem && h.vector[indexRight].priority > h.vector[indexMax].priority)
    {
        indexMax = indexRight;
    }

    if (index != indexMax) {
        EmergencyCall temp = h.vector[index];
        h.vector[index] = h.vector[indexMax];
        h.vector[indexMax] = temp;

        bubbleUp(h, indexMax); // repeat from the last position
    }
}

void insertion(heap* h,EmergencyCall call){
    EmergencyCall *vect1 = (EmergencyCall *)malloc((h->numElem + 1)*sizeof(EmergencyCall));
    for (int i = 0; i < (h->numElem + 1); i++)
    {
        vect1[i] = h->vector[i]; // copy all previous elements
    }
    h->numElem++; 
    free(h->vector);  // dezalocate memory
    h->vector = vect1; // repoint to the new array

    h->vector[h->numElem - 1] = call;

    // sort the heap
    for (int i = (h->numElem - 1) / 2 ; i>=0 ; i--)
    {
        bubbleUp(*h, i);
    }
}


void extractRoot(heap* h,EmergencyCall* call){
    EmergencyCall *vect1 = (EmergencyCall *)malloc((h->numElem -1)*sizeof(EmergencyCall));

    EmergencyCall temp = h->vector[0];  // first element becomes last
    h->vector[0] = h->vector[h->numElem - 1];
    h->vector[h->numElem - 1] = temp;

    *call = h->vector[h->numElem - 1];
    for (int i = 0; i < (h->numElem - 1); i++)
    {
        vect1[i] = h->vector[i]; // copy all previous except last
    }

    h->numElem--;
    free(h->vector);
    h->vector = vect1;

    // sort the heap
    for (int i = (h->numElem - 1) / 2 ; i>=0 ; i--)
    {
        bubbleUp(*h, i);
    }

}

int main(){

    heap h;
    printf("Number of elements: ");
    scanf("%d", &h.numElem);

    char buffer[20];
    h.vector = (EmergencyCall*)malloc(h.numElem * sizeof(EmergencyCall));

    for (int i = 0; i < h.numElem; i++)
    {
        printf("Priority: ");
        scanf("%d", &h.vector[i].priority);
        printf("Name of caller: ");
        scanf("%s", buffer);
        h.vector[i].callerName = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(h.vector[i].callerName, buffer);
    }
    
    for (int i = (h.numElem - 1) / 2 ; i>=0 ; i--)
    {
        bubbleUp(h, i);
    }

    EmergencyCall lastCall;
    lastCall.callerName = (char *)malloc((strlen("Test") + 1) * sizeof(char));
    strcpy(lastCall.callerName, "Test");
    lastCall.priority = 200;
    insertion(&h, lastCall);





    for (int i = 0; i < h.numElem; i++)
    {
        printf("Priority: \n");
        printf("%d",h.vector[i].priority);
        printf("Name of caller: \n");
        printf("%s",h.vector[i].callerName);
    }


    // EXTRACT ROOT
    EmergencyCall extractedCall;
    extractRoot(&h, &extractedCall);

    printf("Caller-ul with priority: %d has been extracted!", extractedCall.priority);

    for (int i = 0; i < h.numElem; i++)
    {
        printf("Priority: \n");
        printf("%d",h.vector[i].priority);
        printf("Name of caller: \n");
        printf("%s",h.vector[i].callerName);
    }


    return 0;
}


