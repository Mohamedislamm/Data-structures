#ifndef INT_HEAP_H
#define INT_HEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class IntMaxHeap {
private:
    vector<int> heap;

    void heapifyUp(int idx) {
        while (idx > 0 && heap[(idx - 1) / 2] < heap[idx]) {
            swap(heap[(idx - 1) / 2], heap[idx]);
            idx = (idx - 1) / 2;
        }
    }

    void heapifyDown(int idx) {
        int largest = idx;
        int leftChild = 2 * idx + 1;
        int rightChild = 2 * idx + 2;

        if (leftChild < static_cast<int>(heap.size()) && heap[leftChild] > heap[largest])
            largest = leftChild;
        if (rightChild < static_cast<int>(heap.size()) && heap[rightChild] > heap[largest])
            largest = rightChild;

        if (largest != idx) {
            swap(heap[idx], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(int element) {
        heap.push_back(element);
        heapifyUp(static_cast<int>(heap.size()) - 1);
    }

    int extractMax() {
        if (heap.empty()) return -1;
        int maxElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return maxElement;
    }

    int getMax() const {
        return heap.empty() ? -1 : heap[0];
    }
};

class IntPriorityQueue {
private:
    IntMaxHeap maxHeap;

public:
    void insert(int priority) {
        maxHeap.insert(priority);
    }

    int extractMaxPriority() {
        return maxHeap.extractMax();
    }

    int getMaxPriority() const {
        return maxHeap.getMax();
    }
};

inline vector<int> intHeapSort(vector<int>& arr) {
    IntMaxHeap heap;
    for (int elem : arr) {
        heap.insert(elem);
    }

    vector<int> sortedArr;
    int maxElement;
    while ((maxElement = heap.extractMax()) != -1) {
        sortedArr.push_back(maxElement);
    }
    reverse(sortedArr.begin(), sortedArr.end());
    return sortedArr;
}

inline void runIntHeapDemo() {
    IntMaxHeap heap;
    heap.insert(10);
    heap.insert(4);
    heap.insert(15);
    heap.insert(20);
    cout << "Max element in the heap: " << heap.getMax() << endl << endl;

    cout << "Extracted max element: " << heap.extractMax() << endl;
    cout << "Max element after extraction: " << heap.getMax() << endl << endl;

    IntPriorityQueue pq;
    pq.insert(5);
    pq.insert(25);
    pq.insert(15);
    cout << "Max priority element: " << pq.getMaxPriority() << endl;
    cout << "Extracted max priority element: " << pq.extractMaxPriority() << endl << endl;

    vector<int> arr = {4, 10, 3, 5, 1};
    vector<int> sortedArr = intHeapSort(arr);

    cout << "Sorted array: ";
    for (int elem : sortedArr) {
        cout << elem << " ";
    }
    cout << endl;
}

#endif
