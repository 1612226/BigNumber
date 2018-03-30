#include <iostream>
#include <fstream>
#include <cstring>
#include "QInt.h"
#include "QFloat.h"
#include "IntFunction.h"
using namespace std;

int main(int argc,char* argv[]) {
	/*fstream fi, fo;
	fi.open(argv[1], ios::in);
	fo.open(argv[2], ios::out);
	if (!fi.is_open()) cout << "Unable to open\n";
	else {
		while (!fi.eof()) {
			string tmp = "";
			getline(fi, tmp);
			string res = readLine(tmp);
			fo << res << endl;
		}
	}
	fi.close();
	fo.close();*/

	/*int base;
	cin >> base;

	string input;
	cin >> input;
	QFloat f;
	f.ScanQFloat(input, base);
	f.PrintQFloat(base);*/

	//string input1, input2;
	//cin >> input1;
	//cin >> input2;
	//QFloat f1,f2;

	//f1.ScanQFloat(input1, 10);
	//f2.ScanQFloat(input2, 10);

	//f1.PrintQFloat(10);
	//f2.PrintQFloat(10);
	//cout << "\n-------------------\n";
	//QFloat f3 = f1*f2;
	//f3.PrintQFloat(10);
	//cout << endl;
	//QFloat f4 = f1 / f2;
	//f4.PrintQFloat(10);

	//QFloat f1;
	//f1.ScanQFloat("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", 2);
	//f1.PrintQFloat(10);

	return 0;
}
