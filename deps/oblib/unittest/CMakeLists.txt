add_library(oblib_testbase INTERFACE)
target_include_directories(oblib_testbase INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(oblib_testbase INTERFACE -lgmock -lgtest)
file(COPY run_tests.sh DESTINATION .)
enable_testing()

function(oblib_addtest mainfile)
  get_filename_component(testname ${mainfile} NAME_WE)
  add_executable(${testname} ${ARGV})
  add_test(${testname} ${testname})
  target_link_libraries(${testname} PRIVATE objit oblib oblib_testbase -static-libgcc -static-libstdc++
      ${OB_RELRO_FLAG} -Wl,-T,${CMAKE_SOURCE_DIR}/rpm/ld.lds)
endfunction()

add_subdirectory(lib)
add_subdirectory(rpc)
add_subdirectory(common)
