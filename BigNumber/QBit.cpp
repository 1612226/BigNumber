#include "QBit.h"

QBit::QBit()
{
	m_data[0] = m_data[1] = m_data[2] = m_data[3] = 0;
}


QBit::~QBit()
{

}

QBit::QBit(string bit) {
	if (bit.length() > 128)
		return;
	else {
		for (int i = 0; i < 128 - bit.length(); i++) {
			bit = "0" + bit;
		}
		for (int i = 0; i < 128; i++) {
			setBit(bit[i] - '0', i);
		}
	}
}

int QBit::getBit(int pos) const {
	int data_i = pos / 32;
	pos %= 32;
	int bit = (this->m_data[data_i] >> (31 - pos)) & 1;
	return bit;
}

void QBit::setBit(int pos, int bit) {
	int bitpos = this->getBit(pos);
	int data_i = pos / 32;
	pos = pos % 32;
	if (bitpos == 1 && bit == 0) {
		this->m_data[data_i] = this->m_data[data_i] - (1 << (31 - pos));
	}
	else {
		this->m_data[data_i] = this->m_data[data_i] | (bit << (31 - pos));
	}
}
string QBit::toBinary() {
	string res = "";
	for (int i = 0; i < 128; i++) {
		res += getBit(i);
	}
	return res;
}