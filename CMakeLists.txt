cmake_minimum_required(VERSION 2.6)
project(PARALLELRAYTRACER)

include_directories(
	src
	contrib/SDL2/include
	contrib/SDL2_image/include
	contrib/glew/include
	contrib/glm
)


link_directories(
	${CMAKE_SOURCE_DIR}/contrib/SDL2/lib
	${CMAKE_SOURCE_DIR}/contrib/SDL2_image/lib
	${CMAKE_SOURCE_DIR}/contrib/glew/lib	
)

if(MSVC)
  add_definitions(-DSDL_MAIN_HANDLED)
endif()

add_executable(prt 
	src/prt/main.cpp
)

if(MSVC)
  add_custom_command(TARGET prt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:prt>"
  )

  add_custom_command(TARGET prt POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:prt>"
  )
endif()
