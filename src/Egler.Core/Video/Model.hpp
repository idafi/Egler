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
        Model(VertexArray vao, VertexBuffer vbo_pos, VertexBuffer vbo_col, IndexBuffer ibo);

        void SetData(const ModelBuffer& buffer);

    private:
        VertexArray vao;
        VertexBuffer vbo_pos;
        VertexBuffer vbo_col;
        IndexBuffer ibo;
        
        int indexCount;
};