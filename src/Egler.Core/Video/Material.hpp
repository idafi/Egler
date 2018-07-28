#pragma once

#include <map>
#include "Video.hpp"

namespace Egler::Video
{
    struct MaterialProperties
    {
        std::map<const char *, float> f1;
        std::map<const char *, Vector2> f2;
        std::map<const char *, Vector3> f3;
        std::map<const char *, Vector4> f4;
        std::map<const char *, Mat4> m4;

        void Clear()
        {
            f1.clear();
            f2.clear();
            f3.clear();
            f4.clear();
            m4.clear();
        }

        template<typename T>
        void Apply(std::map<const char *, T> properties, const Shader& shader)
        {
            for(auto pair : properties)
            { shader.SetUniform(pair.first, pair.second); }
        }
    };

    class Material
    {
        public:
            ~Material();
            
            void SetShader(Shader& shader);

            void SetProperty(const char *name, float value);
            void SetProperty(const char *name, Vector2 value);
            void SetProperty(const char *name, Vector3 value);
            void SetProperty(const char *name, Vector4 value);
            void SetProperty(const char *name, Mat4 value);

        private:
            Shader *shader;
            MaterialProperties properties;

            template<typename T>
            void SetProperty(std::map<const char *, T>& properties, const char *name, T value)
            {
                CheckPtr(shader);
                CheckPtr(name);

                properties[name] = value;
            }
    };
}