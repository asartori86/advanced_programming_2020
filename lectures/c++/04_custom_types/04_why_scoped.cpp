#include <iostream>

enum class month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

// using namespace std;
using std::cout;
using std::endl;

int main() {
  cout << month::nov << endl; 
  cout << month::dec << endl;

  return 0;
}
