#include "QFloat.h"


int QFloat::getBit(int pos){ //pos tinh tu l->r : 0->127
	int data_i = pos / 32;
	pos %= 32;
	int bit = (this->m_data[data_i] >> (31 - pos)) & 1;
	return bit;
}

//Set bit vào vị trí pos của QFloat
void QFloat::setBit(int pos, int bit){
	int bitpos = this->getBit(pos);
	int data_i = pos / 32;
	pos = pos % 32;
	if (bitpos == 1 && bit == 0){
		this->m_data[data_i] = this->m_data[data_i] - (1 << (31 - pos));
	}
	else{
		this->m_data[data_i] = this->m_data[data_i] | (bit << (31 - pos));
	}
	//or ma bit=1 thi no sẽ set đúng, còn bit=0 thì ko đổi.
}


QFloat::QFloat(){
	m_data[0] = m_data[1] = m_data[2] = m_data[3] = 0;
}

//full constructor
QFloat::QFloat(int x, int y, int z, int t){
	m_data[0] = x;
	m_data[1] = y;
	m_data[2] = z;
	m_data[3] = t;
}
//Constructor với đối số là dãy bit
QFloat::QFloat(string binArr){ //128 bit
	while (binArr.length() < 128)
		binArr += "0";//thêm "0" ở phía sau
	for (int i = 0; i < 128; i++){
		this->setBit(i, binArr[i] - '0');
	}
}
QFloat::QFloat(const QFloat& b){
	for (int i = 0; i < 4; i++){
		this->m_data[i] = b.m_data[i];
	}
}

void QFloat::setSign(string &part1)
{
	if (part1[0] == '-')
	{
		setBit(0, 1);
		part1 = part1.substr(1);
	}
	else
		setBit(0, 0);
}

void QFloat::setExp(string exp_bit)
{
	int pos = 1;
	for (int i = 0; i < exp_bit.size(); i++) {
		setBit(pos, exp_bit[i] - '0');
		pos++;
	}
}

void QFloat::setFraction(string fraction)
{
	int pos = 16;
	for (int i = 0; i < fraction.size(); i++) {
		setBit(pos, fraction[i] - '0');
		pos++;
	}
}

void QFloat::ScanQFloat(string input, int base) {
	if (base == 10)
	{
		// case input equal 0
		if (input == "0" || input == "-0" || input == "+0")
		{
			int pos = 0;
			for (int i = 0; i < 128; i++) {
				setBit(pos, 0);
				pos++;
			}

			return;
		}

		pair <string, string> pss = split_float_num(input);
		string part1 = pss.first;
		string part2 = pss.second;

		
		// set sign
		setSign(part1);

		// count exponent

		string bitPart1 = getBitPart1(part1);
		string bitPart2 = getBitPart2(part2);
		string fraction = bitPart1;


		fraction.insert(fraction.end(), bitPart2.begin(), bitPart2.end());


		int exp = countExponent(bitPart1, bitPart2);
		
		string exp_bit = cvBias(exp);

		setExp(exp_bit);

		//update fraction

		for (int i = 0; i < fraction.size(); i++) {
			if (fraction[i] == '1') {
				if (i >= 0)
					fraction.erase(fraction.begin(), fraction.begin() + i + 1);

				break;
			}
		}
		cout << endl;
		

		int tmp = fraction.size();
		for (int i = 1; i <= 112 - tmp; i++) {
			fraction.push_back('0');
		}
		if (fraction.size() > 112) {
			fraction.erase(fraction.begin() + 112, fraction.end());
		}

		setFraction(fraction);
	}
	else if (base == 2) {
		if (input.size() != 128) {
			puts("invalid input!!!");
			return;
		}
		else {
			for (int i = 0; i < input.size(); i++)
			{
				setBit(i, input[i] - '0');
			}
		}
	}
	else {
		puts("unavailable base!!");
	}
}

void QFloat::printNormalize(string bit) {
	string exp_bit;
	for (int i = 1; i <= 15; i++) {
		exp_bit.push_back(bit[i]);
	}
	int exp = cvBiasToNum(exp_bit);



	string part1 = "";
	string part2 = "";
	if (exp < 0) {
		part1 += "0";
		for (int i = 1; i <= abs(exp) - 1; i++)
			part2 += "0";
		part2 += "1";
		for (int i = 16; i < 128; ++i)
			part2.push_back(bit[i]);
	}
	else {
		part1.push_back('1');
		for (int i = 16; i < 16 + exp; i++)
			part1.push_back(bit[i]);
		for (int i = 16 + exp; i < 128; i++)
			part2.push_back(bit[i]);
	}


	if (getBit(0) == 1)
		cout << "-";
	cout << BitToNumBeforeDot(part1);
	cout << "." << BitToNumAfterDot(part2);
	cout << endl;

}

void QFloat::printDeNormalize(string bit)
{
	if (bit[0] == 1)
		cout << "-";

	bit = bit.substr(16);
	
	string res = "0";

	for (int i = 111; i >= 0; i--) {
		if (bit[111 - i] == '1') {
			int exp = 16494 + i;
			res = addFrac(res, _2Exp_n(exp));
		}
	}

	cout << res << endl;
}

void QFloat::PrintQFloat(int base) {
	
	string bit;
	for (int i = 0; i < 128; i++) {
		bit.push_back(getBit(i)+'0');
	}
	if (base == 2) {
		cout << bit << endl;
		return;
	}

	int type = Classification(bit);

	switch (type) {
	case 0:
		cout << "0";
		break;
	case 1:
		printNormalize(bit);
		break;
	case 2:
		printDeNormalize(bit);
		break;
	case 3:
		cout << "Inf\n";
		break;
	case 4:
		cout << "NaN\n";
		break;
	}
}

bool QFloat::checkZero() {
	for (int i = 1; i < 128; i++)
		if (getBit(i) == 1)
			return false;
	return true;
}

bool QFloat::checkExpEqual( QFloat&y) {
	for (int i = 1; i < 16; i++)
		if (getBit(i) != y.getBit(i))
			return false;
	return true;
}
bool QFloat::checkExpOverflow() {
	for (int i = 1; i < 16; i++) {
		if (getBit(i) == 0)
			return false;
	}
	return true;
}
bool QFloat::checkExpUnderflow() {
	for (int i = 1; i < 16; i++) {
		if (getBit(i) == 1)
			return false;
	}
	return true;
}
void QFloat::shiftLeftLogical(int start, int end, int bit) {
	for (int i = 0; i < bit; i++) {
		for (int j = start; j < end; j++) {
			setBit(j, getBit(j + 1));
		}
		setBit(end, 0);
	}
}
void QFloat::shiftRightLogical(int start, int end, int bit) {
	for (int i = 0; i < bit; i++) {
		for (int j = end; j > start; j--) {
			setBit(j, getBit(j - 1));
		}
		setBit(start, 0);
	}
}
bool QFloat::isSignificandZero() {
	for (int i = 1; i < 16; i++)
		if (getBit(i) != 0)
			return false;
	return true;
}

void QFloat::IncrementOne(int start, int end) {
	int rem = 1;
	for (int i = end; i >= start; i--) {
		int temp = getBit(i) + rem;
		setBit(i, temp % 2);
		rem = temp / 2;
	}
}
void QFloat::DecrementOne(int start, int end) {
	int rem = 1;
	for (int i = end; i >= start; i--) {
		int temp = getBit(i) - rem;
		setBit(i, temp == 0 ? 0 : 1);
		temp == 0 ? rem = 0 : rem = 1;
	}
}

QFloat QFloat::operator+(const QFloat &num2) {
	QFloat res, x = *this, y = num2;
	string remBit = "";
	//Kiem tra x hoac y co bang 0 hay khong
	if (x.checkZero()) {
		res = y;
		return res;
	}
	else {
		if (y.checkZero()) {
			res = x;
			return res;
		}
		else {
			//Lap den khi ca 2 phan mu deu bang nhau
			bool flag = 0;
			for (int i = 1; i < 16; i++) {
				if (x.getBit(i) < y.getBit(i)) {
					flag = 1;
					break;
				}
			}

			while (!x.checkExpEqual(y)) {
				//Tang ben mu nho hoc
				flag == 1 ? x.IncrementOne(1, 15) : y.IncrementOne(1, 15);
				flag == 1 ? x.shiftRightLogical(16, 127, 1) : y.shiftRightLogical(16, 127, 1);
				//Kiem tra tri co bang 0 hay khong
				if (x.isSignificandZero()) {
					res = y;
					return res;
				}
				if (y.isSignificandZero()) {
					res = x;
					return res;
				}
			}

			//Lay gia tri phan mu bang nhau gan cho res
			for (int i = 1; i < 16; i++) {
				res.setBit(i, x.getBit(i));
			}
			
			//Cong phan dau
			res.setBit(0, (x.getBit(0) + y.getBit(0)) % 2);
			//Cong phan tri cua 2 so vao nhau
			int rem = 0;
			for (int j = 127; j >= 16; j--) {
				int temp = x.getBit(j) + y.getBit(j) + rem;
				res.setBit(j, temp % 2);
				rem = temp / 2;
			}
			res.PrintQFloat(10);
			cout << endl;
			//Kiem tra neu 2 so trai dau va tong phan tri bang 0 thi se ra 0
			if (x.getBit(0) != y.getBit(0) && res.isSignificandZero()) {
				res.m_data[0] = res.m_data[1] = res.m_data[2] = res.m_data[3] = 0;
				return res;
			}
			//Nguoc lai, xay ra tran so phan tri -> dich phai 1 bit, roi tang phan mu len 1
			else {
				if (rem == 1) {
					remBit += to_string(res.getBit(127));
					res.shiftRightLogical(16, 127, 1);
					res.IncrementOne(1, 15);
					//Kiem tra xem co tran mu hay khong?
					if (res.checkExpOverflow()) {
						cout << "Tran so tren!" << endl;
						return res;
					}
				}
				else {
					//Dua ve dang chuan (tuc la bit dau cua phan tri khac 0)
					while (res.getBit(16) != 0) {
						res.shiftLeftLogical(16, 127, 1);
						res.setBit(127, remBit[0]);
						remBit = remBit.substr(1, remBit.length() - 1);
						res.DecrementOne(1, 15);
					}
					if (res.checkExpUnderflow() && rem == 1) {
						cout << "Tran so duoi!" << endl;
						return res;
					}
					/*Lam tron ket qua (remBit co dang 01111 -> khong can lam tron,
					remBit co dang 10010->lam tron)*/
					/*if (remBit[0] == 1) {
						for (int i = 1; i < remBit.length(); i++) {
							if (remBit[i] == 1)
								res.IncrementOne(16, 127);
						}
					}*/
					return res;
				}
			}
		}
	}
}
QFloat QFloat::operator-(const QFloat &num2) {
	QFloat res, x = *this, y = num2;
	y.getBit(0) == 0 ? y.setBit(0, 1) : y.setBit(0, 0);
	res = x + y;
	return res;
}

bool QFloat::is0(){
	for (int i = 0; i < 128; i++){
		if (this->getBit(i) == 1) return false;
	}
	return true;
}


string normalize(string multi, int& addExp){ //addExp: số mũ cần tăng hoặc giảm
	multi = multi.substr(30);
	int i = 0;
	for (; i < multi.length(); i++){
		if (multi[i] == '1') {
			addExp = 1 - i; //công thức chứng minh sau
			break;
		}
	}
	return multi.substr(i + 1); //return về dãy bit mantissa của kết quả 
}

QFloat QFloat::operator * (QFloat& y){
	QFloat x, z;
	x = (*this);
	if (x.is0() || y.is0())
		return QFloat("0");
	int addExp = 0; //số mũ cần modify sau khi normalize
	string biasOfx = x.getFromTo(1, 15); //getFromTo định nghĩa ở dưới
	string biasOfy = y.getFromTo(1, 15);
	QInt t1(biasOfx), t2(biasOfy);
	string fracOfx = x.getFromTo(16, 127);
	string fracOfy = y.getFromTo(16, 127);
	fracOfx.insert(fracOfx.begin(), '1');
	fracOfy.insert(fracOfy.begin(), '1');
	QInt f1(fracOfx);
	QInt f2(fracOfy);
	string fracOfz = normalize(f1.nhan(f2), addExp); //nhan return string 128*2=256 bits, normalize định nghĩa ở dưới
	string biasOfz = (QInt(biasOfx) + QInt(biasOfy) - QInt("011111111111111") + QInt(0, 0, 0, addExp)).getFromTo(113, 127);

	string minus = "0";
	if (x.getBit(0) != y.getBit(0)) {//trái dấu
		minus = "1";
	}
	return QFloat(minus + biasOfz + fracOfz);
}




//Phép chia cũng có các hàm tương tự như sau
string normalizeDivision(string quotient, int& addExp){ //qutient đã lượt bỏ 0 đầu
	//113/56 -> 58 kí tự
	if (quotient.length() == 58) {//nghĩa là bit nguyên =1
		addExp = 0;
	}
	else { //quotient.length()==57
		addExp = -1;
	}
	quotient.erase(quotient.begin()); //bỏ bit 1 đầu để đưa về dạng chuẩn
	return quotient;
}
QFloat QFloat::operator /(QFloat& y){
	QFloat x, z;
	x = (*this);
	if (x.is0())
		return QFloat("0");
	if (y.is0())
		return QFloat("01111111111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

	string biasOfx = x.getFromTo(1, 15);
	string biasOfy = y.getFromTo(1, 15);
	QInt t1(biasOfx), t2(biasOfy);

	string fracOfx = x.getFromTo(16, 127);
	string fracOfy = y.getFromTo(16, 127);
	fracOfx.insert(fracOfx.begin(), '1');
	fracOfy.insert(fracOfy.begin(), '1');
	fracOfy = fracOfy.substr(0, 56);
	QInt f1(fracOfx);
	QInt f2(fracOfy);
	int addExp = 0; //0 or -1
	string fracOfz = normalizeDivision(f1.chia(f2), addExp);
	string biasOfz = (QInt(biasOfx) + QInt("011111111111111") - QInt(biasOfy) + QInt(0, 0, 0, addExp)).getFromTo(113, 127);
	string minus = "0";
	if (x.getBit(0) != y.getBit(0)) {//trái dấu
		minus = "1";
	}
	while (fracOfz.length() < 116) fracOfz += "0";
	return QFloat(minus + biasOfz + fracOfz);
}
string QFloat::getFromTo(int x, int y){
	string res = "";
	for (int i = x; i <= y; i++){
		res += getBit(i) + '0';
	}
	return res;
}