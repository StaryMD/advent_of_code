file(GLOB_RECURSE SOLUTION_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(FILTER SOLUTION_FILES INCLUDE REGEX "[0-9]+/[0-9]+/(a|b|both).cpp")

file(GLOB_RECURSE UTILITY_FILES "${CMAKE_CURRENT_SOURCE_DIR}/utility/*.cpp")

add_executable(report report.cpp ${SOLUTION_FILES} ${UTILITY_FILES})

target_include_directories(report PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/gen)

set_property(TARGET report PROPERTY CXX_STANDARD ${MY_CPP_VERSION})
set_property(TARGET report PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_options(report PRIVATE -Ofast)

find_package(Python REQUIRED)

execute_process(
    COMMAND ${Python_EXECUTABLE} ${CMAKE_MODULE_PATH}/solution_setup.py
        --srcs "${CMAKE_SOURCE_DIR}/src"
        --indir "${CMAKE_BINARY_DIR}/data"
        --sols "${CMAKE_BINARY_DIR}/gen/solution_files.hpp"
)
