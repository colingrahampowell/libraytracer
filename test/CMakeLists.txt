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

add_executable(raytracer_test src/example_test.cpp)
target_compile_features(raytracer_test PRIVATE cxx_auto_type)
target_link_libraries(raytracer_test gtest_main raytracer::raytracer)

