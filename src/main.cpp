#include "currencyconverter/currencyconverter.h"
#include "window/window.h"
#include <string>
#include <vector>

int main() {
  std::string filepath = "in.txt";
  currency::CurrencyConverter cc(filepath);
  window::Window w;

  cc.convertCurrencies();
  w.Run();
  w.RunPythonScript("src/test.py");
  return 0;
}
