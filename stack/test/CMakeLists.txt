add_executable(test_stack stack_test.cpp)
target_link_libraries(test_stack PRIVATE hc_stack GTest::gtest_main)
gtest_discover_tests(test_stack)
