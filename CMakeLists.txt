# Adapted from "Modern CMake Sample"
# https://github.com/pabloariasal/modern-cmake-sample

cmake_minimum_required(VERSION 3.18.0)
project(libraytracer VERSION 0.0.1 LANGUAGES CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

# Create target, set properties
########################################

add_library(raytracer INTERFACE) 
add_library(raytracer::raytracer ALIAS raytracer)

target_include_directories(raytracer
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(raytracer INTERFACE cxx_auto_type)


# Here we would add link libraries, but currently there are none
# target_link_libraries(raytracer ....)

# Installation instructions
########################################

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/raytracer)

install(TARGETS raytracer 
    EXPORT  raytracer_targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT raytracer_targets
    FILE
        raytracer_targets.cmake
    NAMESPACE
        raytracer::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)                

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/raytracer_config_version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/raytracer_config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/raytracer_config.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/raytracer_config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/raytracer_config_version.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

# Exporting from build tree 
########################################

export(EXPORT raytracer_targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/raytracer_targets.cmake
    NAMESPACE raytracer::)

export(PACKAGE raytracer)

# Add testing
########################################

enable_testing()
add_subdirectory(test)

