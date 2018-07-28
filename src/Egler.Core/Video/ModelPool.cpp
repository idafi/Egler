#include "Video.hpp"

using namespace Egler::Logging;

namespace Egler::Video
{
	ModelPool::ModelPool()
	{
		LogNote("Creating model pool...");

		if(!SDL_GL_GetCurrentContext())
		{ throw NotInitializedException("No GL context has been initialized yet."); }

		LogDebug("...generating GL buffers...");

		glGenBuffers(maxVAOs, vaos);
		glGenBuffers(maxVBOs, vbos);
		glGenBuffers(maxIBOs, ibos);
		
		LogDebug("...assigning buffer IDs to models...");

		std::unique_ptr<Model[]> initModels(new Model[MaxModels]);
		for(int i = 0; i < MaxModels; i++)
		{
			VertexArray vao = vaos[i];
			VertexBuffer vbo_pos = vbos[i * 2];
			VertexBuffer vbo_col = vbos[(i * 2) + 1];
			IndexBuffer ibo = ibos[i];

			initModels[i] = Model(vao, vbo_pos, vbo_col, ibo);
		}

		LogDebug("...creating pool...");
		models = Pool<Model, MaxModels>(initModels.get(), MaxModels);	

		LogNote("...done.");
	}

	ModelPool::~ModelPool()
	{
		LogNote("Destroying model pool...");

		LogDebug("...clearing pool...");
		models.Clear();

		LogDebug("...deleting GL buffers...");
		glDeleteBuffers(maxIBOs, ibos);
		glDeleteBuffers(maxVBOs, vbos);
		glDeleteBuffers(maxVAOs, vaos);

		LogNote("...done.");
	}

    int ModelPool::Capacity()
    {
        return models.Capacity();
    }

    int ModelPool::Count()
    {
        return models.Count();
    }

    ModelPool::Ptr ModelPool::Allocate(const ModelBuffer& dataBuffer)
    {
        Ptr ptr = models.Allocate();
		models[ptr].SetData(dataBuffer);

		return ptr;
    }

    void ModelPool::Free(const Ptr& ptr)
    {
        models.Free(ptr);
    }

    bool ModelPool::IsAllocated(const Ptr& ptr)
    {
        return models.IsAllocated(ptr);
    }

    void ModelPool::Clear()
    {
        models.Clear();
    }
}