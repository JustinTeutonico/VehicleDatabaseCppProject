#include"Date.h"
void Date::setDate(int m, int d, int y) {
	day = d; month = m;	year = y;
}

void Date::getDate(int &m, int &d, int &y) {
	d = day;	m = month;	y = year;
}

ostream& operator<<(ostream& out, const Date& d) {
	out << d.month << " / " << d.day << " / " << d.year;
	return out;
}

istream& operator>>(istream& in, Date&d) {
	in >> d.month; cin >> d.day; cin >> d.year;
	return in;
}