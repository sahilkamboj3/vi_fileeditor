#include "../util/fileio.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace currency {
class CurrencyConverter {
public:
  CurrencyConverter(std::string &filepath, std::string &out_currency);
  CurrencyConverter(std::string &filepath);
  ~CurrencyConverter();
  std::vector<std::string> &getInputCurrencies();
  void convertCurrencies();
  std::unordered_map<std::string, double> conversions = {
      {"AUD", 0.72}, {"RUPEE", 0.013}, {"USD", 1.0}};

private:
  std::string _filepath;
  std::string _out_currency;
  util::FileIO _fi;
  std::vector<std::string> *_in_currencies;
  void _getInputCurrencies(const std::string &FILE_PATH);
  void _parseCurrencyPair(double &amount, std::string &currency,
                          const std::string &c_pair);
  void _toUpper(std::string &s);
};
} // namespace currency
