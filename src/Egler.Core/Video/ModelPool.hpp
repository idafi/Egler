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
		
		VertexArray vaos[maxVAOs];
        VertexBuffer vbos[maxVBOs];
        IndexBuffer ibos[maxIBOs];
		
		Pool<Model, MaxModels> models;
};