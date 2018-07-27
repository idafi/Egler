#pragma once

#include "Video.hpp"

class ModelPool
{
	public:
		static constexpr int MaxModels = 64;
		
		ModelPool();
		~ModelPool();
	
	private:
		static constexpr int maxVAOs = MaxModels;
        static constexpr int maxVBOs = MaxModels * 2;
        static constexpr int maxIBOs = MaxModels;
		
		vertex_array vaos[maxVAOs];
        vertex_buffer vbos[maxVBOs];
        index_buffer ibos[maxIBOs];
		
		Pool<Model, MaxModels> models;
};