#include "Menu.hpp"

//get Screen Resolution
const long nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
const long nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);
bool menuOpen = false;

/*----------------------------------------------------------------------------------------
*	\brief	This function is called to initialise opengl.
*/
void Init(){
	glEnable(GL_LIGHT0);
}

void keys(unsigned char key, int xmouse, int ymouse)
{
	switch (key) {
	case 27:
		if (menuOpen) {
			menuOpen = closeMainMenu();
		}
		else {
			menuOpen = callMainMenu();
		}
		break;

	default:
		break;
	}
}
 
int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_BORDERLESS | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(nScreenWidth, nScreenHeight);
	glutCreateWindow("OpenGL Test Window");
	glutKeyboardFunc(keys);

	glewInit();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);

	menuOpen = callMainMenu();

	glutMainLoop();
	
	return 0;
}