#include "Vehicle.h"
#pragma once
class CompanyVehicle : public Vehicle {
public:
	CompanyVehicle();
	CompanyVehicle(Vehicle info, double miles_driven, double fuel_cost, string purpose);
	CompanyVehicle(const CompanyVehicle &obj) :Vehicle(obj), miles_driven(obj.miles_driven), fuel_cost(obj.fuel_cost), purpose(obj.purpose) {}

	~CompanyVehicle() {  }

	void setMilesDriven(double a) { miles_driven = a; }
	void setFuelCost(double a) { fuel_cost = a; }
	void setPurpose(string a) { purpose = a; }

	double getMilesDriven() { return miles_driven; }
	double getFuelCost() { return fuel_cost; }
	string getPurpose() { return purpose; }

	virtual void print();
private:
	double miles_driven;
	double fuel_cost;
	string purpose;
};