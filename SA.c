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

#define MAX_VAl 600.5 /* Search space upper bound */
#define MIN_VAL -600.5 /* Seach space lower bound */

#define ALPHA 0.9
#define E 2.71828

double neighbor (double solution) /* Returns a value on the neighbor of 'solution' */
{
	double neighbor;
	time_t t;	
	srand((unsigned) time(&t));

	neighbor = (((double)rand()/(double)RAND_MAX)-0.5) + solution; /* Adds a value between -0.5 and 0.5 to 'solution' */

	if (neighbor < 0) /* Makes sure the minimum values don't go under 0 ("maximum" minimum value) */ 
	{
		return 1;
	}

	return neighbor;
}

double cost (double solution) /* Calculates the value of sin(solutin) for the given 'solution' */
{
	/* function: sum{_1}{^10}(x^2) - search space [-600.5,600.5]*/
	double cost = 0.0;

	for (int i = 0; i < 10; i++)
	{
		cost += pow(solution,2);
	}

	return cost;
}

double acceptance_probability(double old_cost, double new_cost, double t)
{
	double probability;
	double power_value;

	power_value = (new_cost - old_cost)/t;

	probability = pow(E, power_value);

	return probability;
}

int main () 
{
	int i;

	double big_t = 1.0;				/* #define T 1.0 */ 
	double big_t_min = 0.00001;		/* #define T_MIN 0.00001 */

	double solution = 0,
		   best_solution = 0, 
		   old_solution = 0, 
		   new_solution = 0,
		   new_cost = 0,
		   old_cost = 0,
		   ap = 0;
	
	time_t t;	
	srand((unsigned) time(&t));

	printf("Calculation simulated anealing process...");
	printf("\n");

	solution = ((double)rand()/(double)RAND_MAX)*MAX_VAl;

	old_cost = cost(solution);

	if (solution > 1.57)		/* Checks if the solution doesn't go beyond MAX_VAL. */
	{
		solution = MAX_VAl;		/* If it does, then solution equals MAX_VAL. */
		big_t_min = big_t*2;	/* Algorithm doesn't have to go through "cooling" process. */
	} 

	while (big_t > big_t_min)
	{
		i = 1;

		while (i <= 100)
		{
			new_solution = neighbor(solution);
			new_cost = cost(new_solution);
			ap = acceptance_probability(old_cost, new_cost, big_t);

			if (new_solution > 1.57)	/* Checks if the solution doesn't go beyond MAX_VAL. */
			{
				solution = MAX_VAl;		/* If it does, then solution equals MAX_VAL. */
				big_t_min = big_t*2;	/* Algorithm exits the "cooling" process (external while loop). */
				i = 100; 				/* Algorithm exits the "cooling" process (internal while loop). */ 
			} 

			if (ap > ((double)rand()/(double)RAND_MAX))
			{
				solution = new_solution;
				old_cost = new_cost;

				if (new_solution > 1.57)	/* Checks if the solution doesn't go beyond MAX_VAL. */
				{
					solution = MAX_VAl;		/* If it does, then solution equals MAX_VAL. */
					big_t_min = big_t*2;	/* Algorithm exits the "cooling" process (external while loop). */
					i = 100; 				/* Algorithm exits the "cooling" process (internal while loop). */
				}
			}

			i++;
		}

		big_t = big_t*ALPHA;
	}

	printf("Simulated anealing ended.\n\n");
	printf("========= Results =========\n");

	printf("\n");		

	printf("Solution: %lf\n", solution);
	printf("Solution cost: %lf\n", old_cost);

	return 0;
}