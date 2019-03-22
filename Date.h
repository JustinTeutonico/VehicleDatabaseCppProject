#include <iostream>
using namespace std;
#pragma once
class Date {
private:
	int day;
	int month;
	int year;
public:
	Date() : day(1), month(1), year(1) {}
	Date(int m, int d, int y) : month(m), day(d), year(y) {}
	void setDate(int m, int d, int y);
	void getDate(int &m, int &d, int &y);
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date&d);
};