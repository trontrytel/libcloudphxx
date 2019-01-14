# TODO (tmp): get information about current host name
cmake_host_system_information(RESULT current_host QUERY HOSTNAME)

# needed for the OpenMP test to work in C++-only project
# (see http://public.kitware.com/Bug/view.php?id=11910)
#cmake_minimum_required(VERSION 2.8.8) 

# the policies we care about:
# - CMP0025 - make CMake distinguis between Apple and LLVM clang
# - CMP0042 - make CMake use RPATHs on OSX
# - CMP0060 - make CMake always keep absoult RPATHs, even if installing in implicit directory
#if(CMAKE_VERSION VERSION_GREATER 2.9)
#  cmake_policy(VERSION 3.0)
#endif()

#set(CMAKE_MACOSX_RPATH ON) # explicit, since policy CMP0042 didn't work...

############################################################################################
# the following variables will be set:
set(libcloudphxx_FOUND False)
set(libcloudphxx_INCLUDE_DIRS "")
set(libcloudphxx_LIBRARIES "")
#set(libcloudphxx_CXX_FLAGS_DEBUG "")
#set(libcloudphxx_CXX_FLAGS_RELWITHDEBINFO "")
#set(libcloudphxx_CXX_FLAGS_RELEASE "")

############################################################################################
# libcloudphxx libs and headers 
# also work for non-default install location (i.e. for make DESTDIR=<dir> install)
set(libcloudphxx_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../include/")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CONFIG_SUFFIX "")
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
  set(CONFIG_SUFFIX "_relwithdbg")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CONFIG_SUFFIX "_dbg")
endif()

if(APPLE)
  set(libcloudphxx_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../../lib/libcloudphxx_lgrngn${CONFIG_SUFFIX}.dylib")
else()
  set(libcloudphxx_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../../lib/libcloudphxx_lgrngn${CONFIG_SUFFIX}.so")
endif()
if(NOT EXISTS ${libcloudphxx_LIBRARIES})
  message(FATAL_ERROR "The libcloudph++ library for selected config not found at ${libcloudphxx_LIBRARIES}") 
endif() 


############################################################################################
# release with debug info mode compiler flags
#if("${current_host}" MATCHES "sampo")
#  set(libcloudphxx_CXX_FLAGS_RELWITHDEBINFO "${libcloudphxx_CXX_FLAGS_RELWITHDEBINFO} -std=c++11 -O3 ")
#else()
#  set(libcloudphxx_CXX_FLAGS_RELWITHDEBINFO "${libcloudphxx_CXX_FLAGS_RELWITHDEBINFO} -std=c++11 -O3 -march=native")
#endif()

############################################################################################
# Boost libraries
find_package(Boost)
if(Boost_FOUND)
#TODO: if boost is not linked in some program, link boost libs to libcloudphxx_lgrngn.so ?
#  set(libcloudphxx_LIBRARIES "${libcloudphxx_LIBRARIES};${Boost_LIBRARIES}")
  set(libcloudphxx_INCLUDE_DIRS "${libcloudphxx_INCLUDE_DIRS};${Boost_INCLUDE_DIRS}")
else()
#TODO: check separately for optional and mandatory components
message(FATAL_ERROR "Boost (or some of its components) not found.

* To insall Boost, please try:
*   Debian/Ubuntu: sudo apt-get install libboost-all-dev
*   Fedora: sudo yum install boost-devel
")
endif()

############################################################################################
#list(REMOVE_DUPLICATES libcloudpxxx_INCLUDE_DIRS)
list(REMOVE_ITEM libcloudphxx_INCLUDE_DIRS "")
set(libcloudphxx_FOUND TRUE)
