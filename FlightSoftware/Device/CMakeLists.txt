add_subdirectory(I2C_Device)
add_subdirectory(Serial)
add_subdirectory(GPIO)
add_subdirectory(Interrupts)
add_subdirectory(FakeInterface)
set(SOURCE 
	${SOURCE}
	${CMAKE_CURRENT_SOURCE_DIR}/GpsEnetBlock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/ImuEnetBlock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MagEnetBlock.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/MotorEnetBlock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/EnetTmBlock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/FileTmBlock.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/UDP_Device.cpp
	PARENT_SCOPE)


set(HEADERS
	${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/GpsEnetBlock.h
	${CMAKE_CURRENT_SOURCE_DIR}/ImuEnetBlock.h
	${CMAKE_CURRENT_SOURCE_DIR}/MagEnetBlock.h 
	${CMAKE_CURRENT_SOURCE_DIR}/MotorEnetBlock.h
	${CMAKE_CURRENT_SOURCE_DIR}/EnetTmBlock.h
	${CMAKE_CURRENT_SOURCE_DIR}/FileTmBlock.h
	${CMAKE_CURRENT_SOURCE_DIR}/UDP_Device.h
	PARENT_SCOPE)
