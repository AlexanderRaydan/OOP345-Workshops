#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca
{

    // Global variables
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;
        Workstation *m_pNextStation{nullptr};

    public:
        Workstation(const std::string &str) : Station(str) {}

        Workstation(const Workstation &) = delete;
        Workstation &operator=(const Workstation &) = delete;
        Workstation(Workstation &&) = delete;
        Workstation &operator=(Workstation &&) = delete;

        // Member functions
        void fill(std::ostream &os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation *station = nullptr);
        Workstation *getNextStation() const;
        void display(std::ostream &os) const;
        Workstation &operator+=(CustomerOrder &&newOrder);
    };

} // namespace seneca

#endif
