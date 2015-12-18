#include "center_based_ES.h"

center_based_ES::center_based_ES(void)
{
	maximum_capacity = 20;
	average_cost_time = 7.25;
	timeslicesize = 15.0;
	safetime = 120.0;
	for(int i=0;i<10;i++)
		sortedNumber.push_back(0);

	node_flight_number[0] = 3;
	node_flight_number[1] = 30;
	node_flight_number[2] = 5;
	node_flight_number[3] = 12;
	node_flight_number[4] = 9;
	node_flight_number[5] = 29;
	for(int i=0;i< 140;i++)
		ratio.push_back(0.0);

}


center_based_ES::~center_based_ES(void)
{
}

void center_based_ES::greedy_schedule(int i){
	vector<int>temp;
	vector<vector<int>>temp_generation = getGeneration_pool();
	temp = temp_generation[i];
	for(int i=0;i<temp.size();i++){
		vector<eachAirplane>temp_eachairplane;//Store each node's flight
		for(int j=0;j<sortedConf.size();j++){
			if(sortedConf.at(j).getEntrancenode()==(i+1)){//Node start from 1
				sortedConf.at(j).setMap(j);
				temp_eachairplane.push_back(sortedConf.at(j));
		}
		}
		double safe_time = 60*15.0/temp[i];
		//cout<<safe_time<<endl;
		int index = 0;//This index is to tag those already arranged flight
		for(int i=0;i<temp_eachairplane.size();i++){
			if(temp_eachairplane.at(i).getEntrancetimeslice()==0){
				double temp_time = temp_eachairplane.at(index).getEntrancetime();
				int temp_map = temp_eachairplane.at(index).getMap();
				setSortedconf(temp_map,temp_time);
				temp_eachairplane.at(index).setSortedentrancetime(temp_time);
				index++;
		}
		}
		for(;index<temp_eachairplane.size();index++){
			double time_difference = calculate_time_difference(temp_eachairplane.at(index-1),temp_eachairplane.at(index),safe_time);
			if (temp_eachairplane.at(index).getEntrancetime()<temp_eachairplane.at(index-1).getSortedentrancetime()){
				double temp_time = temp_eachairplane.at(index-1).getSortedentrancetime()+safe_time/(60.0*100);
				temp_time = ((int)(temp_time*100)+1)/100.0;
				if(temp_time-(int)temp_time>=0.6){
					temp_eachairplane.at(index).setSortedentrancetime(temp_time+0.4);
					int temp_map = temp_eachairplane.at(index).getMap();
				    setSortedconf(temp_map,temp_time+0.4);
				}
				else{
					temp_eachairplane.at(index).setSortedentrancetime(temp_time);
					int temp_map = temp_eachairplane.at(index).getMap();
				    setSortedconf(temp_map,temp_time);
				}
			}
			else{
			if(time_difference>=safe_time){
				double temp_time = temp_eachairplane.at(index).getEntrancetime();
				int temp_map = temp_eachairplane.at(index).getMap();
				setSortedconf(temp_map,temp_time);
				temp_eachairplane.at(index).setSortedentrancetime(temp_time);
			}
			else{
				double temp_time = temp_eachairplane.at(index).getEntrancetime()+(safe_time-time_difference)/(60.0*100);
				temp_time = ((int)(temp_time*100)+1)/100.0;
				if(temp_time-(int)temp_time>=0.6){
					temp_eachairplane.at(index).setSortedentrancetime(temp_time+0.4);
					int temp_map = temp_eachairplane.at(index).getMap();
				    setSortedconf(temp_map,temp_time+0.4);
				}
				else{
					temp_eachairplane.at(index).setSortedentrancetime(temp_time);
					int temp_map = temp_eachairplane.at(index).getMap();
				   setSortedconf(temp_map,temp_time);
				}
			}
		}
		}
		/*for(int i=0;i<temp_eachairplane.size();i++){
			cout<<temp_eachairplane.at(i).getFlightname()<<" "<<temp_eachairplane.at(i).getEntrancetime()<<" "<<temp_eachairplane.at(i).getSortedentrancetime()<<endl;
		}
		system("pause");*/
	}
}

double center_based_ES::calculate_time_difference(eachAirplane prior, eachAirplane next,double safe_time){
	double time_difference;
	if(next.getEntrancetime()>=prior.getSortedentrancetime()){
		if((int)prior.getSortedentrancetime()==(int)next.getEntrancetime())
			return 60*100*(next.getEntrancetime()-prior.getSortedentrancetime());
	else
		return 60*100*(next.getEntrancetime()-0.4-prior.getSortedentrancetime());
	}
	else
		return safe_time;
}


void center_based_ES::setSortedconf(int n,double time){
	sortedConf.at(n).setSortedentrancetime(time);
}


bool center_based_ES::kickOverflow(){
	for(int i=0;i<sortedNumber.size();i++)
		sortedNumber[i] = 0;
	for(int i=0;i<sortedConf.size();i++){
		if(sortedConf.at(i).getSortedentrancetime()>=8.45&&sortedConf.at(i).getSortedentrancetime()<=9.00)
			sortedNumber[0]+=1;
		else if(sortedConf.at(i).getSortedentrancetime()>9.00&&sortedConf.at(i).getSortedentrancetime()<=9.15)
			sortedNumber[1]+=1;
		else if(sortedConf.at(i).getSortedentrancetime()>9.15&&sortedConf.at(i).getSortedentrancetime()<=9.30)
			sortedNumber[2]+=1;
		else if(sortedConf.at(i).getSortedentrancetime()>9.30&&sortedConf.at(i).getSortedentrancetime()<=9.45)
			sortedNumber[3]+=1;
		else if(sortedConf.at(i).getSortedentrancetime()>9.45&&sortedConf.at(i).getSortedentrancetime()<=10.00)
			sortedNumber[4]+=1;
		else if(sortedConf.at(i).getSortedentrancetime()>10.00&&sortedConf.at(i).getSortedentrancetime()<=10.15)
			sortedNumber[5]+=1;
		else if(sortedConf.at(i).getSortedentrancetime()>10.15&&sortedConf.at(i).getSortedentrancetime()<=10.30)
			sortedNumber[6]+=1;
		else
			sortedNumber[7]+=1;
	}
	for(int i=1;i<sortedNumber.size()-1;i++){
		int number = sortedNumber[i]+ (int)(sortedNumber[i-1]*average_cost_time/timeslicesize+0.5);
		if(number>maximum_capacity){
			return true; 
			break;
		}
	}
	return false;
}


bool center_based_ES::kickUnsafe(int i){
	vector<int>temp;
	vector<vector<int>>temp_generation = getGeneration_pool();
	temp = temp_generation[i];
	for(int i=0;i<temp.size();i++){
		if(60*timeslicesize/temp.at(i)<safetime){
			return true;
			break;
		}
		else 
			continue;
	}
	return false;
}
double center_based_ES::fitness_calculation(){
	double delay = 0.0;
	for(int i=0;i<sortedConf.size();i++){
		double delay_of_eachairplane = 0.0;
		if((int)sortedConf.at(i).getEntrancetime() == (int)sortedConf.at(i).getSortedentrancetime())
			delay_of_eachairplane = 100*(sortedConf.at(i).getSortedentrancetime()-sortedConf.at(i).getEntrancetime());
		else
			delay_of_eachairplane = 100*(sortedConf.at(i).getSortedentrancetime()-0.4-sortedConf.at(i).getEntrancetime());
		delay+=delay_of_eachairplane;
	}
	return delay;
}

void center_based_ES::displaySortednumber(){
	for(int i=0;i<sortedNumber.size();i++)
		cout<<sortedNumber[i]<<" ";
}

vector<double> center_based_ES::occupation_ratio(){
	vector<vector<int>>temp_generation = getGeneration_pool();
	for(int i=0;i<temp_generation.size();i++){
		vector<int>temp = temp_generation[i];
		double single_ratio = 0.0;
		for(int j=0;j<temp.size();j++){
			single_ratio += (1.0*node_flight_number[j])/(7*temp[j]);
		}
		ratio[i] = single_ratio;
	}
	return ratio;
}