# Find include file & library:
IF (UNIX)
	find_path(LIBARCHIVE_INCLUDE_DIR archive.h)
	find_library(LIBARCHIVE_LIBRARIES NAMES archive)
ELSEIF (WIN32)
	set(LIBARCHIVE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
	set(LIBARCHIVE_LIBRARIES ${CMAKE_SOURCE_DIR}/libarchive.dll)
ENDIF (UNIX)
# Set success status:
IF (LIBARCHIVE_LIBRARIES AND LIBARCHIVE_INCLUDE_DIR)
	set(LIBARCHIVE_FOUND "YES")
ELSE (LIBARCHIVE_LIBRARIES AND LIBARCHIVE_INCLUDE_DIR)
	set(LIBARCHIVE_FOUND "NO")
ENDIF (LIBARCHIVE_LIBRARIES AND LIBARCHIVE_INCLUDE_DIR)

IF (LIBARCHIVE_FOUND)
	IF (NOT LIBARCHIVE_FIND_QUIETLY)
		message(STATUS "Found LibArchive: ${LIBARCHIVE_LIBRARIES}")
	ENDIF (NOT LIBARCHIVE_FIND_QUIETLY)
ELSE (LIBARCHIVE_FOUND)
	IF (LIBARCHIVE_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find LibArchive library")
	ENDIF (LIBARCHIVE_FIND_REQUIRED)
ENDIF (LIBARCHIVE_FOUND)

mark_as_advanced(LIBARCHIVE_LIBRARIES LIBARCHIVE_INCLUDE_DIR)
