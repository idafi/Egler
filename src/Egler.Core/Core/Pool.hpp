#pragma once

#include <queue>
#include "Core.hpp"

namespace Egler::Core
{
    template<typename T, int size>
    class EGAPI Pool
    {
        public:
            struct Ptr
            {
                int Index, Revision;

                Ptr() : Index(-1), Revision(0) { }
                Ptr(int index, int revision) : Index(index), Revision(revision) { }
            };

            Pool()
            {
                Clear();
            }

            Pool(const T * const initValues, const int initValueCount) : Pool()
            {
                CheckPtr(initValues);
                CheckSign(initValueCount);
                CheckRange(initValueCount, size);

                for(int i = 0; i < initValueCount; i++)
                { values[i].Item = initValues[i]; }
            }

            T& operator [](const int index)
            {
                if(!IsAllocated(index))
                { throw OutOfRangeException("Index %i is invalid or not allocated", index); }

                return values[index].Item;
            }

            T& operator [](const Ptr& ptr)
            {
                if(!IsAllocated(ptr))
                { throw OutOfRangeException("Pool pointer (index: %i, revision: %i) is invalid", ptr.Index, ptr.Revision); }

                return values[ptr.Index].Item;
            }

            int Capacity()
            {
                return size;
            }

            int Count()
            {
                return (size - freeIndices.size());
            }

            Ptr Allocate()
            {
                if(freeIndices.size() <= 0)
                { throw InvalidOperationException("Pool has no more free values"); }
                
                int i = freeIndices.front();
                freeIndices.pop();
                values[i].IsAllocated = true;

                Ptr ptr(i, values[i].Revision);
                return ptr;
            }

            void Free(const Ptr& ptr)
            {
                if(IsAllocated(ptr))
                {
                    Value *val = &values[ptr.Index];
                    val->IsAllocated = false;
                    val->Revision++;

                    freeIndices.push(ptr.Index);
                }
            }

            bool IsAllocated(const int index)
            {
                if(index > -1 && index < size)
                {
                    if(values[index].IsAllocated)
                    { return true; }
                }

                return false;
            }

            bool IsAllocated(const Ptr& ptr)
            {
                if(IsAllocated(ptr.Index))
                { return (ptr.Revision == values[ptr.Index].Revision); }

                return false;
            }

            void Clear()
            {
                for(int i = 0; i < size; i++)
                {
                    values[i].IsAllocated = false;
                    values[i].Revision = 1;
                }

                freeIndices = std::queue<int>();
                for(int i = 0; i < size; i++)
                { freeIndices.push(i); }
            }

            struct Iterator
            {
                Pool<T, size>& pool;
                int Index;

                Iterator(Pool<T, size>& pool) : pool(pool) { Index = GetNext(-1); }
                T& operator *() { return pool.values[Index].Item; }
                bool operator !=(int i) { return (Index != i); }

                Iterator& operator ++()
                {
                    Index = GetNext(Index);
                    return *this;
                }

                int GetNext(int current)
                {
                    do { current++; }
                    while(current < pool.Capacity() && !pool.values[current].IsAllocated);

                    return current;
                }
            };

            Iterator begin() { return Iterator(*this); }
            int end() { return Capacity(); }

        private:
            struct Value
            {
                T Item;

                bool IsAllocated;
                int Revision;
            };

            Value values[size];
            std::queue<int> freeIndices;
    };
}