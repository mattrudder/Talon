#include <UnitTest++.h>
#include <Talon/Talon.h>
using namespace Talon;

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