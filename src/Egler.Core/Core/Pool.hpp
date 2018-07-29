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
                for(int i = 0; i < size; i++)
                { freeIndices.push(i); }

                memset(values, 0, sizeof(values));
            }

            Pool(const T * const initValues, const int initValueCount) : Pool()
            {
                CheckPtr(initValues);
                CheckSign(initValueCount);
                CheckRange(initValueCount, size);

                for(int i = 0; i < initValueCount; i++)
                { values[i].Item = initValues[i]; }
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

            bool IsAllocated(const Ptr& ptr)
            {
                if(ptr.Index > -1 && ptr.Index < size)
                {
                    if(values[ptr.Index].IsAllocated)
                    { return (ptr.Revision == values[ptr.Index].Revision); }
                }

                return false;
            }

            void Clear()
            {
                memset(values, 0, sizeof(values));

                freeIndices = std::queue<int>();
                for(int i = 0; i < size; i++)
                { freeIndices.push(i); }
            }

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