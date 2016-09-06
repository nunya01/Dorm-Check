#pragma once
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class Room
{
private:
	string roomNum;
	string jk1c, jk1s, jk2c, jk2s, jk3c, jk3s, jk4s, jk4c;
	string loc12, loc15, loc22, loc25;
	string apCond, apLink, comment;

public:
	Room();
	void setRoomNum(string);
	void setJacks(string, string, string, string, string, string, string, string);
	void setLoc(string, string, string, string);
	void setAp(string, string, string);
	void lout(string&, string); // fName + action

	string getRoomNum();

	bool operator==(const Room&);

	friend ostream& operator<<(ostream&, Room&);
};