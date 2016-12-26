#include "PriceTableIMP.h"
#include <fstream>

void PriceTableIMP::calcAllPairsShortestPath(std::string mapFile)
{
	std::string begin,end;
	int dist;
	
	// read the graph
	std::ifstream ifs(mapFile);
    while(ifs>>begin) 
	{
		ifs>>end>>dist;
		this->distTable[begin][end]=dist;
		this->distTable[end][begin]=dist;
	}
	
	// run the Floyd‐Warshall’s Algorithm
	for(int k=0;k<StationNum;k++)
		for(int i=0;i<StationNum;i++)
			for(int j=0;j<StationNum;j++)
			{
				const std::string &stk = StationNames[k];
				const std::string &sti = StationNames[i];
				const std::string &stj = StationNames[j];
				if(distTable[sti][stj]>distTable[sti][stk]+distTable[stk][stj]&&distTable[sti][stj]>distTable[sti][stk]&&distTable[sti][stj]>distTable[stk][stj])
					distTable[sti][stj]=distTable[sti][stk]+distTable[stk][stj];
			}
				
}

int PriceTableIMP::calcPrice
(int milageDiff, std::string bClass, std::string from, std::string toStation)
{
	if(milageDiff>distTable[from][toStation])
		return milageDiff*(oriRates.at(bClass));
	else
		return milageDiff*(dscntRates.at(bClass));
}

PriceTableIMP::PriceTableIMP()
{
	for(int i=0;i<StationNum;i++) 
		for(int j=0;j<StationNum;j++)
		{
			const std::string &sti = StationNames[i];
			const std::string &stj = StationNames[j];
			this->distTable[sti][stj]=(i==j?0:INT_MAX);
		}
}
