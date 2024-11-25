#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include "Utilities.h"
#include "Station.h"

namespace seneca
{

    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string &src) : m_itemName(src) {}
    };

    class CustomerOrder
    {
        std::string m_name;
        std::string m_product;
        size_t m_cntItem{0};
        Item **m_lstItem{nullptr};
        static size_t m_widthField;

    public:
        CustomerOrder();

        CustomerOrder(const std::string &record);

        CustomerOrder(const CustomerOrder &);

        ~CustomerOrder();

        CustomerOrder(CustomerOrder &&) noexcept;

        CustomerOrder &operator=(CustomerOrder &&) noexcept;

        bool isOrderFilled() const;
        bool isItemFilled(const std::string &itemName) const;
        void fillItem(Station &station, std::ostream &os);
        void display(std::ostream &os) const;
    };

} // namespace seneca

#endif
