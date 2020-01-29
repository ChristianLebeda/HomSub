# Set the project name
project (homomorphism)

file(GLOB homomorphism_SRC
    "include/homomorphism/*.h"
    "src/*.cpp"
)

# Add a library with the above sources
add_library(${PROJECT_NAME} ${homomorphism_SRC}) 
add_library(thesis::homomorphism ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)