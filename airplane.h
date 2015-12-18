#ifndef AIRPANE_H
#define AIRPLANE_H
#pragma once

#include<vector>

#include"eachAirplane.h"

using namespace std;
class airplane
{
public:
	airplane(void);
	~airplane(void);
	void read_conf();
	void displayconf();
	int Getflight_number();
	vector<eachAirplane>sortedConf;
private:
	int flight_number;
	vector<string>raw_data;
};
#endif
