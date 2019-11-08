#include "Collision.h"

int checkCollision(Model player, glm::vec3& position, Cube toTest, float scale) {
	if (boundary(position.x - toTest.getX(),
		(position.y - toTest.getY()))) {
		if (between((position.z + player.getDimZ()[0] * scale) - toTest.getZ(), 0.0f, 0.03f)) {
			return 3;
		}
		else if (between((position.z + player.getDimZ()[1] * scale) - toTest.getZ(), -0.5f, 0.0f)) {
			return -3;
		}
	}
	else if (boundary(position.y - toTest.getY(),
		(position.z - toTest.getZ()))) {
		if (between((position.x + player.getDimX()[0] * scale) - toTest.getX(), -0.5f, 0.0f)) {
			return 1;
		}
		else if (between((position.x + player.getDimX()[1] * scale) - toTest.getX(), 0.0f, 0.5f)) {
			return -1;
		}
	}
}

bool boundary(float d1, float d2) {
	return abs(d1) < 1.0f && abs(d2) < 1.0f;
}
bool between(float curCoord, float min, float max) {
	return curCoord > min && curCoord < max;
}
