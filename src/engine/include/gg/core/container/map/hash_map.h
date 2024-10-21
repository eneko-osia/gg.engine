#ifndef _gg_hash_map_h_
#define _gg_hash_map_h_

#include "gg/core/container/container.h"
#include "gg/core/debug/assert.h"
#include "gg/core/macro/macro.h"

#include <unordered_map>

namespace gg
{
    template <typename KEY_TYPE, typename ITEM_TYPE>
    class hash_map final
    {
    private:

        // type definitions

        typedef std::unordered_map<KEY_TYPE, ITEM_TYPE> hash_map_type;

    public:

        // type definitions

        typedef KEY_TYPE                key_type;
        typedef ITEM_TYPE               item_type;

        typedef item_type *             pointer;
        typedef item_type const *       const_pointer;

        typedef item_type &             reference;
        typedef item_type const &       const_reference;

        typedef typename
        hash_map_type::value_type       value_type;

        typedef typename
        hash_map_type::iterator         iterator;
        typedef typename
        hash_map_type::const_iterator   const_iterator;

        // constructors

        hash_map(void) noexcept
            : m_data()
        {
        }

        hash_map(hash_map const & map) noexcept
            : m_data(map.m_data)
        {
        }

        hash_map(hash_map && map) noexcept
            : m_data(type::move(map.m_data))
        {
        }

        ~hash_map(void) noexcept = default;

        // operators

        reference operator[](key_type const & key) noexcept
        {
            return m_data[key];
        }

        const_reference operator[](key_type const & key) const noexcept
        {
            return m_data[key];
        }

        hash_map & operator=(hash_map const & map) noexcept
        {
            GG_ASSERT(this != &map);
            m_data = map.m_data;
            return *this;
        }

        hash_map & operator=(hash_map && map) noexcept
        {
            GG_ASSERT(this != &map);
            m_data = type::move(map.m_data);
            return *this;
        }

        bool8 operator==(hash_map const & map) noexcept
        {
            return m_data == map.m_data;
        }

        bool8 operator!=(hash_map const & map) noexcept
        {
            return !(*this == map);
        }

        // methods

        iterator begin(void) noexcept
        {
            return m_data.begin();
        }

        const_iterator begin(void) const noexcept
        {
            return m_data.begin();
        }

        void clear(void) noexcept
        {
            m_data.clear();
        }

        template <typename... ARGS>
        void emplace(key_type const & key, ARGS &&... args) noexcept
        {
            m_data.emplace(key, type::forward<ARGS>(args)...);
        }

        iterator end(void) noexcept
        {
            return m_data.end();
        }

        const_iterator end(void) const noexcept
        {
            return m_data.end();
        }

        void erase(key_type const & key) noexcept
        {
            erase(find(key));
        }

        iterator erase(const_iterator cit) noexcept
        {
            return m_data.erase(cit);
        }

        iterator
        erase(const_iterator cit_start, const_iterator cit_end) noexcept
        {
            return m_data.erase(cit_start, cit_end);
        }

        iterator find(key_type const & key) noexcept
        {
            return m_data.find(key);
        }

        const_iterator find(key_type const & key) const noexcept
        {
            return m_data.find(key);
        }

        template <typename FUNCTION>
        iterator find_if(FUNCTION && function) noexcept
        {
            return
                container::find_if(
                    begin(), end(), type::forward<FUNCTION>(function));
        }

        template <typename FUNCTION>
        const_iterator find_if(FUNCTION && function) const noexcept
        {
            return
                container::find_if(
                    begin(), end(), type::forward<FUNCTION>(function));
        }

        template <typename FUNCTION>
        FUNCTION for_each(FUNCTION && function) noexcept
        {
            return
                container::for_each(
                    begin(), end(), type::forward<FUNCTION>(function));
        }

        template <typename FUNCTION>
        FUNCTION for_each(FUNCTION && function) const noexcept
        {
            return
                container::for_each(
                    begin(), end(), type::forward<FUNCTION>(function));
        }

        void insert(key_type const & key, item_type const & item) noexcept
        {
            m_data.insert(std::make_pair(key, item));
        }

        void insert(key_type const & key, item_type && item) noexcept
        {
            m_data.insert(
                std::make_pair(key, type::forward<item_type>(item)));
        }

        size_type max_size(void) const noexcept
        {
            return
                type::cast_static<size_type>(m_data.max_size());
        }

        size_type size(void) const noexcept
        {
            return
                type::cast_static<size_type>(m_data.size());
        }

        // inquiries

        bool8 has(key_type const & key) const noexcept
        {
            return find(key) != end();
        }

        bool8 is_empty(void) const noexcept
        {
            return m_data.empty();
        }

    private:

        // attributes

        hash_map_type m_data;
    };
}

#endif // _gg_hash_map_h_
