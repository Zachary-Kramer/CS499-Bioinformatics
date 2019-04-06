###############################################################################
# Metadata
###############################################################################
CMAKE_MINIMUM_REQUIRED (VERSION 3.4)
PROJECT (bio-499)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
SET (CMAKE_COMPILETIME_LIB_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
SET (GTEST_SOURCE_DIR ${CMAKE_COMPILETIME_LIB_DIRECTORY}/googletest)
INCLUDE_DIRECTORIES (include/)
FILE (GLOB SOURCE_CODE "src/*.cpp")


###############################################################################
# Options
###############################################################################
SET (ENABLE_TESTING ON)


###############################################################################
# Compiler
###############################################################################
# Compiler is set by exporting CXX
# Default build flags
SET (CMAKE_CXX_FLAGS                "-pthread -std=gnu++1z -fopenmp" CACHE STRING "compile flags" FORCE)
IF (WIN32)
    # Windows needs lpthread and GoogleTest has deprecated function gettimeofday()
    SET (CMAKE_CXX_FLAGS            "-lpthread -std=gnu++1z -Wno-deprecated-declarations -fopenmp" CACHE STRING "compile flags" FORCE)
ENDIF (WIN32)
SET (CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS} -g" CACHE STRING "compile flags" FORCE)
SET (CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS} -Ofast -funsafe-math-optimizations -DNDEBUG" CACHE STRING "compile flags" FORCE)
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -O3 -g" CACHE STRING "compile flags" FORCE)

# Set default build type to RelWithDebInfo
IF (NOT CMAKE_BUILD_TYPE)
  SET (CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo."
      FORCE)
ENDIF (NOT CMAKE_BUILD_TYPE)


###############################################################################
# CLI
##############################################################################
ADD_EXECUTABLE (run ${SOURCE_CODE})


###############################################################################
# Google Test
###############################################################################
IF (ENABLE_TESTING)
	# Google Test initialization
	ADD_SUBDIRECTORY (${GTEST_SOURCE_DIR})
	ENABLE_TESTING ()
	INCLUDE_DIRECTORIES (SYSTEM ${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

	# Unit tests (automatic discovery)
    FILE (GLOB TEST_SOURCES "test/*.cpp")
    LIST (REMOVE_ITEM SOURCE_CODE "${CMAKE_SOURCE_DIR}/src/Driver.cpp")
	ADD_EXECUTABLE (tester ${TEST_SOURCES} ${SOURCE_CODE})
	TARGET_LINK_LIBRARIES (tester gtest gtest_main)
	ADD_TEST (tester tester)
ENDIF ()
