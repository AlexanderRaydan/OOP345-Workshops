#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <functional>
#include "mediaItem.h"

namespace seneca
{
    class Collection
    {
    private:
        std::string m_name;
        std::vector<MediaItem *> m_items;
        void (*m_observer)(const Collection &, const MediaItem &) = nullptr;

    public:
        Collection(const std::string &name) : m_name{name} {}

        Collection(const Collection &) = delete;
        Collection(Collection &&) = delete;
        Collection &operator=(const Collection &) = delete;
        Collection &operator=(Collection &&) = delete;

        ~Collection()
        {
            for (auto *item : m_items)
            {
                delete item;
            }
        }

        const std::string &name() const { return m_name; }

        size_t size() const { return m_items.size(); }

        void setObserver(void (*observer)(const Collection &, const MediaItem &))
        {
            m_observer = observer;
        }

        Collection &operator+=(MediaItem *item)
        {
            // Check for duplicate by title
            auto it = std::find_if(m_items.begin(), m_items.end(),
                                   [item](const MediaItem *existingItem)
                                   { return existingItem->getTitle() == item->getTitle(); });

            if (it == m_items.end())
            { // No duplicate
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

        MediaItem *operator[](size_t idx) const
        {
            if (idx >= m_items.size())
            {
                throw "Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_items.size()) + "] items.";
            }
            return m_items[idx];
        }

        MediaItem *operator[](const std::string &title) const
        {
            auto it = std::find_if(m_items.begin(), m_items.end(),
                                   [title](const MediaItem *item)
                                   {
                                       return item->getTitle() == title;
                                   });
            return (it != m_items.end()) ? *it : nullptr;
        }

        auto begin() { return m_items.begin(); }

        auto end() { return m_items.end(); }

        void removeQuotes()
        {
            std::for_each(m_items.begin(), m_items.end(), [](MediaItem *item)
                          {
                auto removeQuotesLambda = [](std::string str) -> std::string
                {
                    if (!str.empty() && str.front() == '"') {
                        str = str.substr(1); // Remove leading quote
                    }
                    if (!str.empty() && str.back() == '"') {
                        str = str.substr(0, str.size() - 1); // Remove trailing quote
                    }
                    return str;
                };
                item->setTitle(removeQuotesLambda(item->getTitle()));
                item->setSummary(removeQuotesLambda(item->getSummary())); });
        }

        void sort(const std::string &field)
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
                          return false; // Default no sort if unknown field
                      });
        }

        friend std::ostream &operator<<(std::ostream &os, const Collection &collection)
        {
            std::for_each(collection.m_items.begin(), collection.m_items.end(),
                          [&os](const MediaItem *item)
                          { os << *item; });
            return os;
        }
    };
}

#endif // SENECA_COLLECTION_H
