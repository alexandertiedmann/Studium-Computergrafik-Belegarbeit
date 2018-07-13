#pragma once
#ifndef ActualLevel_Header
#define ActualLevel_Header

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

class ActualLevel{
private:
	vector<vector<char>> level;
	int width;
	int height;
public:
	ActualLevel(vector<vector<char>> lvl);
	string toString();
};

#endif