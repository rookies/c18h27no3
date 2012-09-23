# Find include file & library:
IF (UNIX)
	find_path(LIBAVUTIL_INCLUDE_DIR libavutil/avutil.h)
	find_library(LIBAVUTIL_LIBRARIES NAMES avutil)
ELSEIF (WIN32)
	set(LIBAVUTIL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
	set(LIBAVUTIL_LIBRARIES ${CMAKE_SOURCE_DIR}/avutil-51.dll)
ENDIF (UNIX)
# Set success status:
IF (LIBAVUTIL_LIBRARIES AND LIBAVUTIL_INCLUDE_DIR)
	set(LIBAVUTIL_FOUND "YES")
ELSE (LIBAVUTIL_LIBRARIES AND LIBAVUTIL_INCLUDE_DIR)
	set(LIBAVUTIL_FOUND "NO")
ENDIF (LIBAVUTIL_LIBRARIES AND LIBAVUTIL_INCLUDE_DIR)

IF (LIBAVUTIL_FOUND)
	IF (NOT LIBAVUTIL_FIND_QUIETLY)
		message(STATUS "Found libavutil: ${LIBAVUTIL_LIBRARIES}")
	ENDIF (NOT LIBAVUTIL_FIND_QUIETLY)
ELSE (LIBAVUTIL_FOUND)
	IF (LIBAVUTIL_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find libavutil library")
	ENDIF (LIBAVUTIL_FIND_REQUIRED)
ENDIF (LIBAVUTIL_FOUND)

mark_as_advanced(LIBAVUTIL_LIBRARIES LIBAVUTIL_INCLUDE_DIR)
