file(GLOB SOURCES ./*.cpp)
file(GLOB HEADERS ./*.h)

add_library(pmp $<IF:$<BOOL:${PMP_BUILD_SHARED_LIBRARY}>,"SHARED","STATIC">)
add_library(pmp::pmp ALIAS pmp)
set_target_properties(pmp PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
target_sources(pmp PRIVATE ${SOURCES} ${HEADERS})

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
  target_link_libraries(pmp PUBLIC OpenMP::OpenMP_CXX)
endif()

set_target_properties(pmp PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(
  pmp
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../>
          $<INSTALL_INTERFACE:include/>)

target_compile_features(pmp PUBLIC cxx_std_17)
target_link_libraries(pmp PUBLIC Eigen3::Eigen)

if(NOT EMSCRIPTEN AND PMP_INSTALL)
  install(
    TARGETS pmp
    EXPORT pmpTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES
    DESTINATION include)
  install(FILES ${HEADERS} DESTINATION include/pmp/)
else()
  target_include_directories(pmp PUBLIC ${EIGEN3_INCLUDE_DIR})
endif()

include(algorithms/CMakeLists.txt)
include(io/CMakeLists.txt)
