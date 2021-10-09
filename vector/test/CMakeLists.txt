add_executable(test_vector vector_test.cpp)
target_link_libraries(test_vector PRIVATE hc_vector GTest::gtest_main)
gtest_discover_tests(test_vector)
