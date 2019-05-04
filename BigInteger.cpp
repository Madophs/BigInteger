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
		BigInteger operator - (BigInteger);
		BigInteger operator -= (BigInteger);
		BigInteger operator * (BigInteger);
		BigInteger operator *= (BigInteger);
		BigInteger operator / (BigInteger);
		BigInteger operator /= (BigInteger);
		int & operator[](int);
		void operator = (BigInteger);
		bool operator == (BigInteger);
		bool operator < (BigInteger);
		bool operator <= (BigInteger);
		bool operator > (BigInteger);
		bool operator >= (BigInteger);
		bool operator != (BigInteger);
		friend istream & operator >> (istream &, BigInteger &);
		friend ostream & operator << (ostream &, BigInteger &);
		void print();
		int length();
		void readString(string);
	private:
		vector<int> value;
};

BigInteger::BigInteger(){
	this->value.emplace_back(0);
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
int BigInteger::length(){
	return this->value.size();
}
void BigInteger::readString(string str){
	if(str.empty())return;
	value.clear();
	for(int i = str.length()-1; i>-1; i--){
		this->value.emplace_back(str[i]-'0');
	}
}

int & BigInteger::BigInteger::operator[](int index){
	return this->value[this->length()-1-index];
}

istream & operator >> (istream &in,BigInteger &bigInteger){
	string str;
	in>>str;
	bigInteger.readString(str);
	return in;
}

ostream & operator << (ostream &out, BigInteger &bigInteger){
	for(int i = 0; i < bigInteger.length(); i++){
		out<<bigInteger[i];
	}
	return out;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	BigInteger a, b;
	BigInteger c("8769478954785748975894792");
	while(cin>>a>>b){
		cout<<a<<" "<<b<<endl;
		cout<<c[5]<<endl;
	}
	return 0;
}