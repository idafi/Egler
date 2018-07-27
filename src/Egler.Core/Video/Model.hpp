#pragma once

#include "Video.hpp"

class Model
{
    enum class VertexAttr
    {
        Position,
        Color
    };

    public:
        Model();
        Model(vertex_array vao, vertex_buffer vbo_pos, vertex_buffer vbo_col, index_buffer ibo);

        void SetData(const ModelBuffer& buffer);

    private:
        vertex_array vao;
        vertex_buffer vbo_pos;
        vertex_buffer vbo_col;
        index_buffer ibo;
        
        int indexCount;
};