#ifndef EA_H
#define EA_H
#pragma once
#include<iostream>
#include<vector>
#include<string>

using namespace std;
class EA
{
public:
	EA(void);
	~EA(void);
	void initial();
	void crossover();
	void swap_parents(int row,int n);
	void mutation();
	void selection_probability(vector<double>fitness);
	void cumulative_probability();
	void highroulette_wheel();//High selection pressure
	void lowroulette_wheel();//Low selection pressure
	void displayair();//This function is for testing and print out individual pool
	vector<int> GetIndividual(vector<vector<int>>a,int number);
	int getEntrance_number();
	int getTimeslice();
	vector<vector<int>> getGeneration_pool();
	int getIndividualnumber();
	void mating_to_generation();
private:
	int entrance_number;
	int time_slice;
	int individual_number;
	double prob_crossover;
	double prob_mutation;
	vector<int>individual_chromo;
	vector<vector<int>>generation_pool;
	vector<vector<int>>mating_pool;
	vector<double>probability;
	vector<double>cumulative_prob;
};
#endif
