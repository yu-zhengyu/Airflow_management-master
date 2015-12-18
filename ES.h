#ifndef ES_H
#define ES_H
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;
class ES
{
public:
	ES(void);
	~ES(void);
	void initial();
	void crossover();
	void mutation();
	int getEntrance_number();
	vector<int> GetIndividual(vector<vector<int>>a,int number);
	int getTimeslice();
	vector<vector<int>> getGeneration_pool();
	int getIndividualnumber();
	int getTotalnumber();
	void seletion(vector<double> fitness);
	void display();//This function is for testing and print out individual pool
	double Normal(double x,double miu,double sigma);
	double AverageRandom(double min, double max);
	double NormalRandom(double miu, double sigma,double min,double max);
	void BooSort();
	double best_fitness;
	int best_fitness_index;
	vector<int> get_best_combination();
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

};
#endif
