#ifndef JTEST_H_INCLUDED
#define JTEST_H_INCLUDED

template <typename T>
void assert_equal(T a, T b);

template <typename T>
void assert_not_null(T * a);

template <typename T>
void assert_null(T * a);

template <typename T>
void assert_gt(T a, T b);

template <typename T>
void assert_gte(T a, T b);

template <typename T>
void assert_lt(T a, T b);

template <typename T>
void assert_lte(T a, T b);

#endif // JTEST_H_INCLUDED
