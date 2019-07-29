#include <bits/stdc++.h>
using namespace std;
#define Database vector<vector<float>>

void loadCSV(string name, Database &db)
{
  FILE *f = fopen(name.c_str(), "r");
  if (f == NULL)
  {
    printf("File \"%s\" not found", name.c_str());
    return;
  }
  db.clear(); db.push_back(vector<float>());
  float value; char end;
  while (fscanf(f, "%f", &value) != EOF)
  {
    db.back().push_back(value);
    if (fscanf(f, "%c", &end) == EOF) break;
    if (end == '\n') db.push_back(vector<float>());
  }
  fclose(f);
}

void printDatabase(Database &db)
{
  printf("%d x %d\n", (int) db.size(), (int) db[0].size());
  for (int i = 0; i < db.size(); i ++)
    for (int j = 0; j < db[i].size(); j ++)
      printf("%5.1lf%c", db[i][j], j < db[i].size() - 1 ? ' ' : '\n');
}

void splitDatabase(Database &db, Database &traindb, Database &testdb, float proportion = 0.8)
{
  set<float> outcomes;
  for (int i = 0; i < db.size(); i ++)
    outcomes.insert(db[i].back());

  map<float, int> outcomesMap;
  for (float o: outcomes)
    outcomesMap[o] = outcomesMap.size();

  vector<Database> eachOutcamedb(outcomes.size());
  for (int i = 0; i < db.size(); i ++)
    eachOutcamedb[outcomesMap[db[i].back()]].push_back(db[i]);

  for (int i = 0; i < eachOutcamedb.size(); i ++)
  {
    vector<int> permutation(eachOutcamedb[i].size()); for (int j = 0; j < permutation.size(); j ++) permutation[j] = j;
    random_shuffle(permutation.begin(), permutation.end());
    for (int j = 0, end = eachOutcamedb[i].size() * proportion; j < end; j ++)
      traindb.push_back(eachOutcamedb[i][permutation[j]]);
    for (int j = eachOutcamedb[i].size() * proportion; j < eachOutcamedb[i].size(); j ++)
      testdb.push_back(eachOutcamedb[i][permutation[j]]);
  }
  random_shuffle(traindb.begin(), traindb.end());
  random_shuffle(testdb.begin(), testdb.end());
}