#####################################
# cmake module for finding ZTopUtils
# Benjamin.Lutz@desy.de
# Dec. 2013
#####################################


SET(CMSSW_DIR "$ENV{CMSSW_BASE}")


## NEED to find out where the CMSSW local libraries are stored
## I didn't figure out a straight forward approach for this,
## doing a bit of gymnastics in the hope it will be robust with different versions of CMSSW
FILE(GLOB_RECURSE localLibraries FOLLOW_SYMLINKS ${CMSSW_DIR}/.edmplugincache )
LIST(GET localLibraries 0 anyLibrary )
GET_FILENAME_COMPONENT(CMSSW_LIBRARIES_PATH ${anyLibrary} PATH)


FIND_LIBRARY( ZTopUtils_LIBRARY
  NAMES TopAnalysisZTopUtils
  PATHS ${CMSSW_LIBRARIES_PATH}
  NO_DEFAULT_PATH )
MARK_AS_ADVANCED(ZTopUtils_LIBRARY)

SET(ZTopUtils_INCLUDE_DIR ${CMSSW_DIR}/src)
MARK_AS_ADVANCED(ZTopUtils_INCLUDE_DIR)

IF ( ZTopUtils_INCLUDE_DIR AND ZTopUtils_LIBRARY )
  SET(ZTopUtils_FOUND TRUE)
  SET(ZTopUtils_LIBRARIES ${ZTopUtils_LIBRARY} )
  SET(ZTopUtils_INCLUDE_DIRS ${ZTopUtils_INCLUDE_DIR} )
ENDIF ( ZTopUtils_INCLUDE_DIR AND ZTopUtils_LIBRARY )


MESSAGE(STATUS "--------------- ZTopUtils SUMMARY ----------------")
MESSAGE(STATUS "CMSSW_DIR:              " ${CMSSW_DIR} )
MESSAGE(STATUS "CMSSW_LIBRARIES_PATH:   " ${CMSSW_LIBRARIES_PATH} )
MESSAGE(STATUS "ZTopUtils_INCLUDE_DIRS: " ${ZTopUtils_INCLUDE_DIRS} )
MESSAGE(STATUS "ZTopUtils_LIBRARIES:    " "${ZTopUtils_LIBRARIES}" )
MESSAGE(STATUS "ZTopUtils_DEFINITIONS:  " ${ZTopUtils_DEFINITIONS} )
MESSAGE(STATUS "---------------------------------------------")

IF ( ZTopUtils_FIND_REQUIRED AND NOT ZTopUtils_FOUND )
  MESSAGE( FATAL_ERROR "Cannot find ZTopUtils!!" )
ENDIF ( ZTopUtils_FIND_REQUIRED AND NOT ZTopUtils_FOUND )

