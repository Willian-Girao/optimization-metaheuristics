/*
		Federal University of Amazon
		Fluminense Federal University
			Computing Institute
Laboratory of Algorithm Complexity and Optmization

	  Author: Willian Soares Girao
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define POP_SIZE 8 /* Population size */
#define R_MAX 600.5 /* Search space upper bound */
#define R_MIN -600.5 /* Seach space lower bound */
#define L 20 /* chromosssome length */
#define T_MAX 500 /* maximum number of iterations */

struct top_half 
{	
	int binary_individual[L];			
	int cromossome_position;
	double fitness;
} temporary[POP_SIZE], temp;

double best_cromossome;

int selected_already[POP_SIZE/2] = {-1, -1, -1, -1}; /* Used to control parents during cross over (each cromossome must be select only once) */

/* Function to be optimized - 'real' is the real valued interpretation of the binary coding */
double opt_func_min (double real)
{
	/* function: sum{_1}{^10}(x^2) - search space [-600.5,600.5]*/
	int result = 0;

	for (int i = 0; i < 10; i++)
	{
		result += pow(real,2);
	}

	return result;
}

int convertion_binary_integer (int j) 
{
	int integer = 0;
	int expo = 18;
	int sign = 1;

	if (temporary[j].binary_individual[0] == 1)
	{
		sign = -1;
	}
	
	for (int i = 1; i < L; i++) 
	{

		if (temporary[j].binary_individual[i] == 0) 
		{

			expo--;
		}
		else 
		{

			integer += pow((temporary[j].binary_individual[i])*2, expo);		
			expo--;		
		}		
	}

	return integer*sign;
}

double real_value(int z) 
{
	double r;

	r = ((R_MAX - R_MIN) / (pow(2,L-1) - 1)) * z + R_MIN;

	return r;
}

struct top_half* list_of_pop(int i) 
{
	struct top_half* elem = (struct top_half*) malloc(sizeof(struct top_half));
	
	for (int j = 0; j < L; j++) 
	{
		elem->binary_individual[j] = rand() % 2;				
	}

	elem->cromossome_position = i;
	elem->fitness = 0.0;
	
	return elem;
}


void calc_fitness() 
{
	for (int i = 0; i < POP_SIZE; i++) 
	{
		temporary[i].fitness = opt_func_min(real_value(convertion_binary_integer(i)));
	}
}

void first_population() 
{
	for (int i = 0; i < POP_SIZE; i++) 
	{
		temporary[i] = *list_of_pop(i);
	}
}

void print_population() 
{
	for (int j = 0; j < POP_SIZE; j++) 
	{
		printf("Individual: %d\n", temporary[j].cromossome_position);
		printf("Binary representation: ");

		for (int i = 0; i < L; ++i)	
		{
			printf("%d", temporary[j].binary_individual[i]);
		}

		printf("\n");		
		printf("Fitness: %.19lf\n", temporary[j].fitness);
		printf("\n");
	}	
}

void selection() 
{
	for (int i = 0; i < POP_SIZE; i++) 
	{
		for (int j = i; j < POP_SIZE; j++) 
		{
			if (temporary[i].fitness > temporary[j].fitness)
			{
				temp = temporary[i];
				temporary[i] = temporary[j];
				temporary[j] = temp;
			}
		}
	}
}

void new_best ()
{
	if (best_cromossome > temporary[0].fitness) 
	{
		printf("\n");
		printf("New best individual found. \n");

		best_cromossome = temporary[0].fitness;
		
    	printf("Fitness: %.19lf\n", best_cromossome);

		printf("Binary representation: ");

		for (int i = 0; i < L; ++i)	
		{
			printf("%d", temporary[0].binary_individual[i]);
		}
		printf("\n");		
	} 
}

int check_parent(int p) 
{
	for (int i = 0; i < POP_SIZE/2; i++) 
	{
		if (p == selected_already[i]) 
		{
			return -1;
		}

		else 
		{
			if (selected_already[i] == -1) 
			{
				selected_already[i] = p;
				return p;
			}

			else 
			{
			}
		}
	}
	
	return 9;
}

void crossover(int indiv_change) /* indiv_change has to be the "bad half" of the previous population */
{
	int parent1, parent2, crossover_point;

	parent1 = rand() % 4;
	check_parent(parent1);

	if (parent1 == check_parent(parent1)) 
	{
		while (parent1 == check_parent(parent1)) 
		{
			parent1 = rand() % 4;
		}
	}

	parent2 = rand() % 4;
	check_parent(parent2);

	if (parent2 == check_parent(parent2))
	{
		while (parent2 == check_parent(parent2)) 
		{
			parent2 = rand() % 4;
		}
	}

	crossover_point = rand() % L;		

	if (parent2 == parent1) 
	{
		while (parent2 == parent1) 
		{
			parent2 = rand() % 4;
		}

		check_parent(parent2);
	}

	for (int i = 0; i < crossover_point; i++) 
	{
		temporary[indiv_change].binary_individual[i] = temporary[parent1].binary_individual[i];
	}

	for (int i = crossover_point; i < L; i++) 
	{
		temporary[indiv_change].binary_individual[i] = temporary[parent2].binary_individual[i];
	}

	temporary[indiv_change].fitness = 0.0;

	for (int i = 0; i < crossover_point; i++) 
	{
		temporary[indiv_change+1].binary_individual[i] = temporary[parent2].binary_individual[i];
	}

	for (int i = crossover_point; i < L; i++) 
	{
		temporary[indiv_change+1].binary_individual[i] = temporary[parent1].binary_individual[i];
	}

	temporary[indiv_change+1].fitness = 0.0;
}

int mutation() 
{
	double random;	

	for (int i = 4; i < POP_SIZE; i++) 
	{
		for (int j = 0; j < L; j++) 
		{
			random = (double)rand()/(double)RAND_MAX;

			if (random < 0.083333) 
			{
				if (temporary[i].binary_individual[j] == 0) 
				{
					temporary[i].binary_individual[j] = 1;
				}
				else 
				{
					temporary[i].binary_individual[j] = 0;					
				}

				return 1;
			}				
		}
	}

	return 0;	
}


int main () {

	int num_populations, num_mutations;
	time_t t;
	double random;

	num_mutations = 0;	
	
	srand((unsigned) time(&t));

	first_population();	
	calc_fitness();
	selection();
	
	best_cromossome = temporary[0].fitness;	

	num_populations = 1;
	
	for (int j = 0; j < T_MAX; j++) {
		selection();
		new_best();

		for (int i = 4; i < POP_SIZE; i++) {

			crossover(i);
			i++;
		}

		num_mutations += mutation();

		calc_fitness();

		num_populations++;
	}

	printf("\n");	
	printf("---------------------------------------------------------------------------\n");	
	printf("		Best Cromossome: %d\n", temporary[0].cromossome_position);
	printf("		Fitness: %.19lf\n", best_cromossome);
	printf("		Binary representation: ");

	for (int i = 0; i < L; ++i)	
	{
		printf("%d", temporary[0].binary_individual[i]);
	}

	printf("\n");
	printf("\n");
	printf("---------------------------------------------------------------------------\n");
	printf("		Number of populations generated: %d\n", num_populations);	
	printf("---------------------------------------------------------------------------\n");
	printf("\n");
	printf("\n");

	double test = opt_func_min(real_value(convertion_binary_integer(0)));
	printf("		Real valued solution X found: %.19lf\n", real_value(convertion_binary_integer(0)));
	printf("		Value of opt. min f(X) : %.19lf\n", test);
	printf("---------------------------------------------------------------------------\n");
	printf("\n");
	printf("\n");
	

	return 0;
}
