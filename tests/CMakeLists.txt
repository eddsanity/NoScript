set(BINARY ${CMAKE_PROJECT_NAME}_test)

enable_testing()

add_executable(${BINARY} ParseLetStatementTest.cpp ParseRetStatementTest.cpp)
add_test(NAME ParseLetStatementTest
         COMMAND ${BINARY})

add_test(NAME ParseRetStatementTest
         COMMAND ${BINARY})

# target_include_directories(BINARY PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/doctest/include)
# target_compile_features(test PRIVATE cxx_std_17)
target_include_directories(${BINARY} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/doctest/doctest)
# target_link_libraries(test PRIVATE doctest::doctest)