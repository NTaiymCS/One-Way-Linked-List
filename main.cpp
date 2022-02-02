#include "list.h"
#include "pqueue.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    List L;
    pq_init(L);
    NodeData a = {10,2};
    NodeData b = {5,2};
    NodeData c = {45,29};
    NodeData d = {30,1};
    NodeData e = {7,5};
    
    pq_print(L);
    pq_front(L);
    pq_print(L);
    
    pq_nudge(L, 1);
    
    pq_enqueue(L, 10, 2);
    pq_duplicate(L);
    pq_print(L);
    
    pq_clear(L);
    return 0;
}