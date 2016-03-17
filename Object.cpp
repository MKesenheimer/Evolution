#include "Object.h"
#include <iostream>

Object::Object(int x, int y) {
  x_ = x;
  y_ = y;
}

int Object::x() {
  return x_;
}

int Object::y() {
  return y_;
}

int Object::vx() {
  return vx_;
}

int Object::vy() {
  return vy_;
}

void Object::set_pos(int x, int y) {
  x_ = x;
  y_ = y;
}

void Object::set_v(int vx, int vy) {
  vx_ = vx;
  vy_ = vy;
}

void Object::update_position() {
  x_ = x_ + vx_;
  y_ = y_ + vy_;
  saveDimensions();
}

void Object::save_point(int x, int y, int n) {
  points.push_back(n);
  points.push_back(x);
  points.push_back(y);
}

std::vector<int> Object::get_point(int n) {
  std::vector<int> retv;

  for (int i=0; i<n; i += 3) {
    if (points[i] == n) {
      retv.push_back(points[i+1]);
      retv.push_back(points[i+2]);
      
      return retv;
    }
  }
  
  std::cout<<"an error occured in Object.cpp: n="<<n<<" is not a valid index"<<std::endl;
  return points;
}

void Object::saveDimensions() {
  //head
  save_point(x_,y_,1);
}

Object::~Object() {

}