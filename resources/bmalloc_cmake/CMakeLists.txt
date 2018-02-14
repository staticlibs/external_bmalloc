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

# this file is based on https://trac.webkit.org/browser/webkit/releases/WebKitGTK/webkit-2.17.4/Source/bmalloc/CMakeLists.txt
cmake_minimum_required ( VERSION 2.8.12 )
project ( bmalloc CXX )

if ( NOT DEFINED ${PROJECT_NAME}_LOOKASIDE_DIR )
    set ( ${PROJECT_NAME}_LOOKASIDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../lookaside_webkitgtk4 CACHE INTERNAL "" )
endif ( )

# sources
set ( ${PROJECT_NAME}_SRC 
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/Allocator.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/Cache.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/Deallocator.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/Environment.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/Heap.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/LargeMap.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/Logging.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/ObjectType.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/StaticMutex.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/VMHeap.cpp
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/mbmalloc.cpp )

if ( CMAKE_SYSTEM_NAME MATCHES "Darwin" )
    list ( APPEND ${${PROJECT_NAME}_SRC}
            ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc/Zone.cpp )
endif ()
source_group ( "src" FILES ${${PROJECT_NAME}_SRC} )

# library
add_library ( ${PROJECT_NAME} STATIC 
        ${${PROJECT_NAME}_SRC} )
target_include_directories ( ${PROJECT_NAME} BEFORE PRIVATE
        ${${PROJECT_NAME}_LOOKASIDE_DIR}/Source/bmalloc/bmalloc )
#target_compile_definitions ( ${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DEFINITIONS} )
target_compile_options ( ${PROJECT_NAME} PRIVATE -Wno-expansion-to-defined )

# check deplibs cache
if ( STATICLIB_USE_DEPLIBS_CACHE )
    set ( ${PROJECT_NAME}_CACHED_LIB_PATH ${STATICLIB_DEPLIBS_CACHE_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX} )
    if ( EXISTS ${${PROJECT_NAME}_CACHED_LIB_PATH} )
        add_library( ${PROJECT_NAME} STATIC IMPORTED GLOBAL )
        set_target_properties( ${PROJECT_NAME} PROPERTIES IMPORTED_LOCATION ${${PROJECT_NAME}_CACHED_LIB_PATH} )
        message ( STATUS "Using cached library: [${${PROJECT_NAME}_CACHED_LIB_PATH}]" )
        return ( )
    endif ( )
endif ( )
