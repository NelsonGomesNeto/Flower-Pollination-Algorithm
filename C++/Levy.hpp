#include "randn.hpp"
#include <vector>
using namespace std;
const float BETA = 3.0/2.0, INV_BETA = 2.0/3.0;
const float sigma = pow(tgammaf(1+BETA) * sin(PI*BETA/2.0) / (tgammaf((1+BETA)/2.0) * BETA * pow(2, (BETA-1)/2.0)), INV_BETA);

vector<float> Levy()
{
  vector<float> temp(dimensions);
  for (int i = 0; i < dimensions; i ++)
    temp[i] = randn() * sigma / pow(abs(randn()), INV_BETA) * 0.01;
  return(temp);
}