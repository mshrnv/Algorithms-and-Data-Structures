project(Set)

set(TESTS_NAME Set_tests)
set(TESTS_NAME Cone_tests)

#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG        release-1.11.0
#        UPDATE_DISCONNECTED   ON
#)
#FetchContent_MakeAvailable(googletest)

add_subdirectory(../lib/googletest build)

add_executable(Set_tests Set.tests.cpp)
target_link_libraries(Set_tests Set gtest_main)

add_executable(Cone_tests Cone.tests.cpp)
target_link_libraries(Cone_tests Set gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(Set_tests)
gtest_discover_tests(Cone_tests)