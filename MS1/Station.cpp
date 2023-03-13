// Name: Harikrishna Paresh Patel
// Seneca Student ID: 150739217
// Seneca email: hpatel296@myseneca.ca
// Date of completion: 13/03/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;
namespace sdds {
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 1;

    Station::Station(string record) {
       Utilities ut;
       size_t ps = 0;
       bool other;
       m_id = id_generator++;

       try {
          m_name = ut.extractToken(record, ps, other);
          m_nextSerial = stoi(ut.extractToken(record, ps, other));
          m_stockQty = stoi(ut.extractToken(record, ps, other));
          m_widthField = max(ut.getFieldWidth(), m_widthField);
          m_desc = ut.extractToken(record, ps, other);
       }
       catch (string& err) {
          cout << err;
       }
    }

    const string& Station::getItemName() const {
       return m_name;
    }

    size_t Station::getNextSerialNumber() {
       return m_nextSerial++;
    }

    size_t Station::getQuantity() const {
       return m_stockQty;
    }

    void Station::updateQuantity() {
       m_stockQty--;
       if (0 > m_stockQty) m_stockQty = 0;
    }

    void Station::display(ostream& os, bool full) const {
       os << setfill('0') << setw(3) << right << m_id;
       os << " | " << setw(m_widthField) << setfill(' ') << left << m_name;
       os << " | " << setfill('0') << setw(6) << right << m_nextSerial << " | ";

       if (full) {
          os << setfill(' ') << setw(4) << right << m_stockQty << " | ";
          os << left << m_desc << endl;
       }
       else {
          os << endl;
       }
    }
}