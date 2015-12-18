#ifndef EP_H
#define EP_H
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;
class EP
{
public:
	EP(void);
	~EP(void);
	void initial();
	void mutation();
	int getEntrance_number();
	vector<int> GetIndividual(vector<vector<int>>a,int number);
	int getTimeslice();
	vector<vector<int>> getGeneration_pool();
	int getIndividualnumber();
	int getTotalnumber();
	void seletion(vector<double> fitness);
	void display();//This function is for testing and print out individual pool
	void BooSort();
	void debugdisplay();
	double best_fitness;
	int best_fitness_index;
	vector<int> get_best_combination();
	double sampleNormal();
private:
	int time_slice;
	int entrance_number;
	int lamda;
	int individual_number;
	double prob_crossover;
	vector<int> individual_chromo;
	vector<double> individual_sigma;
	vector< vector<int> > generation_pool;
	vector< vector<double> > sigma_pool;
	vector< vector<int> > lamda_chromo_pool;
	vector< vector<double> > lamda_sigma_pool;
	vector< vector<int> > total_generation_pool;
	vector< vector<double> > total_sigma_pool;
	vector<double> total_fitness;
	int win[80];
};
#endif
