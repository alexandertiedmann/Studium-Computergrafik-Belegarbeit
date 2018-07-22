#include "Menu.hpp"

//get Screen Resolution
const long nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
const long nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

bool menuOpen = false;
bool labyOpen = false;

/*----------------------------------------------------------------------------------------
*	\brief	This function is called to initialise opengl.
*/
void Init(){
	glEnable(GL_LIGHT0);
}

void getOpenLabyrinth() {
	labyOpen = getLabbyOpen();
}

void keys(unsigned char key, int xmouse, int ymouse) {
	getOpenLabyrinth();
	cout << key << endl;

	if (labyOpen) {
		switch (key) {
		case 27:
			cout << "esc Key was pressed" << endl;
			if (menuOpen) {
				menuOpen = closeMainMenu();
			}
			else {
				menuOpen = callMainMenu();
			}
			break;
		case 'w':
			cout << "w Key was pressed" << endl;
			getLabyrinth().movePlayer(getActualLevelFromLabyrinth(), 'w');
		case 'a':
			cout << "a Key was pressed" << endl;
			 getLabyrinth().movePlayer(getActualLevelFromLabyrinth(), 'a');
		case 'd':
			cout << "d Key was pressed" << endl;
			getLabyrinth().movePlayer(getActualLevelFromLabyrinth(), 'd');
		default:
			break;
		}
	}	
}
 
int main(int argc, char **argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_BORDERLESS | GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(nScreenWidth, nScreenHeight);
	glutCreateWindow("OpenGL Test Window");

	glewInit();
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(renderScene);

	glutKeyboardFunc(keys);

	bool tmp = callMainMenu();

	glutMainLoop();
	
	return 0;
}