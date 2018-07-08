#include "Labyrinth.hpp"
#include "glm.hpp"
#include <string>
#include "matrix_transform.hpp"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
using namespace std;
using namespace glm;

class Labyrinth {
private:
	glm::mat4 Model; // Walls
	glm::mat4 View; // Camera
	glm::mat4 Projection;
	GLuint programID;


public:
	Labyrinth(string walls[]) {
		
		drawLabyrinth(walls);
	}

	void sendMVP()
	{
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 MVP = Projection * View * Model;
		
		glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]); // Ist das richtig?
	    

		/*glUniformMatrix4fv(glGetUniformLocation(programID, "M"), 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programID, "V"), 1, GL_FALSE, &View[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programID, "P"), 1, GL_FALSE, &Projection[0][0]);*/ //Brauche ich das?
	}

	void drawLabyrinth(string walls[])
	{
		Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		View = glm::lookAt(glm::vec3(0, 0, -5), // Camera is at (0,0,-5), in World Space
			glm::vec3(0, 0, 0),  // and looks at the origin
			glm::vec3(0, 1, 0)); // Head is up (set to 0,-1,0 to look upside-down)
		Model = glm::mat4(1.0f);
		string *ptr;
		ptr = walls;
		double xpos = 0.0;
		double zpos = 0.0;

		int rootArray = std::sqrt(sizeof(walls));
		for (int i = 0; i < sizeof(walls); i++) {
			if (i + 1 % rootArray == 0) {
				zpos++;
				xpos = 0;
			}
			if (*ptr == "X") {
				Model = glm::translate(Model, glm::vec3(xpos, 0.0, zpos));
				sendMVP();
			}

			xpos++;
			ptr++;
		}
	}
	bool movePlayer() {

	}

	
};




