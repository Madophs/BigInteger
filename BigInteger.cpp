#include <bits/stdc++.h>

using namespace std;

class BigInteger{
	public:
		BigInteger();
		BigInteger(string);
		BigInteger(int);
		BigInteger(long long);
		BigInteger operator + (BigInteger);
		BigInteger operator += (BigInteger);
		BigInteger & operator ++();
		BigInteger operator ++(int);
		BigInteger operator - (BigInteger);
		BigInteger operator -= (BigInteger);
		BigInteger & operator --();
		BigInteger operator --(int);
		BigInteger operator * (BigInteger);
		BigInteger operator *= (BigInteger);
		BigInteger operator / (BigInteger);
		BigInteger operator /= (BigInteger);
		BigInteger operator % (BigInteger);
		BigInteger operator %= (BigInteger);
		unsigned int & operator[](int);
		void operator = (BigInteger);
		bool operator == (BigInteger &);
		bool operator != (BigInteger &);
		bool operator < (BigInteger &);
		bool operator <= (BigInteger &);
		bool operator > (BigInteger &);
		bool operator >= (BigInteger &);
		void print();
		int length();
		bool isPositive();
		void readString(string);
	private:
		vector<unsigned int> value;
		bool positive;
		void addLeadingZeros(int);
		void removeLeadingZeros();
		void makePositiveIfZero();
		unsigned int & getValueAt(int);
		BigInteger addition(BigInteger &,BigInteger &);
		BigInteger substraction(BigInteger, BigInteger &);
		BigInteger multiplication(BigInteger &, BigInteger &);
		BigInteger division(BigInteger &, BigInteger &);
		BigInteger pow(BigInteger &);
		BigInteger pow(int);
};

BigInteger::BigInteger(){
	this->value.emplace_back(0);
	positive = true;
}

BigInteger::BigInteger(string stringValue){
	readString(stringValue);
}

BigInteger::BigInteger(int integerValue){
	string stringValue = to_string(integerValue);
	readString(stringValue);
}

BigInteger::BigInteger(long long LLValue){
	string stringValue = to_string(LLValue);
	readString(stringValue);
}
BigInteger BigInteger::operator + (BigInteger bigNumber){
	return addition(*this,bigNumber);
}

BigInteger BigInteger::operator += (BigInteger bigNumber){
	*this = addition(*this,bigNumber);
	return *this;
}
BigInteger & BigInteger::operator ++ (){
	BigInteger one("1");
	*this = addition(*this,one);
	return *this;
}

BigInteger BigInteger::operator ++ (int){
	BigInteger one("1");
	BigInteger prevCopy = *this;
	*this = addition(*this,one);
	return prevCopy;
}

BigInteger BigInteger::operator - (BigInteger bigNumber){
	bigNumber.positive = !bigNumber.positive;
	return addition(*this, bigNumber);
}

BigInteger BigInteger::operator -= (BigInteger bigNumber){
	bigNumber.positive = !bigNumber.positive;
	*this = addition(*this,bigNumber);
	return *this;
}

BigInteger & BigInteger::operator -- (){
	BigInteger one("1");
	one.positive = false;
	*this = addition(*this,one);
	return *this;
}
BigInteger BigInteger::operator --(int){
	BigInteger one("1");
	one.positive = false;
	BigInteger prevCopy = *this;
	*this = addition(*this,one);
	return prevCopy;
}
unsigned int & BigInteger::operator[](int index){
	return this->value[this->length()-1-index];
}

void BigInteger::operator = (BigInteger bigNumber){
	this->value = bigNumber.value;
	this->positive = bigNumber.positive;
}

bool BigInteger::operator == (BigInteger &bigNumber){
	if(this->positive != bigNumber.positive) return false;
	if(value.size() != bigNumber.length()) return false;
	for(int i = 0; i<bigNumber.length(); i++){
		if(getValueAt(i) != bigNumber.getValueAt(i)) return false;
	}
	return true;
}

bool BigInteger::operator != (BigInteger &bigNumber){
	if(this->positive != bigNumber.positive) return true;
	if(value.size() != bigNumber.length()) return true;
	for(int i = 0; i<bigNumber.length(); i++){
		if(getValueAt(i) != bigNumber.getValueAt(i)) return true;
	}
	return false;
}
bool BigInteger::operator < (BigInteger &bigNumber){
	if(!this->positive && !bigNumber.positive){
		if(this->length() != bigNumber.length()){
			if(this->length() > bigNumber.length()) return true;
			return false;
		}
		for(int i = this->length()-1; i>=0; i--){
			if(this->getValueAt(i) == bigNumber.getValueAt(i)) continue;
			if(this->getValueAt(i) > bigNumber.getValueAt(i)) return true;
		}
		return false;
	}
	if(this->positive != bigNumber.positive){
		if(!this->positive && bigNumber.positive) return true;
		return false;
	}
	if(this->length() != bigNumber.length()){
		if(this->length() < bigNumber.length()) return true;
		return false;
	}
	for(int i = this->length()-1; i>=0; i--){
		if(this->value[i] == bigNumber.value[i]) continue;
		if(this->value[i] < bigNumber.value[i]) return true;
	}
	return false;
}

bool BigInteger::operator <= (BigInteger &bigNumber){
	if(!this->positive && !bigNumber.positive){
		if(this->length() != bigNumber.length()){
			if(this->length() > bigNumber.length()) return true;
			return false;
		}
		for(int i = this->length()-1; i>=0; i--){
			if(this->getValueAt(i) > bigNumber.getValueAt(i)) return true;
			if(this->getValueAt(i) == bigNumber.getValueAt(i)) continue;
			if(this->getValueAt(i) < bigNumber.getValueAt(i)) return false;
		}
		return true;
	}
	if(this->positive != bigNumber.positive){
		if(!this->positive && bigNumber.positive) return true;
		return false;
	}
	if(this->length() != bigNumber.length()){
		if(this->length() < bigNumber.length()) return true;
		return false;
	}
	for(int i = this->length()-1; i>=0; i--){
		if(this->value[i] < bigNumber.value[i]) return true;
		if(this->value[i] == bigNumber.value[i]) continue;
		if(this->value[i] > bigNumber.value[i]) return false;
	}
	return true;
}

bool BigInteger::operator > (BigInteger &bigNumber){
	return !(*this <= bigNumber);
}

bool BigInteger::operator >= (BigInteger &bigNumber){
	return !(*this < bigNumber);
}
istream & operator >> (istream &in,BigInteger &bigInteger){
	string str;
	in>>str;
	bigInteger.readString(str);
	return in;
}


ostream & operator << (ostream &out, BigInteger bigInteger){
	if(!bigInteger.isPositive()) cout<<"-";
	for(int i = 0; i < bigInteger.length(); i++){
		out<<bigInteger[i];
	}
	return out;
}
int BigInteger::length(){
	return this->value.size();
}
bool BigInteger::isPositive(){
	return this->positive;
}
void BigInteger::readString(string str){
	if(str.empty())return;
	value.clear();
	positive = str[0] != '-';
	for(int i = str.length()-1; i>-1+!positive; i--){
		this->value.emplace_back(str[i]-'0');
	}
	removeLeadingZeros();
	makePositiveIfZero();
}
void BigInteger::addLeadingZeros(int zeros){
	while(zeros--) value.emplace_back(0);
}

void BigInteger::removeLeadingZeros(){
	while(value.back() == 0 && value.size() > 1)
		value.pop_back();
}
void BigInteger::makePositiveIfZero(){
	if(this->length() > 1) return;
	if(!this->getValueAt(0)) positive = true;
}
unsigned int & BigInteger::getValueAt(int index){
	return value[index];
}
BigInteger BigInteger::addition(BigInteger &big1, BigInteger &big2){
	if(big1.isPositive() != big2.isPositive()){
		if(big1.length() != big2.length()){
			if(big1.length() > big2.length()){
				return substraction(big1,big2);
			}else{
				return substraction(big2,big1);
			}
		}else{
			for(int i = big1.length()-1; i>=0; i++){
				if(big1.getValueAt(i) == big2.getValueAt(i)) continue;
				if(big1.getValueAt(i) > big2.getValueAt(i)) return substraction(big1,big2);
				return substraction(big2,big1);
			}
			return BigInteger();
		}
	}

	BigInteger result;
	result.addLeadingZeros(max(big1.length(),big2.length())+1);
	int i = 0, carry = 0, maxLength = max(big1.length(), big2.length());
	for(; i < maxLength; i++){
		int sum = (i<big1.length()?big1.getValueAt(i):0) + (i<big2.length()?big2.getValueAt(i):0) + carry;
		carry = sum/10;
		result.getValueAt(i) = sum%10;
	}
	while(carry) result.getValueAt(i++) = carry, carry = carry/10;
	result.removeLeadingZeros();
	result.positive = big1.positive;
	result.makePositiveIfZero();
	return result;
}

BigInteger BigInteger::substraction(BigInteger big1, BigInteger &big2){
	BigInteger result;
	result.addLeadingZeros(big1.length());
	for(int i = 0; i<big1.length(); i++){
		int diff = 0;
		if(i < big2.length() && big1.getValueAt(i) < big2.getValueAt(i)){
			for(int j = i+1; j<big1.length(); j++){
				if(big1.getValueAt(j)){
					--big1.getValueAt(j);
					break;
				}else{
					big1.getValueAt(j) = 9;
				}
			}
			int val1 = big1.getValueAt(i)+10, val2 = big2.getValueAt(i);
			result.getValueAt(i) = val1-val2;
		}else{
			result.getValueAt(i) = big1.getValueAt(i) - (i<big2.length()?big2.getValueAt(i):0);
		}
	}
	if(!big1.isPositive()){
		result.positive = false;
	}
	result.removeLeadingZeros();
	result.makePositiveIfZero();
	return result;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	BigInteger a, b;
	BigInteger c("8769478954785748975894792");
	BigInteger limit;
	BigInteger one("1");
	BigInteger x,y,w,z;
	for(BigInteger i("00020"); i>=limit; i--){
		//cout<<i<<" ";
		cout<<++x<<" "<<y++<<" ";
		cout<<--w<<" "<<z--<<endl;
	}
	cout<<endl;
	for(int i =-10; i<=10; i++){
		cout<<i<<" ";
	}
	cout<<endl;
	cout<<"Value = "<<BigInteger("-000010")<<endl;
	while(cin>>a>>b){
		cout<<a<<" "<<b<<endl;
		cout<<a-b<<endl;
		cout<<a+b<<endl;
	}
	return 0;
}