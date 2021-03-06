#
# Copyright 2016 Ahnaf Siddiqui
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
#

cmake_minimum_required(VERSION 3.2.0)
project(Quantum2D)


# Flags
set(CMAKE_CXX_FLAGS -std=c++11)


# Header includes
include_directories(
	include/
	extern/DiamondUtils/include
)

# Libraries
if(APPLE)
	set(LINK_LIBS -stdlib=libc++)
endif()


# Get source files
file(GLOB_RECURSE SOURCES src/*.cpp)


# Build Quantum2D library
add_library(Quantum2D STATIC ${SOURCES})
target_link_libraries(Quantum2D ${LINK_LIBS})
install(TARGETS Quantum2D DESTINATION lib)


# Build subdirectories
# TODO: this will work on mac if you rebuild gtest with clang
# add_subdirectory(test)
