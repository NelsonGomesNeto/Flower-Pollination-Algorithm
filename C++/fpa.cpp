#include <bits/stdc++.h>
const int dimensions = 2;
const float PI = acos(-1);
#include "vectorMath.hpp"
#include "Levy.hpp"
#define lli long long int
using namespace std;

// n == Amount of Flowers
const int n = 20, iterations = 1000;

const float p = 0.8;

float f(vector<float> &x)
{
  // 5*x0 + 2*x1 = 185
  // return(abs(5 * x[0] + 2 * x[1] - 185));
  return(pow(5 * x[0] + 2 * x[1] - 185, 2));
}

struct Flower
{
  vector<float> x;
  float fitness;
  void init()
  {
    x.resize(dimensions);
    for (int i = 0; i < dimensions; i ++)
      x[i] = (rand() - RAND_MAX/2.0) / (RAND_MAX/2.0);
    evaluate();
  }
  float evaluate()
  {
    return(fitness = f(x));
  }
  void print()
  {
    printf("[");
    for (int i = 0; i < dimensions; i ++)
      printf("%5.3f%c", x[i], i < dimensions - 1 ? ' ' : ']');
    printf(" - %8.5f\n", fitness);
  }
};
Flower flowers[n], bestFlower;

void init()
{
  srand(time(NULL));
  for (int i = 0; i < n; i ++)
  {
    flowers[i].init();
    if (i == 0 || flowers[i].fitness < bestFlower.fitness)
      bestFlower = flowers[i];
  }
  printf("Started\n");
}

void nextIteration()
{
  for (int i = 0; i < n; i ++)
  {
    // printf("Here %d s\n", i); fflush(stdout);
    Flower current = flowers[i];
    if ((float) rand() / RAND_MAX > p) // Biotic
    {
      // vector<float> dS = (flowers[i].x - bestFlower.x) * Levy();
      vector<float> dS = Levy();
      // printf("Here %d m biotic\n", i); fflush(stdout);
      current.x = flowers[i].x + dS; // missing limit
    }
    else // Abiotic
    {
      // printf("Here %d m abiotic\n", i); fflush(stdout);
      float epsilon = rand() / RAND_MAX;
      int j = rand() % n, k = rand() % n;
      while (j == k) k = rand() % n;
      current.x = current.x + (flowers[j].x - flowers[k].x) * epsilon; // missing limit
    }
    // printf("Here %d f\n", i); fflush(stdout);

    current.evaluate();
    if (current.fitness <= flowers[i].fitness) flowers[i] = current;
    if (current.fitness <= bestFlower.fitness) bestFlower = current;
  }
}

int main()
{
  init();

  for (int t = 0; t < iterations; t ++)
  {
    nextIteration();
    bestFlower.print();
  }
  printf("Finished, bestFlower:\n");
  bestFlower.print();

  return(0);
}