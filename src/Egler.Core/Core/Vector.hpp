#pragma once

// - - - - - -
// vector math - completely compatible with matrix objects
// - - - - - -

#include "Core.hpp"

namespace Egler::Core
{
	template<int size>
	struct Vector : public Matrix<1, size>
	{
		public:
			static constexpr int Size = size;

			Vector<size>() : Matrix<1, size>() { }
			Vector<size>(const Matrix<1, size>& m) : Matrix<1, size>(m) { }
		
			Vector<size> operator *(float s) const
			{
				Vector<size> nVec;
				for(int i = 0; i < size; i++)
				{ nVec[i] = (*this)[i] * s; }
				
				return nVec;
			}
			
			void operator *=(float s)
			{
				*this = *this * s;
			}
			
			float Dot(Vector<size> v) const
			{
				float d = 0;
				for(int i = 0; i < size; i++)
				{ d += (*this)[i] * v[i]; }
				
				return d;
			}
			
			float SqrMagnitude() const
			{
				return Dot(*this);
			}
			
			float Magnitude() const
			{
				float sqr = SqrMagnitude();
				return sqrtf(sqr);
			}
			
			Vector<size> ClampMagnitude(float minMag, float maxMag) const
			{
				float min = Max(Min(minMag, maxMag), 0);
				float max = Max(Max(minMag, maxMag), 0);			
				float mag = Magnitude();

				if(mag > 0)
				{
					if(mag < min)
					{
						float s = min / mag;
						return (*this * s);
					}
					if(mag > max)
					{
						float s = max / mag;
						return (*this * s);
					}
				}
				
				return *this;
			}
			
			Vector<size> Normalize() const
			{
				float mag = Magnitude();
				if(mag > 0)
				{
					float s = 1 / mag;
					return (*this * s);
				}
				
				return *this;
			}
			
			Vector<size> Project(Vector<size> v) const
			{
				return v * (this->Dot(v) / v.Dot(v));
			}
			
			static Vector<size> Lerp(Vector<size> a, Vector<size> b, float t)
			{
				Vector<size> v = b - a;
				v *= t;
				
				return a + v;
			}
	};

	struct Vector2 : public Vector<2>
	{
		public:
			Vector2() : Vector<2>() { }
			Vector2(const Vector<2>& v) : Vector<2>(v) { }
			Vector2(const Matrix<1, 2>& m) : Vector<2>(m) { }
			
			Vector2(float x, float y)
			{
				(*this)[0] = x;
				(*this)[1] = y;
			}
			
			Vector2(float degrees)
			{
				float rad = (float)(degrees / (180.0f / M_PI));
				(*this)[0] = (float)(cos(rad));
				(*this)[1] = (float)(sin(rad));
			}
			
			float ToAngle() const
			{
				float x = (*this)[0];
				float y = (*this)[1];
				float rad = (float)(atan2(y, x));
				
				return (float)(rad * (180.0f / M_PI));
			}
	};

	struct Vector3 : public Vector<3>
	{
		public:
			Vector3() : Vector<3>() { }
			Vector3(const Vector<3>& v) : Vector<3>(v) { }
			Vector3(const Matrix<1, 3>& m) : Vector<3>(m) { }
			
			Vector3(float x, float y, float z)
			{
				(*this)[0] = x;
				(*this)[1] = y;
				(*this)[2] = z;
			}

			Vector3 Cross(Vector3 v) const
			{
				float x = ((*this)[1] * v[2]) - ((*this)[2] * v[1]);
				float y = ((*this)[2] * v[0]) - ((*this)[0] * v[2]);
				float z = ((*this)[0] * v[1]) - ((*this)[1] * v[0]);
				
				return Vector3(x, y, z);
			}
	};

	struct Vector4 : public Vector<4>
	{
		public:
			Vector4() : Vector<4>() { }
			Vector4(const Vector<4>& v) : Vector<4>(v) { }
			Vector4(const Matrix<1, 4>& m) : Vector<4>(m) { }
			
			Vector4(float x, float y, float z, float w)
			{
				(*this)[0] = x;
				(*this)[1] = y;
				(*this)[2] = z;
				(*this)[3] = w;
			}
	};
}