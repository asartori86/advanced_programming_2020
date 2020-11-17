# Exercises - session 03

## Matrix transpose

- Write a function that computes the transpose of a matrix. The matrix is represented by a simple `std::array<double,N>` where N is the total size of the matrix (i.e., number of rows times number of columns). The original array must be modified inside the function `transpose`. 

*Hints*: 

- In C/C++, the matrices are accessed row-wise
- You are not required to do the transpose *in place*
- Test with both square and rectangular matrices.
- Use `std::swap` defined in header `<utility>`

## Convert `argv` to types

- Modify the above program such that the number of rows and columns are read from command line arguments.

*Hints*:
 - Use `std::istringstream` defined in the header `<sstream>`

 ```c++
#include <sstream>

std::size_t rows;
{
  std::istringstream is{argv[1]};
  is >> rows;
}
 ```


## Mean and Median

- Store the numbers contained in file `temperatures.txt` into a `std::vector<double>` and compute:
  - the mean
  - the median

*Hints*:

- use `push_back()`
- you can increment a variable using `+=` operator
- you can **sort** the elements of a vector `v` as follows
```c++
#include <algorithm>

std::vector<double> v;
...
std::sort( v.begin(), v.end() );
```


## Avoid repeated words

- Read from stdin a sequence of words. Store each word in a `std::vector<std::string>`. Then, print the words without repetitions.

*Hints*:

- you can print the words in any order you want (i.e., you are not required to print the words in the order you have read them)

## **Optional**: Use `std::map` and `std::unordered_map`

- Read the `LittleWomen.txt` and then print all the read words (without repetitions) followed by the number of repetitions of that word. Compare the time to do the same using `std::vector`, `std::map`, `std::unordered_map`. The order in which the words are printed is **not** relevant.

- You can measure the elapsed time as follows:
```c++
#include <chrono>

auto t0 = std::chrono::high_resolution_clock::now();
...
auto t1 = std::chrono::high_resolution_clock::now();

auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
std::cout << "Elapsed " << elapsed.count() << " [milliseconds]" << std::endl;
```

- You can avoid to repeat `std::chrono::` if you write
```c++

using namespace std::chrono;

auto t0 = high_resolution_clock::now();
```

- Compile with the flag `-O3` (is a capital O, not a zero)


## **Optional**: Conway's Game of Life
- Implement the [Game of Life](https://www.wikidata.org/wiki/Q244615#sitelinks-wikipedia)
- You can slow down your code by forcing a "nap".
```c++
#include <chrono>
#include <thread>
...
std::this_thread::sleep_for (std::chrono::milliseconds(50));
```
