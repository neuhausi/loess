cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(dloess)
enable_language(C)
enable_language(Fortran)

find_package(BLAS REQUIRED)

set(DLOESS_FORTRAN_SRC
  "src/loessf.f"
  "thirdparty/netlib-linpack-part/dqrsl.f"
  "thirdparty/netlib-linpack-part/dsvdc.f"
)

set(DLOESS_C_SRC
  "src/loessc.c"
  "src/loess.c"
  "src/predict.c"
  "src/misc.c"
)

set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -std=legacy")

add_library(dloess STATIC ${DLOESS_C_SRC} ${DLOESS_FORTRAN_SRC})
target_link_libraries(dloess INTERFACE m ${BLAS_LINKER_FLAGS} ${BLAS_LIBRARIES})
set_property(TARGET dloess PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(air "src/air.c")
target_link_libraries(air dloess)

add_executable(ethanol "src/ethanol.c")
target_link_libraries(ethanol dloess)

add_executable(galaxy "src/galaxy.c")
target_link_libraries(galaxy dloess)

add_executable(gas "src/gas.c")
target_link_libraries(gas dloess)

add_executable(madeup "src/madeup.c")
target_link_libraries(madeup dloess)

INSTALL(FILES "src/loess.h"
  DESTINATION include
)
INSTALL(TARGETS dloess
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
