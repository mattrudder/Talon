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