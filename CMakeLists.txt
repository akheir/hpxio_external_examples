# Copyright (c) 2015 Alireza Kheirkhahan
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# We require at least CMake V2.8.10
cmake_minimum_required(VERSION 2.8.10 FATAL_ERROR)

################################################################################
# project metadata
################################################################################
project(hpxio_external_examples)

################################################################################
# Find and Include HPX
################################################################################
if(NOT HPX_ROOT)
   message(FATAL_ERROR "HPX_ROOT not set, unable to find HPX!")
endif()

if(HPX_ROOT AND NOT HPX_DIR)
   set(HPX_DIR "${HPX_ROOT}/lib/cmake/HPX")
endif()

# Instruct cmake to find the HPX settings, it looks for HPXConfig.cmake in ${HPX_DIR}
find_package(HPX)

include_directories(${HPX_INCLUDE_DIR})
link_directories(${HPX_LIBRARY_DIR})

# Adjust auxiliary build settings for HPX to work properly
if(NOT MSVC)
  set(HPX_RPATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}${HPX_RPATH})
else()
  # enable solution folders for MSVC
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  if(HPX_NO_INSTALL)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/$(Configuration)" CACHE PATH
      "Prefix prepended to install directories." FORCE)
  endif()
endif()

################################################################################
# Build and Create Executable
################################################################################
link_directories(/home/alireza/lib/hpx/lib)

set(example_programs
	hello_world
  hello_world_agas
  hello_world_server
  hello_world_client
  )

foreach(example_program ${example_programs})
	set(sources ${example_program}.cpp)
	source_group("Source Files" FILES ${sources})
  set(${example_program}_FLAGS DEPENDENCIES
    iostreams_component local_file)

	add_hpx_executable(${example_program}
	SOURCES ${sources}
	${${example_program}_FLAGS}
	FOLDER "hpxio_external_examples/${example_program}")
endforeach()
