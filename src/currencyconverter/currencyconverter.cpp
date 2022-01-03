#include "currencyconverter.h"
#include "../util/print.h"

namespace currency {
CurrencyConverter::CurrencyConverter(std::string &filepath,
                                     std::string &out_currency) {
  _filepath = filepath;
  _toUpper(out_currency);
  _out_currency = out_currency;
  _getInputCurrencies(filepath);
}

CurrencyConverter::CurrencyConverter(std::string &filepath) {
  _filepath = filepath;
  _out_currency = "USD";
  _getInputCurrencies(filepath);
}

CurrencyConverter::~CurrencyConverter() {
  *_in_currencies->erase(_in_currencies->begin(), _in_currencies->end());
  delete _in_currencies;
}

void CurrencyConverter::convertCurrencies() {
  std::vector<std::string> vec;
  for (std::string &currency_pair : *_in_currencies) {
    double amount = 0;
    std::string currency;
    _parseCurrencyPair(amount, currency, currency_pair);
    _toUpper(currency);
    double new_amount = amount * conversions[currency];
    vec.push_back(std::to_string((int)new_amount) + " " + _out_currency);
  }
  _fi.writeToFile(vec);
}

std::vector<std::string> &CurrencyConverter::getInputCurrencies() {
  return *_in_currencies;
}

void CurrencyConverter::_parseCurrencyPair(double &amount,
                                           std::string &currency,
                                           const std::string &c_pair) {
  bool space_reached = false;
  for (const char &c : c_pair) {
    if (c == ' ') {
      space_reached = true;
      continue;
    }
    if (!isalnum(c)) {
      continue;
    }
    if (space_reached) { // add to currency
      currency += c;
    } else {
      amount = (amount * 10) + (c - '0');
    }
  }
}

void CurrencyConverter::_toUpper(std::string &s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](char &c) { return std::toupper(c); });
}

void CurrencyConverter::_getInputCurrencies(const std::string &FILE_PATH) {
  _in_currencies = _fi.readFile(FILE_PATH); // potential leak
}
} // namespace currency
