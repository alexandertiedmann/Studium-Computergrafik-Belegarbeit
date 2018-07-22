#pragma once
#ifndef Labyrinth_Header
#define Labyrinth_Header

#include "glm.hpp"
#include <string>
#include "matrix_transform.hpp"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "objects.hpp"
#include "shader.hpp"

#include "ActualLevel.hpp"
#include "ActualGame.hpp"
using namespace std;
using namespace glm;

class Labyrinth {
private:
	glm::mat4 Model; // Walls
	glm::mat4 View; // Camera
	glm::mat4 Projection;
	glm::vec3 cameraPos; // Camera Position
	glm::vec3 cameraFront; // Camera Direction

	glm::mat3 transformMatrixLeft; // Transformationsmatrix Drehung links
	glm::mat3 transformMatrixRight; // Transformmatrionsmatrix Drehung rechts
	glm::vec3 cameraUp;
	GLuint programID;
	ActualLevel level;
	ActualGame game;
	//void keys(unsigned char key, int xmouse, int ymouse);

public:
	Labyrinth();
	Labyrinth(ActualLevel al, ActualGame ag);
	
	void sendMVP();
	void loadLabyrinth();
	void movePlayer(ActualLevel al, char keyPressed);
	bool isPlayerFinished();
	ActualGame getActualGame();
};

#endif