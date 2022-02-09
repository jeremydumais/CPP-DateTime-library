cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

project(DateTime C CXX)

# Set project name
set(PROJECT_NAME    "datetime")
set(PROJECT_UNITTEST_NAME   "datetime_unittests")

find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
    )
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-header-filter=.;-checks=*,-llvm-header-guard,-google-build-using-namespace,-fuchsia-default-arguments,-modernize-pass-by-value,-fuchsia-overloaded-operator,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-hicpp-vararg,-cppcoreguidelines-pro-type-vararg,-cppcoreguidelines-owning-memory")
endif()

#set(CMAKE_BUILD_TYPE Debug)

# Set directories
set(PROJECT_PATH    "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_PATH        "${PROJECT_PATH}/src")
set(TEST_SRC_PATH   "${PROJECT_PATH}/test/datetime_unittest")
if (WIN32)
	set(PTHREAD		"")
	option(VCPKG_APPLOCAL_DEPS "Automatically copy dependencies into the output directory for executables." ON)
else()
	set(PTHREAD		"pthread")
endif()

# c++14 required
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++14 HAS_CXX14_FLAG)
check_cxx_compiler_flag(-std=c++17 HAS_CXX17_FLAG)
check_cxx_compiler_flag(-std=c++2a HAS_CXX20_FLAG)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") # the quotes are needed here, maybe because "MSVC" seems to be a keyword
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19)
		message(FATAL_ERROR "Visual Studio 2015 or newer is required.")
	endif()
else()
	if(HAS_CXX17_FLAG)
		set(CMAKE_CXX_STANDARD 17)
	elseif(HAS_CXX14_FLAG)
		set(CMAKE_CXX_STANDARD 14)
	else()
		message(FATAL_ERROR "${PROJECT_NAME} requires c++14")
	endif()

	if(NOT (DEFINED CMAKE_CXX_STANDARD) OR CMAKE_CXX_STANDARD STREQUAL "" OR CMAKE_CXX_STANDARD LESS 14)
		message(FATAL_ERROR "${PROJECT_NAME} requires c++14")
	endif()
endif()

# Set CMake build-type. If it not supplied by the user, the default built type is "Release".
if(((NOT CMAKE_BUILD_TYPE)
      AND (NOT BUILD_COVERAGE_ANALYSIS))
      OR (CMAKE_BUILD_TYPE STREQUAL "Release"))
          message(STATUS "WARNING: building release version!")
          set(CMAKE_BUILD_TYPE Release)
elseif((CMAKE_BUILD_TYPE STREQUAL "Debug") OR (BUILD_COVERAGE_ANALYSIS))
      message(STATUS "WARNING: building debug version!")
endif(((NOT CMAKE_BUILD_TYPE)
    AND (NOT BUILD_COVERAGE_ANALYSIS))
    OR (CMAKE_BUILD_TYPE STREQUAL "Release"))

set(PROJECT_SOURCE_FILES ${SRC_PATH}/datetime.cpp
    ${SRC_PATH}/timespan.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	#For MSVC create the library as a shared library
	add_library(${PROJECT_NAME} SHARED
		${PROJECT_SOURCE_FILES})
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	target_compile_definitions(${PROJECT_NAME}
		PRIVATE DATETIME_EXPORTS
		INTERFACE NOMINMAX # avoid Win macro definition of min/max, use std one
		INTERFACE _SCL_SECURE_NO_WARNINGS) # disable security-paranoia warning
else()
	#For other compiler create the library as a static library
	add_library(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") #gcc
		# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
		target_compile_options(${PROJECT_NAME}
			PRIVATE "-Wfatal-errors" # stops on first error
			"-Wall" # enables all the warnings about constructions
			"-Wextra" # Print extra warning messages"
			"-Werror" # Make all warnings into errors.
			"-pedantic" # Issue all the warnings demanded by strict ISO C and ISO C++
			"-pedantic-errors" # Like -pedantic, except that errors are produced rather than warnings http://stackoverflow.com/questions/30255294/how-to-hide-extra-output-from-pragma-message
			"-ftrack-macro-expansion=0"
			"-fno-diagnostics-show-caret"
			)
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		target_compile_options(${PROJECT_NAME}
			PRIVATE "-Wfatal-errors" # stops on first error
			"-Wall" # enables all the warnings about constructions
			"-Wextra" # Print extra warning messages"
			"-Werror" # Make all warnings into errors.
			"-pedantic" # Issue all the warnings demanded by strict ISO C and ISO C++
			"-pedantic-errors" # Like -pedantic, except that errors are produced rather than warnings http://stackoverflow.com/questions/30255294/how-to-hide-extra-output-from-pragma-message
			)
	endif()
endif()

#Run clang-tidy on project
if(CLANG_TIDY_EXE AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif()

if (BUILD_TESTING)
  enable_testing()

  # Download and unpack googletest at configure time
  configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif() 

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                   ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                   EXCLUDE_FROM_ALL)
  include(GoogleTest)

  add_executable(${PROJECT_UNITTEST_NAME} ${INCLUDE_PATH}
  ${TEST_SRC_PATH}/main.cpp
  ${TEST_SRC_PATH}/datetime_unittest.cpp
  ${TEST_SRC_PATH}/timespan_unittest.cpp
  )

  target_link_libraries(${PROJECT_UNITTEST_NAME} ${PROJECT_NAME} gtest gtest_main ${PTHREAD})
  gtest_discover_tests(${PROJECT_UNITTEST_NAME})

endif()

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/datetime
            FILES_MATCHING PATTERN "*.h")


# Uninstall target
CONFIGURE_FILE(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeUninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeUninstall.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
	"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeUninstall.cmake")

