project(test)

file(GLOB test_SRC
    "include/test/*.h"
    "src/*.cpp"
    "main.cpp"
)

# Create the executable
add_executable(${PROJECT_NAME} ${test_SRC})

target_link_libraries(${PROJECT_NAME}
    thesis::homomorphism
)
