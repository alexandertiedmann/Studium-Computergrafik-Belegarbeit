#include "DateTime.hpp"
/*
*	\brief	Construktor for new date
*/
DateTime::DateTime(){
	time_t theTime = time(NULL);
	struct tm *aTime;
	aTime = localtime(&theTime);

	year = aTime->tm_year + 1900; // Year is # years since 1900
	month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	day = aTime->tm_mday;
	hour = aTime->tm_hour;
	minute = aTime->tm_min;
	/*
	year = 1900;
	month = 01;
	day = 03;
	hour = 06;
	minute = 05;
	*/
}

/*
*	\brief	Construktor for date from file
*	\param	stringdate	-	The date in format "YYYY-MM-DD HH:MM"
*/
DateTime::DateTime(string stringdate) {
	ostringstream  temp;
	//year
	temp << stringdate[0] << stringdate[1] << stringdate[2] << stringdate[3] << endl;
	year = stoi(temp.str());
	//month
	temp.str("");
	temp << stringdate[5] << stringdate[6] << endl;
	month = stoi(temp.str());
	//day
	temp.str("");
	temp << stringdate[8] << stringdate[9] << endl;
	day = stoi(temp.str());
	//hours
	temp.str("");
	temp << stringdate[11] << stringdate[12] << endl;
	hour = stoi(temp.str());
	//minutes
	temp.str("");
	temp << stringdate[14] << stringdate[15] << endl;
	minute = stoi(temp.str());
}


/*
*	\brief sets a Array for teh current date
*/
void DateTime::setCurrentDate() {
	time_t theTime = time(NULL);
	struct tm *aTime;
	aTime = localtime(&theTime);

	year = aTime->tm_year + 1900; // Year is # years since 1900
	month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	day = aTime->tm_mday;
	hour = aTime->tm_hour;
	minute = aTime->tm_min;
}

/*
*	\brief returns the value of the date
*	\param	y = year	
*			m = month
*			d = day
*			h = hour
*			t = minute
*/
int DateTime::getDate(char v) {
	switch(v) {
		case 'y':
			return year;
		case 'm':
			return month;
		case 'd':
			return day;
		case 'h':
			return hour;
		case 't':
			return minute;
	}
	return 0;
}

/*
*	\brief	returns the string from the date in format "YYYY-MM-DD HH:MM"
*/
string DateTime::toString() {
	ostringstream  date;
	date << year << "-" << month << "-" << day << " " << hour << ":" << minute;
	return date.str();
}

/*
*	\brief	returns the youngest DateTime
*/
DateTime getYoungest(DateTime one, DateTime two) {
	//check year
	if (one.getDate('y') == two.getDate('y')) {
		//check month
		if (one.getDate('m') == two.getDate('m')) {
			//check day
			if (one.getDate('d') == two.getDate('d')) {
				//check hour
				if (one.getDate('h') == two.getDate('h')) {
					//check minute
					if (one.getDate('t') == two.getDate('t')) {
						//if minutes same --> first
						return one;
					}
					else { //if minute not ==
						if (one.getDate('t') < two.getDate('t')) {
							return two;
						}
						else {
							return one;
						}
					}
				}
				else { //if hour not ==
					if (one.getDate('h') < two.getDate('h')) {
						return two;
					}
					else {
						return one;
					}
				}
			}
			else { //if day not ==
				if (one.getDate('d') < two.getDate('d')) {
					return two;
				}
				else {
					return one;
				}
			}
		}
		else { //if month not ==
			if (one.getDate('m') < two.getDate('m')) {
				return two;
			}
			else {
				return one;
			}
		}
	}
	else { //if year not ==
		if (one.getDate('y') < two.getDate('y')) {
			return two;
		}
		else {
			return one;
		}
	}
}


int getHours(int seconds) {
	return seconds / 3600;
}

int getMinutes(int seconds, int hours) {
	return (seconds - (hours * 3600)) / 60;
}

int getSeconds(int seconds, int hours, int minutes) {
	return (seconds - (hours * 3600)) - (minutes * 60);
}

string getTimeFromSec(int seconds) {
	ostringstream time;
	//hours
	int hours = getHours(seconds);
	string hour = to_string(hours);
	if (hour.length() < 2) {
		hour = "0" + to_string(hours);
	}
	//minutes
	int minutes = getMinutes(seconds, hours);
	string minute = to_string(minutes);
	if (minute.length() < 2) {
		minute = "0" + to_string(minutes);
	}
	//seconds
	int sec = getSeconds(seconds, hours, minutes);
	string second = to_string(sec);
	if (second.length() < 2) {
		second = "0" + to_string(sec);
	}
	//to string
	time << hour << ":" << minute << ":" << second;
	return time.str();
}