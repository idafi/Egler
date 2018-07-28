#pragma once

#include "Video.hpp"

namespace Egler::Video
{
    struct ModelData
    {
        const float *VertexPositions;
        const float *VertexColors;
        int VertexCount;
        
        const ushort *Indices;
        int IndexCount;
    };
}