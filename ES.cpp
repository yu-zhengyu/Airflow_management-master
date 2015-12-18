#include "ES.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define PI 3.1415926

ES::ES(void)
{
	best_fitness = 0;
	entrance_number = 6;
	individual_number = 40;
	lamda = 100;
	time_slice = 7;
	prob_crossover=0.5;
	//
	for(int i = 0; i < entrance_number; i++)
	{
		individual_chromo.push_back(0);
		individual_sigma.push_back(0.0);	
	}
	for (int p = 0; p < individual_number; p++)
	{
		generation_pool.push_back(individual_chromo);
		sigma_pool.push_back(individual_sigma);
	}
	for(int j = 0; j < lamda; j++)
	{
		lamda_chromo_pool.push_back(individual_chromo);
		lamda_sigma_pool.push_back(individual_sigma);
	}

	for (int h = 0; h < lamda+individual_number;h++)
	{
		total_generation_pool.push_back(individual_chromo);
		total_sigma_pool.push_back(individual_sigma);
	}

	for (int t = 0; t < individual_number + lamda; t++)
	{
		total_fitness.push_back(0.0);
	}
}

ES::~ES(void)
{

}

void ES::initial()
{	
	//We initialize the first generation with 40 individuals 
	//and each contains 6 integers ranging from 1 to 10
	//srand(20);
	for(int i = 0; i < individual_number; i++){
		for(int j=0;j<entrance_number;j++){
			individual_chromo[j] = (rand() % 7)+1;
			individual_sigma[j] = rand() * 1.0 / RAND_MAX * 3.0;
		}
		generation_pool[i] = individual_chromo;
		sigma_pool[i] = individual_sigma;
	}	
}

void ES::crossover(){
	for(int i=0; i<lamda; i++){
		int number_choose1, number_choose2;
		number_choose1 = rand() % individual_number;
		number_choose2 = rand() % individual_number;
		if(rand() <= 0.5)
			lamda_chromo_pool[i] = generation_pool[number_choose1];
		else
			lamda_chromo_pool[i] = generation_pool[number_choose2];
		vector<double> c1 = sigma_pool[number_choose1];
		vector<double> c2 = sigma_pool[number_choose2];
		for(int j = 0; j < entrance_number; j++)
		{
			double temp = 0;
			lamda_sigma_pool[i][j] = (c1[j] + c2[j]) / 2;
		}
	}
}

void ES::mutation(){
	for(int i = 0; i < 	lamda; i++)
	{
		double gammapi = 1 / sqrt(2 * 30);
		double gamma = 1 / sqrt(2 * sqrt(30.0));
		double globalnorm = NormalRandom(0,1, -3, 3);
		//cout << globalnorm << endl;
		vector<double> input_sigma = lamda_sigma_pool[i];
		vector<int> input_chromo = lamda_chromo_pool[i];
		for(int j = 0; j < entrance_number; j++)
		{
			double Ni = NormalRandom(0,1,-3,3);
			input_sigma[j] = input_sigma[j] * exp(gammapi * globalnorm + gamma * Ni);
			input_chromo[j] = input_chromo[j] + input_sigma[j] * Ni;
			if(input_chromo[j] < 1)
				input_chromo[j] = 1;
			if(input_chromo[j] > 8)
				input_chromo[j] = 8;
			if(input_sigma[j] < 0.04)
				input_sigma[j] = 0.04;
		}
		lamda_chromo_pool[i] = input_chromo;
		lamda_sigma_pool[i] = input_sigma;
	}	
}



void ES::seletion(vector<double> fitness)
{
	//QuickSort(fitness, 0, (individual_number+lamda-1));
	//for (int j = 0; j < fitness.size(); j++)
	//{
	//	total_fitness[j] = fitness[j];
	//}
	best_fitness = fitness[0];
	best_fitness_index = 0;
	for(int i = 1; i < fitness.size(); i++)
	{
		if(fitness[i] <= best_fitness)
		{
			best_fitness_index = i;
			best_fitness = fitness[i];
		}
	}

	total_fitness = fitness;
	BooSort();

	for (int i = 0; i < individual_number; i++)
	{
		generation_pool[i] = total_generation_pool[i];
		sigma_pool[i] = total_sigma_pool[i];
	}
	cout << total_fitness[0] << endl;
}

vector<int> ES::get_best_combination()
{
	return generation_pool[0];
}
 
void ES::BooSort()
{
	for(int i = 0; i < lamda+individual_number; i++)

	{
		for(int j = 0; j < lamda+individual_number; j++)
		{
			if(total_fitness[i] < total_fitness[j])
			{
				double temp = total_fitness[i];
				total_fitness[i] = total_fitness[j];
				total_fitness[j] = temp;
				vector<int> temp_generation = total_generation_pool[i];
				vector<double> temp_sigma = total_sigma_pool[i];
				total_generation_pool[i] = total_generation_pool[j];
				total_generation_pool[j] = temp_generation;
				total_sigma_pool[i] = total_sigma_pool[j];
				total_sigma_pool[j] = temp_sigma;
			}
		}
	}
}

double ES::Normal(double x,double miu,double sigma) 
{
	return 1.0/sqrt(2*PI*sigma) * exp(-1*(x-miu)*(x-miu)/(2*sigma*sigma));
}

double ES::AverageRandom(double min, double max){
	double rate = rand()/(double)(1+RAND_MAX);
	return min+(max-min)*rate;
}

double ES::NormalRandom(double miu, double sigma,double min,double max) //choosing random number base on  normal distribution
{
	double x;
	double dScope;
	double y;
	do
	{
		x = AverageRandom(min,max);        
		y = Normal(x, miu, sigma);         
		dScope = AverageRandom(0, Normal(miu,miu,sigma));
	}while( dScope > y);                  
	return x;
}

vector<int> ES::GetIndividual(vector<vector<int>>a,int number){
	vector<int> Single_individual;
	a = generation_pool;
	int row = number;
	for(int i=0;i<entrance_number;i++)
		Single_individual.push_back(generation_pool[row][i]);
	return Single_individual;
}

int ES::getIndividualnumber(){
	return individual_number;
}

int ES::getTotalnumber(){
	return lamda + individual_number;
}

int ES::getEntrance_number(){
	return entrance_number;
}

int ES::getTimeslice(){
	return time_slice;
}

vector<vector<int>>ES::getGeneration_pool(){
	total_generation_pool.clear();
	total_sigma_pool.clear();
	for (int i = 0; i < individual_number; i++)
	{
		total_generation_pool.push_back(generation_pool[i]);
		total_sigma_pool.push_back(sigma_pool[i]);
	}
	for (int j = 0; j < lamda; j++)
	{
		total_generation_pool.push_back(lamda_chromo_pool[j]);
		total_sigma_pool.push_back(lamda_sigma_pool[j]);
	}
	return total_generation_pool;
}

void ES::display()
{
	//cout << NormalRandom(0,1, 0, 1) << endl;
	//cout << lamda_sigma_pool[0][1] << endl;
	for(int j = 0; j < 100; j++)
	{
		for (int i = 0; i < entrance_number; i++)
		{
			cout << lamda_chromo_pool[j][i] << " ";
		}
	cout << endl;
	}
	/*
	for (int i = 0; i < entrance_number; i++)
	{
		cout << lamda_chromo_pool[0][i] << " ";
	}
	*/
	cout << endl;
	//cout << total_fitness[0] << endl;

}