# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TestTask_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TestTask_autogen.dir\\ParseCache.txt"
  "TestTask_autogen"
  )
endif()
