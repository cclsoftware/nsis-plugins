#************************************************************************************************
#
# CCL Tools NSIS Plugin
# 
# Copyright (c) 2026 CCL Software Licensing GmbH.
#
# Redistribution and use in source and binary forms, with or without modification, are permitted
# provided that the following conditions are met :
#
# 1. Redistributions of source code must retain the above copyright notice, this list of
#    conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice, this list of
#    conditions and the following disclaimer in the documentation and /or other materials provided
#    with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors may be used to
#    endorse or promote products derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
# FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# Filename    : CMakeLists.txt
# Description : CCL NSIS Plugin CMakeLists file
#
#************************************************************************************************
                                 
cmake_minimum_required (VERSION 3.30 FATAL_ERROR)

# This plugin does not target anything else than Win32
if (CMAKE_GENERATOR_PLATFORM)
	if (NOT CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
		message (FATAL_ERROR
			"This project is x86-only.\n"
			"Platform selected: ${CMAKE_GENERATOR_PLATFORM}"
		)
	endif ()
else ()
	set (CMAKE_GENERATOR_PLATFORM "Win32" CACHE STRING "" FORCE)
endif ()

set (NSIS_ROOT "$ENV{ProgramFiles\(x86\)}/NSIS" CACHE PATH "Path to NSIS installation")

# Check whether NSIS is installed
if (NOT EXISTS "${NSIS_ROOT}")
	message (FATAL_ERROR
		"NSIS not found at: ${NSIS_ROOT}\n"
		"Set NSIS_ROOT to your NSIS install directory."
	)
endif ()

project (ccltools LANGUAGES CXX)

add_library (ccltools SHARED
	../source/ccltools.h
	../source/utils.cpp
	../source/shellexecute.cpp
	../source/dllmain.cpp
)

set_target_properties (ccltools PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "../bin"
)

target_compile_definitions (ccltools PRIVATE
	UNICODE
	_UNICODE
)

target_include_directories (ccltools PRIVATE
	"${NSIS_ROOT}/Examples/Plugin"
)

target_link_directories (ccltools PRIVATE
	"${NSIS_ROOT}/Examples/Plugin/nsis"
)

target_link_libraries (ccltools PRIVATE
	pluginapi-x86-unicode.lib
)

target_link_options (ccltools PRIVATE
	"/NODEFAULTLIB:LIBC"
	"/SAFESEH:NO"
)
