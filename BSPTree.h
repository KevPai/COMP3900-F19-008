#include "Cube.h"
#include <list>
struct BSPT {
  Cube pos;
  float** im;
  BSPT * front;
  BSPT * back;
}
void buildBSPTree(BSPT tree, std::list<Cube> cubes);
