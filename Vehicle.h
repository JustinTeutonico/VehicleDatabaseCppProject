#include <iostream>
#include <string>
#include"Date.h"

using namespace std;

const int MAX = 99;

#pragma once
class Vehicle{
private://record ID, date, name, mileage, type usage, content
	int ID;//ID
	string drivername;//NAME
	int mileage;//MILAGE
	string contents[MAX];//CONTENT
	bool checkedout;
	string usage_type;
	Date curDate;
public:
	Vehicle();
	Vehicle(Date d, string type, int ID, int mileage, string drivername, bool checkedout) :curDate(d), usage_type(type), ID(ID), mileage(mileage), drivername(drivername), checkedout(checkedout){ }
	Vehicle(const Vehicle &obj) :curDate(obj.curDate), usage_type(obj.usage_type), ID(obj.ID), mileage(obj.mileage), drivername(obj.drivername), checkedout(obj.checkedout) { }
	~Vehicle() {  }

	void setID(int a) { ID = a; }
	int getID() { return ID; }

	void setDrivername(string a) { drivername = a; }
	string getDrivername() { return drivername; }

	void setMileage(int a) { mileage = a; }
	int getMileage() { return mileage; }

	void setCheckedout(bool c) { checkedout = c; }
	bool getCheckout() { return checkedout; }

	void setContents(string a[], int num);

	void setType(string a) { usage_type = a; }
	string getUsageType() { return usage_type; }

	void setDate(int d, int m, int y) { curDate.setDate(d, m, y); }
	void setDate(Date d) { curDate = d; }
	Date getDate() { return curDate; }
	int getMonth();
	int getDay();
	int getYear();

	friend istream& operator >> (istream&is, Vehicle&v);
	friend ostream& operator << (ostream&os, Vehicle&v);

	virtual void print();
};