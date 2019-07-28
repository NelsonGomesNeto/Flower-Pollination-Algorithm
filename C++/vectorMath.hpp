#include <vector>
using namespace std;

vector<float> operator*(const vector<float> &a, const vector<float> &b)
{
  vector<float> temp = a;
  for (int i = 0; i < dimensions; i ++) temp[i] *= b[i];
  return(temp);
}
vector<float> operator-(const vector<float> &a, const vector<float> &b)
{
  vector<float> temp = a;
  for (int i = 0; i < dimensions; i ++) temp[i] -= b[i];
  return(temp);
}
vector<float> operator+(const vector<float> &a, const vector<float> &b)
{
  vector<float> temp = a;
  for (int i = 0; i < dimensions; i ++) temp[i] += b[i];
  return(temp);
}
vector<float> operator*(const vector<float> &a, const float b)
{
  vector<float> temp = a;
  for (int i = 0; i < dimensions; i ++) temp[i] *= b;
  return(temp);
}