#include "UBikeHeapIMP.h"

// Add your code here
void bubbleup(std::array< UBike*, 1024 > &heap ,int number)
{
	if (heap[number / 2]->mileage < heap[number]->mileage && (number/2)!=0)
	{
		std::swap(heap[number], heap[number / 2]);
		bubbleup(heap, number / 2);
	}
	else
	{
		heap[number]->heapIndex = number;
		return;
	}
	return;
}

void bubbledown(std::array< UBike*, 1024 > &heap, int number)
{
	if (heap[number * 2] == nullptr && heap[number * 2 + 1] == nullptr)
	{
		heap[number]->heapIndex = number;
	}
	else if (heap[number * 2 + 1] == nullptr && heap[number * 2] != nullptr)
	{
		if (heap[number]->mileage > heap[number * 2]->mileage)
			std::swap(heap[number], heap[number * 2]);
		heap[number * 2]->heapIndex = number * 2;
	}
	else
	{
		bool left_or_right = (heap[number * 2]->mileage <= heap[number * 2 + 1]->mileage) ? 1 : 0;
		if (left_or_right && heap[number * 2]->mileage < heap[number]->mileage)
		{
			std::swap(heap[number], heap[number * 2]);
			bubbledown(heap,number*2);
		}
		else if (!left_or_right && heap[number * 2 + 1]->mileage < heap[number]->mileage)
		{
			std::swap(heap[number], heap[number * 2 +1]);
			bubbledown(heap, number * 2+1);
		}
		else
		{
			heap[number]->heapIndex = number;
		}
	}
	return;

}

void UBikeHeapIMP::addUBikePtr(UBike * ubptr)
{
	if (number == 0) 
	{
		(*this)[++number] = ubptr;
		ubptr->heapIndex = number;
		return;
	}
	else
	{
		(*this)[++number] = ubptr;
		bubbleup((*this),number);
		return;
	}
}

UBike * UBikeHeapIMP::removeUBikePtr(int heapIndex)
{
	if (heapIndex == number)
	{
		delete((*this)[heapIndex]);
		(*this)[heapIndex] = nullptr;
		return nullptr;
	}
	else
	{
		delete((*this)[heapIndex]);
		(*this)[heapIndex] = (*this)[number];
		(*this)[number--] = nullptr;

		if ((*this)[heapIndex]->mileage < (*this)[heapIndex / 2]->mileage)
		{
			bubbleup((*this),heapIndex);
			return nullptr;
		}
		else
		{
			bubbledown((*this), heapIndex);
			return nullptr;
		}
	}
}
