#ifndef TADPOLE_H
#define TADPOLE_H

#include <vector>
#include "Brain.h"
#include "Object.h"

class Tadpole : public Object {
  public:
    //the constructor
    Tadpole(int nneurons, int x, int y, int hsize, int tsize);
    //the destructor
    ~Tadpole();
    
    //gives the size of the head
    int hsize();
    //gives the size of the tail
    int tsize();

    //set the Tadpole size
    //head
    void set_hsize(int hsize);
    //tail
    void set_tsize(int tsize);
    
    //gives the tadpole head-tip position;
    int xhead1();
    int yhead1();

  private:
    int hsize_;
    int tsize_;
    //the tadpoles brain
    Brain *brain;

};

#endif