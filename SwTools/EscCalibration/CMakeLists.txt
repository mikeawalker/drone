cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(motorCal)


set(EIGEN /usr/include/eigen3)






INCLUDE_DIRECTORIES(${EIGEN})
INCLUDE_DIRECTORIES(../../FlightSoftware/Device)
INCLUDE_DIRECTORIES(../../FlightSoftware/Device/I2C_Device)
INCLUDE_DIRECTORIES(../../FlightSoftware/Device/I2C_Device/PCA9685)
INCLUDE_DIRECTORIES(../../FlightSoftware/Device/GPIO)
INCLUDE_DIRECTORIES(../../FlightSoftware/Tools)
INCLUDE_DIRECTORIES(../../FlightSoftware/Include)


set(HEADERS
	
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Include/ControlConsts.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Include/Defines.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Include/Includes.h 
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Include/Structs.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Include/Types.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Device/I2C_Device/I2C_Device.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Device/I2C_Device/PCA9685/PCA9685.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Device/I2C_Device/PCA9685/PCA9685_MemMap.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Device/GPIO/GPIO_Device.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Tools/MyTime.h
	)





set(SOURCE 
	${SOURCE}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Device/I2C_Device/I2C_Device.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Device/I2C_Device/PCA9685/PCA9685.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Device/GPIO/GPIO_Device.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../FlightSoftware/Tools/MyTime.cpp
	)


add_executable( motorCal ${SOURCE} ${HEADERS}  ${MAINCPP} )
