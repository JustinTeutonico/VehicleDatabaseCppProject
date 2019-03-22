//CSC 330 Project 1

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <ostream>

#include "Date.h"
#include "Vehicle.h"
#include "CompanyVehicle.h"
#include "PersonalVehicle.h"
using namespace std;

void c(string a) { cout << a << endl; }//function that displays a string and indents.
void p() { system("pause"); }//shortcut for calling pause
void cls() { system("cls"); }//shortcut for calling cls
fstream inputfile;	ofstream outputfile;//input/outfile files, global

int counter = 0;//GLOBAL VARIABLE - keeps track of # cars

void save(Vehicle *log[]) {
	if (counter == 0) {
		c("Error, there is nothing to save."); p(); return;
	}

	cout << "You can do a 'quick save', which will save a .txt file locally, or you can manually input where you want the text file to be saved." << endl;
	cout << "[1] Select this option to quick save to file location (WARNING: WILL OVERWRITE)\n";
	cout << "[2] Manually input a place on CPU to save file.\n";
	cout << "[3] Abort save.\n";
	int ans;
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	if (ans == 1) {
		outputfile.open("output.txt");
		outputfile << "This is the log for the Vehicle Checkout Program.\n";
		outputfile << "Total vehicles: " << counter << "\n";
		outputfile << "-------------------------------------\n";
		for (int i = 0; i < counter; i++)	{
			streambuf *oldbuf = cout.rdbuf();
			cout.rdbuf(outputfile.rdbuf());
			log[i]->print();
			cout.rdbuf(oldbuf);
			outputfile << "-------------------------------------\n";
		}
		outputfile.close();
		p();
	}
	else if (ans == 2) {
		string path;
		cout << "Now, carefully input the path to save the file to.\n";
		cout << "For example: C:\\Users\\NAME\\Documents\\FILENAME.TXT" << endl;
		cin >> path;
		cout << "Make sure your path is correct before continuing!\n";
		cout << "You entered: " << path << endl;
		cout << "You must also name the file at the end of the path, with a .txt filetype.\n";
		cout << "Are you sure with your input ? \n";
		cout << "[1] Yes\n[2] Resubmit...\n[3] Quit...\n";
		while (!(cin >> ans)) {
			cin.clear();
			cin.ignore(1000, '\n');//ignores 1000 inputs. 
			cout << "Bad input. Try again: " << endl;
		}
		if (ans == 1) {
			outputfile.open(path);
			outputfile << "This is the log for the Vehicle Checkout Program.\n";
			outputfile << "Total vehicles: " << counter << "\n";
			outputfile << "-------------------------------------\n";
			for (int i = 0; i < counter; i++) {
				streambuf *oldbuf = std::cout.rdbuf(); //<--get stuff from a void() onto a text file
				cout.rdbuf(outputfile.rdbuf());//accept the print function. outputfile<<log[i].print() will give error
				log[i]->print();
				cout.rdbuf(oldbuf);//makes it return to normal.
				outputfile << "-------------------------------------\n";
			}
			outputfile.close();
			p();
		}
		else if (ans == 2) {
			cout << "Input: " << endl; cin >> path;
			outputfile.open(path);
			outputfile << "This is the log for the Vehicle Checkout Program.\n";
			outputfile << "Total vehicles: " << counter << "\n";
			outputfile << "-------------------------------------\n";
			for (int i = 0; i < counter; i++){
				streambuf *oldbuf = std::cout.rdbuf(); //thanks to google i found a way to make it so that you can get stuff from a void() onto a text file
				cout.rdbuf(outputfile.rdbuf());//this changes it so that it can accept the print function. outputfile<<log[i].print() will give error
				log[i]->print();
				cout.rdbuf(oldbuf);//makes it return to normal.
				outputfile << "-------------------------------------\n";
			}
			outputfile.close();
			p();
		}
		else if (ans == 3)
			return;
	}
}
void actual_load(Vehicle *log[], string path) {
	int int_1, int_2, int_3;
	string strings, data1;
	counter = 0;
	inputfile.open(path);
	if (!inputfile)
	{
		cout << "ERROR! FILE NOT FOUND!\n"; return;
	}
	for (int k = 0; k < 11; k++)
		inputfile >> strings;
	inputfile >> int_1;
	int vehicle_count = int_1;
	inputfile >> strings;
	int num_loaded = 1;
	cout << "Number of vehicles loaded: ";
	for (int l = 0; l<vehicle_count; l++)
	{
		cout << num_loaded++ << "... ";
		if (num_loaded % 10 == 0)
			cout << endl;
		inputfile >> strings;//will read "ID:"
		inputfile >> int_1;//will read actual ID
		inputfile >> strings;//will read "purpose"
		inputfile >> data1;//will read actual purpose
		if (data1 == "Company")
		{
			CompanyVehicle v;
			v.setType(data1); v.setID(int_1);
			inputfile >> strings;//will read "Driver:"
			inputfile >> strings;//will read actual driver
			v.setDrivername(strings);
			inputfile >> strings;//will read text, "Date"
			inputfile >> strings;//will read text, "added:"
			inputfile >> int_1;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_2;//will read day
			inputfile >> strings;//will read '/'
			inputfile >> int_3;//will read year

			v.setDate(int_1, int_2, int_3);
			inputfile >> strings;//will read "mileage"
			inputfile >> int_1;//will read actual milage
			v.setMileage(int_1);
			inputfile >> strings;//will read "checkout"
			inputfile >> strings;//will read "status"
			inputfile >> strings;//will read"checked"
			inputfile >> strings;//will read in or out
			if (strings == "in")
				v.setCheckedout(false);
			else
				v.setCheckedout(true);
			inputfile >> strings;//will read"contents"
			inputfile >> strings;//will read content, if there

			if (strings != "Unset!")
			{
				string contents[99]; int i = 0;
				bool loop = true;
				contents[i] = strings;
				i += 1;
				while (loop)
				{
					inputfile >> strings;
					if (strings == "Miles")
						loop = false;
					else
						contents[i++] = strings;
				}
				string *actualcontents = new string[i];
				for (int j = 0; j < i; j++)
					actualcontents[j] = contents[j];
				v.setContents(actualcontents, i);
			}
			else if (strings == "Unset!")
				inputfile >> strings;//will read "miles"
			inputfile >> strings;//will read"driven"
			inputfile >> int_1;//will read miles driven
			v.setMilesDriven(int_1);
			for (int p = 0; p < 3; p++)
				inputfile >> strings;//fuel cost $
			inputfile >> int_1;
			v.setFuelCost(int_1);
			for (int p = 0; p < 3; p++)
				inputfile >> strings;//purpose of trip:
			inputfile >> strings;//actual purpose
			v.setPurpose(strings);
			inputfile >> strings;// "-------------"
			log[counter++] = new CompanyVehicle(v);

		}
		else if (data1 == "Personal") {
			PersonalVehicle v;
			v.setType(data1); v.setID(int_1);
			inputfile >> strings;//will read "Driver:"
			inputfile >> strings;//will read actual driver
			v.setDrivername(strings);
			inputfile >> strings;//will read text, "Date"
			inputfile >> strings;//will read text, "added:"
			inputfile >> int_1;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_2;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_3;//will read month
			v.setDate(int_1, int_2, int_3);

			inputfile >> strings;//will read "mileage"
			inputfile >> int_1;//will read actual milage
			v.setMileage(int_1);
			inputfile >> strings;//will read "checkout"
			inputfile >> strings;//will read "status"
			inputfile >> strings;//will read"checked"
			inputfile >> strings;//will read in or out
			if (strings == "in")
				v.setCheckedout(false);
			else
				v.setCheckedout(true);
			inputfile >> strings;//will read"contents"
			inputfile >> strings;//will read content, if there

			if (strings != "Unset!")
			{
				string contents[99]; int i = 0;
				bool loop = true;
				contents[i] = strings;
				i += 1;
				while (loop)
				{
					inputfile >> strings;
					if (strings == "Insurance")
						loop = false;
					else
						contents[i++] = strings;
				}
				string *actualcontents = new string[i];
				for (int j = 0; j < i; j++)
					actualcontents[j] = contents[j];
				v.setContents(actualcontents, i);
			}
			else if (strings == "Insurance")
				inputfile >> strings;//will read "nsurance"
			inputfile >> strings;//will read"company"
			inputfile >> strings;
			inputfile >> strings;//will read actual company
			v.setInsurCompName(strings);
			inputfile >> strings;//will read"policy"
			inputfile >> strings;//will read "#:"
			inputfile >> int_1;//will read policy#
			v.setPolicyNumber(int_1);
			inputfile >> strings;//will read"date"
			inputfile >> strings;//will read "effective"
			inputfile >> int_1;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_2;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_3;//will read month
			v.setEffective(int_1, int_2, int_3);

			inputfile >> strings;//will read "expires"
			inputfile >> int_1;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_2;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_3;//will read month

			v.setExpiration(int_1, int_2, int_3);

			inputfile >> strings;//will read"car"
			inputfile >> strings;//will read "makemodel"
			inputfile >> strings;//will read actual makemodel
			v.setCarMakeModel(strings);
			inputfile >> strings;//will read "year"
			inputfile >> int_1;//actual year
			v.setCarYear(int_1);
			inputfile >> strings;// "-------------"
			log[counter++] = new PersonalVehicle(v);
		}
		else if (data1 == "Passenger" || data1 == "Cargo") {
			Vehicle v;
			v.setType(data1); v.setID(int_1);
			inputfile >> strings;//will read "Driver:"
			inputfile >> strings;//will read actual driver
			v.setDrivername(strings);
			inputfile >> strings;//will read text, "Date"
			inputfile >> strings;//will read text, "added:"
			inputfile >> int_1;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_2;//will read month
			inputfile >> strings;//will read '/'
			inputfile >> int_3;//will read month
			v.setDate(int_1, int_2, int_3);

			inputfile >> strings;//will read "mileage"
			inputfile >> int_1;//will read actual milage
			v.setMileage(int_1);
			inputfile >> strings;//will read "checkout"
			inputfile >> strings;//will read "status"
			inputfile >> strings;//will read"checked"
			inputfile >> strings;//will read in or out
			if (strings == "in")
				v.setCheckedout(false);
			else
				v.setCheckedout(true);
			inputfile >> strings;//will read"contents"
			inputfile >> strings;//will read content, if there

			if (strings != "-------------------------------------")
			{
				string contents[99]; int i = 0;
				bool loop = true;
				contents[i] = strings;
				i += 1;
				while (loop)
				{
					inputfile >> strings;
					if (strings == "-------------------------------------")
						loop = false;
					else
						contents[i++] = strings;
				}
				string *actualcontents = new string[i];
				for (int j = 0; j < i; j++)
					actualcontents[j] = contents[j];
				v.setContents(actualcontents, i);
			}
			Vehicle* newV = new Vehicle(v);
			log[counter++] = newV;
		}
	}
	inputfile.close();
	cout << endl;
}
void load(Vehicle *log[]) {
	int ans = 0;
	if (counter != 0) {//log is not currently empty
		c("WARNING! This will overwrite whatever is currently in the log of the program itself. Continue?");
		c("[1] Yes"); c("[2] QUIT");
		while (!(cin >> ans)) {
			cin.clear();
			cin.ignore(1000, '\n');//ignores 1000 inputs. 
			cout << "Bad input. Try again: " << endl;
		}
		if (ans == 2)
			return;//aborts
	}
	cout << "You can do a 'quick load', which will load from a .txt file stored locally, or you can manually input where you want the text file to be loaded from." << endl;
	cout << "[1] Select this option to quick load to file location (will fail if never quick-saved)\n";
	cout << "[2] Manually input a place on CPU to load file.\n";
	cout << "[3] Abort load.\n";
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	if (ans == 1) {
		string path = "output.txt";
		actual_load(log, path);
	}
	else if (ans == 2)
	{
		string path;
		cout << "Now, carefully input the path to load the file from.\n";
		cout << "For example: C:\\Users\\NAME\\Documents\\FILENAME.TXT" << endl;
		cin >> path;
		cout << "Make sure your path is correct before continuing!\n";
		cout << "You entered: " << path << endl;
		cout << "You must also include the file type at the end of the path, with a .txt filetype.\n";
		cout << "Are you sure with your input ? \n";
		cout << "[1] Yes\n[2] Resubmit...\n[3] Quit...\n";
		while (!(cin >> ans)) {
			cin.clear();
			cin.ignore(1000, '\n');//ignores 1000 inputs. 
			cout << "Bad input. Try again: " << endl;
		}
		if (ans == 1)
			actual_load(log, path);
		else if (ans == 2) {
			cin >> path;
			actual_load(log, path);
		}
	}
	else if (ans == 3)
		return;
}

void editVehicle(Vehicle *v, Vehicle *log[]) {
	c("You may edit the aspects of the car, one item at a time.");
	c("You may not change its type.");
	c("To alter checkout status or contents, go to 'Check Out Vehicle' option in main menu.");
	bool loop = true; int a; string b; Date d;
	while (loop) {
		c("The current information for the car: ");
		v->print();
		c("You can edit...");
		cout << "[1] The ID\n[2] Driver Name\n[3] Date\n[4] Mileage\n[5] EXIT";
		while (!(cin >> a)) {
			cin.clear();
			cin.ignore(1000, '\n');//ignores 1000 inputs. 
			cout << "Bad input. Try again: " << endl;
		}
		if (a == 1) {
			cout << "Enter new ID: ";
			while (!(cin >> a)) {
				cin.clear();
				cin.ignore(1000, '\n');//ignores 1000 inputs. 
				cout << "Bad input. Try again: " << endl;
			}
			v->setID(a);
		}
		else if (a == 2) {
			cout << "Enter new driver name: "; cin >> b; v->setDrivername(b);
		}
		else if (a == 3) {
			cout << "Enter the date (m d yyyy): ";
			while (!(cin >> d)) {
				cin.clear();
				cin.ignore(1000, '\n');//ignores 1000 inputs. 
				cout << "Bad input. Try again: " << endl;
			}
			v->setDate(d);
		}
		else if (a == 4) {
			cout << "Enter the mileage: ";
			while (!(cin >> a)) {
				cin.clear();
				cin.ignore(1000, '\n');//ignores 1000 inputs. 
				cout << "Bad input. Try again: " << endl;
			}
			v->setMileage(a);
		}
		else{
			loop = false; return;
		}
		cls();

	}
}

void deleteV(Vehicle* log[]) {
	int ans;
	c("Enter vehicle ID to delete or -1 to cancel: ");
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	if (ans == -1)
		return;
	bool found = false;
	int index;
	for (int i = 0; i < counter; i++) {
		if (log[i]->getID() == ans) {
			delete log[i];
			index = i;
			i = counter;
			c("The vehicle was found, and deleted.");
			found = true;
		}
	}
	if (found)
	{
		for (int i = index; i < counter - 1; i++) {
			log[i] = log[i + 1];
		}
		--counter;
	}
	else
		c("Vehicle with that ID was not found.");
}

void showLog(Vehicle* log[]) {
	if (counter == 0){
		cout << "Log is empty!" << endl; return;
	}
	c("Now displaying current log for all vehicles.");
	cout << "Type    \t   ID:  \t  Driver \t      Checked-in?" << endl;
	for (int i = 0; i < counter; i++){
		cout << log[i]->getUsageType();
		if (log[i]->getUsageType() == "Passenger" || log[i]->getUsageType() == "Personal")
			cout << " \t ";
		else
			cout << "\t\t ";
		cout << log[i]->getID() << "\t\t " << log[i]->getDrivername() << "\t \t ";
		if (log[i]->getCheckout())
			c("Checked-OUT");
		else
			c("Checked-IN");
	}
	bool loop = true; bool found = false; int g;
	while (loop) {
		c("You may...");
		c("[1] See additional information for a specific car..."); c("[2] Edit a specific car's information");
		c("[3] Sort list by type"); c("[4] Delete vehicle"); c("[5] Exit log");
		while (!(cin >> g)) {
			cin.clear();
			cin.ignore(1000, '\n');//ignores 1000 inputs. 
			cout << "Bad input. Try again: " << endl;
		}
		if (g == 1)
		{
			c("Enter the ID of the car in question.");
			while (!(cin >> g)) {
				cin.clear();
				cin.ignore(1000, '\n');//ignores 1000 inputs. 
				cout << "Bad input. Try again: " << endl;
			}
			for (int i = 0; i < counter; i++)	{
				if (log[i]->getID() == g){
					c("The information for that car:");
					log[i]->print();
					found = true;
					i = counter;
				}
			}
			if (!found)
				c("Error, car with that ID is not within database.");
			found = false;
			cout << endl;
		}
		else if (g == 2) {
			c("Enter the ID of the car in question.");
			while (!(cin >> g)) {
				cin.clear();
				cin.ignore(1000, '\n');//ignores 1000 inputs. 
				cout << "Bad input. Try again: " << endl;
			}
			for (int i = 0; i < counter; i++) {
				if (log[i]->getID() == g) {
					editVehicle(log[i], log);
					c("The new information for that car:");
					log[i]->print();
					found = true;
					i = counter;
				}
			}
			if (!found)
				c("Error, car with that ID is not within database.");
			found = false;
			loop = false;
		}
		else if (g == 3) {
			c("The list will now be sorted by type.");
			cout << "Type    \t   ID:  \t  Driver \t      Checked-in?" << endl;
			for (int i = 0; i < counter; i++)
			{
				if (log[i]->getUsageType() == "Company")
				{
					cout << log[i]->getUsageType();
					cout << "\t\t ";
					cout << log[i]->getID() << "\t\t " << log[i]->getDrivername() << "\t \t ";
					if (log[i]->getCheckout())
						cout << "Checked-OUT" << endl;
					else
						cout << "Checked-IN" << endl;
				}
			}
			for (int i = 0; i < counter; i++)
			{
				if (log[i]->getUsageType() == "Personal")
				{
					cout << log[i]->getUsageType();
					cout << " \t ";
					cout << log[i]->getID() << "\t\t " << log[i]->getDrivername() << "\t \t ";
					if (log[i]->getCheckout())
						cout << "Checked-OUT" << endl;
					else
						cout << "Checked-IN" << endl;
				}
			}
			for (int i = 0; i < counter; i++)
			{
				if (log[i]->getUsageType() == "Passenger")
				{
					cout << log[i]->getUsageType();
					cout << " \t ";
					cout << log[i]->getID() << "\t\t " << log[i]->getDrivername() << "\t \t ";
					if (log[i]->getCheckout())
						cout << "Checked-OUT" << endl;
					else
						cout << "Checked-IN" << endl;
				}
			}
			for (int i = 0; i < counter; i++)
			{
				if (log[i]->getUsageType() == "Cargo")
				{
					cout << log[i]->getUsageType();
					cout << "\t\t ";
					cout << log[i]->getID() << "\t\t " << log[i]->getDrivername() << "\t \t ";
					if (log[i]->getCheckout())
						cout << "Checked-OUT" << endl;
					else
						cout << "Checked-IN" << endl;
				}
			}
		}
		else if (g == 4) {
			//Delete
			deleteV(log);
			//Show log again if not empty
			if (counter != 0) {
				cout << "Type    \t   ID:  \t  Driver \t      Checked-in?" << endl;
				for (int i = 0; i < counter; i++){
					cout << log[i]->getUsageType();
					if (log[i]->getUsageType() == "Passenger" || log[i]->getUsageType() == "Personal")
						cout << " \t ";
					else
						cout << "\t\t ";
					cout << log[i]->getID() << "\t\t " << log[i]->getDrivername() << "\t \t ";
					if (log[i]->getCheckout())
						cout << "Checked-OUT" << endl;
					else
						cout << "Checked-IN" << endl;
				}
			}
			//Return if empty
			else {
				cout << "\nLog is empty!" << endl; return;
			}
		}
		else
			loop = false;
	}
	cls();

}


void companyv(CompanyVehicle &v, Vehicle* log[]) {
	v.setType("Company");
	//t[counter] = Tracker(d[counter], "Company");
	c("Input the miles driven: ");
	double a;
	while (!(cin >> a)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	v.setMilesDriven(a);
	c("Input the total fuel cost: ");
	cout << "$ ";
	while (!(cin >> a)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	v.setFuelCost(a);
	c("Input the purpose of the trip (no spaces): ");
	string purpose;	cin >> purpose;
	v.setPurpose(purpose);
	c("Now moving on to vehicle information.");
	// record ID, date, name, mileage, type usage, content
	c("Enter the driver's name (NO SPACES). I.e. JohnSmith");
	string name; cin >> name;
	v.setDrivername(name);
	c("Enter the ID number");
	int ans;
	bool loop = true;

	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}

	v.setID(ans);
	c("Enter mileage");
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	v.setMileage(ans);
}

void personalv(PersonalVehicle &v, Vehicle* log[]) {
	v.setType("Personal");
	c("Enter the driver's name (NO SPACES). I.e. JohnSmith");
	string name; cin >> name;
	v.setDrivername(name);
	c("Enter the ID number");
	int ans;

	bool loop = true;

	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}

	v.setID(ans);
	c("Enter mileage");
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	v.setMileage(ans);
	c("Now moving on to insurance details...");
	c("Enter the name of the insurance company");
	cin >> name;
	v.setInsurCompName(name);
	c("Enter the policy number");
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	v.setPolicyNumber(ans);
	c("Enter the effective date.");
	c("For example, if it is May 1 2015, an example of correct input : 5 1 2015");
	Date d;
	cin >> d;
	v.setEffective(d);
	c("Enter expiration date");
	cin >> d;
	v.setExpiration(d);
	c("Enter the car make/model");
	cin >> name; 	v.setCarMakeModel(name);

	c("Finally, input the year of the car: ");
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	};
	v.setCarYear(ans);

}

void genv(Vehicle &v, Vehicle* log[]) {
	c("Enter the driver's name (NO SPACES). I.e. JohnSmith");
	string name;
	cin >> name;
	while (cin.get() == ' ')
	{
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	v.setDrivername(name);
	c("Enter the ID number");
	int ans;

	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}

	v.setID(ans);
	c("Enter mileage");
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	v.setMileage(ans);
}

void create(Vehicle* log[]) {
	cls();
	c("We will begin with inputing the type of usage that the car is being used for.");
	c("Input:\n[1] For Company Use"); c("[2] Personal Use");
	c("[3] Carrying passengers"); c("[4] Carrying cargo");
	int ans;
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	c("Now, input the numeric value for the current month, day, and year.");
	c("Example of input: If today is January 1, input would be: '1 1 2016'.");
	Date d; cin >> d;
	if (ans == 1) {
		CompanyVehicle v; v.setDate(d); companyv(v, log);
		log[counter] = new CompanyVehicle(v);
		cout << "The car has been added to the database.\n";
	}
	else if (ans == 2) {
		PersonalVehicle v; v.setDate(d); personalv(v, log);
		log[counter] = new PersonalVehicle(v);
		cout << "The car has been added to the database.\n";
	}
	else if (ans > 2) {
		Vehicle v;
		v.setDate(d);
		if (ans == 3)
			v.setType("Passenger");
		else
			v.setType("Cargo");
		genv(v, log);
		cout << "That is all, for now. The contents of the vehicle will be determined upon checkout." << endl;
		Vehicle* newV = new Vehicle(v);
		log[counter] = newV;
	}
	counter++;
	cout << "\nWould you like to make another vehicle?\n[1]Yes\n[2]Quit\n";
	cin >> ans;
	if (ans == 1)
		create(log);
	cls();
}

void check(Vehicle* log[], int a) {
	int ans;
	if (a == 2) {
		cout << "Please enter the ID" << endl;
		while (!(cin >> ans)) {
			cin.clear();
			cin.ignore(1000, '\n');//ignores 1000 inputs. 
			cout << "Bad input. Try again: " << endl;
		}
		bool done = false;
		for (int i = 0; i < counter; i++){
			if (ans == log[i]->getID() && log[i]->getCheckout()){
				log[i]->setCheckedout(false);
				cout << "Vehicle has been checked in.";
				i = counter; done = true;
			}
			else if (ans == log[i]->getID() && !log[i]->getCheckout()){
				cout << "Vehicle is already checked in."; i = counter; done = true;
			}
		}
		if (!done)
			c("Error. ID did not match any vehicle whatsoever in database.");
	}
	else{
		cout << "Please enter the ID" << endl;
		while (!(cin >> ans)) {
			cin.clear();
			cin.ignore(1000, '\n');//ignores 1000 inputs. 
			cout << "Bad input. Try again: " << endl;
		}
		bool done = false;
		for (int i = 0; i < counter; i++){
			if (ans == log[i]->getID() && !log[i]->getCheckout()){
				log[i]->setCheckedout(true);
				c("The car is available for checkout.");
				c("You must enter what you are carrying before fully checking out.");
				c("How many unique items/persons are going in the car?");
				cin >> ans;
				c("Enter each item. Seperate each unique item with a space. An example of proper input:");
				c("FIRST_ITEM NEXT_ITEM etc");
				string *stuff = new string[ans];
				for (int i = 0; i < ans; i++)
					cin >> stuff[i];
				log[i]->setContents(stuff, ans);
				cout << "Vehicle has been checked out.";
				i = counter; done = true;
			}
			else if (ans == log[i]->getID() && log[i]->getCheckout()){
				cout << "Vehicle is already checked out."; i = counter; done = true;
			}
		}
		if (!done)
			c("Error. ID did not match any vehicle whatsoever in database.");

	}
}

void main() {
	HWND console = GetConsoleWindow();//MAKES WINDOW BIGGER BY DEFAULT. 
	SetWindowPos(console, 0, 200, 30, 200, 300, SWP_NOSIZE | SWP_NOZORDER);
	// position of console:   x   y
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 900, 500, TRUE); // 900 width, 500 height console.
	SetConsoleTitle("Vehicle Checkout Program");//title of console window
	Vehicle* log[99];//vehicle log stores up to 99 vehicle objects
	cout << "Welcome to the Vehicle Checkout Program!\n";
	c("This system is designed to store data for vehicles via .txt files."); p();

	int ans;
	c("Is this your first time using this program?");
	cout << "[1] Yes\n[2] No\n";
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	if (ans == 1)
	{
		c("It's recommended to put this .exe file into its own folder so that the quick-save function works smoothly.");
		c("Otherwise, the saved output file can be buried among other files in the download folder."); p();
	}

	c("Would you like to load a previously made log?");
	cout << "[1] Yes\n[2] No\n";
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	if (ans == 1)
		load(log);
	cout << endl;
	bool loop = true;
	cout << "---------------------------------\n";
	cls();
	while (loop) {
		cout << "You have the option of..." << endl;
		cout << "[1] Add a vehicle to the database\n[2] Check in a vehicle\n";
		cout << "[3] Check out vehicle\n[4] See log\n[5] Output a detailed log to text file.";
		cout << "\n[6] Load a log\n[7] EXIT PROGRAM\n";
		while (!(cin >> ans)) {
			cin.clear();
			cin.ignore(1000, '\n');//ignores 1000 inputs. 
			cout << "Bad input. Try again: " << endl;
		}
		if (ans == 1)
			create(log);
		else if (ans == 2 || ans == 3)
			check(log, ans);
		else if (ans == 4)
			showLog(log);
		else if (ans == 5)
			save(log);
		else if (ans == 6)
			load(log);
		else if (ans == 7)
			loop = false;
		else
			cout << "Not an option. Try again. " << endl;
	}
	cout << "Now exiting program. Before you go: Did you remember to save?\n";
	cout << "[1] Save\n[2] EXIT\n";
	while (!(cin >> ans)) {
		cin.clear();
		cin.ignore(1000, '\n');//ignores 1000 inputs. 
		cout << "Bad input. Try again: " << endl;
	}
	if (ans == 1)
		save(log);
	else
		exit(0);
}