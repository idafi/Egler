#include "Video.hpp"

ModelPool::ModelPool()
{
	assert(SDL_GL_GetCurrentContext());

	glGenBuffers(maxVAOs, vaos);
	glGenBuffers(maxVBOs, vbos);
	glGenBuffers(maxIBOs, ibos);
	
	std::unique_ptr<Model[]> initModels(new Model[MaxModels]);
	for(int i = 0; i < MaxModels; i++)
	{
		VertexArray vao = vaos[i];
		VertexBuffer vbo_pos = vbos[i * 2];
		VertexBuffer vbo_col = vbos[(i * 2) + 1];
		IndexBuffer ibo = ibos[i];

		initModels[i] = Model(vao, vbo_pos, vbo_col, ibo);
	}

	models = Pool<Model, MaxModels>(initModels.get(), MaxModels);	
}

ModelPool::~ModelPool()
{
	glDeleteBuffers(maxIBOs, ibos);
	glDeleteBuffers(maxVBOs, vbos);
	glDeleteBuffers(maxVAOs, vaos);

	models.Clear();
}