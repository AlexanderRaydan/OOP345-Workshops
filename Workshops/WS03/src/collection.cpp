#include "collection.h"
#include <algorithm>

namespace seneca
{
    Collection::Collection(const std::string &name) : m_name{name} {}

    Collection::~Collection()
    {
        for (auto *item : m_items)
        {
            delete item;
        }
    }

    const std::string &Collection::name() const { return m_name; }

    size_t Collection::size() const { return m_items.size(); }

    void Collection::setObserver(void (*observer)(const Collection &, const MediaItem &))
    {
        m_observer = observer;
    }

    Collection &Collection::operator+=(MediaItem *item)
    {
        auto it = std::find_if(m_items.begin(), m_items.end(),
                               [item](const MediaItem *existingItem)
                               { return existingItem->getTitle() == item->getTitle(); });

        if (it == m_items.end())
        {
            m_items.push_back(item);

            if (m_observer)
            {
                m_observer(*this, *item);
            }
        }
        else
        {
            delete item;
        }
        return *this;
    }

    MediaItem *Collection::operator[](size_t idx) const
    {
        if (idx >= m_items.size())
        {
            throw "Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_items.size()) + "] items.";
        }
        return m_items[idx];
    }

    MediaItem *Collection::operator[](const std::string &title) const
    {
        auto it = std::find_if(m_items.begin(), m_items.end(),
                               [title](const MediaItem *item)
                               {
                                   return item->getTitle() == title;
                               });
        return (it != m_items.end()) ? *it : nullptr;
    }

    void Collection::removeQuotes()
    {
        auto removeQuotesLambda = [](std::string str) -> std::string
        {
            if (!str.empty() && str.front() == '"')
            {
                str = str.substr(1);
            }
            if (!str.empty() && str.back() == '"')
            {
                str = str.substr(0, str.size() - 1);
            }
            return str;
        };

        std::transform(m_items.begin(), m_items.end(), m_items.begin(),
                       [=](MediaItem *item)
                       {
                           item->setTitle(removeQuotesLambda(item->getTitle()));
                           item->setSummary(removeQuotesLambda(item->getSummary()));
                           return item;
                       });
    }

    void Collection::sort(const std::string &field)
    {
        std::sort(m_items.begin(), m_items.end(),
                  [field](const MediaItem *a, const MediaItem *b)
                  {
                      if (field == "title")
                          return a->getTitle() < b->getTitle();

                      if (field == "year")
                          return a->getYear() < b->getYear();

                      if (field == "summary")
                          return a->getSummary() < b->getSummary();
                      return false;
                  });
    }

    std::ostream &operator<<(std::ostream &os, const Collection &collection)
    {
        std::for_each(collection.m_items.begin(), collection.m_items.end(),
                      [&os](const MediaItem *item)
                      { os << *item; });
        return os;
    }
}
