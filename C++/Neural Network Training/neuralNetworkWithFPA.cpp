#include <bits/stdc++.h>
int dimensions = 2;
const float PI = acos(-1);
#include "../vectorMath.hpp"
#include "../Levy.hpp"
#include "dblib.hpp"
#define lli long long int
using namespace std;

Database database, traindb, testdb;
vector<int> layers = {8, 2, 1};

// n == Amount of Flowers
const int n = 20, iterations = 100000;
const float p = 0.8, eps = 1e-6;
const bool applyLimits = false;

vector<float> lowerLimit(dimensions), upperLimit(dimensions);
vector<float> limit(vector<float> vec)
{
  if (!applyLimits) return(vec);
  for (int i = 0; i < dimensions; i ++)
  {
    vec[i] = min(upperLimit[i], vec[i]);
    vec[i] = max(lowerLimit[i], vec[i]);
  }
  return(vec);
}

struct NeuralNetwork
{
  vector<vector<vector<float>>> weights;
  vector<vector<vector<float>>> biases;
  void init(vector<int> layersVec)
  {
    weights.resize(layersVec.size() - 1);
    for (int i = 0; i < layersVec.size() - 1; i ++)
    {
      weights[i].resize(layersVec[i]);
      for (int j = 0; j < layersVec[i]; j ++)
      {
        weights[i][j].resize(layersVec[i + 1]);
        for (int k = 0; k < layersVec[i + 1]; k ++)
          weights[i][j][k] = (float) rand() / RAND_MAX;
      }
    }
    biases.resize(layersVec.size() - 1);
    for (int i = 0; i < layersVec.size() - 1; i ++)
    {
      biases[i].resize(1);
      biases[i][0].resize(layersVec[i + 1]);
      for (int j = 0; j < layersVec[i + 1]; j ++)
        biases[i][0][j] = (float) rand() / RAND_MAX;
    }
  }
  void print()
  {
    printf("NeuralNetwork:\n");
    printf("\t%d layersVec\n", (int) weights.size() + 1);
    printf("\tweights:\n");
    for (int i = 0; i < weights.size(); i ++)
    {
      printf("\t\t%d (%d x %d):\n", i + 1, (int) weights[i].size(), (int) weights[i][0].size());
      for (int j = 0; j < weights[i].size(); j ++)
      {
        printf("\t\t\t");
        for (int k = 0; k < weights[i][j].size(); k ++)
          printf("%3.1f%c", weights[i][j][k], k < weights[i][j].size() - 1 ? ' ' : '\n');
      }
    }
    printf("\tbiases:\n");
    for (int i = 0; i < biases.size(); i ++)
    {
      printf("\t\t%d (1 x %d):\n\t\t\t", i + 1, (int) biases[i].size());
      for (int j = 0; j < biases[i][0].size(); j ++)
        printf("%3.1f%c", biases[i][0][j], j < biases[i].size() - 1 ? ' ' : '\n');
    }
  }
  void setUnidimensionalVector(vector<float> &temp)
  {
    int a = 0;
    for (int i = 0; i < weights.size(); i ++)
      for (int j = 0; j < weights[i].size(); j ++)
        for (int k = 0; k < weights[i][j].size(); k ++)
          weights[i][j][k] = temp[a ++];
    for (int i = 0; i < biases.size(); i ++)
      for (int j = 0; j < biases[i].size(); j ++)
        for (int k = 0; k < biases[i][j].size(); k ++)
          biases[i][j][k] = temp[a ++];
  }
  vector<float> getUnidimensionalVector()
  {
    vector<float> temp;
    for (int i = 0; i < weights.size(); i ++)
      for (int j = 0; j < weights[i].size(); j ++)
        for (int k = 0; k < weights[i][j].size(); k ++)
          temp.push_back(weights[i][j][k]);
    for (int i = 0; i < biases.size(); i ++)
      for (int j = 0; j < biases[i].size(); j ++)
        for (int k = 0; k < biases[i][j].size(); k ++)
          temp.push_back(biases[i][j][k]);
    return(temp);
  }
  vector<float> feedForward(vector<float> x)
  {
    vector<vector<float>> ans; ans.push_back(x);
    for (int i = 0; i < weights.size(); i ++)
      ans = sigmoid(matAdd(matMult(ans, weights[i]), biases[i]));
    return(ans[0]);
  }
  vector<float> classify(Database db)
  {
    vector<float> ans;
    for (int i = 0; i < db.size(); i ++)
    {
      vector<float> kkk;
      for (int j = 0; j < db[i].size() - 1; j ++) kkk.push_back(db[i][j]);
      vector<float> output = feedForward(kkk);
      ans.push_back(round(output[0]));
    }
    return(ans);
  }
};
NeuralNetwork neuralNetwork;

float f(vector<float> &x)
{
  neuralNetwork.setUnidimensionalVector(x);
  vector<float> ans = neuralNetwork.classify(database);
  float correct = 0;
  // printf("Evaluation:\n");
  for (int i = 0; i < database.size(); i ++)
  {
    // printf("%f %f\n", ans[i], database[i].back());
    correct += abs(ans[i] - database[i].back()) < eps;
  }
  return(1 - correct / database.size());
}

struct Flower
{
  vector<float> x;
  float fitness;
  void init()
  {
    neuralNetwork.init(layers);
    x = neuralNetwork.getUnidimensionalVector();
    evaluate();
  }
  float evaluate()
  {
    return(fitness = f(x));
  }
  void print(bool printX = true)
  {
    if (printX)
    {
      printf("[");
      for (int i = 0; i < dimensions; i ++)
        printf("%5.3f%c", x[i], i < dimensions - 1 ? ' ' : ']');
      printf(" - %8.5f\n", 1 - fitness);
    }
    else printf("%8.5f\n", 1 - fitness);
  }
};
Flower flowers[n], bestFlower;

void init()
{
  srand(time(NULL));
  loadCSV("diabetes.csv", database);
  // printDatabase(database);
  splitDatabase(database, traindb, testdb, 0.8);
  neuralNetwork.init(layers);
  dimensions = neuralNetwork.getUnidimensionalVector().size();

  for (int i = 0; i < dimensions; i ++) lowerLimit[i] = -100, upperLimit[i] = 100;

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
      current.x = limit(flowers[i].x + dS); // missing limit
    }
    else // Abiotic
    {
      // printf("Here %d m abiotic\n", i); fflush(stdout);
      float epsilon = rand() / RAND_MAX;
      int j = rand() % n, k = rand() % n;
      while (j == k) k = rand() % n;
      current.x = limit(current.x + (flowers[j].x - flowers[k].x) * epsilon); // missing limit
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
    if (t % 100 == 0) { printf("%d - ", t); bestFlower.print(false); }
  }
  printf("Finished, bestFlower:\n");
  bestFlower.print();

  return(0);
}