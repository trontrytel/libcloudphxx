add_executable(run_model run_model.cpp)
add_test(run_model run_model ${CMAKE_BINARY_DIR})

foreach(micro blk_1m blk_2m lgrngn)
  add_executable(plt_${micro} plt_${micro}.cpp)
  add_test(plt_${micro} plt_${micro} ${CMAKE_BINARY_DIR})
  target_link_libraries(plt_${micro} ${libmpdataxx_LIBRARIES})
  target_include_directories(plt_${micro} PUBLIC ${libmpdataxx_INCLUDE_DIRS})
endforeach()
