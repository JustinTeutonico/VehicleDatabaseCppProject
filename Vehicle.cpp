#include"Vehicle.h"

int Vehicle::getMonth() {
	int getMonth; int dum;
	curDate.getDate(dum, getMonth, dum);
	return getMonth;
}
int Vehicle::getDay() {
	int getDay; int dum;
	curDate.getDate(getDay, dum, dum);
	return getDay;
}
int Vehicle::getYear() {
	int getYear; int dum;
	curDate.getDate(dum, dum, getYear);
	return getYear;
}

Vehicle::Vehicle() {
	setDate(1, 1, 2016);
	setType("Unknown");
	ID = 11111; mileage = 100;
	drivername = "Default";
	checkedout = false;
	contents[99];//static array for holding 99 unique items. make dynamic?
}

void Vehicle::setContents(string a[], int num) {
	for (int i = 0; i < num; i++)
		this->contents[i] = a[i];
}

void Vehicle::print() {
	cout << endl << "ID: " << ID << endl;
	cout << "Purpose: " << usage_type << endl;
	cout << "Driver: " << drivername << endl;
	cout << "Date added: " << curDate << endl;
	cout << "Mileage: " << mileage << endl;
	cout << "Checkout status: ";
	if (checkedout)
		cout << "Checked out" << endl;
	else
		cout << "Checked in" << endl;
	if (!contents[0].empty()){//if there are contents registered
		cout << "Contents: " << endl;
		for (int i = 0; i < 99; i++) {
			if (!contents[i].empty())
				cout << contents[i] << endl;
			else
				i = 99;//kills loop if it detects no more items
		}
		cout << endl;
	}
	else
	{
		cout << "Contents:" << endl;
		cout << "Unset!" << endl;
	}
}


istream& operator >> (istream&is, Vehicle&v) {
	is >> v.ID >> v.drivername >> v.mileage >> v.checkedout >> v.usage_type >> v.curDate;
	return is;
}
ostream& operator << (ostream&os, Vehicle&v) {
	v.print();
	return os;
}