cmake_minimum_required(VERSION 3.3.1)

project(Projekt_kompetencyjny)

set(OpenCV_DIR "C:/pk")

find_package(OpenCV 4.5.0 REQUIRED)

include_directories(
	${OpenCV_INCLUDE_DIRS}
)

add_executable(Projekt_kompetencyjny
	main.cpp
	processing.cpp
	questions.cpp
	processing.h
	questions.h
	# You can put here your .h and .cpp files to expand the example.
)

target_link_libraries(Projekt_kompetencyjny
	${OpenCV_LIBS}
)

