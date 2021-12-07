#ifndef JTEST_H_INCLUDED
#define JTEST_H_INCLUDED

template <typename T>
class JTest {
public:
	static void assert_equal(T a, T b);
	static void assert_array_equal(T * a, int aLen, T * b, int bLen);
	static void assert_not_null(T * a);
	static void assert_null(T * a);
	static void assert_gt(T a, T b);
	static void assert_gte(T a, T b);
	static void assert_lt(T a, T b);
	static void assert_lte(T a, T b);
};


#endif // JTEST_H_INCLUDED
