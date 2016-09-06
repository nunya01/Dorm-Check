#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Room.h"
#include <stdlib.h>

using namespace std;

void fileOpen(bool, string);
void appendFile(vector<Room>, string);
void newRoom(string[], vector<Room>&);
void printRooms(vector<Room>&);
void getInput(string[], vector<Room>&);
void delRoom(vector<Room>&);
bool dupCheck(string, vector<Room>&);
void jackLoop(string[], int&);
void locSig(string[]);
string getDB();
string fName;

int main()
{
	int choice = 1;
	bool isNewFile = true;
	string fType = ".csv", toOpen, comment;
	char userIsNewFile, saveList;
	string status[16];
	vector<Room> roomList;

	cout << "*******************\n";
	cout << "* DormCheck 1.4.5 *\n";
	cout << "*******************\n";

	cout << "\n------------------------------------------------\n";
	cout << "| Dorm Check is a 10-key friendly way to enter |\n";
	cout << "| the status of dorm rooms without having to   |\n";
	cout << "| deal with entering data in excel blocks. The |\n"; 
	cout << "| output is a .csv file that can be pasted into|\n";
	cout << "| an excel worksheet.                          |\n";
	cout << "------------------------------------------------\n";

	//new file?
	cout << "\nCreate a new file: Y/N ? [default Y] ";
	cin >> userIsNewFile;

	if (toupper(userIsNewFile) == 'Y')
		isNewFile = true;
	else
		isNewFile = false;

	//get file name
	cout << "\nEnter the file name, no spaces.\n-> ";
	cin >> fName;
	toOpen.append(fName + fType);
	fileOpen(isNewFile, toOpen);

	//getting input
	while (choice != 6)
	{
		cout << "\n(1) add a room\n(2) display list of rooms done\n(4) delete a room\n(5) write (save) and start new list\n(6) quit\n-> ";
		cin >> choice;
		switch (choice)

		{
			case 1: getInput(status, roomList);
				break;
			case 2:	
			{
				printRooms(roomList);
				cout << "\nPress Enter to continue...\n";
				cin.ignore();
				cin.ignore();
			}
				break;
			case 3:
			case 4: 
			{
				printRooms(roomList);
				delRoom(roomList);  
			}
				break;
			case 5:
			{
				cout << "\nOnce you save a list of rooms, it cannot be edited.\n";
				cout << "Continue? Y/N or 1/0 ";
				cin >> saveList;

				if (toupper(saveList) == 'Y' || saveList == '1')
				{
					cout << "\nSaving...\n";
					appendFile(roomList, toOpen);
					cout << "\nPreparing for next list\n";
					roomList.clear();
				}
				else
					cout << "\nAborting save...\n";
			}
			break;
			default: 
			{
				cout << "\nSaving...\n";
				appendFile(roomList, toOpen);
				cout << "\nQuitting...\n";
			}
		}
	}
	return 0;
}

//open new file, write columns headings
void fileOpen(bool isnew, string toOpen)
{
	fstream newFile;
	newFile.open(toOpen, std::fstream::app);
	if (newFile.is_open())
	{
		if (isnew)
		{
			newFile << "Room," << "Jack 1," << "Jack 1 Speed," << "Jack 2," << "Jack 2 Speed,"
				<< "Jack 3," << "Jack 3 Speed," << "Jack 4," << "Jack 4 Speed," << "Location 1 2.4Ghz,"
				<< "Location 1 5Ghz," << "Location 2 2.4Ghz," << "Location 2 5Ghz," << "AP Condition,"
				<< "AP Link Light," << "Comment\n";
			cout << "\nFile has been created...\n";
		}
		else
			cout << "\nVerified existing file...\n";

		newFile.close();
	}
}

//append existing file
void appendFile(vector<Room> roomList, string toAppend)
{
	fstream newFile;
	newFile.open(toAppend, std::fstream::app);
	for (int x = 0; x < (int)roomList.size(); x++)
		newFile << roomList[x] << endl;
	newFile.close();
	cout << "\n**Room data written to file**\n";
}

// adds new room to roomList
void newRoom(string myarray[16], vector<Room>& roomList)
{
	Room temp;
	temp.setRoomNum(myarray[0]);
	temp.setJacks(myarray[1], myarray[2], myarray[3], myarray[4], myarray[5], myarray[6], myarray[7], myarray[8]);
	temp.setLoc(myarray[9], myarray[10], myarray[11], myarray[12]);
	temp.setAp(myarray[13], myarray[14], myarray[15]);
	roomList.push_back(temp);
	temp.lout(fName, "Added");
}

//print list of rooms entered
void printRooms(vector<Room> &roomList)
{
	cout << endl;
	for (int x = 0; x < (int)roomList.size(); x++)
		cout << roomList[x].getRoomNum() << endl;
}

//get input from the user.
void getInput(string status[16], vector<Room> &roomList)
{
	int numJacks;
	bool runAgain = true, firstRun = true;
	char addRoom, /*jackCond, jackSpeed,*/ apCond, linkLi;
	string userIn;

	status[0] = "Null";
	while (runAgain)
	{
		system("CLS");
		if (!firstRun)
			cout << "The last room was: " << status[0] << endl;
		cout << "\nRoom number: ";
		cin >> status[0];
		if (dupCheck(status[0], roomList))
		{
			char reptCheck;
			cout << "\nYou have already entered room " << status[0] << " once.\n";
			cout << "Do you really want to enter it again? Y/N ";
			cin >> reptCheck;
			if (toupper(reptCheck) != 'Y')
			{
				cout << "\nRoom number\n-> ";
				cin >> status[0];
			}
		}

		cout << "\nEnter number of jacks in the room (1-4): ";
		cin >> numJacks;
		while (numJacks < 1 || numJacks > 4)
		{
			cout << "***OUT OF RANGE***\n";
			cout << "Enter number of jacks in the room (1-4): ";
			cin >> numJacks;
		}

		jackLoop(status, numJacks); //gets jack count and status via jackLoop function

		locSig(status); //gets the wireless signal for each location via locSig function

		//AP condition
		system("CLS");
		cout << "----------------\n";
		cout << "| Access Point |\n";
		cout << "----------------\n";
		cout << "\nAP Condition:\n(1) Good\n(2) Damaged\n(3) No Signal\n(4) N/A\n-> ";
		cin >> userIn;

		while (userIn.length() != 1)
		{
			cout << "\n--------------------------------\n";
			cout << "|Input ERROR. Please try again.|\n";
			cout << "--------------------------------\n-> ";
			cin >> userIn;
		}

		apCond = userIn[0];

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
		default: {
				cout << "\n***INVALID INPUT***\n";
				cout << "Manually input your choice: ";
				cin >> status[13]; 
			}
		}

		//AP status (only if AP cond is not N/A)
		if (apCond != '4')
		{
			cout << "\nAP Link:\n(1) Green\n(2) Amber\n(3) No Signal\n(4) N/A\n";
			cin >> userIn;

			while (userIn.length() != 1)
			{
				cout << "\n--------------------------------\n";
				cout << "|Input ERROR. Please try again.|\n";
				cout << "--------------------------------\n-> ";
				cin >> userIn;
			}

			linkLi = userIn[0];

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
			default: cout << "\n--------------------------------\n";
				cout << "|Input ERROR. Please try again.|\n";
				cout << "--------------------------------\n-> ";
				cout << "Manually input your choice: ";
				cin >> status[14];
			}
		}

		else
			status[14] = "N/A,";

		cin.ignore();
		system("CLS");
		cout << "\nOptional Comment (ENTER to skip): ";
		getline(cin, status[15]); // gets comment, optional

		cout << "\n------------------------------------\n";
		cout << "|To Edit this room, enter 'E' below|\n";
		cout << "------------------------------------\n";
		cout << "\nAnother room? [Y/N] or [1/0] ";
		cin >> addRoom;

		if (toupper(addRoom) != 'E')
		{	
			newRoom(status, roomList);
			cout << "\nAdded to list...\n";
		}
		
		if (toupper(addRoom) != 'Y' && addRoom != '1' && toupper(addRoom) != 'E')
		{
			runAgain = false;
			system("CLS");
		}

		if (toupper(addRoom) == 'E')
			status[0] = ("Editing " + status[0]);
	
		firstRun = false;
	}
}

//jack loop
void jackLoop(string status[], int& numJacks)
{
	int y = 1;
	char jackCond, jackSpeed;
	string userIn;

	for (int x = 0; x < numJacks; x++)
	{
		system("CLS");
		cout << "-----------------\n";
		cout << "| Jack number " << x + 1 << " |\n";
		cout << "-----------------\n";
		cout << "\nCondition of jack:\n";
		cout << "(1) Good\n(2) Damaged\n(3) No Signal\n(4) N/A\n-> ";
		cin >> userIn;

		while (userIn.length() != 1)
		{
			cout << "\n--------------------------------\n";
			cout << "|Input ERROR. Please try again.|\n";
			cout << "--------------------------------\n-> ";
			cin >> userIn;
		}

		jackCond = userIn[0];
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
		default:
		{
			cout << "\n--------------------------------\n";
			cout << "|Input ERROR. Please try again.|\n";
			cout << "--------------------------------\n-> ";
			cout << "Manually enter the condition: ";
			cin >> status[y];
		}
		}

		cout << "\nSpeed:\n(1) 1000\n(2) 100\n(3) 10\n(4) N/A\n -> ";
		cin >> userIn;

		while (userIn.length() != 1)
		{
			cout << "\n--------------------------------\n";
			cout << "|Input ERROR. Please try again.|\n";
			cout << "--------------------------------\n-> ";
			cin >> userIn;
		}

		jackSpeed = userIn[0];
		switch (jackSpeed)
		{
		case '1': status[y + 1] = "1000 mbps,";
			break;
		case '2': status[y + 1] = "100 mbps,";
			break;
		case '3': status[y + 1] = "10 mbps,";
			break;
		case '4': status[y + 1] = "N/A,";
			break;
		default: {
			cout << "\n--------------------------------\n";
			cout << "|Input ERROR. Please try again.|\n";
			cout << "--------------------------------\n-> ";
			cout << "Manually enter the jack speed: ";
			cin >> status[y + 1];
		}
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
}

//deletes a room from the list by room number
void delRoom(vector<Room>& roomList)
{
	string roomToDel;
	bool flag = false;
	cout << "\nEnter the room # to delete: ";
	cin >> roomToDel;
	for (int x = 0; x < (int)roomList.size(); x++)
	{
		if (roomToDel == roomList[x].getRoomNum())
		{			
			roomList[x].lout(fName, "Deleted");
			roomList.erase(roomList.begin() + x);
			cout << "\nDeleted " << roomToDel << endl;
			flag = true;
		}
	}
	if (!flag)
		cout << "\nThe record was not found.\n";
}

//location signal wireless input
void locSig(string status[])
{
	system("CLS");
	cout << "\n--------------------------------\n";
	cout << "| Wireless Signal levels (-dB) |\n";
	cout << "--------------------------------\n\n";
	cout << "Loc 1 2.4 Ghtz -db (no minus): ";
	status[9] = getDB();
	cout << "Loc 1 5 Ghtz -db (no minus): ";
	status[10] = getDB();
	cout << "\n**********************\n";
	cout << "*  Change Locations  *\n";
	cout << "**********************\n\n";
	cout << "Loc 2 2.4 Ghtz -db (no minus): ";
	status[11] = getDB();
	cout << "Loc 2 5 Ghtz -db (no minus): ";
	status[12] = getDB(); 
}

//gets the neg DB string and validates the length at 2.
string getDB() 
{
	string negDB = "99";
	cin >> negDB;
	while (negDB.length() != 2)
	{
		cout << "\n**Out of bounds. Try again**\n";
		cout << "\nEnter the value of -dB WITHOUT minus sign.\n-> ";
		cin >> negDB;
	}
	return negDB;
}

//checks for duplicate room and returns t/f
bool dupCheck(string rm, vector<Room>& roomList)
{
	for (int x = 0; x < (int)roomList.size(); x++)
	{
		if (roomList[x].getRoomNum() == rm)
			return true;
	}
	return false;
}

