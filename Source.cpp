#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void fileOpen(bool, string);
void appendFile(string[], string);

int main()
{
	int numJacks;
	bool isNewFile = true, runAgain = true, firstRun = true;
	string fName, fType = ".csv", toOpen, comment;
	char userIsNewFile, addRoom, jackCond, jackSpeed, apCond, linkLi;
	string status[16];

	cout << "*****************\n";
	cout << "* DormCheck 1.1 *\n";
	cout << "*****************\n";

	//new file?
	cout << "\nShould I create a new file: Y/N ? [default Y] ";
	cin >> userIsNewFile;

	if (toupper(userIsNewFile) == 'Y')
		isNewFile = true;
	else
		isNewFile = false;

	//get file name
	cout << "\nEnter the file name, no spaces: \n";
	cin >> fName;
	toOpen.append(fName + fType);
	fileOpen(isNewFile, toOpen);

	//getting input
	status[0] = "Null";
	while (runAgain)
	{
		if (!firstRun)
			cout << "The last room was: " << status[0] << endl;
		cout << "\nRoom number: ";
		cin >> status[0];

		cout << "\nEnter number of jacks in the room (1-4): ";
		cin >> numJacks;
		while (numJacks < 1 || numJacks > 4)
		{
			cout << "***OUT OF RANGE***\n";
			cout << "Enter number of jacks in the room (1-4): ";
			cin >> numJacks;
		}

		//jack loop
		int y = 1;
		for (int x = 0; x < numJacks; x++)
		{
			cout << "\nCondition of jack number " << x + 1 << ":\n";
			cout << "(1) Good\n(2) Damaged\n(3) No Signal\n(4) N/A\n";
			cin >> jackCond;

			switch (jackCond)
			{
			case '1': 
			case 'g':
				status[y] = "Good,";
				break;
			case '2': 
			case 'd':
				status[y] = "Damaged,";
				break;
			case '3': status[y] = "No Signal,";
				break;
			case '4': status[y] = "N/A,";
				break;
			default: cout << "\n***INVALID INPUT***\n";
				cout <<"Manually input your choice: ";
				cin >> status[y];
			}

			cout << "\nSpeed:\n(1) 1000\n(2) 100\n(3) 10\n(4) N/A\n";
			cin >> jackSpeed;

			switch (jackSpeed)
			{
			case '1': status[y + 1] = "1000 mbps,";
				break;
			case '2': status[y + 1] = "100 mbps,";
				break;
			case '3': status[y + 1] = "10 mbps,";
				break;
			case '4': status[y+1] = "N/A,";
				break;
			default: cout << "\n***INVALID INPUT***\n";
				cout << "Manually input your choice: ";
				cin >> status[y+1];
			}
			y += 2;
		}

		//unpopulated jacks
		if (numJacks < 4)
		{
			status[8] = "N/A,";
			status[7] = "N/A,";
		}
		if (numJacks < 3)
		{
			status[6] = "N/A,";
			status[5] = "N/A,";
		}
		if (numJacks < 2)
		{
			status[4] = "N/A,";
			status[3] = "N/A,";
		}

		//location signal
		bool outBounds = false;
		while (!outBounds)
		{
			cout << "Loc 1 2.4 Ghtz -db (no minus): ";
			cin >> status[9];
			cout << "Loc 1 5 Ghtz -db (no minus): ";
			cin >> status[10];
			cout << "Loc 2 2.4 Ghtz -db (no minus): ";
			cin >> status[11];
			cout << "Loc 2 5 Ghtz -db (no minus): ";
			cin >> status[12];

			bool flag = true;
			for (int x = 9; x <= 12; x++)
			{
				if (status[x].length() != 2)
				{
					flag = false;
					cout << "**\nAt least one of your inputs is out of bounds. Try again**\n";
				}
			}
			outBounds = flag;
		}

		//AP condition
		cout << "\nAP Condition:\n(1) Good\n(2) Damaged\n(3) No Signal\n(4) N/A\n";
		cin >> apCond;
		
		switch (apCond)
		{
		case '1': 
		case 'g':
			status[13] = "Good,";
			break;
		case '2': 
		case 'd':
			status[13] = "Damaged,";
			break;
		case '3': status[13] = "No Signal,";
			break;
		case '4': status[13] = "N/A,";
			break;
		default: cout << "\n***INVALID INPUT***\n";
			cout << "Manually input your choice: ";
			cin >> status[13];
		}

		//AP status (only if AP cond is not N/A)
		if (apCond != '4')
		{
			cout << "\nAP Link:\n(1) Green\n(2) Amber\n(3) No Signal\n(4) N/A\n";
			cin >> linkLi;
			
			switch (linkLi)
			{
			case '1':
			case 'g':
				status[14] = "Green,";
				break;
			case '2': 
			case 'a':
				status[14] = "Amber,";
				break;
			case '3': status[14] = "No Signal,";
				break;
			case '4': status[14] = "N/A,";
				break;
			default: cout << "\n***INVALID INPUT***\n";
				cout << "Manually input your choice: ";
				cin >> status[14];
			}
		}
		else
		{
			status[14] = "N/A,";
		}

		cin.ignore();
		cout << "Comment (ENTER to skip): ";
		getline(cin, status[15]);
		appendFile(status, toOpen);

		cout << "Another room? Y/N ";
		cin >> addRoom;
		if (toupper(addRoom) != 'Y')
			runAgain = false;
		system("CLS");
		firstRun = false;
	}

	cout << "\nQuitting...\n";
	return 0;
}

//open new file, write columns headings
void fileOpen(bool isnew, string toOpen)
{
	fstream newFile;
	newFile.open(toOpen, std::fstream::app);
	if (isnew)
	{
		newFile << "Room," << "Jack 1," << "Jack 1 Speed," << "Jack 2," << "Jack 2 Speed,"
			<< "Jack 3," << "Jack 3 Speed," << "Jack 4," << "Jack 4 Speed," << "Location 1 2.4Ghz,"
			<< "Location 1 5Ghz," << "Location 2 2.4Ghz," << "Location 2 5Ghz," << "AP Condition,"
			<< "AP Link Light," << "Comment\n";
	}
	newFile.close();
	cout << "\nFile has been created...\n";
}

//append existing file
void appendFile(string myarray[16], string toAppend)
{
	fstream newFile;
	newFile.open(toAppend, std::fstream::app);

	newFile << myarray[0] << "," << myarray[1] << myarray[2] << myarray[3] << myarray[4] << myarray[5] << myarray[6] << myarray[7]
		<< myarray[8] << "-" << myarray[9] << "," << "-" << myarray[10] << "," << "-" << myarray[11] << "," << "-" << myarray[12] << "," << myarray[13]
		<< myarray[14] << myarray[15] << "\n";
	newFile.close();
	cout << "\n**Room data written to file**\n";
}