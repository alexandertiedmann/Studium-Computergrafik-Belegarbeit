#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include "MenuButton.h"
using namespace std;

class MyMouse{
public:
	MyMouse(MenuButton btnList[]);
	void MouseButton(int button, int state, int x, int y);
	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
private:
	MenuButton* btnMenuList;
	int x;		/*	the x coordinate of the mouse cursor	*/
	int y;		/*	the y coordinate of the mouse cursor	*/
	int lmb;	/*	is the left button pressed?		*/
	int mmb;	/*	is the middle button pressed?	*/
	int rmb;	/*	is the right button pressed?	*/
				/*
				*	These two variables are a bit odd. Basically I have added these to help replicate
				*	the way that most user interface systems work. When a button press occurs, if no
				*	other button is held down then the co-ordinates of where that click occured are stored.
				*	If other buttons are pressed when another button is pressed it will not update these
				*	values.
				*
				*	This allows us to "Set the Focus" to a specific portion of the screen. For example,
				*	in maya, clicking the Alt+LMB in a view allows you to move the mouse about and alter
				*	just that view. Essentually that viewport takes control of the mouse, therefore it is
				*	useful to know where the first click occured....
				*/
	int xpress; /*	stores the x-coord of when the first button press occurred	*/
	int ypress; /*	stores the y-coord of when the first button press occurred	*/
};

