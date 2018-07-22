#pragma once
#ifndef DataTime_Header
#define DataTime_Header


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <time.h>
#include <string>

using namespace std;

class DateTime{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
public:
	DateTime();
	DateTime(string stringdate);
	string toString();
	void setCurrentDate();
	int getDate(char v);
};

DateTime getYoungest(DateTime one, DateTime two);

int getHours(int seconds);
int getMinutes(int seconds, int hours);
int getSeconds(int seconds, int hours, int minutes);
string getTimeFromSec(int seconds);

#endif