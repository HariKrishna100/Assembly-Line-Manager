#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"
using namespace std;
namespace sdds{
   CustomerOrder::CustomerOrder(std::string& token) {
      Utilities ut;
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
      return false;
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName) const {
      return false;
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os) {

   }

   void CustomerOrder::display(std::ostream& os) const {

   }
}