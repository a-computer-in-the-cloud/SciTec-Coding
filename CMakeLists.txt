cmake_minimum_required(VERSION 3.0)
project(lla-ecef CXX)
set(CMAKE_CXX_STANDARD 11)


# Build libraries and executable
add_executable(main src/main.cc)
add_library(lla-ecef.so src/main.cc)
add_library(parser src/parser.cc src/parser.h)
add_library(row src/row.cc src/row.h)
add_library(conversion src/conversion.cc src/conversion.h)
add_library(linear-interpolation src/linear-interpolation.cc src/linear-interpolation.h)
target_link_libraries(
  main
  parser
  row
  conversion
  linear-interpolation
)

# Enabling tests
if (TEST_ENABLED)
  add_executable(testing tests/main.cc)
  target_link_libraries(
    testing
    parser
    row
    conversion
    linear-interpolation
  )
  add_test(
    NAME testing
    WORKING_DIRECTORY ./
    COMMAND ./testing
  )
  message("Testing enabled..")
endif (TEST_ENABLED)

# Install to a system location
install (TARGETS main DESTINATION bin)
install (TARGETS lla-ecef.so DESTINATION lib)
install (FILES 
  ${CMAKE_SOURCE_DIR}/src/parser.h
  ${CMAKE_SOURCE_DIR}/src/row.h
  ${CMAKE_SOURCE_DIR}/src/linear-interpolation.h
  ${CMAKE_SOURCE_DIR}/src/conversion.h
  ${CMAKE_SOURCE_DIR}/src/config.h
  ${CMAKE_SOURCE_DIR}/src/ECEFPoint.h
  ${CMAKE_SOURCE_DIR}/src/LLAPoint.h
  ${CMAKE_SOURCE_DIR}/src/XYZVelocity.h
  ${CMAKE_SOURCE_DIR}/src/status.h
  DESTINATION include
)