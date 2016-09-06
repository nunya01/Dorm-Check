#include "Room.h"

Room::Room()
{
	roomNum = "NULL";
}

void Room::setRoomNum(string rn)
{
	roomNum = rn;
}

void Room::setJacks(string c1, string s1, string c2, string s2, string c3, string s3, string c4, string s4)
{
	jk1c = c1;
	jk1s = s1;
	jk2c = c2;
	jk2s = s2;
	jk3c = c3;
	jk3s = s3;
	jk4c = c4;
	jk4s = s4;
}

void Room::setLoc(string l12, string l15, string l22, string l25)
{
	loc12 = l12;
	loc15 = l15;
	loc22 = l22;
	loc25 = l25;
}

void Room::setAp(string apCon, string apLi, string com)
{
	apCond = apCon;
	apLink = apLi;
	comment = com;
}

string Room::getRoomNum()
{
	return roomNum;
}

bool Room::operator==(const Room & rt)
{
	return (roomNum == rt.roomNum);
}

void Room::lout(string& fName, string action)
{
	time_t now = time(0);
	char* dt = ctime(&now);

	fstream newFile;
	newFile.open(fName + ".log", std::fstream::app);
	if (newFile.is_open())
	{
		newFile << dt;
		newFile << "<" << action << ">" << ": Room "<< roomNum << ", Jack 1: " << jk1c << jk1s << "Jack 2: " << jk2c << jk2s << "Jack 3: " 
			<< jk3c << jk3s << "Jack 4: " << jk4c << jk4s << "Signal: -" << loc12 << ",-" << loc15 << ",-" << loc22 << ",-" 
			<< loc25 << ", AP Stats: " << apCond << apLink << "\nComment: " << comment << endl;
		newFile.close();
	}
}
ostream& operator<<(ostream& os, Room& rm)
{
	os << rm.roomNum << "," << rm.jk1c << rm.jk1s << rm.jk2c << rm.jk2s << rm.jk3c << rm.jk3s << rm.jk4c << rm.jk4s
		<< "-" << rm.loc12 << ",-" << rm.loc15 << ",-" << rm.loc22 << ",-" << rm.loc25 << "," << rm.apCond << rm.apLink << rm.comment;
	return os;
}

