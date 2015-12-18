#pragma once

#include<iostream>

#include"airplane.h"
#include"EP.h"
#include"eachAirplane.h"
using namespace std;

class center_based_EP:public airplane, public EP
{
public:
	center_based_EP(void);
	~center_based_EP(void);
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
	vector<double> ratio;
	int node_flight_number[6];
};

