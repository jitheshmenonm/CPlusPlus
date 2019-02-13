#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int populationUnitSize = 10;
int populationHowmanyunits = 10;
typedef std::vector<int> populationUnit;
int sumValue2Reach = 200;
std::vector<populationUnit> population;

void printPopulation()
{
	for (auto i : population)
	{
		std::cout << std::endl;
		for (int j : i)
			std::cout << " " << j;
	}
	std::cout << std::endl;
}
int fitnessFunction(populationUnit& p)
{
	int sum = std::accumulate(p.begin(), p.end(), 0);
	return abs(sumValue2Reach - sum);
}
int averageFitnessOfPopulation()
{
	int sumOfFitnessofAllPopulation = 0;
	for (int i = 0; i < populationHowmanyunits; i++)
		sumOfFitnessofAllPopulation += fitnessFunction(population[i]);
	return sumOfFitnessofAllPopulation / (populationUnitSize*populationHowmanyunits);
}
bool CompareFitness(populationUnit& p1, populationUnit& p2)
{
	return (fitnessFunction(p1) < fitnessFunction(p2));
}
void evolve()
{
	//population is already sorted with the top ones being most fit
	//take first 4 and create rest of population
	populationUnit pChosen[4];
	for (int i = 0; i < 3; i++)
		pChosen[i] = population[i];

	//selecting an less fit one as well to ensure diversity in population
	if(((rand() % 100) + 1)> 50)
		pChosen[3] = population[7];
	else
		pChosen[3] = population[9];

	//update vector 4 onwards in population with the breeded values
	for (int n = 4; n < 10; ++n)
	{
		int firsthalf = ((rand() % 10) + 1);
		while (firsthalf > 3 || firsthalf < 0)
			firsthalf = ((rand() % 10) + 1);
		int secondhalf = ((rand() % 10) + 1);
		while (secondhalf > 3 || secondhalf < 0 || firsthalf==secondhalf)
			secondhalf = ((rand() % 10) + 1);
		for (int m = 0; m < 10; ++m)
		{
			if (m < 5)
				population[n][m] = pChosen[firsthalf][m];//0-4
			else
				population[n][m] = pChosen[secondhalf][m];//5-9

		}
	}
	//mutate randomly some values in population
	for (int n = 0; n < populationHowmanyunits; ++n)
	{
		for (int m = 0; m < populationUnitSize; ++m)
		{
			if (((rand() % 100) + 1) > 90)
				population[n][m] = ((rand() % 100) + 1);
		}
	}
}
int main()
{
	srand((int)time(0));
	population.reserve(populationHowmanyunits);
	for (int n = 0; n < populationHowmanyunits; n++)
	{
		populationUnit p;
		for (int k = 0; k < populationUnitSize; k++)
			p.push_back((rand() % 100) + 1);

		population.push_back(p);
	}

	printPopulation();

	std::sort(population.begin(), population.end(), CompareFitness);
	std::cout << std::endl;
	std::cout << "Average fitness of population at start = " << averageFitnessOfPopulation() << std::endl << std::endl;
	std::cout << "****************Fitness value should be closer to 0 to be more fit****************" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "Evolve and mutate the population and outputting average fitness...." << std::endl << std::endl;
		
	int naverage = 100;
	int nCountEvolutions = 0;
	while (naverage > 1)//evolve
	{
		evolve();
		std::sort(population.begin(), population.end(), CompareFitness);
		//printPopulation();
		naverage = averageFitnessOfPopulation();
		std::cout <<naverage << " ";		
		nCountEvolutions++;
	}

	std::cout << std::endl << std::endl;
	std::cout << "Final population after "<< nCountEvolutions << " evolutions" << std::endl;
	printPopulation();
	std::cout << std::endl;
	std::cout << "Average fitness of population after evolution = " << averageFitnessOfPopulation() << std::endl;

	char p;
	std::cin >> p;

}
