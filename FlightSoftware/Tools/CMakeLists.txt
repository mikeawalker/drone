
set(SOURCE 
	${SOURCE}
	${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/FIR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LookupTable.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Tools.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MyTime.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/XPlatform.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/NmeaStream.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GroundStream.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/XmlUtils.cpp
	PARENT_SCOPE)


set(HEADERS
	${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/Controller.h
	${CMAKE_CURRENT_SOURCE_DIR}/Derivative.h
	${CMAKE_CURRENT_SOURCE_DIR}/FIR.h
	${CMAKE_CURRENT_SOURCE_DIR}/Integrator.h
	${CMAKE_CURRENT_SOURCE_DIR}/LookupTable.h
	${CMAKE_CURRENT_SOURCE_DIR}/PID.h
	${CMAKE_CURRENT_SOURCE_DIR}/Tools.h
	${CMAKE_CURRENT_SOURCE_DIR}/MyTime.h
	${CMAKE_CURRENT_SOURCE_DIR}/NmeaStream.h
	${CMAKE_CURRENT_SOURCE_DIR}/GroundStream.h
        ${CMAKE_CURRENT_SOURCE_DIR}/XmlUtils.h
	PARENT_SCOPE)
