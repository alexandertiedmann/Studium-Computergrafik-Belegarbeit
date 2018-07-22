#include "Menu.hpp"

//get Screen Resolution
const long nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
const long nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

bool menuOpen = getMenuOpen();
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

	if (labyOpen) {
		switch (key) {
		case 27:
			cout << "esc Key was pressed" << endl;
			if (menuOpen) {
				setMenuOpen(closeMainMenu());
			}
			else {
				setMenuOpen(callMainMenu());
			}
			break;
		case 'w':
			cout << "w Key was pressed" << endl;
			getLabyrinth().movePlayer('w');
			break;
		case 'a':
			cout << "a Key was pressed" << endl;
			getLabyrinth().movePlayer('a');
			break;
		case 'd':
			cout << "d Key was pressed" << endl;
			getLabyrinth().movePlayer('d');
			break;
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

	setMenuOpen(callMainMenu());

	glutMainLoop();
	
	return 0;
}