# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appQt624Template_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appQt624Template_autogen.dir/ParseCache.txt"
  "appQt624Template_autogen"
  "external/sonic/CMakeFiles/sonic_autogen.dir/AutogenUsed.txt"
  "external/sonic/CMakeFiles/sonic_autogen.dir/ParseCache.txt"
  "external/sonic/sonic_autogen"
  )
endif()
