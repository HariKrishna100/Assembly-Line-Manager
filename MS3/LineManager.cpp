#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
using namespace std;
namespace sdds {
   Utilities ut;
   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
      ifstream File(file);
      string data{};
      size_t ps = 0;
      bool other;

      if (!File) {
         throw string("Unable to open file:" + file);
      }

      while (!File.eof()) {
         Workstation* curWorkStn{};
         Workstation* nexWorkStn{};
         string curStation, nexStation;

         getline(File, data);

         if (other) {
            nexStation = ut.extractToken(data, ps, other);
         }
         
         for_each(stations.begin(), stations.end(), [&curWorkStn, &nexWorkStn, curStation, nexStation](Workstation* Ws) {
            if (Ws->getItemName() == nexStation) {
               curWorkStn = Ws;
            }
            else if (Ws->getItemName() == nexStation) {
               nexWorkStn = Ws;
            }
         });

         if (m_activeLine.size() == 0) {
            m_firstStation = curWorkStn;
         }

         curWorkStn->setNextStation(nexWorkStn);
         m_activeLine.push_back(curWorkStn);
      }
      File.close();
   }

   void LineManager::reorderStations() {
      vector<Workstation*> newStations;
      Workstation* lastStation{};
      size_t count = 0;

      while (count < m_activeLine.size()) {
         for (size_t i = 0; i < m_activeLine.size(); i++) {
            newStations.push_back(m_activeLine[i]);
            lastStation = m_activeLine[i];
            count++;
            break;
         }
      }

      reverse(newStations.begin(), newStations.end());
      m_firstStation = newStations[0];
      m_activeLine = newStations;
   }

   bool LineManager::run(std::ostream& os) {
      static size_t counter = 1;

      os << "Line Manager Iteration: " << counter++ << endl;

      if (!g_pending.empty()) {
         (*m_firstStation) += move(g_pending.front());
         g_pending.pop_front();
      }

      for (auto station : m_activeLine) {
         station->fill(os);
      }

      for (auto station : m_activeLine) {
         station->attemptToMoveOrder();
      }

      return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
   }

   void LineManager::display(std::ostream& os) const {
      for (unsigned i = 0; i < m_activeLine.size(); i++)
         m_activeLine[i]->display(os);
   }
}