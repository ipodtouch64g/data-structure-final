#include "UBikeHashTableIMP.h"
#include <cctype>

void UBikeHashTableIMP::addUBikePtr(UBike* ubptr)
{
	int hashNum=0;
	int license_letter;
	for(int i=0;i<5;i++)
	{
		license_letter=isalpha(ubptr->license[i])?(ubptr->license[i]-'A'+10):(ubptr->license[i]-'0');
		hashNum=hashNum*29+license_letter;
	}
	hashNum=(hashNum>>5)%256;
	
	(*this)[hashNum].push_front(ubptr);
}

UBike* UBikeHashTableIMP::findUBikePtr(std::string license, bool toRemove)
{
	//hash function
    int hashNum=0;
	int license_letter;
	for(int i=0;i<5;i++)
	{
		license_letter=isalpha(license[i])?(license[i]-'A'+10):(license[i]-'0');
		hashNum=hashNum*29+license_letter;
	}
	hashNum=(hashNum>>5)%256;
	
	//find the ubike by license
	UBike* ubptrl=nullptr;
	for(UBikePtrList::iterator it=(*this)[hashNum].begin();it!=(*this)[hashNum].end();it++)
		if((*it)->license==license)
		{
			ubptrl=(*it);
			break;
		}
	if(ubptrl==nullptr)
		return nullptr;
	
	//remove or not
	if(toRemove&&!ubptrl->isRented)
	{
		(*this)[hashNum].remove(ubptrl);
		return ubptrl;
	}
	else
		return ubptrl;
}













