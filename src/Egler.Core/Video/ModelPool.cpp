#include "Video.hpp"

ModelPool::ModelPool()
{
	glGenBuffers(maxVAOs, vaos);
	glGenBuffers(maxVBOs, vbos);
	glGenBuffers(maxIBOs, ibos);
	
	Model *modelArray = new Model[MaxModels];
	for(int i = 0; i < MaxModels; i++)
	{ modelArray[i] = Model(i, i * 2, (i * 2) + 1, i); }

	models = Pool<Model, MaxModels>(modelArray, MaxModels);	
	delete[] modelArray;
}

ModelPool::~ModelPool()
{
	glDeleteBuffers(maxIBOs, ibos);
	glDeleteBuffers(maxVBOs, vbos);
	glDeleteBuffers(maxVAOs, vaos);
}