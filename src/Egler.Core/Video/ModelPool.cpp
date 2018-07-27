#include "Video.hpp"

ModelPool::ModelPool()
{
	glGenBuffers(maxVAOs, vaos);
	glGenBuffers(maxVBOs, vbos);
	glGenBuffers(maxIBOs, ibos);
	
	Model *modelArray = new Model[MaxModels];
	for(int i = 0; i < MaxModels; i++)
	{
		VertexArray vao = vaos[i];
		VertexBuffer vbo_pos = vbos[i * 2];
		VertexBuffer vbo_col = vbos[(i * 2) + 1];
		IndexBuffer ibo = ibos[i];

		modelArray[i] = Model(vao, vbo_pos, vbo_col, ibo);
	}

	models = Pool<Model, MaxModels>(modelArray, MaxModels);	
	delete[] modelArray;
}

ModelPool::~ModelPool()
{
	glDeleteBuffers(maxIBOs, ibos);
	glDeleteBuffers(maxVBOs, vbos);
	glDeleteBuffers(maxVAOs, vaos);

	models.Clear();
}