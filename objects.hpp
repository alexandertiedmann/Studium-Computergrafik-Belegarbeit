#ifndef OBJECTS_HPP
#define OBJECTS_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "Dependencies\glew\glew.h" // Include GLEW
#include "Dependencies\freeglut\freeglut.h"

void drawWireCube(); // Wuerfel mit Kantenlaenge 2 im Drahtmodell
void drawCube();     // Bunter Wuerfel mit Kantenlaenge 2
//void drawSphere(GLuint slices, GLuint stacks); // Kugel mit radius 1 bzw. Durchmesser 2

#endif
