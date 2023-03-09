// Name: Harikrishna Paresh Patel
// Seneca Student ID: 150739217
// Seneca email: hpatel296@myseneca.ca
// Date of completion: 16/03/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"
using namespace std;
namespace sdds{
   Utilities ut;
   CustomerOrder::CustomerOrder(std::string& token) {
      size_t ps = 0;
      bool other;

      m_name = ut.extractToken(token, ps, other);
      m_product = ut.extractToken(token, ps, other);
      m_cntItem = stoi(ut.extractToken(token, ps, other));

      std::vector<Item*> itemList;
      do {
         itemList.push_back(new Item(ut.extractToken(token, ps, other)));
      } while (other);

      m_lstItem = new Item * [m_cntItem];

      size_t i{};
      std::for_each(itemList.begin(), itemList.end(), [&](Item* I) {
         m_lstItem[i] = I;
         i++;
      });

      m_widthField = max(ut.getFieldWidth(), m_widthField);
   }

   CustomerOrder::CustomerOrder(CustomerOrder&& toMove) noexcept {
      operator=(move(toMove));
   }

   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& toMove) noexcept {
      if (this != &toMove) {
         for (size_t i = 0; i < m_cntItem; i++) delete m_lstItem[i];
         delete[] m_lstItem;

         m_lstItem = toMove.m_lstItem;
         toMove.m_lstItem = nullptr;
         m_name = toMove.m_name;
         toMove.m_name = nullptr;
         m_product = toMove.m_product;
         toMove.m_product = nullptr;
         m_cntItem = toMove.m_cntItem;
         toMove.m_cntItem = 0;
      }
      return *this;
   }

   CustomerOrder::~CustomerOrder() {
      for (unsigned i = 0; i < m_cntItem; i++) {
         delete m_lstItem[i];
         m_lstItem[i] = nullptr;
      }
      delete[] m_lstItem;
   }

   bool CustomerOrder::isOrderFilled() const {
      return std::all_of(m_lstItem, (m_lstItem + m_cntItem), [](const Item* I) {
         return I->m_isFilled;
      });
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName) const {
      return std::all_of(m_lstItem, (m_lstItem + m_cntItem), [&itemName](Item* I) {
         if (I->m_itemName == itemName) return (I->m_isFilled);
         return true;
      });
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os) {
      bool flag = true;
      std::for_each(m_lstItem, (m_lstItem + m_cntItem), [&](Item* I) {
         if (station.getItemName() == I->m_itemName && flag) {
            if (station.getQuantity() > 0) {
               station.updateQuantity();
               I->m_serialNumber = station.getNextSerialNumber();
               I->m_isFilled = true;
               os << "    Filled " << m_name << ", " << m_product << " [" << I->m_itemName << "]" << endl;
               flag = false;
            }
            else os << "    Unable to fill " << m_name << ", " << m_product << " [" << I->m_itemName << "]" << endl;
         }
      });
   }

   void CustomerOrder::display(std::ostream& os) const {
      os << rtrim(m_name) << " - " << rtrim(m_product) << "\n";
      std::for_each(m_lstItem, (m_lstItem + m_cntItem), [&](Item* I) {
         os << "[" << setw(6) << setfill('0') << I->m_serialNumber << "] " << setfill(' ') << setw(CustomerOrder::m_widthField) << setiosflags(ios::left) << I->m_itemName << resetiosflags(ios::left) << " - ";
         if (I->m_isFilled) 
            os << "FILLED";
         else 
            os << "TO BE FILLED";
         os << endl;
      });
   }

   string rtrim(const std::string str) {
      size_t end = str.find_last_not_of(' ');
      return (end == string::npos) ? "" : str.substr(0, end + 1);
   }
}