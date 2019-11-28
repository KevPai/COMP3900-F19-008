#include "Collision.h"
float front, back;

int checkCollision(Model player, glm::vec3& position, Cube toTest, float scale) {	
	front = player.getDimZ()[0] * scale + 0.5f;
	back  = player.getDimZ()[1] * scale - 0.5f;
	if ( boundary(position.x - toTest.getX() , player.getDimX()[0] * scale + 0.5f)) {
		if ( between( (position.z + player.getDimZ()[0] * scale) - toTest.getZ(), back, front)) {
			return 3;
		}
		if (between( (position.z + player.getDimZ()[1] * scale) - toTest.getZ(), back, front)) {
			return -3;
		}
	}
	else if (boundary( position.z - toTest.getZ() , player.getDimX()[0] * scale + 0.5f)) {
		if (between((position.x + player.getDimX()[0] * scale) - toTest.getX(), back, front)) {
			return 1;
		}
		if (between((position.x + player.getDimX()[1] * scale) - toTest.getX(), back, front)) {
			return -1;
		}
	}
	return 0;
}

bool boundary(float d1, float delta) {	
	return abs(d1) < delta;
}
bool between(float curCoord, float min, float max) {
	return (curCoord > min && curCoord < max);
}