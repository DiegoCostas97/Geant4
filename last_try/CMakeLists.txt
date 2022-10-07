cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Last_Try)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES
	"*.mac"
)

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(last last.cc ${sources} ${headers})
target_link_libraries(last ${Geant4_LIBRARIES})

add_custom_target(Last_Try DEPENDS last)