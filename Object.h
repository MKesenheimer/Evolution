#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

class Object {
  public:
    //the constructor
    Object(int x, int y);
    //the destructor
    ~Object();
    
    //gives the x and y position in the 2 dimensional world
    int x();
    int y();
    //gives the velocity in x- and y-direction
    int vx();
    int vy();
    
    //set the x and y position in the 2 dimensional world
    void set_pos(int x, int y);
    void set_v(int vx, int vy);
    
    //update the new position of the Object
    void update_position();
    
    //save a new coordinate and remember the index
    void save_point(int x, int y, int n);
    std::vector<int> get_point(int n);

    //save the dimension of the tadpole, for example the position of the eyes
    //etc. in respect to x- and y-coordinates
    void saveDimensions();

  private:
    int x_;
    int y_;
    int vx_;
    int vy_;
    
    std::vector<int> points;
};

#endif