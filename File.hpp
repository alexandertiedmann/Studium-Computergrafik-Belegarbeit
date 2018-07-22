#pragma once
#ifndef File_Header
#define File_Header

#include "DateTime.hpp"
#include "ActualGame.hpp"
#include "ActualLevel.hpp"
#include <algorithm> 
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <vector>

using namespace std;

DateTime readSavedate(int savenum);
ActualGame readSave(int savenum);
ActualLevel readLevel(int levelnum);
void writeGame(int levelnum, ActualGame game);
void addHighscore(int);
vector<int> readScores(int numScores);

#endif