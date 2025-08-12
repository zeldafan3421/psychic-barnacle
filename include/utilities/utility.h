#pragma once

#include <array>
#include <cstring>
#include <memory>
#include <new>
#include <stdexcept>

namespace utility
{   
    constexpr std::size_t BYTE_SIZE = sizeof(std::byte);

    template <std::size_t SZ=1024>
    class SmallDataArena
    {
    public:
        struct ArenaDeleter
        {
            SmallDataArena* m_arena; // Pointer to the parent arena

            template <class T>
            void operator()(T* ptr) const
            {
                if (m_arena)
                {
                    m_arena->destroy(ptr);
                }
            }
        };

        template <class T>
        using arena_ptr = std::unique_ptr<T, ArenaDeleter>;

        SmallDataArena() : 
            m_DataPool{}, 
            m_NextFreeChunk{m_DataPool.data()},
            m_BytesFree{SZ}
        {
            static_assert(SZ > BYTE_SIZE);
        }

        template <class T, class... Args>
        T* allocate(Args&&... args) 
        {
            constexpr std::size_t alignment = alignof(T);
            constexpr std::size_t size = sizeof(T);
            void* p = m_NextFreeChunk;
            std::size_t space = m_BytesFree;

            if (std::align(alignment, size, p, space))
            {
                T* result = new (p) T(std::forward<Args>(args)...); // Placement-new

                m_NextFreeChunk = static_cast<std::byte*>(p) + size;
                m_BytesFree = space - size;

                return result;
            }

            throw std::bad_alloc{};
        }

        template <class T>
        void destroy(T *ptr)
        {
            if (!ptr) return;

            void* const p_void = ptr;
            void* const start = m_DataPool.data();
            void* const end = m_DataPool.data() + m_DataPool.size();

            if (p_void >= start && p_void < end)
            {
                ptr->~T();
            }
        }

        void reset()
        {
            m_NextFreeChunk = m_DataPool.data();
            m_BytesFree = SZ;
        }

        template <class T, class... Args>
        auto make_ptr(Args&&... args)
        {
            T* ptr = allocate<T>(std::forward<Args>(args)...);
            return arena_ptr<T>(ptr, ArenaDeleter{this});
        }
    private:
        std::array<std::byte, SZ> m_DataPool;
        std::byte* m_NextFreeChunk;
        std::size_t m_BytesFree;
    };
}
