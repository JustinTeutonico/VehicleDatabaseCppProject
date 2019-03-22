#include "Vehicle.h"
#pragma once
class PersonalVehicle : public Vehicle {
private:
	string insurCompName;
	int policyNumber;
	Date effective;
	Date expiration;
	int carYear;
	string carMakeModel;
public:
	PersonalVehicle();
	PersonalVehicle(Vehicle info, string i, int p, Date ef, Date ex, int cy, string make);
	PersonalVehicle(const PersonalVehicle &obj) :Vehicle(obj), insurCompName(obj.insurCompName), policyNumber(obj.policyNumber), effective(obj.effective), expiration(obj.expiration), carYear(obj.carYear), carMakeModel(obj.carMakeModel){}

	~PersonalVehicle() { }

	void setInsurCompName(string n) { this->insurCompName = n; }
	void setPolicyNumber(int f) { this->policyNumber = f; }
	void setEffective(Date d) { this->effective = d; }
	void setEffective(int a, int b, int c);
	void setExpiration(Date d) { this->expiration = d; }
	void setExpiration(int a, int b, int c);
	void setCarYear(int g) { carYear = g; }
	void setCarMakeModel(string g) { carMakeModel = g; }

	string getInsurCompName() { return insurCompName; }
	int getPolicyNumber() { return policyNumber; }
	Date getEffective() { return effective; }
	Date getExpiration() { return expiration; }
	int getYear() { return carYear; }
	string getCarMakeModel() { return carMakeModel; }

	void print();
};