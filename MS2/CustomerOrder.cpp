#include <iostream>
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
   }

   CustomerOrder::CustomerOrder(CustomerOrder&& toMove) noexcept {

   }

   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& toMove) noexcept {
      
   }

   CustomerOrder::~CustomerOrder() {

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