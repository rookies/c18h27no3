# Find include file:
find_path(SFMLgraphics_INCLUDE_DIR SFML/Graphics.hpp)
# Find library:
find_library(SFMLgraphics_LIBRARIES NAMES sfml-graphics)
# Set success status:
IF (SFMLgraphics_LIBRARIES AND SFMLgraphics_INCLUDE_DIR)
	set(SFMLgraphics_FOUND "YES")
ELSE (SFMLgraphics_LIBRARIES AND SFMLgraphics_INCLUDE_DIR)
	set(SFMLgraphics_FOUND "NO")
ENDIF (SFMLgraphics_LIBRARIES AND SFMLgraphics_INCLUDE_DIR)

IF (SFMLgraphics_FOUND)
	IF (NOT SFMLgraphics_FIND_QUIETLY)
		message(STATUS "Found SFMLgraphics: ${SFMLgraphics_LIBRARIES}")
	ENDIF (NOT SFMLgraphics_FIND_QUIETLY)
ELSE (SFMLgraphics_FOUND)
	IF (SFMLgraphics_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find SFMLgraphics library")
	ENDIF (SFMLgraphics_FIND_REQUIRED)
ENDIF (SFMLgraphics_FOUND)

mark_as_advanced(SFMLgraphics_LIBRARIES SFMLgraphics_INCLUDE_DIR)
