#include "EA.h"


EA::EA(void)
{
	entrance_number = 6;
	individual_number = 40;
	prob_crossover=0.7;
	prob_mutation=0.0017;
	time_slice = 7;
	//We first initialize vector in order to use them as array later
	for(int i=0;i<entrance_number;i++)
		individual_chromo.push_back(0);
	for(int i=0;i<individual_number;i++){
		probability.push_back(0.0);
		cumulative_prob.push_back(0.0);
	}
}


EA::~EA(void)
{
}


void EA::initial(){
	//We initialize the first generation with 40 individuals 
	//and each contains 6 integers ranging from 1 to 10
	//srand(1234);
	for(int i=0;i<individual_number;i++){
		for(int j=0;j<entrance_number;j++){
			individual_chromo[j] = (rand()%7)+1;
		}
		generation_pool.push_back(individual_chromo);
		mating_pool.push_back(individual_chromo);
	}

}

void EA::crossover(){
	for(int i=0;i<individual_number;){
		double probability = rand()/RAND_MAX;
		if(probability<=prob_crossover){
			int break_point = (rand()%5)+1;
			swap_parents(i,break_point);
		}
		i+=2;
	}
}

void EA::swap_parents(int row,int n){
	for(int i=n;i<entrance_number;i++){
		int temp = generation_pool[row][i];
		generation_pool[row][i] = generation_pool[row+1][i];
		generation_pool[row+1][i] = temp;
	}
}

void EA::mutation(){
	for(int i=0;i<individual_number;i++)
		for(int j=0;j<entrance_number;j++){
			double probability = (double)rand()/RAND_MAX;
			if(probability<=prob_mutation)
				generation_pool[i][j] = (rand()%10)+1;
		}
}
void EA::displayair(){
	for(int i=0;i<individual_number;i++){
		for(int j=0;j<entrance_number;j++){
			cout<<generation_pool[i][j]<<" ";
		}
		cout<<endl;
	}
}

vector<int> EA::GetIndividual(vector<vector<int>>a,int number){
	vector<int> Single_individual;
	a = generation_pool;
	int row = number;
	for(int i=0;i<entrance_number;i++)
		Single_individual.push_back(generation_pool[row][i]);
	return Single_individual;
}

int EA::getEntrance_number(){
	return entrance_number;
}

int EA::getTimeslice(){
	return time_slice;
}

vector<vector<int>>EA::getGeneration_pool(){

	return generation_pool;
}


void EA::selection_probability(vector<double>fitness){
	double summation = 0.0;
	for(int i=0;i<fitness.size();i++)
		if(fitness.at(i)!=0.0)
			summation+=1.0/fitness.at(i);
		else
			summation+=fitness.at(i);
	for(int i=0;i<fitness.size();i++){
		double temp_probability = 0.0;
		if(fitness.at(i)!=0)
			temp_probability = 1.0/(fitness.at(i)*summation);
		else 
			temp_probability = 0.0;
		probability[i] = temp_probability;
	}
}

void EA::cumulative_probability(){
	double temp_probability = 0.0;
	for(int i=0;i<probability.size();i++){
		temp_probability+=probability[i];
		cumulative_prob[i] = temp_probability;
	}
}

void EA::highroulette_wheel(){
	int current_number = 0;
	while(current_number<individual_number){
		double variable = rand() /double(RAND_MAX);
		int i = 0;
		if(variable == 1){
			mating_pool[current_number] = generation_pool[individual_number-1];
		}else{
		while(cumulative_prob[i]<variable){
			i+=1;
		}
		mating_pool[current_number] = generation_pool[i];
		}
		current_number+=1;
	}
}

int EA::getIndividualnumber(){
	return individual_number;
}

void EA::mating_to_generation(){
	generation_pool = mating_pool;
}