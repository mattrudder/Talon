#include <UnitTest++.h>
#include <Talon/Talon.h>
using namespace Talon;

TEST(Vector2LoadStore)
{
	float2a f(1, 2);
	Vector a = Vector2Load(f.x, f.y);
	Vector b = Vector2Load(&f);

	CHECK(memcmp(&a, &b, sizeof(Vector)) == 0);

	float2 v;
	StoreFloat2(&v, a);

	CHECK(f.x == v.x && f.y == v.y);
}

TEST(Vector3LoadStore)
{
	float3a f(1, 2, 3);
	Vector a = Vector3Load(f.x, f.y, f.z);
	Vector b = Vector3Load(&f);

	CHECK(memcmp(&a, &b, sizeof(Vector)) == 0);

	float3 v;
	StoreFloat3(&v, a);

	CHECK(f.x == v.x && f.y == v.y && f.y == v.y && f.z == v.z);
}

TEST(Vector4LoadStore)
{
	float4a f(1, 2, 3, 4);
	Vector a = Vector4Load(f.x, f.y, f.z, f.w);
	Vector b = Vector4Load(&f);

	CHECK(memcmp(&a, &b, sizeof(Vector)) == 0);

	float4 v;
	StoreFloat4(&v, a);

	CHECK(f.x == v.x && f.y == v.y && f.y == v.y && f.z == v.z && f.w == v.w);
}

TEST(VectorAdd)
{
	Vector a = Vector2Load(2, 0);
	Vector b = Vector2Load(0, 3);

	float2 r;
	StoreFloat2(&r, a + b);

	CHECK(r.x == 2);
	CHECK(r.y == 3);
}

TEST(VectorSubtract)
{
	Vector a = Vector2Load(2, 6);
	Vector b = Vector2Load(1, 3);

	float2 r;
	StoreFloat2(&r, a - b);

	CHECK(r.x == 1);
	CHECK(r.y == 3);
}

TEST(VectorMultiply)
{
	Vector a = Vector2Load(2, 2);
	Vector b = Vector2Load(4, 8);

	float2 r;
	StoreFloat2(&r, a * b);

	CHECK(r.x == 8);
	CHECK(r.y == 16);
}

TEST(VectorDivide)
{
	Vector a = Vector2Load(4, 8);
	Vector b = Vector2Load(2, 2);

	float2 r;
	StoreFloat2(&r, a / b);

	CHECK(r.x == 2);
	CHECK(r.y == 4);
}

TEST(VectorNegate)
{
	Vector a = Vector2Load(4, 8);

	float2 r;
	StoreFloat2(&r, -a);

	CHECK(r.x == -4);
	CHECK(r.y == -8);
}

TEST(VectorScale)
{
	Vector a = Vector2Load(4, 8);

	float2 r;
	StoreFloat2(&r, a * 10);

	CHECK(r.x == 40);
	CHECK(r.y == 80);
}

TEST(VectorDot)
{
	Vector a = Vector4Load(1, 2, 3, 4);
	Vector b = Vector4Load(5, 6, 7, 8);

	float r = Vector4Dot(a, b);
	CHECK(r == 70);

	a = Vector3Load(1, 2, 3);
	b = Vector3Load(3, 4, 5);
	r = Vector3Dot(a, b);
	CHECK(r == 26);

	a = Vector2Load(1, 2);
	b = Vector2Load(3, 4);
	r = Vector2Dot(a, b);
	CHECK(r == 11);
}