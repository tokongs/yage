
add_executable(tests test.cpp test_input.cpp ../../editor/src/MovingCamera.cpp ../../editor/src/MovingCamera.h)

find_package(Catch2 REQUIRED)
if(CATCH_FOUND)
    target_link_libraries(tests Catch2::Catch2)
    target_include_directories(tests PUBLIC ${CATCH_INCLUDE_DIR})
    message(${CATCH_INCLUDE_DIR})
else()
    message([ERROR] "Failed to find Catch")
endif()



include(CTest)
include(Catch)
catch_discover_tests(tests)