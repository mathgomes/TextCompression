#ifndef BWT_H
#define BWT_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <sstream>
#include <cstring>

using namespace std;

void BWTencode(string input_name, stringstream& output_ss, int block_size);
void BWTdecode(stringstream& input_ss, string output_name);


#endif