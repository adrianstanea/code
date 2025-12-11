export module calculator;

import std;

export {
  // Add your exported functions/variables here
  void hello_from_calculator();
}

// Implementation (not exported)
void hello_from_calculator() {
  std::print("Hello from calculator module in day1!\n");
}
