// Name: Harikrishna Paresh Patel
// Seneca Student ID: 150739217
// Seneca email: hpatel296@myseneca.ca
// Date of completion: 16/03/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_
#include <iostream>
namespace sdds {
   class Station {
      int m_id;
      std::string m_name;
      std::string m_desc;
      unsigned m_nextSerial;
      unsigned m_stockQty;
      static size_t m_widthField;
      static size_t id_generator;
   public:
      Station(std::string record);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;
   };
}
#endif // !SDDS_STATION_H_
