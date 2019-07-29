#include <bits/stdc++.h>
#include "dblib.hpp"
using namespace std;

Database database, traindb, testdb;

struct NeuralNetwork
{
  vector<vector<vector<float>>> weights;
  vector<vector<float>> biases;
  void init(vector<int> layers)
  {
    weights.resize(layers.size() - 1);
    for (int i = 0; i < layers.size() - 1; i ++)
    {
      weights[i].resize(layers[i]);
      for (int j = 0; j < layers[i]; j ++)
      {
        weights[i][j].resize(layers[i + 1]);
        for (int k = 0; k < layers[i + 1]; k ++)
          weights[i][j][k] = (float) rand() / RAND_MAX;
      }
    }
    biases.resize(layers.size() - 1);
    for (int i = 0; i < layers[i] - 1; i ++)
    {
      biases[i].resize(layers[i + 1]);
      for (int j = 0; j < layers[i + 1]; j ++)
        biases[i][j] = (float) rand() / RAND_MAX;
    }
  }
  void print()
  {
    printf("NeuralNetwork:\n");
    printf("\t%d layers\n", (int) weights.size() + 1);
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
      for (int j = 0; j < biases[i].size(); j ++)
        printf("%3.1f%c", biases[i][j], j < biases[i].size() - 1 ? ' ' : '\n');
    }
  }
};
NeuralNetwork neuralNetwork;

int main()
{
  srand(time(NULL));
  loadCSV("diabetes.csv", database);
  // printDatabase(database);
  splitDatabase(database, traindb, testdb);
  // printDatabase(testdb);

  neuralNetwork.init({8, 8, 1});
  neuralNetwork.print();

  return(0);
}