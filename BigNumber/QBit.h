#pragma once
#include <string>
#include <cstdint>
using namespace std;

class QBit
{
protected:
	uint32_t m_data[4];
public:
	QBit();
	~QBit();
	QBit(string bit);
	int getBit(int pos) const;
	void setBit(int pos, int bit);
	string toBinary();
};