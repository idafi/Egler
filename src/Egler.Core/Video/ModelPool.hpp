#pragma once

#include "Video.hpp"

namespace Egler::Video
{
	class ModelPool
	{
		public:
			typedef typename Pool<Model, MaxModels>::Ptr Ptr;

			ModelPool();
			~ModelPool();

			Model& operator [](const Ptr& ptr);

            int Capacity();
            int Count();

            Ptr Allocate(const ModelData& data);
            void Free(const Ptr& ptr);
            bool IsAllocated(const Ptr& ptr);
            void Clear();
		
		private:
			static constexpr int maxVAOs = MaxModels;
			static constexpr int maxVBOs = MaxModels * 2;
			static constexpr int maxIBOs = MaxModels;
			
			VertexArray vaos[maxVAOs];
			VertexBuffer vbos[maxVBOs];
			IndexBuffer ibos[maxIBOs];
			
			Pool<Model, MaxModels> models;
	};
}