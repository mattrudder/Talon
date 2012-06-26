
#pragma once

namespace Talon
{
	inline Vector Vector4Load(const float4* v)
	{
		return Vector4Load(v->x, v->y, v->z, v->w);
	}

	inline Vector Vector4Load(const float4a* v)
	{
		return _mm_load_ps(&v->x);
	}
	
	inline Vector Vector4Load(float x, float y, float z, float w)
	{
		return _mm_set_ps(w, z, y, x);
	}

	inline Vector Vector3Load(const float3* v)
	{
		return Vector3Load(v->x, v->y, v->z);
	}

	inline Vector Vector3Load(const float3a* v)
	{
		// Read 4 elements, zero out the last.
		__m128 t = _mm_load_ps(&v->x);
		return _mm_and_ps(t, VectorMask3);
	}

	inline Vector Vector3Load(float x, float y, float z)
	{
		__m128 vX = _mm_load_ss(&x);
		__m128 vY = _mm_load_ss(&y);
		__m128 vZ = _mm_load_ss(&z);
		__m128 vXY = _mm_unpacklo_ps(vX, vY);
		return _mm_movelh_ps(vXY, vZ);
	}

	inline Vector Vector2Load(const float2* v)
	{
		return Vector2Load(v->x, v->y);
	}
	
	inline Vector Vector2Load(const float2a* v)
	{
		__m128 x = _mm_load_ss(&v->x);
		__m128 y = _mm_load_ss(&v->y);
		return _mm_unpacklo_ps(x, y);
	}
	
	inline Vector Vector2Load(float x, float y)
	{
		__m128 _x = _mm_load_ss(&x);
		__m128 _y = _mm_load_ss(&y);
		return _mm_unpacklo_ps(_x, _y);
	}

	inline void StoreFloat4(float4* p, VectorArgL1 v)
	{
		_mm_storeu_ps(&p->x, v);
	}
	
	inline void StoreFloat3(float3* p, VectorArgL1 v)
	{
		Vector t1 = _mm_shuffle_ps(v, v,_MM_SHUFFLE(1,1,1,1));
		Vector t2 = _mm_shuffle_ps(v, v,_MM_SHUFFLE(2,2,2,2));
		_mm_store_ss(&p->x, v);
		_mm_store_ss(&p->y, t1);
		_mm_store_ss(&p->z, t2);
	}
	
	inline void StoreFloat2(float2* p, VectorArgL1 v)
	{
		Vector t = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
		_mm_store_ss(&p->x, v);
		_mm_store_ss(&p->y, t);
	}
}