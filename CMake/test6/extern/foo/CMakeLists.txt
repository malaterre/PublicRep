cmake_minimum_required(VERSION 3.9)

# Defines project-specific attributes (PROJECT_xxx and foo_xxx)
# https://cmake.org/cmake/help/v3.11/command/project.html
project(foo VERSION 0.1.2 LANGUAGES C DESCRIPTION "An installable sample library.")

# This include defines standard install locations.
# https://cmake.org/cmake/help/v3.11/module/GNUInstallDirs.html
include(GNUInstallDirs)

# This include provides some helper functions that simplify packaging.
# https://cmake.org/cmake/help/v3.11/module/CMakePackageConfigHelpers.html
include(CMakePackageConfigHelpers)

# All source files and private header files go here.
set(SOURCE_FILES
        foo.c)

# Here we define the library.
add_library(foo
        ${HEADER_FILES}
        ${SOURCE_FILES})

# We also add an alias definition so that we shadown
# the export namespace when using add_subdirectory() instead.
add_library(foo::foo ALIAS foo)

# By prefixing the installation paths with our name and version
# we can have multiple versions installed at the same time.
set(PROJECT_PREFIX foo-${foo_VERSION})

# Defines the headers for this library.
# https://cmake.org/cmake/help/v3.11/command/target_include_directories.html
target_include_directories(foo
        PUBLIC
            # Used when building the library:
            $<BUILD_INTERFACE:${foo_SOURCE_DIR}/include>
            # Used when installing the library:
            $<INSTALL_INTERFACE:include/${PROJECT_PREFIX}>
        PRIVATE
            # Used only when building the library:
            src)

# Here we configure variables specifying the target directories.
set(INSTALL_RUNTIME_DIR ${CMAKE_INSTALL_BINDIR})
set(INSTALL_CONFIG_DIR  ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/cmake)
set(INSTALL_LIBRARY_DIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/${CMAKE_BUILD_TYPE})
set(INSTALL_ARCHIVE_DIR ${CMAKE_INSTALL_LIBDIR}/${PROJECT_PREFIX}/${CMAKE_BUILD_TYPE}/static)
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_PREFIX}/foo)

# Define the configuration file locations.
set(PROJECT_CONFIG_VERSION_FILE "${PROJECT_BINARY_DIR}/foo-config-version.cmake")
set(PROJECT_CONFIG_FILE         "${PROJECT_BINARY_DIR}/foo-config.cmake")

configure_package_config_file(cmake/foo-config.cmake.in
        ${PROJECT_CONFIG_FILE}
        INSTALL_DESTINATION ${INSTALL_CONFIG_DIR})

# This auto-generates a version file.
write_basic_package_version_file(
        ${PROJECT_CONFIG_VERSION_FILE}
        COMPATIBILITY SameMajorVersion)

# The INSTALL(TARGET) command specifies where to install specific targets.
# By specifying EXPORT here, we add these targets to an export group.
install(TARGETS foo
        EXPORT foo-targets
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR})

# The INSTALL(FILES) command specifies where to install specific files, such as headers.
install(FILES ${HEADER_FILES}
        DESTINATION ${INSTALL_INCLUDE_DIR})

# The INSTALL(FILES) command specifies where to install specific files, such as headers.
install(FILES
            ${PROJECT_CONFIG_VERSION_FILE}
            ${PROJECT_CONFIG_FILE}
        DESTINATION ${INSTALL_CONFIG_DIR})

# The INSTALL(EXPORT) command installs a previously defined export group to a script.
install(EXPORT foo-targets
        FILE foo-targets.cmake
        NAMESPACE foo::
        DESTINATION ${INSTALL_CONFIG_DIR})

export(EXPORT foo-targets
       FILE ${CMAKE_CURRENT_BINARY_DIR}/foo-targets.cmake
       NAMESPACE foo::)

# Register the package in the user's package registry.
# https://cmake.org/cmake/help/v3.11/command/export.html
export(PACKAGE foo)
