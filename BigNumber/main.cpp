#include <iostream>
#include <fstream>
#include <cstring>
#include "QInt.h"
#include "QFloat.h"
using namespace std;

int main() {
	//fstream fi, fo;
	//fi.open(argv[1], ios::in);
	//fo.open(argv[2], ios::out);
	//if (!fi.is_open()) cout << "Unable to open\n";
	//else {
	//	while (!fi.eof()) {
	//		string tmp = "";
	//		getline(fi, tmp);
	//		string res = readLine(tmp);
	//		fo << res << endl;
	//	}
	//}
	//fi.close();
	//fo.close();

	int base;
	cin >> base;

	string input;
	cin >> input;
	QFloat f;
	f.ScanQFloat(input, base);
	f.PrintQFloat(base);

	return 0;
}
