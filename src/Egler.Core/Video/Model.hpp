#pragma once

#include "Video.hpp"

namespace Egler::Video
{
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

            void SetData(const ModelData& data);
            void Draw() const;

        private:
            VertexArray vao;
            VertexBuffer vbo_pos;
            VertexBuffer vbo_col;
            IndexBuffer ibo;
            
            int indexCount;
    };
}