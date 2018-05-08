cmake_minimum_required(VERSION 3.1)
project(mig)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENBW)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DNOMINMAX -DWIN32 -D_WINDOWS -D_USRDLL -DSTBI_MSC_SECURE_CRT)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

function(if_unset_then_set var val)
    if (NOT ${var})
        set(${var} ${val} PARENT_SCOPE)
    endif()
endfunction()

if_unset_then_set(MIG_SRC_DIR src/mig)
if_unset_then_set(MIG_SHAPE_SRC_DIR ${MIG_SRC_DIR}/shape)
set(MIG_SRCS 
	${MIG_SRC_DIR}/mig.cpp
	${MIG_SHAPE_SRC_DIR}/mig_circle.cpp
	${MIG_SHAPE_SRC_DIR}/mig_line.cpp
	${MIG_SHAPE_SRC_DIR}/mig_rectangle.cpp
	${MIG_SHAPE_SRC_DIR}/mig_util.cpp
)

add_library(mig SHARED ${MIG_SRCS})
