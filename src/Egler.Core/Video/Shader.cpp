#include "Video.hpp"

using namespace Egler::Logging;

namespace Egler::Video
{
    Shader::Shader()
    {
        program = 0;
    }

    Shader::~Shader()
    {
        glDeleteProgram(program);
        program = 0;
    }

    void Shader::Compile(const ShaderSource &source)
    {
        LogDebug("Creating shader...");

        LogDebug("...compiling source...");

        std::unique_ptr<ShaderObject[]> objects(new ShaderObject[source.SourceFileCount]);
        for(int i = 0; i < source.SourceFileCount; i++)
        { objects[i] = CompileObject(source.SourceFiles[i]); }

        LogDebug("...linking program...");
        program = LinkProgram(objects.get(), source.SourceFileCount);

        LogDebug("...done.");
    }

    void Shader::Use() const
    {
        CheckID(program);

        glUseProgram(program);
    }

    int Shader::GetUniformCount()
    {
        int ct;
        glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &ct);
        return ct;
    }

    ShaderUniform Shader::GetUniform(int index)
    {
        GLenum type;
        GLchar name[32];
        int len;
        int lenlen;
        glGetActiveUniform(program, index, 32, &len, &lenlen, &type, name);
        
        ShaderUniform uniform;
        strcpy_s(uniform.Name, name);
        uniform.Type = (ShaderUniformType)(type);
        return uniform;
    }

    void Shader::SetUniform(const char * const name, const float value)
    {
        CheckPtr(name);

        GLint loc = glGetUniformLocation(program, name);
        if(loc > -1)
        { glUniform1f(loc, value); }
    }

    void Shader::SetUniform(const char * const name, const Vector2& value)
    {
        CheckPtr(name);

        GLint loc = glGetUniformLocation(program, name);
        if(loc > -1)
        { glUniform2f(loc, value[0], value[1]); }
    }

    void Shader::SetUniform(const char * const name, const Vector3& value)
    {
        CheckPtr(name);

        GLint loc = glGetUniformLocation(program, name);
        if(loc > -1)
        { glUniform3f(loc, value[0], value[1], value[2]); }
    }

    void Shader::SetUniform(const char * const name, const Vector4& value)
    {
        CheckPtr(name);

        GLint loc = glGetUniformLocation(program, name);
        if(loc > -1)
        { glUniform4f(loc, value[0], value[1], value[2], value[3]); }
    }

    void Shader::SetUniform(const char * const name, const Mat4& value)
    {
        CheckPtr(name);

        GLint loc = glGetUniformLocation(program, name);
        if(loc > -1)
        { glUniformMatrix4fv(loc, 1, GL_FALSE, value.Data()); }
    }

    ShaderObject Shader::CompileObject(const ShaderSourceFile& source)
    {
        LogDebug("...creating object...");

        ShaderObject obj = glCreateShader((GLenum)(source.Type));
        if(obj <= 0)
        { throw FailureException("Failed to create shader object."); }

        LogDebug("...compiling '%s'...", source.FileName);

        glShaderSource(obj, 1, (const GLchar **)(&source.Source), nullptr);
        glCompileShader(obj);

        GLint result;
        glGetShaderiv(obj, GL_COMPILE_STATUS, &result);
        if(result != GL_TRUE)
        { throw CompileError(obj, source.FileName); }

        LogDebug("...done...");

        return obj;
    }

    ShaderProgram Shader::LinkProgram(const ShaderObject * const objects, const int objectCount)
    {
        LogDebug("...creating program...");

        ShaderProgram program = glCreateProgram();
        if(program <= 0)
        { throw FailureException("Failed to create shader program."); }

        LogDebug("...attaching and linking objects...");

        for(int i = 0; i < objectCount; i++)
        { glAttachShader(program, objects[i]); }
        glLinkProgram(program);

        LogDebug("...cleaning up objects...");

        for(int i = 0; i < objectCount; i++)
        {
            glDetachShader(program, objects[i]);
            glDeleteShader(objects[i]);
        }

        GLint result;
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        if(result != GL_TRUE)
        { throw LinkError(program); }

        return program;
    }

    FailureException Shader::CompileError(const ShaderObject object, const char * const fileName)
    {
        GLint infoLen;
        glGetShaderiv(object, GL_INFO_LOG_LENGTH, &infoLen);

        std::unique_ptr<GLchar[]> err(new GLchar[infoLen]);
        glGetShaderInfoLog(object, infoLen, nullptr, err.get());

        return FailureException("Failed to compile shader object from '%s'.\n\n%s", fileName, err.get());
    }

    FailureException Shader::LinkError(const ShaderProgram program)
    {
        GLint infoLen;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

        std::unique_ptr<GLchar[]> err(new GLchar[infoLen]);
        glGetProgramInfoLog(program, infoLen, nullptr, err.get());

        return FailureException("Failed to link shader program.\n\n%s", err.get());
    }
}