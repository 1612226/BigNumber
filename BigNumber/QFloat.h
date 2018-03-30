#pragma once
#include "QInt.h"
#include "FloatTools.h"

class QFloat
{
private:
	int m_data[4];
public:
	int getBit(int pos);
	void setBit(int pos, int bit);
	QFloat();
	QFloat(int, int, int, int);
	QFloat(string binArr);
	QFloat(const QFloat& b);
	// set bit ở phần dấu
	void setSign(string &part1);
	
	// set bit ở phần mũ
	void setExp(string exp_bit);
	
	// set bit ở phần trị
	void setFraction(string fraction);
	void ScanQFloat(string input, int base);
	void PrintQFloat(int base);
	void printNormalize(string bit);
	void printDeNormalize(string bit);

	//Kiem tra QFloat co bang 0 hay khong?
	bool checkZero();

	//Kiem tra so mu cua 2 so co bang nhau hay khong
	bool checkExpEqual( QFloat&);
	
	//Kiem tra so mu co tran so tren hay khong?
	bool checkExpOverflow();
	
	//Kiem tra so mu co tran so duoi hay khong?
	bool checkExpUnderflow();
	
	//Dich trai logic tu vi tri start den vi tri end mot so bit nhat dinh
	void shiftLeftLogical(int start, int end, int bit);
	
	//Dich phai logic tu vi tri start den vi tri end mot so bit nhat dinh
	void shiftRightLogical(int start, int end, int bit);
	
	//Kiem tra phan tri co bang 0 hay khong?
	bool isSignificandZero();
	
	//Tang 1 doan bit tu start den end len 1 don vi 
	void IncrementOne(int start, int end);
	
	//Giam 1 doan bit tu start den end di 1 don vi 
	void DecrementOne(int start, int end);
	
	//Kiem tra co can lam tron hay khong?
	/*Ham cong 2 so cham dong thuc hien 4 cong viec:
	1. Kiem tra cac so co bang 0 hay khong
	2. Dua ve cung so mu
	3. Thuc hien phep cong
	4. Dua ve dang chuan va lam tron*/
	QFloat operator+(const QFloat &);
	QFloat operator-(const QFloat &);
	
	
	QFloat operator*(QFloat &);
	QFloat operator/(QFloat &);

	bool is0();
	string getFromTo(int x, int y);
};
