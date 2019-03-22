# VehicleDatabaseCppProject
This is a CPP project I did before I learned SQL. 
In other words, its got quite a bit more code than most of my other projects (and definitely was my biggest code project at the time). 
But it works! There's a few "bugs" here and there, e.g. if you enter a date that hasn't happened yet, it won't stop you. 
I am however proud to have a "quick save" system and a handy reminder to save before you manually exit the program.

The file loading system is a bit confusing; Here is my explanation of how the file reading system works.
Essentially the task was to make a vehicle based database, either in C++ or utilizing an SQL database.
I hadn't taken a databases class yet, so my fate was sealed.
I helped develop the program that would have a user input some data, and be able to output the resuls to a .txt file.
My main concern was getting the .txt file to look nice. This meant extra formatting.

An example .txt output is as follows:

This is the log for the Vehicle Checkout Program.
Total vehicles: 1
-------------------------------------

ID: 1
Purpose: Company
Driver: JamesSmith
Date added: 10 / 1 / 2001
Mileage: 800
Checkout status: Checked in
Contents:
Unset!
Miles driven: 75008
Fuel cost: $ 100
Purpose of trip: BusinessMeeting
-------------------------------------

Outputting the data was simple. Reading it in from this format was challenging but I ultimately figured out a solution.
Essentially, all of the "fluff" text was read into the program as dummy text and only the essential information was saved to variables.

Here is the first section of the loading function code:
---

	int int_1, int_2, int_3; //these will load important data variables
	string strings, data1;//strings from the log stored here 
	counter = 0;
	inputfile.open(path);
	if (!inputfile){
		cout << "ERROR! FILE NOT FOUND!\n"; return;
	}
	for (int k = 0; k < 11; k++)//11 dummy strings
		inputfile >> strings;//all are shoved in this variable, never to be accessed 
	inputfile >> int_1;//after the "vehicles:" string, this number is stored and used for a loop below.
	int vehicle_count = int_1;
	inputfile >> strings;//stores the "--------" line
	int num_loaded = 1;
	cout << "Number of vehicles loaded: ";
	for (int l = 0; l<vehicle_count; l++){
  
  ---
 If you count the amount of strings before we actually get to a meaningful piece of data in the log,
 we get 11 strings before hitting the count of how many vehicles are in the database.
 
 The next bit of code is dependant on the type of vehicle, as each vehicle type has different data stored.
 For a company vehicle, it is as follows:
 ---
 
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
    
    ---
    This part of the code actually helps detail what is going on since I myself had to keep track of this craziness.
    
    The rest of the loading functions all function essentially the same. 
    
    I apologise of reading this is still confusing but for what it's worth I am still happy I got this thing running as well
    as it did for the time. I plan on remaking this as a website using PHP and MySQL. Being much less confusing.
