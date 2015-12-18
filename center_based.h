#ifndef CENTER_BASED_H
#define CENTER_BASED_H
#pragma once
#include<iostream>

#include"airplane.h"
#include"EA.h"
#include"eachAirplane.h"

using namespace std;
class center_based: public airplane, public EA
{
public:
	center_based(void);
	~center_based(void);
	void get_node_estimated_flight();
	void greedy_schedule(int i);
	double calculate_time_difference(eachAirplane A, eachAirplane B,double safe_time);
	void setSortedconf(int n,double time);
	bool kickOverflow();
	bool kickUnsafe(int i);
	double fitness_calculation();
	void displaySortednumber();
	vector<double> occupation_ratio();
private:
	int maximum_capacity;
	int sector_acceptance_capacity;
	double average_cost_time;
	double timeslicesize;
	double safetime;
	vector<int>node_count;
	vector<int>sortedNumber;
	int node_flight_number[6];
	vector<double>ratio;
};

#endif