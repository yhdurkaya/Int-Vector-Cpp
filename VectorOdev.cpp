//
// Created by YHD on 24.03.2020 
//

#include <iostream>

#include "Vector.h"

struct AllocationMetrics {
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }

};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size) {
    s_AllocationMetrics.TotalAllocated += size;

    return malloc(size);
}

void operator delete(void* memory, size_t size) {
    s_AllocationMetrics.TotalFreed += size;

    free(memory);
}

static void PrintMemoryUsage() {
    std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << "bytes\n";
}

int main()
{

    Vector a, c2, m2;

    Vector b{ 1,2,3,4,5 }, c{ 9, 8, 7, 6, 5};

    int array[] = { 1,2,3,4,5 };
    c2 = b;

    auto x = b.begin();
    auto y = b.end();
    b.reserve(20);
    b.shrink_to_fit();
    Vector m(array, array+5);
    
    b.insert(b.begin(), c.begin()+1, c.begin()+3);
    b.clear();
    
}