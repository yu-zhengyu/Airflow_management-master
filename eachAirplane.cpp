#include "eachAirplane.h"


eachAirplane::eachAirplane(void)
{
	entrance_node = -1;
	entrance_time_slice = -1;
	entrance_time = 0.0;
	sortedEntrance_time = 0.0;
	isArranged = 0;
	flightName = "0";
}


eachAirplane::~eachAirplane(void)
{
}

void eachAirplane::setEntrancenode(int n){
	entrance_node = n;
}
int eachAirplane::getEntrancenode(){
	return entrance_node;
}
void eachAirplane::setEntrancetime(double n){
	entrance_time = n;
}
double eachAirplane::getEntrancetime(){
	return entrance_time;
}
void eachAirplane::setEntrancetimeslice(int n){
	entrance_time_slice = n;
}
int eachAirplane::getEntrancetimeslice(){
	return entrance_time_slice;
}
void eachAirplane::setFlightname(string n){
	flightName = n;
}
string eachAirplane::getFlightname(){
	return flightName;
}
void eachAirplane::setSortedentrancetime(double n){
	sortedEntrance_time = n;
}
double eachAirplane::getSortedentrancetime(){
	return sortedEntrance_time;
}
void eachAirplane::setMap(int n){
	map = n;
}
int eachAirplane::getMap(){
	return map;
}
