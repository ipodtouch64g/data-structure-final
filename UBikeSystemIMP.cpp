#include "UBikeSystemIMP.h"

// Add your code here

void UBikeSystemIMP::InitDistTable(std::string MapFile)
{
	priceTable.calcAllPairsShortestPath(MapFile);
}
