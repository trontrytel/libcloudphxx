# TODO - tmp
# get information about current host name
cmake_host_system_information(RESULT current_host QUERY HOSTNAME)

if("${current_host}" MATCHES "sampo")
  # using include() istead of find_package(libmpdata++) to use local CMake code
  # and not the system-installed one
  include(${CMAKE_SOURCE_DIR}/../../../libmpdataxx/libmpdata++-config.cmake)
else()
  find_package(libmpdata++)
endif()

if (NOT libmpdataxx_FOUND)
  message(FATAL_ERROR "libmpdata++ not found")
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  # make the Release flags the default
  set(CMAKE_CXX_FLAGS ${libmpdataxx_CXX_FLAGS_RELEASE})
  # ignore CMake defaults
  set(CMAKE_CXX_FLAGS_RELEASE "")
else()
  set(CMAKE_CXX_FLAGS_DEBUG ${libmpdataxx_CXX_FLAGS_DEBUG})
endif()

# std::future
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("#include <future>\n int main() { std::future<void> f; }\n" STD_FUTURE_WORKS)
if(${STD_FUTURE_WORKS})
  add_definitions(-DSTD_FUTURE_WORKS)
endif()

add_executable(icicle icicle.cpp)

target_link_libraries(icicle ${libmpdataxx_LIBRARIES})
target_include_directories(icicle PUBLIC ${libmpdataxx_INCLUDE_DIRS})
if("${current_host}" MATCHES "sampo")
  target_include_directories(icicle PUBLIC ${CMAKE_SOURCE_DIR}/../../../libmpdataxx/) 
endif()

find_package(Boost COMPONENTS thread iostreams system timer program_options filesystem REQUIRED)
target_link_libraries(icicle ${Boost_LIBRARIES})

target_link_libraries(icicle ${libcloudphxx_LIBRARIES})

install(TARGETS icicle DESTINATION bin)
