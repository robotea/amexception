cmake_minimum_required(VERSION 3.12)

set(${CMAKE_RUNTIME_LIBRARY_OUTPUT_DIRECTORY} "build")

# set the project name and version
project(AMException VERSION 201909.0)
file(GLOB SOURCES "src/*.cpp")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

########################################
# Testing
########################################
# Options. Turn on with 'cmake -Dmyvarname=ON'.
# option(BUILD_TESTS "Build all tests." ON) # Makes boolean 'test' available.

# google test is a git submodule for the project, and it is also cmake-based
add_subdirectory(./dependencies/googletest)

enable_testing()
#
# Include the gtest library. gtest_SOURCE_DIR is available due to
# 'project(gtest)' above.
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(dependencies dependencies/googletest/googletest/include dependencies/googletest/googlemock/include)

#set(CMAKE_CXX_FLAGS --coverage)
#set(CMAKE_CXX_FLAGS -fexceptions)
configure_file(src/AMExceptionConfig.h.in ../AMExceptionConfig.h)

add_executable(TEST_AMException dependencies/amlstring/src/AMLString.cpp test/Exception/test_AMException.cpp)
target_link_libraries(TEST_AMException gtest pthread)
#add_custom_target(Tests ALL COMMAND TEST_AMExeption)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" OFF)
# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/docs/doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/html/doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/..
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
