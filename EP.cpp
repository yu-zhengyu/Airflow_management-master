#include "EP.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#define PI 3.1415926

EP::EP(void)
{
	best_fitness = 0.0;
	best_fitness_index = 0;
	entrance_number = 6;
	individual_number = 40;
	lamda = 40;
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
		total_fitness.push_back(0);
	}
	for (int w = 0; w < 80; w++)
	{
		win[w] = 0;
	}
}

EP::~EP(void)
{

}

vector<int> EP::get_best_combination()
{
	int best_index = 0;
	double best_delay = total_fitness[best_index];
	for(int j = 1; j < 40; j++)
	{
		if(total_fitness[j] < best_delay)
		{
			best_index = j;
			best_delay = total_fitness[j];
		}
	}
	return generation_pool[best_index];
}

void EP::initial()
{	
	//We initialize the first generation with 40 individuals 
	//and each contains 6 integers ranging from 1 to 10
	srand(time(NULL));
	for(int i = 0; i < individual_number; i++){
		for(int j=0;j<entrance_number;j++){
			individual_chromo[j] = (rand() % 8)+1;
			individual_sigma[j] = rand() * 1.0 / RAND_MAX * 4.0;
			if(individual_sigma[j] < 3)
				individual_sigma[j] = 3;
		}
		generation_pool[i] = individual_chromo;
		sigma_pool[i] = individual_sigma;
	}	
}

void EP::mutation()
{
	for(int i = 0; i < 	individual_number; i++)
	{
		double gammapi = 1 / sqrt(2 * 40);
		double gamma = 1 / sqrt(2 * sqrt(40.0));
		
		//cout << globalnorm << endl;
		vector<double> input_sigma = sigma_pool[i];
		vector<int> input_chromo = generation_pool[i];
		for(int j = 0; j < entrance_number; j++)
		{
			double Ni =sampleNormal();
			input_chromo[j] = input_chromo[j] + input_sigma[j] * Ni;
			input_sigma[j] = input_sigma[j] * (1 + 0.1 * Ni);
			if(input_chromo[j] > 8)
				input_chromo[j] = 8;
			if(input_chromo[j] < 1)
				input_chromo[j] = 1;
			if(input_sigma[j] < 0.04)
				input_sigma[j] = 0.04;
		}
		lamda_chromo_pool[i] = input_chromo;
		lamda_sigma_pool[i] = input_sigma;
	}	
}

void EP::debugdisplay()
{
	for(int i = 0; i < 40; i++)
	{
		for(int j = 0; j < 6; j++)
			cout << generation_pool[i][j] << " ";
		cout << endl;
	}
}

void EP::seletion(vector<double> fitness)
{
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
	for(int i = 0; i < 80; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			if(fitness[i] < fitness[rand() % 80])
				win[i]++;
		}
	}
	total_fitness = fitness;
	BooSort();
	for (int i = 0; i < individual_number; i++)
	{
		generation_pool[i] = total_generation_pool[i];
		sigma_pool[i] = total_sigma_pool[i];
	}
	int best_index = 0;
	double best_delay = total_fitness[best_index];
	for(int j = 1; j < 40; j++)
	{
		if(total_fitness[j] < best_delay)
		{
			best_delay = total_fitness[j];
			best_index = j;
		}
	}
	cout << total_fitness[best_index] << endl;

}

double EP::sampleNormal() {
double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
double r = u * u + v * v;
if (r == 0 || r > 1) return sampleNormal();
double c = sqrt(-2 * log(r) / r);
return u * c;
}

void EP::BooSort()
{
	for(int i = 0; i < individual_number+individual_number; i++)

	{
		for(int j = 0; j < individual_number+individual_number; j++)
		{
			if(win[i] > win[j])
			{
				int tempwin = win[i];
				win[i] = win[j];
				win[j] = tempwin;
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

vector<int> EP::GetIndividual(vector<vector<int>>a,int number){
	vector<int> Single_individual;
	a = generation_pool;
	int row = number;
	for(int i=0;i<entrance_number;i++)
		Single_individual.push_back(generation_pool[row][i]);
	return Single_individual;
}

int EP::getIndividualnumber(){
	return individual_number;
}

int EP::getTotalnumber(){
	return lamda + individual_number;
}

int EP::getEntrance_number(){
	return entrance_number;
}

int EP::getTimeslice(){
	return time_slice;
}

vector<vector<int>>EP::getGeneration_pool(){
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

void EP::display()
{
	//cout << NormalRandom(0,1, 0, 1) << endl;
	//cout << lamda_sigma_pool[0][1] << endl;
	for(int j = 0; j < 40; j++)
	{
		for (int i = 0; i < entrance_number; i++)
		{
			cout << generation_pool[j][i] << " ";
		}
	cout << endl;
	}
	cout << endl;
	double result = total_fitness[0];
	int result_index = 0;
	for(int i = 1; i < 40; i++)
	{
		if(total_fitness[i] < result)
		{
			result = total_fitness[i];
			result_index = i;
		}
	}

	cout << result << endl;
	for (int i = 0; i < entrance_number; i++)
	{
		cout << generation_pool[result_index][i] << " ";
	}
	cout << endl;
}