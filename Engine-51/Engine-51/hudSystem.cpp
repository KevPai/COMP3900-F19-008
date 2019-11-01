#include "hudSystem.h"
void hudSystem::update() {
	for (hudElement & var : hev)
	{
		if (&var != NULL)
			var.update();
	}
}
int hudSystem::addElement(hudElement& he) {
	hev.emplace_back(he);
}