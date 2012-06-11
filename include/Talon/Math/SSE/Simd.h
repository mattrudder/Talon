
#pragma once
#include <Talon/TalonPublic.h>

#if TALON_WINDOWS
#include <xmmintrin.h>
#endif

namespace Talon
{
	typedef __m128 Vector;

	typedef const Vector VectorArgL1;
	typedef const Vector VectorArgL2;
	typedef const Vector& VectorArgLX;
}

namespace Talon { namespace Simd
{
	inline Vector Load(float _x, float _y, float _z, float _w) { return _mm_set_ps(_x, _y, _z, _w); }
	inline Vector Load(float _x, float _y)
	{
		__m128 x = _mm_load_ss(&_x);
		__m128 y = _mm_load_ss(&_y);
		return _mm_unpacklo_ps(x, y);
	}
	inline Vector Load(const float* p) { return _mm_load_ps(p); }

	inline void Store(float4* p, VectorArgL1 v) { _mm_storeu_ps(&p->x, v); }
	inline void Store(float3* p, VectorArgL1 v)
	{
		Vector t1 = _mm_shuffle_ps(v, v,_MM_SHUFFLE(1,1,1,1));
		Vector t2 = _mm_shuffle_ps(v, v,_MM_SHUFFLE(2,2,2,2));
		_mm_store_ss(&p->x, v);
		_mm_store_ss(&p->y, t1);
		_mm_store_ss(&p->z, t2);
	}
	inline void Store(float2* p, VectorArgL1 v)
	{
		Vector t = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ss(&p->x, v);
		_mm_store_ss(&p->y, t);
	}

    //class SimdType
    //{
    //public:
    //    inline SimdType() {}
    //    inline SimdType(float* pVector)
    //        : m_vector(_mm_load_ps(pVector)) {}
    //    inline SimdType(const __m128& qword)
    //        : m_vector(qword) {}
    //    inline SimdType(float x, float y, float z, float w)
    //        : m_vector(_mm_set_ps(x, y, z, w)) {}
    //    inline SimdType(const SimdType& rhs)
    //        : m_vector(rhs.vector) {}

    //    inline SimdType& operator=(const SimdType& rhs)
    //    {
    //        m_vector = rhs.m_vector;
    //        return *this;
    //    }

    //    inline SimdType& operator+=(const SimdType& rhs)
    //    {
    //        m_vector = _mm_add_ps(m_vector, rhs.m_vector);
    //        return *this;
    //    }

    //    inline SimdType& operator-=(const SimdType& rhs)
    //    {
    //        m_vector = _mm_sub_ps(m_vector, rhs.m_vector);
    //        return *this;
    //    }

    //    inline SimdType& operator*=(const SimdType& rhs)
    //    {
    //        m_vector = _mm_mul_ps(m_vector, rhs.m_vector);
    //        return *this;
    //    }

    //    inline SimdType& operator/=(const SimdType& rhs)
    //    {
    //        m_vector = _mm_div_ps(m_vector, rhs.m_vector);
    //        return *this;
    //    }

    //    inline SimdType& operator+(const SimdType& rhs)
    //    {
    //        return SimdType(_mm_add_ps(m_vector, rhs.m_vector));
    //    }

    //    inline SimdType& operator-(const SimdType& rhs)
    //    {
    //        return SimdType(_mm_sub_ps(m_vector, rhs.m_vector));
    //    }

    //    inline SimdType& operator*(const SimdType& rhs)
    //    {
    //        return SimdType(_mm_mul_ps(m_vector, rhs.m_vector));
    //    }

    //    inline SimdType& operator/(const SimdType& rhs)
    //    {
    //        return SimdType(_mm_div_ps(m_vector, rhs.m_vector));
    //    }

    //    inline void Store(float* pVector) const
    //    {
    //        _mm_store_ps(pVector, m_vector);
    //    }

    //    inline void Bc()
    //    {
    //        m_vector = _mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 3, 3, 3));
    //    }

    //    static inline SimdType Dot(const SimdType& va, const SimdType& vb)
    //    {
    //        const __m128 t0 = _mm_mul_ps(va.m_vector, vb.m_vector);
    //        const __m128 t1 = _mm_shuffle_ps(t0, t0, _MM_SHUFFLE(1, 0, 3, 2));
    //        const __m128 t2 = _mm_add_ps(t0, t1);
    //        const __m128 t3 = _mm_shuffle_ps(t2, t2, _MM_SHUFFLE(2, 3, 0, 1));

    //        return SimdType(_mm_add_ps(t3, t2));
    //    }

    //    static inline SimdType Sqrt(const SimdType& va)
    //    {
    //        return SimdType(_mm_sqrt_ps(va.m_vector));
    //    }

    //    static inline SimdType GetX(float* p, const SimdType& v)
    //    {
    //        _mm_store_ss(p, v.m_vector);
    //    }

    //private:
    //    __m128 m_vector;
    //};
}}