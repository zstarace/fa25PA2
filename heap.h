//
// Created by Manju Muralidharan on 10/19/25.
//
// Zoe Starace

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;


// Structure implementing a simple MinHeap
struct MinHeap {
    int data[64]; // Array to hold heap elements
    int size; // number of elements currently in heap

    //constuctor initailizes heap size to equal zero
    MinHeap() { size = 0; }

    // Inserts a new index into the heap based on its weight
    void push(int idx, int weightArr[]) {
        // insert index at end of heap, restore order using upheap()
        if (size>= 64) {
            cerr << "Heap Overflow\n"; //character error message
            return;
        }
        int pos = size ++;
        data[pos] = idx;
        upheap(pos, weightArr);
    }

    // Removes and returns the index with the smallest weight
    int pop(int weightArr[]) {
        // remove and return smallest index
        if (size == 0) {
            cerr << "Heap Underflow\n";
            return -1;
        }
        int minIdx = data[0];
        //moving last element to root and then shrink
        data[0] = data[--size];
        if (size>0) {
            downheap(0,weightArr);
        }
        return minIdx;
    }

    // Moves an element upward until heap property is restored
    void upheap(int pos, int weightArr[]) {
        //swap child upward while smaller than parent
        while (pos>0) {
            int parent = (pos-1)/2;

            // Compare weights and if child is smaller then swap it with parent
            //smaller index takes priority if there is a tie.
            if (weightArr[data[pos]] < weightArr[data[parent]] ||(weightArr[data[pos]] == weightArr[data[parent]] && data[pos] < data[parent])) {
                swap(data[pos], data[parent]);
                pos = parent;
            }
            else {
                break;
            }
        }
    }

    // Moves an element downward until heap property is restored
    void downheap(int pos, int weightArr[]) {
        //swap parent downward while larger than any child
        while (true) {
            int left = 2* pos +1;
            int right = 2* pos +2;
            int smallest = pos;

            // Check if left child is smaller
            if (left < size &&
                (weightArr[data[left]] < weightArr[data[smallest]] ||
                (weightArr[data[left]] == weightArr[data[smallest]] && data[left] < data[smallest]))) {
                smallest = left;
                }

            // check if right child is smaller than current smallest
            if (right < size &&
                (weightArr[data[right]] < weightArr[data[smallest]] ||
                (weightArr[data[right]] == weightArr[data[smallest]] && data[right] < data[smallest]))) {
                smallest = right;
                }

            // If the smallest is not the parent then swap and continue
            if (smallest != pos) {
                swap(data[pos], data[smallest]);
                pos = smallest;
            } else break;
        }

    }
};

#endif