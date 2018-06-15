#include "MyMouse.h"

MyMouse::MyMouse(MenuButton* btnList){
	x = 0;		/*	the x coordinate of the mouse cursor	*/
	y = 0;		/*	the y coordinate of the mouse cursor	*/
	lmb = 0;	/*	is the left button pressed?		*/
	mmb = 0;	/*	is the middle button pressed?	*/
	rmb = 0;	/*	is the right button pressed?	*/
	for (int i = 0; i < 5; i++)
		btnMenuList[i] = btnList[i];
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever a mouse button is pressed or released
*	\param	button	-	GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, or GLUT_MIDDLE_BUTTON
*	\param	state	-	GLUT_UP or GLUT_DOWN depending on whether the mouse was released
*						or pressed respectivly.
*	\param	x		-	the x-coord of the mouse cursor.
*	\param	y		-	the y-coord of the mouse cursor.
*/
void MyMouse::MouseButton(int button, int state, int x, int y) {
	/*
	*	update the mouse position
	*/
	x = x;
	y = y;

	/*
	*	has the button been pressed or released?
	*/
	if (state == GLUT_DOWN) {
		/*
		*	This holds the location of the first mouse click
		*/
		if (!(lmb || mmb || rmb)) {
			xpress = x;
			ypress = y;
		}

		/*
		*	Which button was pressed?
		*/
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			lmb = 1;
			for (int x = 0; x <= sizeof(btnMenuList); x++) {
				MenuButton ele = btnMenuList[x];
				ele.ButtonPress(x, y);
			}
		case GLUT_MIDDLE_BUTTON:
			mmb = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			rmb = 1;
			break;
		}
	}
	else {
		/*
		*	Which button was released?
		*/
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			lmb = 0;
			for (int x = 0; x <= sizeof(btnMenuList); x++) {
				MenuButton ele = btnMenuList[x];
				ele.ButtonRelease(x, y, xpress, ypress);
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			mmb = 0;
			break;
		case GLUT_RIGHT_BUTTON:
			rmb = 0;
			break;
		}
	}
	/*
	*	Force a redraw of the screen. If we later want interactions with the mouse
	*	and the 3D scene, we will need to redraw the changes.
	*/
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever the mouse cursor is moved AND A BUTTON IS HELD.
*	\param	x	-	the new x-coord of the mouse cursor.
*	\param	y	-	the new y-coord of the mouse cursor.
*/
void MyMouse::MouseMotion(int x, int y) {
	/*
	*	Calculate how much the mouse actually moved
	*/
	int dx = x - x;
	int dy = y - y;

	/*
	*	update the mouse position
	*/
	x = x;
	y = y;


	/*
	*	Check MyButton to see if we should highlight it cos the mouse is over it
	*/
	for (int x = 0; x <= sizeof(btnMenuList); x++) {
		MenuButton ele = btnMenuList[x];
		ele.ButtonPassive(x, y);
	}

	/*
	*	Force a redraw of the screen
	*/
	glutPostRedisplay();
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called whenever the mouse cursor is moved AND NO BUTTONS ARE HELD.
*	\param	x	-	the new x-coord of the mouse cursor.
*	\param	y	-	the new y-coord of the mouse cursor.
*/
void MyMouse::MousePassiveMotion(int x, int y) {
	/*
	*	Calculate how much the mouse actually moved
	*/
	int dx = x - x;
	int dy = y - y;

	/*
	*	update the mouse position
	*/
	x = x;
	y = y;

	/*
	*	Check MyButton to see if we should highlight it cos the mouse is over it
	*/
	for (int x = 0; x <= sizeof(btnMenuList); x++) {
		MenuButton ele = btnMenuList[x];
		ele.ButtonPassive(x, y);
	}
}