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

vector<vector<float>> matMult(vector<vector<float>> &a, vector<vector<float>> &b)
{
  if (a[0].size() != b.size())
  {
    printf("matMult can't be done: (%d x %d) * (%d x %d)\n", (int) a.size(), (int) a[0].size(), (int) b.size(), (int) b[0].size()); fflush(stdout);
    exit(0);
  }
  vector<vector<float>> temp(a.size());
  for (int i = 0; i < a.size(); i ++)
  {
    temp[i].resize(b[0].size());
    for (int j = 0; j < b[0].size(); j ++)
    {
      temp[i][j] = 0;
      for (int k = 0; k < a[0].size(); k ++)
        temp[i][j] += a[i][k] * b[k][j];
    }
  }
  return(temp);
}
vector<vector<float>> matAdd(vector<vector<float>> &a, vector<vector<float>> &b)
{
  if (a.size() != b.size() || a[0].size() != b[0].size())
  {
    printf("matAdd can't be done: (%d x %d) * (%d x %d)\n", (int) a.size(), (int) a[0].size(), (int) b.size(), (int) b[0].size()); fflush(stdout);
    exit(0);
  }
  vector<vector<float>> temp = a;
  for (int i = 0; i < a.size(); i ++)
    for (int j = 0; j < a[0].size(); j ++)
      temp[i][j] += b[i][j];
  return(temp);
}

inline float unitarySigmoid(float x) { return(1.0 / (1 + exp(-x))); }
vector<vector<float>> sigmoid(vector<vector<float>> &mat)
{
  for (int i = 0; i < mat.size(); i ++)
    for (int j = 0; j < mat[0].size(); j ++)
      mat[i][j] = unitarySigmoid(mat[i][j]);
  return(mat);
}