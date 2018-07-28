#pragma once

#include "Video.hpp"

using namespace Egler::Core;

namespace Egler::Video
{
    typedef GLuint ShaderProgram;
    typedef GLuint ShaderObject;

    enum class ShaderType : GLenum
    {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Compute = GL_COMPUTE_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEval = GL_TESS_EVALUATION_SHADER
    };

    struct ShaderSource
    {
        const char * const Source;
        const ShaderType Type;

        const char * const FileName;

        ShaderSource(const char * const source, const ShaderType type, const char * const fileName)
        : Source(source), Type(type), FileName(fileName)
        {
            CheckPtr(source);
            CheckPtr(fileName);
        }
    };

    class Shader
    {
        public:
            Shader(const ShaderSource * const source, const int sourceCount);
            ~Shader();

            void SetUniform(const char * const name, const float value);
            void SetUniform(const char * const name, const Vector2& value);
            void SetUniform(const char * const name, const Vector3& value);
            void SetUniform(const char * const name, const Vector4& value);
            void SetUniform(const char * const name, const Mat4& value);

        private:
            ShaderProgram program;

            ShaderObject CompileObject(const ShaderSource& source);
            ShaderProgram LinkProgram(const ShaderObject * const, const int objectCount);
            FailureException CompileError(const ShaderObject object, const char * const fileName);
            FailureException LinkError(const ShaderProgram program);
    };
}