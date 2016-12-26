#include "UBikeHeapIMP.h"

void UBikeHeapIMP::addUBikePtr(UBike* ubptr)
{
	int i;
	UBike* temp;
	(*this)[++number]=ubptr;
	for(i=number;i>1;i/=2)
	{
		if((*this)[i]->mileage<(*this)[i/2]->mileage)
		{
			temp=(*this)[i];
			(*this)[i]=(*this)[i/2];
			(*this)[i/2]=temp;
			(*this)[i]->heapIndex=i;
		}
		else
			break;
	}
	(*this)[i]->heapIndex=i;
}

UBike* UBikeHeapIMP::removeUBikePtr(int heapIndex)
{
	if(this->isEmpty())
		return nullptr;
	if(heapIndex>number)
		return nullptr;
	if(heapIndex==number)
	{
		number--;
		return (*this)[number+1];
	}
	
	//replace the element by the last one
	UBike* returnPtr=(*this)[heapIndex];
    (*this)[heapIndex]=(*this)[number--];
	
	//heapify
	int i;
	UBike* temp;
	if(heapIndex!=1&&(*this)[heapIndex/2]->mileage>(*this)[heapIndex]->mileage)
	{
		for(i=heapIndex;i>1;i/=2)
		{
			if((*this)[i]->mileage<(*this)[i/2]->mileage)
			{
				temp=(*this)[i];
				(*this)[i]=(*this)[i/2];
				(*this)[i/2]=temp;
				(*this)[i]->heapIndex=i;
			}
			else
				break;
		}
	}
	else
	{
		int lower_one;
		for(i=heapIndex;(2*i)<=number;i=lower_one)
		{
			//choose the lower-value cild
			if(2*i+1>number)
				lower_one=2*i;
			else
				lower_one=((*this)[2*i]->mileage<=(*this)[2*i+1]->mileage)?(2*i):(2*i+1);
			
			if((*this)[i]->mileage>(*this)[lower_one]->mileage)
			{
				temp=(*this)[i];
				(*this)[i]=(*this)[lower_one];
				(*this)[lower_one]=temp;
				(*this)[i]->heapIndex=i;
			}
			else
				break;	
		}
	}
	(*this)[i]->heapIndex=i;
	return returnPtr;
}



