#include "../include/haexa.h"


// Miscellaneous testing stuff while I work


#include <iostream>
#include <random>
using namespace std;


int main() {

  random_device rd;
  std::mt19937 rng;
  rng.seed(rd());

  cout << "Hex rounding" << endl;
  cout.precision(2);
  uniform_real_distribution<double> d_rounding(-1, 1);
  for (int i = 0; i < 10; ++i) {
    // generate some kinda pseudo-sensible decimal hex
    double a = d_rounding(rng) * 10;
    double b = d_rounding(rng) * 10;
    haexa::Hex<double> hex(a, b, -(a + b));
    cout << hex << ' ' << hex.round() << '\t' << (hex.round().valid() ? "ok" : "invalid") << endl;
  }

}
