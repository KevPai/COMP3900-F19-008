#include "Cube.h"
struct BSPT {
  Cube pos;
  float** im;
  BSPT * front;
  BSPT * back;
}
void buildBSPTree(BSPT tree, Cube * cubes);
