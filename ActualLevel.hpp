#pragma once

#define ActualLevel_Header

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "File.hpp"
using namespace std;

class ActualLevel{
private:
	vector<vector<char>> level;
	int width;
	int height;
public:
	ActualLevel();
	ActualLevel(vector<vector<char>> lvl);
	string toString();
	vector<vector<char>> getLevel();
	int getLevelHeight();
	int getLevelWidth();
};

