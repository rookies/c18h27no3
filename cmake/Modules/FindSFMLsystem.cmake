# Find include file:
find_path(SFMLsystem_INCLUDE_DIR SFML/System.hpp)
# Find library:
find_library(SFMLsystem_LIBRARIES NAMES sfml-system)
# Set success status:
IF (SFMLsystem_LIBRARIES AND SFMLsystem_INCLUDE_DIR)
	set(SFMLsystem_FOUND "YES")
ELSE (SFMLsystem_LIBRARIES AND SFMLsystem_INCLUDE_DIR)
	set(SFMLsystem_FOUND "NO")
ENDIF (SFMLsystem_LIBRARIES AND SFMLsystem_INCLUDE_DIR)

IF (SFMLsystem_FOUND)
	IF (NOT SFMLsystem_FIND_QUIETLY)
		message(STATUS "Found SFMLsystem: ${SFMLsystem_LIBRARIES}")
	ENDIF (NOT SFMLsystem_FIND_QUIETLY)
ELSE (SFMLsystem_FOUND)
	IF (SFMLsystem_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find SFMLsystem library")
	ENDIF (SFMLsystem_FIND_REQUIRED)
ENDIF (SFMLsystem_FOUND)

mark_as_advanced(SFMLsystem_LIBRARIES SFMLsystem_INCLUDE_DIR)
