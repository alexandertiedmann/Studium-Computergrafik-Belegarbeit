#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include "MenuButton.h"
#include "MyMouse.h"
using namespace std;

/*----------------------------------------------------------------------------------------
*	Global Variables
/*----------------------------------------------------------------------------------------
*/
//get Screen Resolution
const long nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
const long nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

/*	This is the button visible in the viewport. Notice that the last data
*	member is a pointer to the above function.
*/
MenuButton continueButton(10, (char*)"Continue", 0, continueGame);
MenuButton newButton(10, (char*)"New", continueButton.y, newGame);
MenuButton saveButton(10, (char*)"Save", newButton.y, saveGame);
MenuButton loadButton(10, (char*)"Load", saveButton.y, loadGame);
MenuButton highscoreButton(10, (char*)"Exit", loadButton.y, showHighs);
MenuButton exitButton(10, (char*)"Exit", highscoreButton.y, CloseWindow);

MenuButton btnMenuList[] = { continueButton, newButton, saveButton, loadButton, highscoreButton, exitButton };
MyMouse theMouse(btnMenuList);

/* 
*	Start new game
*/
void newGame() {

}

/*
*	Load last game
*/
void continueGame() {

}

/*
*	save actual game
*/
void saveGame() {

}

/*
*	load one of the savegames
*/
void loadGame() {

}

/*
*	show the best 10 scores
*/
void showHighs() {

}

/*
*	Quit the game
*/
void CloseWindow() {
	glutDestroyWindow(glutGetWindow());
}

/*----------------------------------------------------------------------------------------
*	\brief	This function is called to initialise opengl.
*/
void Init(){
	glEnable(GL_LIGHT0);
}

/*----------------------------------------------------------------------------------------
*	This function will be used to draw the 3D scene
*/
void Draw3D(){
	gluLookAt(0, 1, 5, 0, 0, 0, 0, 1, 0);
	//glutSolidTeapot(1);
}

/*----------------------------------------------------------------------------------------
*	This function will be used to draw an overlay over the 3D scene.
*	This will be used to draw our fonts, buttons etc......
*/
void Draw2D(){
	exitButton.ButtonDraw();
	//ButtonDraw(&exitButton);
}

/*----------------------------------------------------------------------------------------
*	This is the main display callback function. It sets up the drawing for
*	The 3D scene first then calls the Draw3D() function. After that it switches to
*	an orthographic projection and calls Draw2D().
*/
void Draw(){

	/*
	*	Clear the background
	*/
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);

	/*
	*	Enable lighting and the z-buffer
	*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	/*
	*	Set perspective viewing transformation
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (winh == 0) ? (1) : ((float)winw / winh), 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	/*
	*	Draw the 3D elements in the scene
	*/
	Draw3D();

	/*
	*	Disable depth test and lighting for 2D elements
	*/
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	/*
	*	Set the orthographic viewing transformation
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, winw, winh, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*
	*	Draw the 2D overlay
	*/
	Draw2D();

	/*
	*	Bring the back buffer to the front and vice-versa.
	*/
	glutSwapBuffers();
}

/*----------------------------------------------------------------------------------------
*	This function is called when the window is resized. All this does is simply
*	store the new width and height of the window which are then referenced by
*	the draw function to set the correct viewing transforms
*/
/*void Resize(int w, int h){
	winw = w;
	winh = h;

	
	//	Allow drawing in full region of the screen
	glViewport(0, 0, w, h);
}*/




/*----------------------------------------------------------------------------------------
*
*/
 
int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_BORDERLESS | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	//glutFullScreen();
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(nScreenWidth, nScreenHeight);
	glutCreateWindow("OpenGL Test Window");
	 
	glutDisplayFunc(Draw);
	//glutReshapeFunc(Resize);
	glutMouseFunc(theMouse.MouseButton);
	glutMotionFunc(theMouse.MouseMotion);
	glutPassiveMotionFunc(theMouse.MousePassiveMotion);

	Init();
	 
	glutMainLoop();
	 
	return 0;
}