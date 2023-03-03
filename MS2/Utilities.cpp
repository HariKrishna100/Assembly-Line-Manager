#include <iostream>
#include "Utilities.h"
using namespace std;
namespace sdds {
    string whitespace = " \n\r\t\f\v";

    string ltrim(string& str) {
       size_t start = str.find_first_not_of(whitespace);
       return (start == string::npos) ? "" : str.substr(start);
    }

    void Utilities::setFieldWidth(size_t newWidth) {
       m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
       return m_widthField;
    }

    std::string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
       size_t idx = (str.find(getDelimiter(), next_pos));
       string etc = str.substr(next_pos, idx - next_pos);
       etc = ltrim(etc);

       if (idx == next_pos) {
          more = false;
          throw string("Failed to find the delimiter");
       }

       next_pos = idx + 1;
       setFieldWidth(max(m_widthField, etc.size()));
       more = idx != string::npos;

       return etc;
    }

    void Utilities::setDelimiter(char newDelimiter) {
       m_delimiter - newDelimiter;
    }

    char Utilities::getDelimiter() {
       return m_delimiter;
    }
}