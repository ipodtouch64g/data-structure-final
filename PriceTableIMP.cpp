#include "PriceTableIMP.h"
int find_string_in_names(std::string &to_find)
{
	for (int i = 0; i < 12; i++)
		if (to_find == StationNames[i])
			return i;
	return -1;
}

void PriceTableIMP::calcAllPairsShortestPath(std::string mapFile)
{
		std::istringstream iss(mapFile);
		std::string line_in;
		int init_dist_map[12][12];
		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 12; j++)
				init_dist_map[i][j] = 99999999;
		//=================================================================
		// parse mapFile to initial distace map
		//=================================================================
		while (std::getline(iss, line_in))
		{
			std::vector<std::string> tokens;
			std::stringstream line(line_in);
			std::string token;
			while (line >> token)
				tokens.push_back(token);
			int stationA = find_string_in_names(tokens[0]);
			int stationB = find_string_in_names(tokens[1]);
			int distance = stoi(tokens[2]);
			init_dist_map[stationA][stationB] = distance;
			init_dist_map[stationB][stationA] = distance;
		}
		for (int i = 0; i < 12; i++)
			init_dist_map[i][i] = 0;
		//=================================================================
		// calculate shortest distance between stations by initial map
		//=================================================================
		int dist[12][12];
		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 12; j++)
				dist[i][j] = init_dist_map[i][j];
		for (int k = 0; k < 12; k++)
		{
			for (int i = 0; i < 12; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					if (dist[i][k] + dist[k][j] < dist[i][j])
						dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
		//=================================================================
		// get result into distTable
		//=================================================================
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				distTable[StationNames[i]][StationNames[j]] = dist[i][j];
			}
		}
}

int PriceTableIMP::calcPrice(int milageDiff, std::string bClass, std::string from, std::string toStation)
{
	if (milageDiff > distTable.at(from).at(toStation))
		return oriRates.at(bClass)*milageDiff;
	else
		return dscntRates.at(bClass)*distTable.at(from).at(toStation);
}
