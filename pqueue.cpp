//
//Author: Nan Taiym, UIC, Spring 2021
//
//Project 5 part 2
//
//


#include "pqueue.h"
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;
//
// pq_init
//
// Initializes list to empty; must be called before list can 
// be used with other queue functions.
//
void pq_init(List& L)
{
    init_list(L);//calls the function from list.cpp
}

//
// pq_print
// 
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void pq_print(List L)
{
    print_list(L); //calls the print list function from list.cpp
}

//
// pq_front
//
// Returns the ID at the front of the priority queue. Throws 
// an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_front: queue empty");
//
int pq_front(List L)
{
    Node* cur = L.Head; //initializes cur to List head
    int data;
    if(cur != nullptr) // as long as cur != to null
    {
        data = cur->Data.ID; //Pushes the list ti the front and returns ID
    }
    else{ //if cur = null then throw inv argument
        throw invalid_argument("pq_front: queue empty");
    }
    return data;
}

//
// pq_dequeue
//
// Removes the data element at the front of the queue, removing the
// node as well and freeing this memory. Nothing is returned.
// Throws an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_dequeue: queue empty");
//
void pq_dequeue(List& L)
{
    
    Node* cur = L.Head; //initializes cur to List head
    
    if(cur != nullptr) //if cur != null
    {
        remove_from_list(L,0);
    }
    else{ //if cur = null throws invalid argument
        throw invalid_argument("pq_dequeue: queue empty");
    }
}

//
// pq_enqueue
//
// Inserts the given (ID,priority) pair into the queue based on
// the priority, ordered low to high. If elements already exist with
// the same priority, this new element comes after those elements.
// Example: suppose the queue currently contains the following 
// (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to enqueue (79,25) yields the following result:
//
//   (10,19) (84,25) (79,25) (21,50)
//
// If the ID is already in the queue, then the pair is repositioned 
// based on the new priority. For example, suppose the queue is as
// shown above, and we enqueue (84,50). The result is now
//
//   (10,19) (79,25) (21,50) (84,50)
//
void pq_enqueue(List& L, int ID, int priority)
{
    //calls search list function from list.cpp
    if(search_list(L,ID) != -1)
    {
        remove_from_list(L, search_list(L,ID)); //removes the ID from remove_from_list function from list.cpp
    }
    
    Node* cur = L.Head; //initializes cur to List head
    Node* prevCur = nullptr; //initializes prevCur to null
    
    Node* newNode = new Node(); //creates a new Node
    newNode->Data.ID = ID; //stores data from the list into the new Node
    newNode->Data.Priority = priority;
    newNode->Next = nullptr; //sets the next value of the new node to null
    
    while(cur != nullptr) //while cur != null
    {
        if(cur->Data.Priority > priority) //if the priority in cur is > than given priority - breaks
        {
            break;
        }
        prevCur = cur; //sets prevCur to cur and moves cur to next element
        cur = cur->Next;
    }
    
    if(prevCur == nullptr) //if prevCur = null
    {
        newNode->Next = L.Head; //the next newNode to List head
        L.Head = newNode; //List head = new node
    }
    else{
        prevCur->Next = newNode;
        newNode->Next = cur; 
        }
    L.Count++; //increments list count
}

//
// pq_nudge
// 
// Nudges the element with the given ID forward one element in the
// queue. The element takes on the same priority as the element
// that now follows it.  Example: suppose the queue currently contains
// the following (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to "nudge" 21 forward produces this result:
//
//   (10,19) (21,25) (84,25)
//
// If the ID is already at the front of the queue, nothing happens.
// If the ID is not in the queue, throws "invalid_argument" exception, i.e.
// throw invalid_argument("pq_nudge: ID not found");
//
void pq_nudge(List& L, int ID)
{
    Node* cur = L.Head; //initializes cur to List head
    Node* prevCur = nullptr; //initializes previous cur to null
    
    int inputPos;
    inputPos = search_list(L,ID); //searches for the ID and stores it into inputPos
    
    if(inputPos == 0)
    {
        return;
    }
    else if(inputPos == -1)
    {
        throw invalid_argument("pq_nudge: ID not found"); //if nothing is found inputPos is -1 and throws invalid_argument
    }
    else{
        while(0 < inputPos-1) // as long as last element of input pos > 0
        {
            inputPos--; //decreases position
            prevCur = cur; 
            cur = cur->Next;
        }
        Node* nextCur = cur->Next; //initializes next cur in list by calling cur->Next
        cur->Next = nextCur->Next; //moves onto the next element in list
        nextCur->Next = cur;
        
        if(prevCur != nullptr) // if the previous cur is not null moves onto the next value
        {
            prevCur->Next = nextCur;
        }
        else{
            L.Head = nextCur; //sets the List head to the next cur if previous cur = null
        }
        nextCur->Data.Priority = cur->Data.Priority; //sets the priority from cur into next cur
    }
}

//
// pq_clear
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void pq_clear(List& L)
{
    free_list(L); //calls the free list function from list.cpp
}

//
// pq_duplicate
//
// Makes a complete copy of the given list L and returns this duplicate.
// A "deep" copy is made, meaning all nodes and data are duplicated in 
// the new, returned list.
//
List pq_duplicate(List L)
{
    Node* cur = L.Head; //initializes cur to List head
    List List2; //creates a second list
    pq_init(List2); //sets whats inside of the list into the second list **makes a duplicate**
    
    while(cur != nullptr) // as long as cur != null
    {
        pq_enqueue(List2, cur->Data.ID, cur->Data.Priority); //calls enqueue by using the second list 
        cur = cur->Next; //moves cur onto the next set
    }
    return List2; //returns the duplicate
}
