# Find include file:
FIND_PATH(LIBSWSCALE_INCLUDE_DIR libswscale/swscale.h)
# Find library:
FIND_LIBRARY(LIBSWSCALE_LIBRARIES NAMES swscale)
# Set success status:
IF (LIBSWSCALE_LIBRARIES AND LIBSWSCALE_INCLUDE_DIR)
	SET(LIBSWSCALE_FOUND "YES")
ELSE (LIBSWSCALE_LIBRARIES AND LIBSWSCALE_INCLUDE_DIR)
	SET(LIBSWSCALE_FOUND "NO")
ENDIF (LIBSWSCALE_LIBRARIES AND LIBSWSCALE_INCLUDE_DIR)

IF (LIBSWSCALE_FOUND)
	IF (NOT LIBSWSCALE_FIND_QUIETLY)
		MESSAGE(STATUS "Found LIBSWSCALE: ${LIBSWSCALE_LIBRARIES}")
	ENDIF (NOT LIBSWSCALE_FIND_QUIETLY)
ELSE (LIBSWSCALE_FOUND)
	IF (LIBSWSCALE_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find LIBSWSCALE library")
	ENDIF (LIBSWSCALE_FIND_REQUIRED)
ENDIF (LIBSWSCALE_FOUND)

MARK_AS_ADVANCED(LIBSWSCALE_LIBRARIES LIBSWSCALE_INCLUDE_DIR)
