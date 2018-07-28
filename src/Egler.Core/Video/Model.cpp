#include "Video.hpp"

namespace Egler::Video
{
    Model::Model()
    {
        vao = vbo_pos = vbo_col = ibo = 0;
    }

    Model::Model(VertexArray vao, VertexBuffer vbo_pos, VertexBuffer vbo_col, IndexBuffer ibo)
    : vao(vao), vbo_pos(vbo_pos), vbo_col(vbo_col), ibo(ibo) { }

    void Model::SetData(const ModelBuffer& buffer)
    {
        CheckID(vao);
        CheckID(vbo_pos);
        CheckID(vbo_col);
        CheckID(ibo);

        glBindVertexArray(vao);

        // add position data
        glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * buffer.VertexCount, buffer.VertexPositions, GL_STATIC_DRAW);
        glEnableVertexAttribArray((int)(VertexAttr::Position));
        glVertexAttribPointer((int)(VertexAttr::Position), 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        // add color data
        glBindBuffer(GL_ARRAY_BUFFER, vbo_col);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * buffer.VertexCount, buffer.VertexColors, GL_STATIC_DRAW);
        glEnableVertexAttribArray((int)(VertexAttr::Color));
        glVertexAttribPointer((int)(VertexAttr::Color), 4, GL_FLOAT, GL_FALSE, 0, 0);
        
        // add data indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ushort) * buffer.IndexCount, buffer.Indices, GL_STATIC_DRAW);

        glBindVertexArray(0);

        indexCount = buffer.IndexCount;
    }
}