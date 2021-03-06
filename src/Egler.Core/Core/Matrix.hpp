#pragma once

// - - - - - -
// matrix math - matricies are column-major
// - - - - - -

#include "Core.hpp"

namespace Egler::Core
{
	template<int columns, int rows>
	struct EGAPI Matrix
	{
		public:
			static constexpr int Size = columns * rows;

			Matrix()
			{
				memset(c, 0, Size * sizeof(float));
			}
			
			Matrix(const Matrix<columns, rows>& m)
			{
				memcpy(c, &m, Size * sizeof(float));
			}

			bool operator ==(Matrix<columns, rows> m) const
			{
				return !memcmp(this->c, m.c, Size * sizeof(float));
			}
			
			bool operator !=(Matrix<columns, rows> m) const
			{
				return memcmp(this->c, m.c, Size * sizeof(float));
			}
			
			float operator [](int i) const
			{
				CheckIndex(i, Size);
				return c[i];
			}
			
			float& operator [](int i)
			{
				CheckIndex(i, Size);
				return c[i];
			}
			
			Matrix<columns, rows> operator +(Matrix<columns, rows> m) const
			{
				Matrix<columns, rows> nMat = *this;
				for(int i = 0; i < Size; i++)
				{ nMat.c[i] = this->c[i] + m.c[i]; }
				
				return nMat;
			}
			
			Matrix<columns, rows> operator -(Matrix<columns, rows> m) const
			{
				Matrix<columns, rows> nMat = *this;
				for(int i = 0; i < Size; i++)
				{ nMat.c[i] = this->c[i] - m.c[i]; }
			
				return nMat;
			}
			
			template<int otherColumns>
			Matrix<otherColumns, rows> operator *(Matrix<otherColumns, columns> m) const
			{
				Matrix<otherColumns, rows> nMat;

				for(int nCol = 0; nCol < otherColumns; nCol++)
				{
					for(int nRow = 0; nRow < rows; nRow++)
					{
						float val = 0;
						
						for(int i = 0; i < columns; i++)
						{ val += this->Get(i, nRow) * m.Get(nCol, i); }
						
						nMat.Set(nCol, nRow, val);
					}
				}
				
				return nMat;
			}
			
			void operator +=(Matrix<columns, rows> m)
			{
				*this = *this + m;
			}
			
			void operator -=(Matrix<columns, rows> m)
			{
				*this = *this - m;
			}
			
			void operator *=(Matrix<columns, rows> m)
			{
				*this = *this * m;
			}
			
			static Matrix<columns, rows> Identity()
			{
				Matrix<columns, rows> m;
				for(int cl = 0; cl < columns; cl++)
				{ m.Set(cl, cl, 1.0f); }
				
				return m;
			}
			
			float Get(int column, int row) const
			{
				int i = GetIndex(column, row);
				return c[i];
			}

			Matrix<1, rows> GetColumn(int column) const
			{
				Matrix<1, rows> mat;
				for(int i = 0; i < rows; i++)
				{ mat.Set(0, i, Get(column, i)); }

				return mat;
			}

			Matrix<1, columns> GetRow(int row) const
			{
				Matrix<1, columns> mat;
				for(int i = 0; i < columns; i++)
				{ mat.Set(0, i, Get(i, row)); }

				return mat;
			}
			
			void Set(int column, int row, float value)
			{
				int i = GetIndex(column, row);
				c[i] = value;
			}
			
			void SetColumn(int column, Matrix<1, rows> values)
			{
				for(int i = 0; i < rows; i++)
				{ Set(column, i, values.Get(0, i)); }
			}
			
			void SetRow(int row, Matrix<1, columns> values)
			{
				for(int i = 0; i < columns; i++)
				{ Set(i, row, values.Get(0, i)); }
			}
			
			const float * const Data() const
			{
				return c;
			}
			
		private:
			float c[Size];

			int GetIndex(int column, int row) const
			{
				int i = (column * rows) + row;
				CheckIndex(i, Size);

				return i;
			}
	};

	struct Mat4 : public Matrix<4, 4>
	{
		public:
			Mat4() : Matrix<4, 4>() { }
			Mat4(const Matrix<4, 4>& m) : Matrix<4, 4>(m) { }

			Mat4 operator +(Matrix<4, 4>& m) const
			{
				return Matrix<4, 4>(*this) + m;
			}

			static Mat4 Perspective(float fov, float zNear, float zFar, float aspect)
			{
				Mat4 matrix;

				float frustum = GetFrustumScale(fov);
				matrix.Set(0, 0, frustum / aspect);
				matrix.Set(1, 1, frustum);
				matrix.Set(2, 2, (zFar + zNear) / (zNear - zFar));
				matrix.Set(2, 3, -1.0f);
				matrix.Set(3, 2, (2 * zFar * zNear) / (zNear - zFar));

				return matrix;
			}

		private:
			static float GetFrustumScale(float fov)
			{
				const float degToRad = (float)(M_PI * 2.0f / 360.0f);
				float rad = fov * degToRad;
				return 1.0f / tan(rad / 2.0f);
			}
	};
}