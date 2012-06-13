
#pragma once

#include "TalonPlatform.h"
#include <stdint.h>

typedef int8_t i8;
typedef uint8_t u8;

typedef int16_t i16;
typedef uint16_t u16;

typedef int32_t i32;
typedef uint32_t u32;

typedef int64_t i64;
typedef uint64_t u64;

#if TALON_COMPILER_VENDOR == TALON_COMPILER_VENDOR_VS
#	pragma warning(push)
#	pragma warning(disable : 4324) // structure was padded due to __declspec(align())
#endif

struct float2
{
	float x;
	float y;

	float2() : x(0), y(0) {}
	float2(float _x, float _y) : x(_x), y(_y) {}
	explicit float2(const float *pVector) : x(pVector[0]), y(pVector[1]) {}

	float2& operator= (const float2& v) { x = v.x; y = v.y; return *this; }
};

TALON_ALIGN(16, 
struct float2a : public float2
{
	float2a(float _x, float _y) : float2(_x, _y) {}
	explicit float2a(const float *pVector) : float2(pVector) {}

	float2a& operator= (const float2a& v) { x = v.x; y = v.y; return *this; }
});

struct float3
{
	float x;
	float y;
	float z;

	float3() : x(0), y(0), z(0) {}
	float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	explicit float3(const float *pVector) : x(pVector[0]), y(pVector[1]), z(pVector[2]) {}

	float3& operator= (const float3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

TALON_ALIGN(16, 
struct float3a : public float3
{
	float3a(float _x, float _y, float _z) : float3(_x, _y, _z) {}
	explicit float3a(const float *pVector) : float3(pVector) {}

	float3a& operator= (const float3a& v) { x = v.x; y = v.y; z = v.z; return *this; }
});

struct float4
{
	float x;
	float y;
	float z;
	float w;

	float4() : x(0), y(0), z(0), w(0) {}
	float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	explicit float4(const float *pVector) : x(pVector[0]), y(pVector[1]), z(pVector[2]), w(pVector[3]) {}

	float4& operator= (const float4& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
};

TALON_ALIGN(16,
struct float4a : public float4
{
	float4a(float _x, float _y, float _z, float _w) : float4(_x, _y, _z, _w) {}
	explicit float4a(const float *pVector) : float4(pVector) {}

	float4a& operator= (const float4a& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
});

#if TALON_COMPILER_VENDOR == TALON_COMPILER_VENDOR_VS
#	pragma warning(pop)
#endif

//typedef char CHAR8;
//typedef wchar_t CHAR16;
