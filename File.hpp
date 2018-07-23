#pragma once
#ifndef File_Header
#define File_Header


#define WIN32_LEAN_AND_MEAN
// reduces the size of the Win32 header files by
// excluding some of the less frequently used APIs
#include <windows.h>
#include <tchar.h>
#include "DateTime.hpp"
#include "ActualGame.hpp"
#include "ActualLevel.hpp"
#include <algorithm> 
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h> // for getcwd
#include <stdlib.h>  // for MAX_PATH
#include <vector>

using namespace std;

DateTime readSavedate(int savenum);
ActualGame readSave(int savenum);
ActualLevel readLevel(int levelnum);
void writeGame(int levelnum, ActualGame game);
void addHighscore(int);
vector<int> readScores(int numScores);
int dirExists(const string& dirName);
void checkDirectory(string directory);

#endif