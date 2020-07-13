# Adapted from GoogleTest build instructions
# github.com/google/googletest/blob/master/googletest/README.md

find_package(GTest QUIET)
if(NOT GTEST_FOUND)

    # Suppress creation of ZERO_CHECK project
    set(CMAKE_SUPPRESS_REGENERATION true)
    
    # Download and build GoogleTest
    configure_file(${CMAKE_SOURCE_DIR}/cmake/CMakeLists.txt.in 
	${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

endif()

# from "Modern CMake", https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})

    target_link_libraries(${TESTNAME} gtest_main raytracer::raytracer)
	target_compile_features(${TESTNAME} PRIVATE cxx_auto_type)
    
	gtest_discover_tests(${TESTNAME}
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
    )
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()


package_add_test(vec3_test src/vec3_test.cpp)
package_add_test(vec4_test src/vec4_test.cpp)

