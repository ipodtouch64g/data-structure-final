#include "UBikeSystemIMP.h"

void UBikeSystemIMP::InitDistTable
(std::string MapFile)
{
    priceTable.calcAllPairsShortestPath(MapFile);
}

void UBikeSystemIMP::NewBike
(std::string classType, std::string license,
 int mileage, std::string station)
{
    UBike* ubptr=new UBike;
	ubptr->isRented=false;
	ubptr->mileage=mileage;
	ubptr->license=license;
	ubptr->station=station;
	ubptr->classType=classType;
	
	ubHashTable.addUBikePtr(ubptr);
	ubStations[station][classType].addUBikePtr(ubptr);
}

void UBikeSystemIMP::JunkIt
(std::string license)
{
    UBike* ubptr=ubHashTable.findUBikePtr(license,true);
	if(ubptr==nullptr||ubptr->isRented)
		return;
	ubStations[ubptr->station][ubptr->classType].removeUBikePtr(ubptr->heapIndex);
	delete ubptr;
}

void UBikeSystemIMP::Rent
(std::string classType, std::string station)
{
    if(ubStations[station][classType].isEmpty())
		return;
	UBike* ubptr=ubStations[station][classType].removeUBikePtr(1);
	ubStations[station]["Rented"].addUBikePtr(ubptr);
	ubptr->isRented=true;
}

void UBikeSystemIMP::Return
(std::string station, std::string license, int returnMile)
{
	UBike* ubptr=ubHashTable.findUBikePtr(license,false);
    if(ubptr==nullptr)
		return;
	if(!ubptr->isRented)
		return;
	net+=priceTable.calcPrice(returnMile-ubptr->mileage,ubptr->classType,ubptr->station,station);
	ubptr->mileage=returnMile;
	ubptr->isRented=false;
	ubStations[ubptr->station]["Rented"].removeUBikePtr(ubptr->heapIndex);
	ubStations[ubptr->station][ubptr->classType].addUBikePtr(ubptr);
}

void UBikeSystemIMP::Trans
(std::string station, std::string license)
{
    UBike* ubptr=ubHashTable.findUBikePtr(license,false);
    if(ubptr==nullptr)
		return;
	if(ubptr->isRented)
		return;
	ubStations[ubptr->station][ubptr->classType].removeUBikePtr(ubptr->heapIndex);
	ubStations[station][ubptr->classType].addUBikePtr(ubptr);
	ubptr->station=station;
}

void UBikeSystemIMP::ShutDown()
{
	UBike* ubptr;
	for(int i=0;i<StationNum;i++)
		for(int j=0;j<HeapTypeNum;j++)
			for(int k=0;k<ubStations[StationNames[i]][HeapNames[j]].number;k++)
			{
				ubptr=ubStations[StationNames[i]][HeapNames[j]].removeUBikePtr(k);
				delete ubptr;
			}
}


