#pragma once
#ifndef ActualGame_Header
#define ActualGame_Header

#include "DateTime.hpp"
#include <string>

using namespace std;

class ActualGame
{
private:
	time_t starttime;

public:
	//Variables:
	int xCoord;
	int yCoord;
	int level;
	int view;
	double playtime;
	DateTime savedate;
	DateTime startdate;
	//Methods:
	ActualGame();
	ActualGame(int x, int y, int lvl, int perspective, double time, DateTime savedate, DateTime start);
	double diffTime(time_t startTime, time_t endTime);
	void startTimer();
	void stopTimer();
	string toString();
};

#endif