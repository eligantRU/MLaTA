#include "stdafx.h"

#include "../lw6/Impl.hpp"

BOOST_AUTO_TEST_SUITE(lw6)

BOOST_AUTO_TEST_CASE(IsFirstWinner_)
{
	BOOST_CHECK(IsFirstWinner(1));
	BOOST_CHECK(IsFirstWinner(2));
	BOOST_CHECK(!IsFirstWinner(3));
	BOOST_CHECK(IsFirstWinner(4));
	BOOST_CHECK(!IsFirstWinner(5));
	BOOST_CHECK(IsFirstWinner(6));
	BOOST_CHECK(IsFirstWinner(7));
	BOOST_CHECK(!IsFirstWinner(8));
	BOOST_CHECK(IsFirstWinner(9));
	BOOST_CHECK(IsFirstWinner(80));
	BOOST_CHECK(!IsFirstWinner(100));
	BOOST_CHECK(IsFirstWinner(150));
	BOOST_CHECK(!IsFirstWinner(199));
}

BOOST_AUTO_TEST_SUITE_END()
