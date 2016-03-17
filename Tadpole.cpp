#include "Tadpole.h"

Tadpole::Tadpole(int nneurons, int x, int y, int hsize, int tsize) : Object(x,y){
  hsize_ = hsize;
  tsize_ = tsize;

  brain = new Brain(nneurons,2,2);
  saveDimensions();
}

int Tadpole::hsize() {
  return hsize_;
}

int Tadpole::tsize() {
  return tsize_;
}

int Tadpole::xhead1() {
  std::vector<int> temp;
  temp = this->get_point(1);
  //return x-value
  return temp[0];
}

int Tadpole::yhead1() {
  std::vector<int> temp;
  temp = this->get_point(1);
  //return y value
  return temp[1];
}

/*
int Tadpole::

    // x2 and y2 marks the end of the head
    float xhead2f = xhead1f - (float)tad->hsize();
    float yhead2f = yhead1f;
    float xnose1f = xhead1f + (float)tad->hsize();
    float ynose1f = yhead1f;
    float xeye1f = xnose1f + 100.0f;
    float yeye1f = ynose1f + 50.0f;
    float xeye2f = xnose1f + 100.0f;
    float yeye2f = ynose1f - 50.0f;
    
    //tail start
    float xtail1f = xhead2f;
    float ytail1f = yhead2f;
    //tail end
    float xtail2f = xhead2f - (float)tad->tsize();
    float ytail2f = yhead2f;
*/

Tadpole::~Tadpole() {

}