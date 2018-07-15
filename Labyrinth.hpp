class Labyrinth {
private:
	glm::mat4 Model; // Walls
	glm::mat4 View; // Camera
	glm::mat4 Projection;
	GLuint programID;


public:
	Labyrinth(ActualLevel al);
	

	void sendMVP();

	void drawLabyrinth(ActualLevel al);
	
	void movePlayer();

	


};