#ifndef _gg_memory_h_
#define _gg_memory_h_

#include "gg/core/debug/assert.h"
#include "gg/core/type/type_trait.h"

#include <cstdlib>
#include <cstring>
#include <new>

namespace gg
{
    class memory final
    {
    public:

        // methods

        static int32
        compare(void const * lhs, void const * rhs, size_type bytes) noexcept
        {
            GG_ASSERT(lhs);
            GG_ASSERT(rhs);
            return std::memcmp(lhs, rhs, bytes);
        }

        template <typename TYPE>
        static int32
        compare(TYPE const * lhs, TYPE const * rhs, size_type items = 1) noexcept
        {
            return
                compare(
                    type::cast_static<void const *>(lhs),
                    type::cast_static<void const *>(rhs),
                    items * sizeof(TYPE));
        }

        static void *
        copy(void * dest, void const * src, size_type bytes) noexcept
        {
            GG_ASSERT(dest);
            GG_ASSERT(src);
            GG_ASSERT(
                ((type::cast_static<uchar8 *>(dest)) + bytes) <=
                    (type::cast_static<const uchar8 *>(src)) ||
                ((type::cast_static<const uchar8 *>(src)) + bytes) <=
                    (type::cast_static<uchar8 *>(dest)));
            return std::memcpy(dest, src, bytes);
        }

        template <typename TYPE>
        static TYPE *
        copy(TYPE * dest, TYPE const * src, size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(
                copy(
                    type::cast_static<void *>(dest),
                    type::cast_static<void const *>(src),
                    items * sizeof(TYPE)));
        }

        static void *
        move(void * dest, void const * src, size_type bytes) noexcept
        {
            GG_ASSERT(dest);
            GG_ASSERT(src);
            return std::memmove(dest, src, bytes);
        }

        template <typename TYPE>
        static TYPE *
        move(TYPE * dest, TYPE const * src, size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(
                move(
                    type::cast_static<void *>(dest),
                    type::cast_static<void const *>(src),
                    items * sizeof(TYPE)));
        }

        static void *
        zero(void * dest, size_type bytes) noexcept
        {
            GG_ASSERT(dest);
            return std::memset(dest, 0, bytes);
        }

        template <typename TYPE>
        static TYPE *
        zero(TYPE * dest, size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(
                zero(
                    type::cast_static<void *>(dest),
                    items * sizeof(TYPE)));
        }

        static void * allocate(size_type bytes) noexcept
        {
            void * ptr = std::malloc(bytes);
            GG_ASSERT(ptr);
            return ptr;
        }

        template <typename TYPE>
        static TYPE * allocate(size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(allocate(items * sizeof(TYPE)));
        }

        static void deallocate(void * ptr) noexcept
        {
            std::free(ptr);
        }

        template <typename TYPE>
        static void deallocate(TYPE * ptr) noexcept
        {
            return deallocate(type::cast_static<void *>(ptr));
        }

        static void * reallocate(void * ptr, size_type bytes) noexcept
        {
            ptr = std::realloc(ptr, bytes);
            GG_ASSERT(ptr);
            return ptr;
        }

        template <typename TYPE>
        static TYPE * reallocate(TYPE * ptr, size_type items = 1) noexcept
        {
            return
                type::cast_static<TYPE *>(
                    reallocate(
                        type::cast_static<void *>(ptr),
                        items * sizeof(TYPE)));
        }

        template <typename OBJECT_TYPE, typename... ARGS>
        static OBJECT_TYPE *
        construct_object(OBJECT_TYPE * object, ARGS &&... args) noexcept
        {
            GG_ASSERT(object);
            object = new (object) OBJECT_TYPE(type::forward<ARGS>(args)...);
            GG_ASSERT(object);
            return object;
        }

        template <typename OBJECT_TYPE>
        static void delete_object(OBJECT_TYPE *& object) noexcept
        {
            delete object;
            object = nullptr;
        }

        template <typename OBJECT_TYPE>
        static void
        delete_object_array(OBJECT_TYPE *& objects) noexcept
        {
            delete[] objects;
            objects = nullptr;
        }

        template <typename OBJECT_TYPE, typename... ARGS>
        static OBJECT_TYPE *
        new_object(ARGS &&... args) noexcept
        {
            OBJECT_TYPE * object =
                new (std::nothrow) OBJECT_TYPE(
                    type::forward<ARGS>(args)...);
            GG_ASSERT(object);
            return object;
        }

        template <typename OBJECT_TYPE>
        static OBJECT_TYPE *
        new_object_array(size_type size) noexcept
        {
            OBJECT_TYPE * objects = new (std::nothrow) OBJECT_TYPE[size];
            GG_ASSERT(objects);
            return objects;
        }
    };
}

#endif // _gg_memory_h_
