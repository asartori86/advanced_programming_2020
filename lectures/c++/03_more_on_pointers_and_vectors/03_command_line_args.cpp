#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
  for (auto i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;

  unsigned int a;
  {
    std::istringstream s{argv[1]};
    s >> a;
  }
  std::cout << "a is " << a << std::endl;
  return 0;
}
