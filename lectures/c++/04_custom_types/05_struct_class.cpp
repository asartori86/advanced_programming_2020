#include <array>
#include <iostream>
#include <vector>

struct Point_s {
  double x;     // member var.
  double y;
  void print(); //member func.
};  // note ; at the end

void Point_s::print() {
  std::cout << "Structure. x = " << x << "; y = " << y << std::endl;
}

class Point_c {
  double x;
  double y;

 public:
  
  void print() {
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;
  }  // note no ; at the end

};   // note ; at the end

int main() {
  Point_s ps;
  ps.x = 9.9;
  ps.y = 3. / 7;

  ps.print();

  Point_c pc;
  // pc.x =7.6; // error
  pc.print();  // I can access private data through public functions

  Point_s* p = &ps;
  p->x = 0.0;
  p->print();
  (*p).y = 7;

  auto& pr = ps;
  ++pr.x;
  pr.print();

  Point_s array_of_structs[8];  // built-in array
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  Point_s* array_of_pointers[4];
  array_of_pointers[0]=&ps;

  array_of_pointers[0]->print();

  std::array<Point_s, 5> as;
  3[as].x = 3;

  std::vector<Point_s> vs;
  vs.push_back(ps);
  vs[0].x = 999;
  ps.x = 11;
  ps.print();
  vs[0].print();

  return 0;
}
