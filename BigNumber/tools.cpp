#pragma once
#include "tools.h"



string fstrDiv2(string str){
	string res = "";
	int i = 0;
	int soDu = 0;
	while (i < str.length()){
		soDu = 10 * soDu + (str[i] - '0');
		res += (soDu / 2) + '0';
		soDu %= 2;
		i++;
	}
	int l = res.length() - 1;
	for (int i = 0; i < res.length() - 1; i++){
		if (res[i] != '0'){
			l = i;
			break;
		}
	}
	return res.substr(l);
}

//Chuyển so nguyen duong sang dãy bit nhị phân
string intToBin(string Dec){
	string res = "";
	while (Dec != "0"){
		int bit = (Dec[Dec.length() - 1] - 48) % 2;
		res.insert(res.begin(), bit + '0');
		Dec = fstrDiv2(Dec);
	}
	if (res.length() == 0) res += "0";
	return res;
}
string fstrx2(string str){
	int nho = 0;
	string res = "";
	for (int i = str.length() - 1; i >= 0; i--){
		int tmp = (str[i] - '0') * 2 + nho;
		if (tmp >= 10) {
			nho = 1; tmp -= 10;
		}
		else nho = 0;
		res.insert(res.begin(), tmp + '0');
	}
	if (nho) res.insert(res.begin(), nho + '0');
	return res;
}

string fDecToBin(string dec){ //string 128 char
	int minus = 0;
	if (dec[0] == '-'){
		dec.erase(dec.begin());
		minus = 1;
	}
	int posPoint = dec.find('.');
	string part1 = dec.substr(0, posPoint); //before .
	string part2 = dec.substr(posPoint+1); //after .
	part1 = intToBin(part1);
	string binPart2 = "";
	int cnt = 200; //cnt để dừng vòng while khi vô hạn tuần hoàn
	while (part2 != "0"&&cnt--){
		int len = part2.length();
		part2 = fstrx2(part2);
		if (part2.length() > len) {
			binPart2 += "1";
			part2.erase(part2.begin());
		}
		else binPart2+="0";
	}
	int mu = 0;
	if (part1 == "0"){//dich phai
		for (int i = 0; i < binPart2.length(); i++){
			if (binPart2[i] == '1'){
				mu = -(i + 1);
				binPart2 = binPart2.substr(i+1); //fraction
				break;
			}
		}
	}
	else{
		for (int i = 0; i < part1.length(); i++){
			if (part1[i] == '1'){
				mu = part1.length() - (i + 1);
				binPart2 = part1.substr(i + 1) + binPart2;
				break;
			}
		}
	}
	mu += 16383;
	string bias = to_string(mu);
	bias = intToBin(bias);
	while (bias.length() < 15) bias.insert(bias.begin(), '0');
	string res = "";
	if (minus) res += "1"; 
	else res += "0";
	res += bias;
	res += binPart2;
	while (res.length() < 128) res += "0";
	if (res.length()>128) res = res.substr(0, 128);
	return res;
}

string f_2Expn(int n){
	string str = "1";
	for (int i = 0; i < n; i++){
		str = fstrx2(str);
	}
	return str;
}
//cộng 2 chuỗi, trả về chuỗi
void fchen0(string &a, int n){
	while (n--){
		a.insert(a.begin(), '0');
	}
}
string fstrPlusStr(string a, string b){
	int lenA = a.length();
	int lenB = b.length();
	if (lenA > lenB) fchen0(b, lenA - lenB);
	else fchen0(a, lenB - lenA);
	int i = a.length() - 1;
	string res = "";
	int nho = 0;
	while (i >= 0){
		int tmp = (a[i] - '0') + (b[i] - '0') + nho;
		if (tmp >= 10) {
			nho = 1; tmp -= 10;
		}
		else nho = 0;
		res.insert(res.begin(), tmp + '0');
		i--;
	}
	if (nho) res.insert(res.begin(), nho + '0');
	return res;
}

//2 mu trừ n
string fstrDiv2v2(string str){ //str div 2 version 2 ko bỏ "0" đầu
	string res = "";
	int i = 0;
	int soDu = 0;
	while (i < str.length()){
		soDu = 10 * soDu + (str[i] - '0');
		res += (soDu / 2) + '0';
		soDu %= 2;
		i++;
	}
	/*int l = res.length() - 1;
	for (int i = 0; i < res.length() - 1; i++){
	if (res[i] != '0'){
	l = i;
	break;
	}
	}*/
	//return res.substr(l);
	return res;
}
string _2Exp_n(int n){
	string _2Exp_i = "5";
	for (int i = 2; i <= n; i++){
		_2Exp_i = fstrDiv2v2(_2Exp_i + "0");
	}
	return _2Exp_i;
}
string addFrac(string a, string b){
	while (a.length() < b.length()) a += "0";
	return fstrPlusStr(a, b);
}

string fBinToDec(string bin){
	string res = "";
	if (bin[0] == '1') res += "-";
	string bias = bin.substr(1, 15);
	//doi bias sang string thap phan
	string temp = "";
	for (int i = 0; i < bias.length(); i++){
		if (bias[i]=='1'){
			string mu2 = f_2Expn(14 - i);
			temp = fstrPlusStr(temp, mu2);
		}
	}
	bias = temp;
	int mu = stoi(bias) - 16383; //k=16383
	string frac = "";
	for (int i = 16; i < 128; i++){
		if (bin[i] == '1') {
			string mu2 = _2Exp_n(i - 15);
			frac = addFrac(frac, mu2);
		}
	}
	string frac0 = frac; //tach phan thap phan ra nhan 2 mu bias
	for (int i = 0; i < mu; i++){
		frac = fstrx2(frac);
	}
	int du = frac.length() - frac0.length(); //sau khi nhan ta được thêm phần nguyên trước vị trí du
	string part1 = fstrPlusStr(f_2Expn(mu), frac.substr(0,du));
	string part2 = frac.substr(du);
	while (part2[part2.length()-1]=='0')
		 part2.erase(part2.end()-1); //str.end()-1 ms là iterator phần tử cuối
	return res+part1 + "." + part2;
}


//int main(){
//	string a = "9.55";
//	cout << "a=" << a << endl;
//	string b= fDecToBin(a);
//	cout << b.length() << endl;
//	cout << b<<endl;
//
//	string decofa = fBinToDec(b);
//	cout << decofa << endl;
//	return 0;
//}