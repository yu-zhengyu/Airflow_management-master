#include<iostream>
#include<fstream>
#include<ostream>
#include<string>

#include "airplane.h"
#include"eachAirplane.h"

airplane::airplane(void)
{
	flight_number = 88;
}


airplane::~airplane(void)
{
}

void airplane::read_conf(){
	//Read airplane configuration//
ifstream read_raw_data("data.txt");
string temp;
while(read_raw_data>>temp)
	raw_data.push_back(temp);

////////////////////////////////////////////
for(int i=0,j=0;i<raw_data.size();){
	eachAirplane temp;
	temp.setFlightname(raw_data[i]);
	if(raw_data[i+1] == "AKUBA")
		temp.setEntrancenode(1);
	else if(raw_data[i+1] == "BUBDA")
		temp.setEntrancenode(2);
	else if(raw_data[i+1] == "DAPRO")
		temp.setEntrancenode(3);
	else if(raw_data[i+1] == "GOSMA")
		temp.setEntrancenode(4);
	else if(raw_data[i+1] == "LLC")
		temp.setEntrancenode(5);
	else if(raw_data[i+1] == "OVTAN")
		temp.setEntrancenode(6);
	double temptime = atof(raw_data[i+2].c_str());	//Turn string into double
	if(temptime>=8.45&&temptime<=9.00){
		temp.setEntrancetimeslice(0);
		temp.setEntrancetime(temptime);
	}
	else if(temptime>9.00&&temptime<=9.15){
		temp.setEntrancetimeslice(1);
		temp.setEntrancetime(temptime);
	}
	else if(temptime>9.15&&temptime<=9.30){
		temp.setEntrancetimeslice(2);
		temp.setEntrancetime(temptime);
	}
	else if(temptime>9.30&&temptime<=9.45){
		temp.setEntrancetimeslice(3);
		temp.setEntrancetime(temptime);
	}
	else if(temptime>9.45&&temptime<=10.00){
		temp.setEntrancetimeslice(4);
		temp.setEntrancetime(temptime);
	}
	else if(temptime>10.00&&temptime<=10.15){
		temp.setEntrancetimeslice(5);
		temp.setEntrancetime(temptime);
	}
	else if(temptime>10.15&&temptime<=10.30){
	    temp.setEntrancetimeslice(6);
		temp.setEntrancetime(temptime);
	}
	sortedConf.push_back(temp);
	i+=3;
}
}

void airplane::displayconf(){
	for(int i=0;i<flight_number;i++){
		cout<<sortedConf.at(i).getFlightname()<<" "<<sortedConf.at(i).getEntrancenode()<<" "<<sortedConf.at(i).getEntrancetime()<<" "<<sortedConf.at(i).getSortedentrancetime();
		cout<<endl;
	}
}

int airplane::Getflight_number(){
	return flight_number;
}

