#ifndef UBikeHeapIMP_h
#define UBikeHeapIMP_h

#include "readonly/UBikeHeapADT.h"

class UBikeHeapIMP : public UBikeHeapADT
{
public:
    //=================================================================
    // add the ubike pointer to the heap
    //=================================================================
    void addUBikePtr(UBike* ubptr);
    
    //=================================================================
    // remove the ubike pointer in this heap at "index"
    //=================================================================
    UBike* removeUBikePtr(int heapIndex);
};

#endif
