#pragma once

#include "Egler.hpp"

namespace Egler
{
	template<typename T, int max>
	class EntitySystem
	{
		public:
			typedef typename Pool<T, max>::Ptr Ptr;
			
			void Destroy(const Ptr& ptr)
			{
				pool.Free(ptr);
			}
			
			bool Exists(const Ptr& ptr)
			{
				return pool.IsAllocated(ptr);
			}
			
			T& Get(const Ptr& ptr)
			{
				if(!Exists(ptr))
				{ throw BadArgumentException("Provided entity does not exist."); }

				return pool[ptr];
			}
		
		protected:
			Ptr Allocate()
			{
				if(pool.Count() >= pool.Capacity())
				{ throw OutOfMemoryException("Entity pool is full (capacity: %i).", max); }

				return pool.Allocate();
			}
			
			Pool<T, max> pool;
	};
}