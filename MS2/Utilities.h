// Name: Harikrishna Paresh Patel
// Seneca Student ID: 150739217
// Seneca email: hpatel296@myseneca.ca
// Date of completion: 16/03/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_
#include <iostream>
namespace sdds {
   class Utilities {
      size_t m_widthField = 1;
      static char m_delimiter;
   public:
      void setFieldWidth(size_t newWidth);
      size_t getFieldWidth() const;
      std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
      static void setDelimiter(char newDelimiter);
      static char getDelimiter();
      std::string rtrim(const std::string str);
      std::string ltrim(const std::string str);
   };
}
#endif // !SDDS_UTILITIES_H_
