project(Sortings)

set(TESTS_NAME ${PROJECT_NAME}_tests)

include(FetchContent)
FetchContent_Declare(
       googletest
       GIT_REPOSITORY https://github.com/google/googletest.git
       GIT_TAG        release-1.11.0
       UPDATE_DISCONNECTED   ON
)
FetchContent_MakeAvailable(googletest)

# add_subdirectory(../lib/googletest build)

add_executable(ShellSort_tests ShellSort.tests.cpp)
target_link_libraries(ShellSort_tests ShellSort gtest_main)

add_executable(HeapSort_tests HeapSort.tests.cpp)
target_link_libraries(HeapSort_tests HeapSort gtest_main)

add_executable(MergeSort_tests MergeSort.tests.cpp)
target_link_libraries(MergeSort_tests MergeSort gtest_main)

add_executable(QuickSort_tests QuickSort.tests.cpp)
target_link_libraries(QuickSort_tests QuickSort gtest_main)

add_executable(LSDSort_tests LSDSort.tests.cpp)
target_link_libraries(LSDSort_tests LSDSort gtest_main)

add_executable(${TESTS_NAME} Sortings.tests.cpp)
target_link_libraries(${TESTS_NAME} ShellSort gtest_main)
target_link_libraries(${TESTS_NAME} HeapSort gtest_main)
target_link_libraries(${TESTS_NAME} QuickSort gtest_main)
target_link_libraries(${TESTS_NAME} MergeSort gtest_main)
target_link_libraries(${TESTS_NAME} LSDSort gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TESTS_NAME})