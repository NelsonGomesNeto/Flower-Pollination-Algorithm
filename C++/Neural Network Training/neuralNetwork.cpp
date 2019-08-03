#include <bits/stdc++.h>
#include "dblib.hpp"
using namespace std;

Database database, traindb, testdb;

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