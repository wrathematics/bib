cmake_minimum_required(VERSION 2.8.8)
project(libbib C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(OpenMP)
if (OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


file(GLOB SRC_BLAS "src/blas/*.c")
file(GLOB SRC_LAPACK "src/lapack/*.c")
file(GLOB SRC_FUNS "src/funs/*.c")
file(GLOB SRC_GEN "src/gen/*.c")
file(GLOB SRC_IO "src/io/*.c")
file(GLOB SRC_MISC "src/misc/*.c")
set(SOURCES ${SRC_BLAS} ${SRC_LAPACK} ${SRC_FUNS} ${SRC_GEN} ${SRC_IO} ${SRC_MISC})
set(SRC_HEADERS ${PROJECT_SOURCE_DIR}/src/bib.h)

add_library(bib_static STATIC ${SOURCES})
add_library(bib SHARED ${SOURCES})

target_link_libraries(bib ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

install(TARGETS bib DESTINATION lib)
install(TARGETS bib_static DESTINATION lib)
install(FILES ${SRC_HEADERS} DESTINATION include)
