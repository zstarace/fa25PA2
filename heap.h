//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size>= 64) {
            cerr << "Heap Overflow\n"; //character error message
            return;
        }
        int pos = size ++;
        data[pos] = idx;
        upheap(pos, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        // placeholder
        if (size == 0) {
            cerr << "Heap Underflow\n";
            return -1;
        }
        int minIdx = data[0];
        downheap(0,weightArr);
        return minIdx;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos>0) {
            int parent = (pos-1)/2;

            if (weightArr[data[pos]] < weightArr[data[parent]] ||(weightArr[data[pos]] == weightArr[data[parent]] && data[pos] < data[parent])) {
                swap(data[pos], data[parent]);
                pos = parent;
            }
            else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child

    }
};

#endif