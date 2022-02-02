
// Writing C++ libraries for linked-list and priority queue and 
// using it to implement a set of functions to create and manipulate one way linked-lists.
//

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include "list.h"

using namespace std;

//
// Functions:
//

// 
// init_list
//
// Initializes list to empty; must be called before list can 
// be used with other functions.
//
void init_list(List& L)
{
    L.Count = 0; //initializes count to 0
    L.Head = nullptr; //initializes head to null
}

//
// print_list
//
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void print_list(List L)
{
    Node* cur = L.Head; //initializes cur to the list head
    cout << "List: ";
    while(cur != nullptr)
    {
        cout << "(" << cur->Data.ID << "," << cur->Data.Priority << ") ";
        cur = cur->Next; // goes to the next element until null
    }
    cout << endl;
}
//
// push_back_list
//
// Pushes the data onto the end of the list.
//
void push_back_list(List& L, NodeData d)
{
    Node* newNode = new Node(); //creates a new node 
    newNode->Data = d; //stores the data of nodedata into the new node
    
    if(L.Count == 0) //if the count is empty (no values in the set)
    {
        L.Head = newNode;
        newNode->Next = nullptr;
    }
    else{
        Node* cur = L.Head;
        while(cur->Next != nullptr)
        {   
            cur = cur->Next;
        }
        cur->Next = newNode;
        newNode->Next = nullptr;
    }
    L.Count++; //incrememnts count
}

//
// push_front_list
//
// Pushes the data onto the front of the list.
//
void push_front_list(List& L, NodeData d)
{
    Node* newNode = new Node();
    newNode->Data = d; //the new node stores the NodeData d into it
    newNode->Next = L.Head; //the next node is stored as the list head

    L.Head = newNode; //stores new node into the list head
    L.Count++; //increments count

}

//
// free_list
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void free_list(List& L)
{
   Node* cur = L.Head;
   if(L.Count != 0)
   {
       while(cur != nullptr)
       {
           Node* tempCur = cur; //new temporary cur stored as previous cur
           cur = cur->Next;
           delete tempCur; //deletes the temporary cur
           L.Count--; //decreases the count
       }
       L.Head = nullptr; //while loop until nullptr then stores as null to free
   }
    else{
        return; //returns nothing since void 
    }
}

//
// search_list
//
// Search the list for the first occurrence of the given ID. If found,
// its position in the list is returned; positions are 0-based,
// meaning the first node is position 0. If not found, -1 is
// returned.
//
int search_list(List L, int ID)
{
    Node* cur = L.Head;
    int count = 0; //counter variable to store the position
    if(L.Head == nullptr)
    {
        return -1;
    }
    else{
        while(cur != nullptr)
        {
            if(ID == cur->Data.ID) //if the ID searching for is found in the cur->Data.ID
            {
                return count; //returns count
            }
            count++; //increment count
            cur = cur->Next; // goes to the next element
        }
    }
    return -1;
}

//
// retrieve_from_list
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("retrieve_from_list: invalid position");
//
NodeData retrieve_from_list(List L, int pos)
{
    bool found = false; //boolean to find the data
    int counterVar = 0; //counter variable to represent position
    Node* cur = L.Head;
    while(cur != nullptr)
    {
        if(pos == counterVar) //if the position is the same as the counter variable
        {
            found = true; // then position is found and returns the data
            return cur->Data;
        }
        counterVar++; //else will increment countervariable and keep searching
        cur = cur->Next;
    }
    if(0 > pos || pos > L.Count-1 || !found) //if it is not found an argument statement is thrown
    {
        throw invalid_argument("retrieve_from_list: invalid position");
    }
    return cur->Data;
}

//
// remove_from_list
//
// Removes and frees the node at the given position, returning 
// the node's data. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("remove_from_list: invalid position");
//
NodeData remove_from_list(List& L, int pos)
{
    Node* cur = L.Head;
    bool found = false;
    Node* previousCur = nullptr; //initializes the previous cur to null **keeps track
    NodeData data; //new nodeData 
    int counterVar = 0; //counterVar to represent position 
    
    while(cur != nullptr) //as long as the cur is not null
    {
        if(counterVar == pos) //if the position is equal to the counter break out of the statement
        {
            found = true;
            break;
        }
        previousCur = cur; //stores cur into the previous cur
        cur = cur->Next; //goes onto next element
        counterVar++; //increments cur
    }
    if(pos < 0 || pos > L.Count-1 || !found) //if out of bounds or not found then throws argument
    {
        throw invalid_argument("remove_from_list: invalid position");
    }
    else{ //else checks condition if equal to 0
        if(counterVar == 0)
        {
            L.Head = cur->Next; //stores next element into the list head
        }
        else{
            previousCur->Next = cur->Next; //else the next element is stored into the previous cur
        }
        data = cur->Data;
        delete cur; //deletes cur
        L.Count--; //decreases count
    }
    return data; //returns data
}