#include "PersonalVehicle.h"
#pragma once
PersonalVehicle::PersonalVehicle() {
	Vehicle::Vehicle();
	this->insurCompName = "NotSet!";
	this->policyNumber = 1000;
	Date d(1, 1, 2016);
	this->effective = d;
	this->expiration = d;
	this->carYear = 0;
	this->carMakeModel = "NotSet!";
}
PersonalVehicle::PersonalVehicle(Vehicle info, string i, int p, Date ef, Date ex, int cy, string make) {
	Vehicle::Vehicle(info);
	this->insurCompName = i;
	this->policyNumber = p;
	this->effective = ef;
	this->expiration = ex;
	this->carYear = cy;
	this->carMakeModel = make;
}
void PersonalVehicle::setEffective(int a, int b, int c) {
	Date d(a, b, c);
	this->effective = d;
}
void PersonalVehicle::setExpiration(int a, int b, int c) {
	Date d(a, b, c);
	this->expiration = d;
}
void PersonalVehicle::print() {
	Vehicle::print();
	cout << "Insurance company: " << insurCompName << endl << "Policy #: " << policyNumber << endl;
	cout << "Date effective: " << effective << " Expires: " << expiration << endl;
	cout << "Car Make/Model: " << carMakeModel << " Year: " << carYear << endl;
}