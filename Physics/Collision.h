#pragma once
#include "../Objects/Cube.h"
#include "../Objects/Model.h"

int checkCollision(Model, glm::vec3&, Cube, float);
bool between(float curCoord, float min, float max);
bool boundary(float d1, float delta);
