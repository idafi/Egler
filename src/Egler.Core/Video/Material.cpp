#include "Video.hpp"

namespace Egler::Video
{
    Material::~Material()
    {
        shader = nullptr;
        properties.Clear();
    }

    void Material::SetShader(Shader& shader)
    {
        this->shader = &shader;
        properties.Clear();
        
        int ct = shader.GetUniformCount();
        for(int i = 0; i < ct; i++)
        {
            ShaderUniform uniform = shader.GetUniform(i);
            switch(uniform.Type)
            {
                case ShaderUniformType::F1:
                    properties.f1[uniform.Name] = 0;
                    break;
                case ShaderUniformType::F2:
                    properties.f2[uniform.Name] = Vector2();
                    break;
                case ShaderUniformType::F3:
                    properties.f3[uniform.Name] = Vector3();
                    break;
                case ShaderUniformType::F4:
                    properties.f4[uniform.Name] = Vector4();
                    break;
                case ShaderUniformType::M4:
                    properties.m4[uniform.Name] = Mat4();
                    break;
            }
        }
    }

    void Material::SetProperty(const char *name, float value)
    {
        SetProperty<float>(properties.f1, name, value);
    }

    void Material::SetProperty(const char *name, Vector2 value)
    {
        SetProperty<Vector2>(properties.f2, name, value);
    }
    
    void Material::SetProperty(const char *name, Vector3 value)
    {
        SetProperty<Vector3>(properties.f3, name, value);
    }

    void Material::SetProperty(const char *name, Vector4 value)
    {
        SetProperty<Vector4>(properties.f4, name, value);
    }

    void Material::SetProperty(const char *name, Mat4 value)
    {
        SetProperty<Mat4>(properties.m4, name, value);
    }
}