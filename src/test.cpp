#include <armadillo>
#include <iostream>

using namespace arma;
using namespace std;

int main(int argc,char** argv)
{
 mat particles=randu<mat>(100,1);
 particles = particles * 3.14;
 cout << particles;
  return 0;
}
