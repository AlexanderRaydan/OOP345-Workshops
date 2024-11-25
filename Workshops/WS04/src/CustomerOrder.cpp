#include "CustomerOrder.h"
#include <iomanip>
#include <utility>
#include <vector>

namespace seneca
{

    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr) {}

    CustomerOrder::CustomerOrder(const CustomerOrder &)
    {
        throw std::runtime_error("Error: copy constructor is not allowed");
    }

    CustomerOrder::CustomerOrder(const std::string &record)
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(record, next_pos, more);

        m_product = util.extractToken(record, next_pos, more);

        std::vector<std::string> items;
        while (more)
        {
            items.push_back(util.extractToken(record, next_pos, more));
        }

        m_cntItem = items.size();
        m_lstItem = new Item *[m_cntItem];
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            m_lstItem[i] = new Item(items[i]);
        }

        // Update m_widthField
        if (util.getFieldWidth() > m_widthField)
        {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::~CustomerOrder()
    {
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept
    {
        *this = std::move(other);
    }

    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept
    {
        if (this != &other)
        {
            // Release current resources
            for (size_t i = 0; i < m_cntItem; ++i)
            {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            other.m_lstItem = nullptr;
            other.m_cntItem = 0;
        }
        return *this;
    }

    bool CustomerOrder::isOrderFilled() const
    {
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            if (!m_lstItem[i]->m_isFilled)
            {
                return false;
            }
        }
        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string &itemName) const
    {
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
            {
                return false;
            }
        }
        return true;
    }

    void CustomerOrder::fillItem(Station &station, std::ostream &os)
    {
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)
            {
                if (station.getQuantity() > 0)
                {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                    return;
                }
                else
                {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream &os) const
    {
        os << m_name << " - " << m_product << "\n";
        for (size_t i = 0; i < m_cntItem; ++i)
        {
            os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
               << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - "
               << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << "\n";
        }
    }

} // namespace seneca
