#include "UBikeHashTableIMP.h"

// Add your code here

int find_hash_S4(int tag,int s,int (&license_arr)[5])
{
	if (tag > 0)
		return find_hash_S4(tag - 1, s, license_arr) * 29 + license_arr[tag];
	else
		return license_arr[0];
}

int find_hash_address(int(&license_arr)[5])
{
	int s4 = find_hash_S4(4, 0, license_arr);
	std::string s4_s = std::bitset<64>(s4).to_string();
	std::string address_s;
	for (int i = 0; i < 8; i++)
		address_s[i] = s4_s[12 - i];
	std::bitset<8> address_bitset(address_s);
	return address_bitset.to_ulong();
}

void UBikeHashTableIMP::addUBikePtr(UBike * ubptr)
{
	//============================================================
	//hash by license
	//============================================================
	int license_arr[5] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		if (isalpha(ubptr->license[i]))
			license_arr[i] = (ubptr->license[i] - 'A' + 10);
		else
			license_arr[i] = atoi(&(ubptr->license[i]));
	}

	int address = find_hash_address(license_arr);
	//============================================================
	//put it into hash table
	//============================================================
	this->_Elems[address].push_front(ubptr);
	
}

UBike * UBikeHashTableIMP::findUBikePtr(std::string license, bool toRemove)
{
	int i = 0;
	while (i < 256)
	{
		for (auto &it : this->_Elems[i])
			if (it->license == license)
			{
				if (toRemove)
				{
					this->_Elems[i].remove(it);
					return nullptr;
				}	
				else
					return it;
			}
		i++;
	}
	return nullptr;
}
