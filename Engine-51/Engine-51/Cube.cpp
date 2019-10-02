#include "Header.h"
#include "Shader.h"
#include "stb_image.h"

class Cube {
	public:
		Cube(float initX, float initY, float initZ);
		float getX();
		float getY();
		float getZ();
		glm::mat4 getModel();
		glm::vec3 Move(glm::vec3 v);
	private:	
		glm::mat4 model = glm::mat4(1.0f);
		float x, y, z;
};

Cube::Cube(float initX, float initY, float initZ) {
	x = initX;
	y = initY;
	z = initZ;
}
glm::vec3 Cube::Move(glm::vec3 v) {
	return v;
}

glm::mat4 Cube::getModel() {
	return model;
}

float Cube::getX() {
	return x;
}
float Cube::getY() {
	return y;
}
float Cube::getZ() {
	return z;
}