list(APPEND delaunay_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/Operators_test.hpp)
list(APPEND delaunay_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/Reader_test.hpp)
list(APPEND delaunay_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/Triangulation_test.hpp)


list(APPEND delaunay_test_includes ${CMAKE_CURRENT_SOURCE_DIR})

set(delaunay_test_headers ${delaunay_test_headers} PARENT_SCOPE)
set(delaunay_test_includes ${delaunay_test_includes} PARENT_SCOPE)
