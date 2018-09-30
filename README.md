# Global Optimization Meta-heuristics

Implementations in C language of a few optimization meta-heuristics for global optimization:

* **Genetic Algorithm**
* **Simulated Annealing**

## Genetic Algorithm

Early computer simulations involving natural evolution begun around 1954. In the 60's these kind of simulations became commonly used, but Genetic Algorithms (GA's) in their "modern" form became popular in the 70's through the work of John Holland, in particular thanks to his book *Adaptation in Natural and Artificial Systems*.

The algorithm implemented in **GA_binary.c** works with binary encoding of the solution; that is, each chromosome is an array of 0's and 1's. The solution encoded within the chromosomes are converted into a real value, which in turn is evaluated in the objective function.

The objective function must be provided within the **opt_func_min(x)** function in the code:

```c
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

The above function minimizes $\sum_{i=1}^{10}(x^2)$ within the search space [-600.5,600.5].

### Compiling (Linux)

**g++ GA_binary.c -o output_program -lm**

## Expected Output

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
