#include<iostream>
#include<stdlib.h>
#include <time.h>
#include <conio.h>

#include"EA.h"
#include"airplane.h"
#include"center_based.h"
#include "EP.h"
#include "center_based_ES.h"
#include "center_based_EP.h"
using namespace std;


int main()
{
	while(true)
	{
		int algorithm_select;
		cout << "Pleast select the algorithm, 1 is Genetic Algorithm, 2 is Evolutionary Strategy, 3 is Evolutionary Programming, 0 is quit: ";
		cin >> algorithm_select;
		if (algorithm_select == 0)
			break;
		if(algorithm_select == 0)
		cout << endl;
		int iteration_number;
		cout << "Please input the iteration number: ";
		cin >> iteration_number;
		cout << endl;

		vector<double> fitness, fitness_es, fitness_ep;
		vector<double> ratio_fitness, es_ratio_fitness, ep_ratio_fitness;
		center_based AC14;
		center_based_ES EStest;
		center_based_EP EPtest;
		time_t t_start,t_end;  

		AC14.initial();
		EStest.initial();
		EPtest.initial();
		/*AC14.displayair();
		system("pause");*/
		AC14.read_conf();
		EStest.read_conf();
		EPtest.read_conf();
		for (int i = 0; i < EStest.getTotalnumber(); i++)
		{
			fitness_es.push_back(0.0);
			es_ratio_fitness.push_back(0.0);

		}

		for (int i = 0; i < EPtest.getTotalnumber(); i++)
		{
			fitness_ep.push_back(0.0);
			ep_ratio_fitness.push_back(0.0);
		}

		for(int i=0;i<AC14.getIndividualnumber();i++){
			fitness.push_back(0.0);
			ratio_fitness.push_back(0.0);
		}


		t_start = clock();


		if(algorithm_select == 1)
		{
			int index = 0;
			while(index<iteration_number)
			{
				vector<double>ratio =  AC14.occupation_ratio();
				for(int i=0;i<AC14.getIndividualnumber();i++){
					AC14.greedy_schedule(i);
					bool isOverflow = false;
					bool isUnsafe = AC14.kickUnsafe(i);
					if(!isUnsafe)
						isOverflow = AC14.kickOverflow();
					if(isUnsafe||isOverflow){
						ratio_fitness[i] = 1000000.0;
						fitness[i] = 100000.0;
					}
					else{
						fitness[i] = AC14.fitness_calculation();
						ratio_fitness[i] = fitness[i] /  (ratio[i] * 2.7);
					}
				}

				AC14.selection_probability(ratio_fitness);
				AC14.cumulative_probability();
				AC14.highroulette_wheel();
				AC14.mating_to_generation();
				AC14.crossover();
				AC14.mutation();
				index++;
				double result = ratio_fitness[0];
				for(int s = 1; s < ratio_fitness.size(); s++)
				{
					if(ratio_fitness[s] < result)
						result = ratio_fitness[s];
				}
				cout << result << endl;

				// Above is the process of GA
			}
		}



		if(algorithm_select == 2)
		{
			int index_es = 0;
			while(index_es<iteration_number)
			{
				EStest.crossover();
				EStest.mutation();
				//EStest.display();
				vector<double> ratio = EStest.occupation_ratio();
				for(int i=0;i<EStest.getTotalnumber();i++){
					EStest.greedy_schedule(i);
					bool isOverflow = false;
					bool isUnsafe = EStest.kickUnsafe(i);
					if(!isUnsafe)
						isOverflow = EStest.kickOverflow();
					if(isUnsafe||isOverflow)
					{
						es_ratio_fitness[i] = 1000000.0;
						fitness_es[i] = 1000000.0;
					}
					else{
						fitness_es[i] = EStest.fitness_calculation();
						es_ratio_fitness[i] = EStest.fitness_calculation() / (ratio[i] * 2.7);
					}
				}
				EStest.seletion(es_ratio_fitness);
				index_es++;
				// Above is the process of ES
			}
		}

		if(algorithm_select == 3)
		{
			int index_ep = 0;
			while(index_ep<iteration_number)
			{
				//EPtest.display();
				EPtest.mutation();
				//EPtest.debugdisplay();
				vector<double> ratio = EPtest.occupation_ratio();
				for(int i=0;i<EPtest.getTotalnumber();i++){
					EPtest.greedy_schedule(i);
					bool isOverflow = false;
					bool isUnsafe = EPtest.kickUnsafe(i);
					if(!isUnsafe)
						isOverflow = EPtest.kickOverflow();
					if(isUnsafe||isOverflow)
					{
						ep_ratio_fitness[i] = 1000000.0;
						fitness_ep[i] = 1000000.0;
					}
					else{
						fitness_ep[i] = EPtest.fitness_calculation();
						ep_ratio_fitness[i] = EPtest.fitness_calculation() / (ratio[i] * 2.7);
					}
				}
				EPtest.seletion(ep_ratio_fitness);
				index_ep++;
				//Above is the process of EP
			}
		}		
		t_end = clock();
		cout<<"Time Consuming : " << difftime(t_end,t_start)<<endl;
		system("pause");
	}
	return 0;
}
