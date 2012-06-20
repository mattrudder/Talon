
#pragma once

#if TALON_WINDOWS
#include <xmmintrin.h>
#endif

namespace Talon
{
	inline Vector Vector4Load(const float4* v)
	{
		return _mm_load_ps(&v->x);
	}
	
	inline Vector Vector4Load(float x, float y, float z, float w)
	{
		return _mm_set_ps(x, y, z, w);
	}

	inline Vector Vector2Load(const float2* v)
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