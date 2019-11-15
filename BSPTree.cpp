#include "BSPTree.h"
void buildBSPTree(BSPT tree, std::list<Cube> cubes){
  Cube rect = cubes.get(0);
  std::list<Cube> in_fronts, behinds;
  Cube * next;
  int result = 0;
  while(next = &(cubes.get()) != 0)
  {
    result = compare(next); //won't work atm because compare doesn't yet exist
    switch(){
      case IN_FRONT: //in front doesn't yet exist
      in_fronts.add(next);
      break;
      case BEHIND: //ditto
      behinds.add(next);
      break;
      default: //ditto
      break;
    }
  }
  
  //What do I even add here? - Joselito
  
}
