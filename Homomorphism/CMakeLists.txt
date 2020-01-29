# Set the project name
project (homomorphism)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/graph.cpp include/graph/graph.h) 
add_library(thesis::graph ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)