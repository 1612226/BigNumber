﻿#pragma once
#include"QBit.h"
#include "IntFunction.h"

class QInt:public QBit{

public:
	QInt();
	QInt(const QInt& num);
	QInt(int, int, int, int);
	//~QInt();
	QInt& operator =(const QInt& b);
	//Constructor với đối số là dãy bit
	QInt(string binArr);
	//trả về chuỗi bit của số QInt
	string binArr();
	//toán tử and
	QInt operator & (const QInt& b);
	//toán tử or
	QInt operator | (const QInt& b);
	//toán tử not
	friend QInt operator ~ (const QInt& b);//1 ngoi
	//toán tử lấy số đối (1 ngôi)
	friend QInt operator - (QInt b); // 1 ngoi
	QInt operator ^ (const QInt& b);

	//toán tử +,-,*,/ 2 số QInt
	QInt operator + (QInt& b);
	QInt operator - (const QInt& b);
	QInt operator * (/*const*/ QInt& M);
	QInt operator / (/*const*/ QInt& M);


	//dich trai 1 bit
	QInt leftShift();
	//dich phai 1 bit
	QInt rightShift();
	QInt operator >> (unsigned int x);
	QInt operator << (unsigned int x);

	//nhap & convert
	void scan(string str, int base);
	string print(int base);

	//lấy trị tuyệt đối QInt
	QInt ABS(QInt a);

};
