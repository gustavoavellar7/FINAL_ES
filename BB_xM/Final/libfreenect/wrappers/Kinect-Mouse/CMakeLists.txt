INSTALL(FILES libfreenect.hpp
  DESTINATION include)

IF(BUILD_EXAMPLES)

set(CMAKE_C_FLAGS "-Wall")

if (WIN32)
  set(THREADS_USE_PTHREADS_WIN32 true)
  find_package(Threads REQUIRED)

  include_directories(${THREADS_PTHREADS_INCLUDE_DIR})
endif()

include_directories(.)

add_executable(mouse mouse.cpp)

# Mac just has everything already
if(APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "-framework OpenGL -framework GLUT")
  target_link_libraries(mouse freenect X11 Xtst ncurses pthread)
else()
  find_package(Threads REQUIRED)
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)

  include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR} ${USB_INCLUDE_DIRS})

target_link_libraries(mouse freenect X11 Xtst ncurses pthread ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} m)

endif()

install (TARGETS mouse
  DESTINATION bin)

ENDIF()
