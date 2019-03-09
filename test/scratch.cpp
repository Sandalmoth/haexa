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

  cout << "\nHex addition" << endl;
  uniform_int_distribution<int> d_sum(-3, 3);
  for (int i = 0; i < 5; ++i) {
    int a1 = d_sum(rng);
    int b1 = d_sum(rng);
    int a2 = d_sum(rng);
    int b2 = d_sum(rng);
    haexa::Hex<int> h1(a1, b1, -(a1 + b1));
    haexa::Hex<int> h2(a2, b2, -(a2 + b2));
    cout << h1 << " + " << h2 << " = " << h1 + h2 << '\t' << ((h1 + h2).valid() ? "ok" : "invalid") << endl;
  }

  cout << "\nHex subtraction" << endl;
  for (int i = 0; i < 5; ++i) {
    int a1 = d_sum(rng);
    int b1 = d_sum(rng);
    int a2 = d_sum(rng);
    int b2 = d_sum(rng);
    haexa::Hex<int> h1(a1, b1, -(a1 + b1));
    haexa::Hex<int> h2(a2, b2, -(a2 + b2));
    cout << h1 << " + " << h2 << " = " << h1 - h2 << '\t' << ((h1 - h2).valid() ? "ok" : "invalid") << endl;
  }

  cout << "\nHex scalar multiplication" << endl;
  cout.precision(2);
  for (int i = 0; i < 10; ++i) {
    // generate some kinda pseudo-sensible decimal hex
    int a = d_sum(rng);
    int b = d_sum(rng);
    double z = d_rounding(rng) * 3;
    haexa::Hex<int> hex(a, b, -(a + b));
    cout << hex << " * " << z << " = " << hex*z << " = "
         << (hex*z).round() << '\t' << ((hex*z).round().valid() ? "ok" : "invalid") << endl;
  }

  cout << "\nHex scalar division" << endl;
  cout.precision(2);
  for (int i = 0; i < 10; ++i) {
    // generate some kinda pseudo-sensible decimal hex
    int a = d_sum(rng);
    int b = d_sum(rng);
    double z = d_rounding(rng) * 3;
    haexa::Hex<int> hex(a, b, -(a + b));
    cout << hex << " / " << z << " = " << hex*z << " = "
         << (hex/z).round() << '\t' << ((hex/z).round().valid() ? "ok" : "invalid") << endl;
  }
}
