#include "stdafx.h"

#include "../lw1/Impl.hpp"

BOOST_AUTO_TEST_SUITE(Calc_)

BOOST_AUTO_TEST_CASE(Swap_)
{
	{
		BOOST_CHECK_EQUAL(Swap(123), 321);
		BOOST_CHECK_EQUAL(Swap(1230), 231);
	}
}

BOOST_AUTO_TEST_CASE(Check_)
{
	{
		BOOST_CHECK(Check(10, 5) == nullopt);
		BOOST_CHECK(Check(3, 100) == nullopt);
	}
	{
		const auto bla = Check(61, 100);
		const auto isEqual = *bla == list<size_t>{1, 2, 4, 8, 16, 61};
		BOOST_CHECK(isEqual);
	}
	{
		const auto bla = Check(1, 10);
		const auto isEqual = *bla == list<size_t>{1};
		BOOST_CHECK(isEqual);
	}
	{
		const auto bla = Check(2, 10);
		const auto isEqual = *bla == list<size_t>{1, 2};
		BOOST_CHECK(isEqual);
	}
	{
		const auto bla = Check(1221, 1500);
		const auto isEqual = *bla == list<size_t>{1, 11, 22, 221, 122, 1221};
		BOOST_CHECK(isEqual);
	}
	{
		const auto bla = Check(18, 100);
		const auto isEqual = *bla == list<size_t>{1, 2, 4, 8, 81, 18};
		BOOST_CHECK(isEqual);
	}
	{
#ifdef NDEBUG
		const auto bla = Check(22411, 23000);
		const auto isEqual = *bla == list<size_t>{1, 2, 21, 211, 422, 224, 2241, 22411};
		BOOST_CHECK(isEqual);
#endif
	}
}

BOOST_AUTO_TEST_SUITE_END()
