#pragma once

#include "Video.hpp"

namespace Egler::Video
{
    struct ModelBuffer
    {
        float *VertexPositions;
        float *VertexColors;
        int VertexCount;
        
        ushort *Indices;
        int IndexCount;

        ModelBuffer(int maxVertices, int maxIndices)
        {
            CheckSign(maxVertices);
            CheckSign(maxIndices);

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
}