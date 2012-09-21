# Find include file:
FIND_PATH(SFMLgraphics_INCLUDE_DIR SFML/Graphics.hpp)
# Find library:
FIND_LIBRARY(SFMLgraphics_LIBRARIES NAMES sfml-graphics)
# Set success status:
IF (SFMLgraphics_LIBRARIES AND SFMLgraphics_INCLUDE_DIR)
	SET(SFMLgraphics_FOUND "YES")
ELSE (SFMLgraphics_LIBRARIES AND SFMLgraphics_INCLUDE_DIR)
	SET(SFMLgraphics_FOUND "NO")
ENDIF (SFMLgraphics_LIBRARIES AND SFMLgraphics_INCLUDE_DIR)

IF (SFMLgraphics_FOUND)
	IF (NOT SFMLgraphics_FIND_QUIETLY)
		MESSAGE(STATUS "Found SFMLgraphics: ${SFMLgraphics_LIBRARIES}")
	ENDIF (NOT SFMLgraphics_FIND_QUIETLY)
ELSE (SFMLgraphics_FOUND)
	IF (SFMLgraphics_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find SFMLgraphics library")
	ENDIF (SFMLgraphics_FIND_REQUIRED)
ENDIF (SFMLgraphics_FOUND)

MARK_AS_ADVANCED(SFMLgraphics_LIBRARIES SFMLgraphics_INCLUDE_DIR)
