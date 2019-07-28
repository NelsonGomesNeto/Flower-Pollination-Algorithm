#include <random>

std::default_random_engine generator;
std::normal_distribution<float> distribution(0, 1);
float randn()
{
  return(distribution(generator));
}