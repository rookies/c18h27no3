# Find include file & library:
IF (UNIX)
	find_path(SFMLnetwork_INCLUDE_DIR SFML/Network.hpp)
	find_library(SFMLnetwork_LIBRARIES NAMES sfml-network)
ELSEIF (WIN32)
	set(SFMLnetwork_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
	set(SFMLnetwork_LIBRARIES ${CMAKE_SOURCE_DIR}/sfml-network-2.dll)
ENDIF (UNIX)
# Set success status:
IF (SFMLnetwork_LIBRARIES AND SFMLnetwork_INCLUDE_DIR)
	set(SFMLnetwork_FOUND "YES")
ELSE (SFMLnetwork_LIBRARIES AND SFMLnetwork_INCLUDE_DIR)
	set(SFMLnetwork_FOUND "NO")
ENDIF (SFMLnetwork_LIBRARIES AND SFMLnetwork_INCLUDE_DIR)

IF (SFMLnetwork_FOUND)
	IF (NOT SFMLnetwork_FIND_QUIETLY)
		message(STATUS "Found SFML-network: ${SFMLnetwork_LIBRARIES}")
	ENDIF (NOT SFMLnetwork_FIND_QUIETLY)
ELSE (SFMLnetwork_FOUND)
	IF (SFMLnetwork_FIND_REQUIRED)
		message(FATAL_ERROR "Could not find SFML-network library")
	ENDIF (SFMLnetwork_FIND_REQUIRED)
ENDIF (SFMLnetwork_FOUND)

mark_as_advanced(SFMLnetwork_LIBRARIES SFMLnetwork_INCLUDE_DIR)
