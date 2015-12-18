#ifndef EACHAIRPLANE_H
#define EACHAIRPLANE_H
#pragma once

#include<vector>

using namespace std;

class eachAirplane
{
public:
	eachAirplane(void);
	~eachAirplane(void);
	int isArranged;
	void setFlightname(string flightname);
	void setEntrancetime(double entrancetime);
	void setEntrancenode(int entrancenode);
	void setEntrancetimeslice(int entrancetimeslice);
	void setSortedentrancetime(double sortedentrancetime);
	string getFlightname();
	double getEntrancetime();
	int getEntrancenode();
	int getEntrancetimeslice();
	double getSortedentrancetime();
	void setMap(int n);
	int getMap();
	
private:
	int entrance_node;
	int entrance_time_slice;
	string flightName;
	double entrance_time;
	double sortedEntrance_time;
	int map;//This is a map to sortedconf
};
#endif

