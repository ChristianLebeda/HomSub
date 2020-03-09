project(experiments)

file(GLOB experiments_SRC
    "include/experiments/*.h"
    "src/*.cpp"
    "main.cpp"
)

# Create the executable
add_executable(${PROJECT_NAME} ${experiments_SRC})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    thesis::homomorphism
)
