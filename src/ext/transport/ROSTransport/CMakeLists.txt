cmake_minimum_required (VERSION 2.6)

project (ROSTransport)


if(NOT WIN32)
  set_directory_properties(PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra")
endif()

if(UNIX)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
	 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
	 	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
	endif()
endif()


find_package(catkin REQUIRED COMPONENTS
  roscpp
)


find_package(Boost REQUIRED COMPONENTS chrono filesystem signals system)

include_directories(include ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}/ros ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})



link_directories(${ORB_LINK_DIR})
include_directories(
		${RTM_INCLUDE_DIR}
		${ORB_INCLUDE_DIR}
		)

add_definitions(${ORB_C_FLAGS_LIST})

if(WIN32)
  add_definitions(-DNOGDI)
  add_definitions(-DLIBRARY_EXPORTS)
endif()


set(target ROSTransport)

set(srcs ROSTransport.cpp ROSTransport.h ROSInPort.cpp ROSInPort.h ROSOutPort.cpp ROSOutPort.h ROSMessageInfo.cpp ROSMessageInfo.h RosTopicManager.cpp RosTopicManager.h ROSSerializer.cpp ROSSerializer.h)


if(VXWORKS AND NOT RTP)
	set(libs ${RTCSKEL_PROJECT_NAME})

	add_executable(${target} ${srcs})
	target_link_libraries(${target} ${libs} ${catkin_LIBRARIES} ${Boost_LIBRARIES})
	add_dependencies(${target} ${RTM_PROJECT_NAME})

	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				COMPONENT ext)
else()
	if(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME} ${RTCSKEL_PROJECT_NAME})
	else(VXWORKS)
		set(libs ${RTM_PROJECT_NAME} ${ORB_LIBRARIES} ${COIL_PROJECT_NAME})
	endif(VXWORKS)


	add_library(${target} SHARED ${srcs})
	target_link_libraries(${target} ${libs} ${RTM_LINKER_OPTION} ${catkin_LIBRARIES} ${Boost_LIBRARIES})
	add_dependencies(${target} ${RTM_PROJECT_NAME})
	set_target_properties(${target} PROPERTIES PREFIX "")


	install(TARGETS ${target} LIBRARY DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				ARCHIVE DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				RUNTIME DESTINATION ${INSTALL_RTM_EXT_DIR}/transport
				COMPONENT ext)
endif()






if(VXWORKS)
	if(RTP)
	else(RTP)	
		set_target_properties(${target} PROPERTIES SUFFIX ".out")
	endif(RTP)
endif(VXWORKS)

