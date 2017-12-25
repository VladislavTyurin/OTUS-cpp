#define BOOST_TEST_MODULE test_version

#include "ip_filter.cpp"
#include "test_data.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_ip)

BOOST_AUTO_TEST_CASE(test_ip_filter_without_params)
{
    std::vector<VecStr > ip_pool = test_data();
    BOOST_CHECK(filter(ip_pool),std::ostream<<ip_pool);
}

BOOST_AUTO_TEST_SUITE_END()


