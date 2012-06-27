#include <UnitTest++.h>
#include <Talon/Talon.h>
using namespace Talon;

TEST(MatrixIdentity)
{
	Matrix m1 = MatrixIdentity();
	Matrix m2(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	CHECK(MatrixIsIdentity(m1));
	CHECK(MatrixIsIdentity(m2));
}

TEST(MatrixMultiply)
{
	Matrix m1 = MatrixIdentity();
	Matrix m2(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	CHECK(MatrixIsIdentity(MatrixMultiply(m1, m2)));

	Matrix m3(
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 0, 1, 2,
		3, 4, 5, 6
	);

	Matrix m = m3 * m1;
	for (int i = 0; i < 4; ++i) {
		Vector v1 = m.r[i];
		Vector v2 = m3.r[i];

		float4 f1, f2;
		StoreFloat4(&f1, v1);
		StoreFloat4(&f2, v2);

		CHECK(f1.x == f2.x);
		CHECK(f1.y == f2.y);
		CHECK(f1.z == f2.z);
		CHECK(f1.w == f2.w);
	}
	
}

TEST(MatrixRotationX)
{
	Matrix m = MatrixRotationX(Pi);

	float4 f;

	// Row 1
	StoreFloat4(&f, m.r[0]);
	CHECK(f.x == 1 && f.y == 0 && f.z == 0 && f.w == 0);

	// Row 2
	StoreFloat4(&f, m.r[1]);
	CHECK(f.x == 0 && f.y == cosf(Pi) && f.z == sinf(Pi) && f.w == 0);

	// Row 3
	StoreFloat4(&f, m.r[2]);
	CHECK(f.x == 0 && f.y == -sinf(Pi) && f.z == cosf(Pi) && f.w == 0);

	// Row 4
	StoreFloat4(&f, m.r[3]);
	CHECK(f.x == 0 && f.y == 0 && f.z == 0 && f.w == 1);
}

TEST(MatrixRotationY)
{
	Matrix m = MatrixRotationY(Pi);

	float4 f;

	// Row 1
	StoreFloat4(&f, m.r[0]);
	CHECK(f.x == cosf(Pi) && f.y == 0 && f.z == -sinf(Pi) && f.w == 0);

	// Row 2
	StoreFloat4(&f, m.r[1]);
	CHECK(f.x == 0 && f.y == 1.0f && f.z == 0.0f && f.w == 0);

	// Row 3
	StoreFloat4(&f, m.r[2]);
	CHECK(f.x == sinf(Pi) && f.y == 0.0 && f.z == cosf(Pi) && f.w == 0);

	// Row 4
	StoreFloat4(&f, m.r[3]);
	CHECK(f.x == 0 && f.y == 0 && f.z == 0 && f.w == 1);
}

TEST(MatrixRotationZ)
{
	Matrix m = MatrixRotationZ(Pi);

	float4 f;

	// Row 1
	StoreFloat4(&f, m.r[0]);
	CHECK(f.x == cosf(Pi) && f.y == sinf(Pi) && f.z == 0.0 && f.w == 0);

	// Row 2
	StoreFloat4(&f, m.r[1]);
	CHECK(f.x == -sinf(Pi) && f.y == cosf(Pi) && f.z == 0.0f && f.w == 0);

	// Row 3
	StoreFloat4(&f, m.r[2]);
	CHECK(f.x == 0.0f && f.y == 0.0 && f.z == 1.0f && f.w == 0);

	// Row 4
	StoreFloat4(&f, m.r[3]);
	CHECK(f.x == 0 && f.y == 0 && f.z == 0 && f.w == 1);
}

TEST(MatrixScale)
{
	Matrix m = MatrixScale(5);

	float4 f;

	// Row 1
	StoreFloat4(&f, m.r[0]);
	CHECK(f.x == 5.0f && f.y == 0.0f && f.z == 0.0f && f.w == 0.0f);

	// Row 2
	StoreFloat4(&f, m.r[1]);
	CHECK(f.x == 0.0f && f.y == 5.0f && f.z == 0.0f && f.w == 0.0f);

	// Row 3
	StoreFloat4(&f, m.r[2]);
	CHECK(f.x == 0.0f && f.y == 0.0f && f.z == 5.0f && f.w == 0.0f);

	// Row 4
	StoreFloat4(&f, m.r[3]);
	CHECK(f.x == 0.0f && f.y == 0.0f && f.z == 0.0f && f.w == 1.0f);
}