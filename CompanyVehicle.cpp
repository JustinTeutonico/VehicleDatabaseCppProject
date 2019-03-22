#include "CompanyVehicle.h"
#pragma once
CompanyVehicle::CompanyVehicle() {
	Vehicle::Vehicle();
	this->miles_driven = 0.0;
	this->fuel_cost = 0.0;
	this->purpose = "NO PURPOSE SET";
}
CompanyVehicle::CompanyVehicle(Vehicle info, double miles_driven, double fuel_cost, string purpose) {
	Vehicle::Vehicle(info);
	this->miles_driven = miles_driven;
	this->fuel_cost = fuel_cost;
	this->purpose = purpose;
}

void CompanyVehicle::print() {
	Vehicle::print();
	cout << "Miles driven: " << miles_driven << endl;
	cout << "Fuel cost: $ " << fuel_cost << endl;
	cout << "Purpose of trip: " << purpose << endl;
}