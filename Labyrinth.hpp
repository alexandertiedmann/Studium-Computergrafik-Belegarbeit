class Labyrinth {
private:
	glm::mat4 Model; // Walls
	glm::mat4 View; // Camera
	glm::mat4 Projection;
	GLuint programID;


public:
	Labyrinth(string walls[]);
	

	void sendMVP();

	void drawLabyrinth(string walls[]);
	
	void movePlayer();

	


};