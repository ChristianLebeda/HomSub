cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-std=c++17 -Wno-ignored-attributes -pthread")

project(subgraph_thesis)

set (THIRD_PARTY_PATH \"${PROJECT_SOURCE_DIR}/third-party/\")
configure_file(third_party.h.in ${PROJECT_SOURCE_DIR}/homomorphism/include/homomorphism/third_party.h)

# Add sub directories
add_subdirectory(homomorphism)
add_subdirectory(experiments)
