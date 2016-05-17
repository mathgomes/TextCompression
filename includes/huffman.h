#ifndef _HUF_H
#define _HUF_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <sstream>
#include <cstring>
#include <utility>
#include <bitset>

using namespace std;

struct node {
    node* left_child;
    node* right_child;
    int freq;
    char ch;
    string code;
};

typedef pair<int, node*> PAIR;
typedef pair<string, char> STR_PAIR;

class Comparator
{
    public:
        bool operator()(const PAIR& p1, const PAIR& p2) { // <freq, node>
            if(p1.first!=p2.first)
                return p1.first>p2.first;
            else {
                return p1.second->ch > p2.second->ch;
            }
        }
};

void applyHuffman(stringstream& input_ss, stringstream& output_ss);
void getOrderedFrequencies(stringstream& input_ss, priority_queue<PAIR, vector<PAIR>, Comparator >& ordered_freqs, stringstream& output_ss);
void bfs(node* n, map<char, string>& codes);
void decodeHuffman(stringstream& input_ss, stringstream& output_ss);

#endif