#include <iostream>
#include "Workstation.h"
#include "Station.h"
using namespace std;
namespace sdds {
   std::deque<CustomerOrder> g_pending;
   std::deque<CustomerOrder> g_completed;
   std::deque<CustomerOrder> g_incomplete;

   Workstation::Workstation(const string& str) : Station{ str } {}

   void Workstation::fill(std::ostream& os) {
      if (!m_orders.empty())
         m_orders.front().fillItem(*this, os);
   }

   bool Workstation::attemptToMoveOrder() {
      bool success = false;
      if (!m_orders.empty()) {
         if (m_orders.front().isItemFilled(getItemName()) || this->getQuantity() == 0) {
            if (m_pNextStation) {
               *m_pNextStation += move(m_orders.front());
            }
            else {
               if (m_orders.front().isOrderFilled()) {
                  g_completed.emplace_back(move(m_orders.front()));
               }
               else {
                  g_incomplete.emplace_back(move(m_orders.front()));
               }
            }
            m_orders.pop_front();
            success = true;
         }
      }
      return success;
   }

   void Workstation::setNextStation(Workstation* station) {
      m_pNextStation = station;
   }

   Workstation* Workstation::getNextStation() const {
      return m_pNextStation;
   }

   void Workstation::display(std::ostream& os) const {
      os << getItemName();
      os << " --> ";
      (m_pNextStation) ? 
         os << m_pNextStation->getItemName() : os << "End of Line";
      os << endl;
   }

   Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
      m_orders.emplace_back(move(newOrder));
      return *this;
   }
}