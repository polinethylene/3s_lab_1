add_executable(Tests tests.cpp)
add_subdirectory(googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

target_link_libraries(Tests gtest gtest_main)