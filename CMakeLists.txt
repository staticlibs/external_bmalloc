# Copyright 2018, alex at staticlibs.net
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required ( VERSION 2.8.12 )

# project
project ( external_bmalloc CXX C )
set ( ${PROJECT_NAME}_STATICLIB_VERSION 2.14.7-1 )
set ( ${PROJECT_NAME}_DESCRIPTION "bmalloc allocator library build for Staticlibs" )
set ( ${PROJECT_NAME}_URL https://github.com/staticlibs/external_bmalloc )

# options, use set ( OPTNAME ON CACHE BOOL "") in parent to override
option ( ${PROJECT_NAME}_ENABLE_PRECONFIGURATION "Skip configure-step checks and use preconfigured config headers" OFF )

# standalone build
if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
endif ( )

# bmalloc library
add_subdirectory ( ${CMAKE_CURRENT_LIST_DIR}/resources/bmalloc_cmake ${CMAKE_CURRENT_BINARY_DIR}/bmalloc )
set_target_properties ( bmalloc PROPERTIES FOLDER "deps" )
add_custom_target ( ${PROJECT_NAME} DEPENDS bmalloc )

# pkg-config
set ( ${PROJECT_NAME}_MODULE bmalloc )
set ( ${PROJECT_NAME}_PC_CFLAGS "-I${bmalloc_LOOKASIDE_DIR}/Source/bmalloc/bmalloc -Wno-expansion-to-defined" )
set ( ${PROJECT_NAME}_PC_LIBS "-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -lbmalloc" )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/resources/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/bmalloc.pc )
