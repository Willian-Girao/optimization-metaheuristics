# Global Optimization Meta-heuristics

Implementations in C language of a few optimization meta-heuristics for global optimization:

* **Genetic Algorithm**
* **Simulated Annealing**
* [**Random Key Genetic Algorithm**](https://github.com/Willian-Girao/random-key_genetic_algorithms)

## Genetic Algorithm

Early computer simulations involving natural evolution begun around 1954. In the 60's these kind of simulations became commonly used, but Genetic Algorithms (GA's) in their "modern" form became popular in the 70's through the work of John Holland, in particular thanks to his book *Adaptation in Natural and Artificial Systems*.

The algorithm implemented in **GA_binary.c** works with binary encoding of the solution; that is, each chromosome is an array of 0's and 1's. The solution encoded within the chromosomes are converted into a real value, which in turn is evaluated in the objective function.

The objective function must be provided within the **opt_func_min(x)** function in the code:

```c
#define R_MAX 600.5
#define R_MIN -600.5
double opt_func_min (double x)
{
	int result = 0;

	for (int i = 0; i < 10; i++)
	{
		result += pow(x,2);
	}

	return result;
}
```

The above function minimizes $\sum_{i=1}^{10}(x^2)$ within the search space [R_MIN,R_MAX].

### Compiling (Linux)

**g++ GA_binary.c -o output_program -lm**

### Exectuion (Linux)

**./output_program**

### Expected Output

```c
--------------------------------------------------------
	Best Cromossome: 7
	Fitness: 0.0000000000000000000
	Binary representation: 01000000000011010010
--------------------------------------------------------
	Number of populations generated: 15
--------------------------------------------------------
	Real valued solution X found: 0.4821986812565910441
	Value of opt. min f(X) : 0.0000000000000000000
--------------------------------------------------------
```

## Simulated Annealing

The algorithm is named after the process of physical
annealing with solids, in which a crystalline solid is heated and then allowed to cool very slowly until it achieves its most regular possible crystal lattice configuration, and thus is free of crystal defects.  Simulated annealing establishes the connection between this type of thermodynamic behavior and the search for global minima for a discrete optimization problem.

The algorithm implemented in **SA.c** follows the standard configuration of the algorithm when it was proposed.

The following variables within the code can be fine tunned for better performance, depending on the problem.

```c
double big_t = 1.0;
double big_t_min = 0.00001;
```

The objective function to be minimized must be definede within the **cost(x)** function in the code.

```c
#define MAX_VAl 600.5
#define MIN_VAL -600.5
double cost (double x)
{
	double cost = 0.0;

	for (int i = 0; i < 10; i++)
	{
		cost += pow(x,2);
	}

	return cost;
}
```

The above function minimizes $\sum_{i=1}^{10}(x^2)$ within the search space [MIN_VAL,MAX_VAl].

### Compiling (Linux)

**g++ SA.c -o output_program -lm**

### Exectuion (Linux)

**./output_program**

### Expected Output

```c
Calculation simulated anealing process...
Simulated anealing ended.

========= Results =========

Solution: 600.500000
Solution cost: 14695.400030
```

# Contact

In case of any bugs and/or sugestions, send an email to wsg@icomp.ufam.edu.br or williansoaresgirao@gmail.com.
