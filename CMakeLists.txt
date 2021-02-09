
set(LIBNAME cbpmfio)
cmake_minimum_required(VERSION $ENV{ACC_CMAKE_VERSION})

set (CREATE_SHARED true)

set(INC_DIRS 
  include
)

set(SRC_DIRS 
  api
  code
)


set(EXE_SPECS 
  cbpmfio_test_c.cmake
  cbpmfio_test_f.cmake
)

include($ENV{ACC_BUILD_SYSTEM}/Master.cmake)

