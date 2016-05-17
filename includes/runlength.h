#ifndef RL_H
#define RL_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <sstream>
#include <cstring>
#include <climits>

using namespace std;

void RLcompress(stringstream& input_ss, stringstream& output_ss);
void RLdecompress(stringstream& input_ss, stringstream& output_ss);

#endif