cmake_minimum_required(VERSION 3.16.3)
cmake_policy(SET CMP0048 NEW)
project(
  pmp-library
  VERSION 2.0.1
  DESCRIPTION "The Polygon Mesh Processing Library"
  HOMEPAGE_URL "https://www.pmp-library.org")
cmake_policy(SET CMP0072 NEW)

option(PMP_BUILD_EXAMPLES "Build the PMP examples" OFF)
option(PMP_BUILD_TESTS "Build the PMP test programs" OFF)
option(PMP_BUILD_DOCS "Build the PMP documentation" OFF)
option(PMP_BUILD_VIS "Build the PMP visualization tools" OFF)
option(PMP_INSTALL "Install the PMP library and headers" OFF)
option(PMP_STRICT_COMPILATION "Treat compiler warnings as errors" ON)
option(PMP_BUILD_SHARED_LIBRARY "Build PMP as shared library" ON)
option(PMP_SCALAR_TYPE "Type of floating point precision used by PMP" 64)
option(PMP_INDEX_TYPE "Type of integer used by PMP" 32)

if (NOT TARGET Eigen3::Eigen)
  find_package(Eigen3 3.4 CONFIG REQUIRED)
endif()

# set default compiler flags for both gcc and clang
set(COMMON_CXX_FLAGS "-pedantic -Wall -Wextra -Wshadow")
if(PMP_STRICT_COMPILATION)
  set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -Werror")
endif()

if((UNIX OR APPLE) AND CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} ${COMMON_CXX_FLAGS} -Wno-deprecated-copy")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "7.0.0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-int-in-bool-context")
  endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT EMSCRIPTEN)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} ${COMMON_CXX_FLAGS} --system-header-prefix=Eigen")
endif()

if(WIN32)
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -D_USE_MATH_DEFINES -DNOMINMAX -D_CRT_SECURE_NO_WARNINGS"
  )
endif()

if(MSVC)
  add_compile_options(/wd4267) # conversion from size_t
  add_compile_options(/wd4244) # conversion from double to float
  add_compile_options(/wd4305) # truncation from double to float
endif()

# make a release build by default
if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type specified. Using 'Release' as default.")
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE
        STRING
        "The build type. Possible values: Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb")
endif()

# choose size of the scalar type
if(PMP_SCALAR_TYPE EQUAL 64)
  message(STATUS "Using 64-bit scalar type")
  add_definitions(-DPMP_SCALAR_TYPE_64)
endif()

# choose size of the index type
if(PMP_INDEX_TYPE EQUAL 64)
  message(STATUS "Using 64-bit index type")
  add_definitions(-DPMP_INDEX_TYPE_64)
endif()

# which directories to process
add_subdirectory(src/pmp)
if(PMP_BUILD_DOCS)
  add_subdirectory(docs)
endif()
if(PMP_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
if(PMP_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(NOT EMSCRIPTEN AND PMP_INSTALL)

  # Generate package configuration files
  include(CMakePackageConfigHelpers)

  set(PMP_CONFIG_PATH "lib${LIB_SUFFIX}/cmake/pmp")

  configure_package_config_file(
    cmake/pmpConfig.cmake.in pmpConfig.cmake
    INSTALL_DESTINATION "${PMP_CONFIG_PATH}"
    NO_CHECK_REQUIRED_COMPONENTS_MACRO)

  install(
    EXPORT pmpTargets
    FILE pmpTargets.cmake
    EXPORT_LINK_INTERFACE_LIBRARIES
    DESTINATION "${PMP_CONFIG_PATH}")

  export(TARGETS pmp FILE pmpTargets.cmake)

  write_basic_package_version_file(
    pmpConfigVersion.cmake
    VERSION ${PMP_VERSION}
    COMPATIBILITY SameMajorVersion)

  install(FILES "${PROJECT_BINARY_DIR}/pmpConfig.cmake"
                "${PROJECT_BINARY_DIR}/pmpConfigVersion.cmake"
          DESTINATION "${PMP_CONFIG_PATH}")

endif()

# add uninstall target if none is defined
if(NOT TARGET uninstall AND PMP_INSTALL)

  configure_file("${CMAKE_MODULE_PATH}/cmake_uninstall.cmake.in"
                 cmake_uninstall.cmake IMMEDIATE @ONLY)

  add_custom_target(uninstall "${CMAKE_COMMAND}" -P
                              "${PROJECT_BINARY_DIR}/cmake_uninstall.cmake")

endif()
