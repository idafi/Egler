#pragma once

// - - - - - -
// matrix math - matricies are column-major
// - - - - - -

#include "Common.hpp"

template<int columns, int rows>
struct Matrix
{
	public:
		Matrix()
		{
			memset(c, 0, size * sizeof(float));
		}
		
		Matrix(const Matrix<columns, rows>& m)
		{
			memcpy(c, &m, size * sizeof(float));
		}

		bool operator ==(Matrix<columns, rows> m) const
		{
			return !memcmp(this->c, m.c, size * sizeof(float));
		}
		
		bool operator !=(Matrix<columns, rows> m) const
		{
			return memcmp(this->c, m.c, size * sizeof(float));
		}
		
		float operator [](int i) const
		{
			AssertIndex(i);
			return c[i];
		}
		
		float& operator [](int i)
		{
			AssertIndex(i);
			return c[i];
		}
		
		Matrix<columns, rows> operator +(Matrix<columns, rows> m) const
		{
			Matrix<columns, rows> nMat = *this;
			for(int i = 0; i < size; i++)
			{ nMat.c[i] = this->c[i] + m.c[i]; }
			
			return nMat;
		}
		
		Matrix<columns, rows> operator -(Matrix<columns, rows> m) const
		{
			Matrix<columns, rows> nMat = *this;
			for(int i = 0; i < size; i++)
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
		
		void Set(int column, int row, float value)
		{
			int i = GetIndex(column, row);
			c[i] = value;
		}
		
		template<int rows>
		void SetColumn(int column, Matrix<1, rows> values)
		{
			int i = GetIndex(column, 0);
			memcpy(&c[i], values.Data(), sizeof(float) * rows);
		}
		
		template<int columns>
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
		static constexpr int size = columns * rows;
		float c[size];

		inline void AssertIndex(int i)
		{
			assert(i > -1 && i < size);
		}
		
		int GetIndex(int column, int row) const
		{
			int i = (column * rows) + row;
			AssertIndex(i);

			return i;
		}
};

struct Mat4 : public Matrix<4, 4>
{
	public:
		Mat4() : Matrix<4, 4>() { }
		Mat4(const Matrix<4, 4>& m) : Matrix<4, 4>(m) { }
}