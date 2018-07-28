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

    struct ShaderSourceFile
    {
        const char * const Source;
        const ShaderType Type;

        const char * const FileName;

        ShaderSourceFile(const char * const source, const ShaderType type, const char * const fileName)
        : Source(source), Type(type), FileName(fileName)
        {
            CheckPtr(source);
            CheckPtr(fileName);
        }
    };

    struct ShaderSource
    {
        const ShaderSourceFile * const SourceFiles;
        const int SourceFileCount;

        ShaderSource(const ShaderSourceFile * const sourceFiles, const int sourceFileCount)
        : SourceFiles(sourceFiles), SourceFileCount(sourceFileCount)
        {
            CheckPtr(sourceFiles);
            CheckSign(sourceFileCount);
        }
    };

    class Shader
    {
        public:
            Shader();
            Shader(const ShaderSource& source);
            ~Shader();

            void SetUniform(const char * const name, const float value);
            void SetUniform(const char * const name, const Vector2& value);
            void SetUniform(const char * const name, const Vector3& value);
            void SetUniform(const char * const name, const Vector4& value);
            void SetUniform(const char * const name, const Mat4& value);

        private:
            ShaderProgram program;

            ShaderObject CompileObject(const ShaderSourceFile& source);
            ShaderProgram LinkProgram(const ShaderObject * const, const int objectCount);

            FailureException CompileError(const ShaderObject object, const char * const fileName);
            FailureException LinkError(const ShaderProgram program);
    };
}