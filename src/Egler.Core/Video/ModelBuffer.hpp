#pragma once

#include "Video.hpp"

struct ModelBuffer
{
    float *VertexPositions;
    float *VertexColors;
    int VertexCount;
    
    ushort *Indices;
    int IndexCount;

    ModelBuffer(int maxVertices, int maxIndices)
    {
        assert(maxVertices > -1);
        assert(maxIndices > -1);

        VertexPositions = new float[maxVertices];
        VertexColors = new float[maxVertices];
        Indices = new ushort[maxIndices];
    }

    ~ModelBuffer()
    {
        delete VertexPositions;
        delete VertexPositions;
        delete Indices;
    }
};