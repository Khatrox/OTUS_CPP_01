#define BOOST_TEST_MODULE test

#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "lib.h"

BOOST_AUTO_TEST_SUITE(BOOST_TEST_MODULE)

BOOST_AUTO_TEST_CASE(Check)
{
	BOOST_CHECK(ProjectVersion::GetPatch() != 0);
}

}
