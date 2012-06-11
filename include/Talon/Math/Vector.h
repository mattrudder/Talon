
#pragma once
#include <Talon/TalonPublic.h>

#if TALON_MATH==TALON_MATH_SSE2
#include <Talon/Math/SSE/Simd.h>
#endif

namespace Talon
{
#if TALON_MATH == TALON_MATH_SSE2
	typedef __m128 Vector;

#endif

	Vector operator+ (VectorArgL1 V);
	Vector operator- (VectorArgL1 V);
	Vector& operator+= (Vector& V1, VectorArgL1 V2);
	Vector& operator-= (Vector& V1, VectorArgL1 V2);
	Vector& operator*= (Vector& V1, VectorArgL1 V2);
	Vector& operator/= (Vector& V1, VectorArgL1 V2);
	Vector& operator*= (Vector& V, float S);
	Vector& operator/= (Vector& V, float S);
	Vector operator+ (VectorArgL1 V1, VectorArgL1 V2);
	Vector operator- (VectorArgL1 V1, VectorArgL1 V2);
	Vector operator* (VectorArgL1 V1, VectorArgL1 V2);
	Vector operator/ (VectorArgL1 V1, VectorArgL1 V2);
	Vector operator* (VectorArgL1 V, float S);
	Vector operator* (float S, VectorArgL1 V);
	Vector operator/ (VectorArgL1 V, float S);
}

//namespace Talon { namespace Math
//{
//	template <typename Real, typename Rep>
//	class Vector4
//	{
//	public:
//		inline Vector4() {}
//		inline Vector4(Real *pVector)
//			: m_rep(pVector) {}
//		inline Vector4(Real f)
//			: m_rep(f) {}
//		inline Vector4(Real x, Real y, Real z, Real w)
//			: m_rep(x, y, z, w) {}
//		inline Vector4(const Rep& rep)
//			: m_rep(rep) {}
//		inline Vector4(const Vector4& rhs)
//			: m_rep(rhs.m_rep) {}
//
//		inline Vector4& operator=(const Vector4& rhs)
//		{
//			XMVECTOR
//			XMVector2Dot();
//			m_rep = rhs.m_rep;
//			return *this;
//		}
//
//		inline Vector4& operator+=(const Vector4& rhs)
//		{
//			m_rep += rhs.m_rep;
//			return *this;
//		}
//
//		inline Vector4& operator-=(const Vector4& rhs)
//		{
//			m_rep -= rhs.m_rep;
//			return *this;
//		}
//
//		inline Vector4& operator*=(const Vector4& rhs)
//		{
//			m_rep *= rhs.m_rep;
//			return *this;
//		}
//
//		inline Vector4& operator/=(const Vector4& rhs)
//		{
//			m_rep /= rhs.m_rep;
//			return *this;
//		}
//
//		inline Vector4& operator+(const Vector4& rhs)
//		{
//			return Vector4(m_rep + rhs.m_rep);
//		}
//
//		inline Vector4& operator-(const Vector4& rhs)
//		{
//			return Vector4(m_rep - rhs.m_rep);
//		}
//
//		inline Vector4& operator*(const Vector4& rhs)
//		{
//			return Vector4(m_rep * rhs.m_rep);
//		}
//
//		inline Vector4& operator/(const Vector4& rhs)
//		{
//			return Vector4(m_rep / rhs.m_rep);
//		}
//
//		inline void Store(Real* pVector) const
//		{
//			m_rep.Store(pVector);
//		}
//
//		inline void Bc()
//		{
//			m_rep.Bc();
//		}
//
//		static inline Vector4 Dot(const Vector4)
//
//	private:
//		Rep m_rep;
//	};
//
//	typedef Vector4<float, SimdType> vec4;
//}