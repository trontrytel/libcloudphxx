# tests from GMD_2015 paper (should be run on CUDA)
add_executable(calc_psc calc_psc.cpp)
add_test(calc_psc calc_psc ${CMAKE_BINARY_DIR})

find_package(HDF5 COMPONENTS CXX REQUIRED QUIET)
find_package(Boost COMPONENTS iostreams system filesystem REQUIRED)

foreach(micro blk_1m_psc)
  add_executable(plot_${micro} plot_${micro}.cpp)
  add_test(plot_${micro} plot_${micro} ${CMAKE_BINARY_DIR})
  target_link_libraries(plot_${micro} ${HDF5_LIBRARIES})
  target_include_directories(plot_${micro} PUBLIC ${HDF5_INCLUDE_DIRS})
  target_link_libraries(plot_${micro} ${Boost_LIBRARIES})
  target_include_directories(plot_${micro} PUBLIC ${Boost_INCLUDE_DIRS})
endforeach()

