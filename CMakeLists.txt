cmake_minimum_required(VERSION 3.3.1)

project(Projekt_kompetencyjny)

set(OpenCV_DIR "C:/pk/build")
set(SFML_DIR "C:/pk/SFML/lib/cmake/SFML")
set(CMAKE_CXX_STANDARD 14)
set(SFML_INCLUDE_DIR "C:/pk/SFML/include")
set(SFML_LIBRARY_DIR "C:/pk/SFML/lib")


find_package(OpenCV 4.5.0 REQUIRED)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(Projekt_kompetencyjny
	main.cpp
	FingersDetector.cpp
	FingersDetector.h
	Question.cpp
	Question.h
	QuestionList.cpp
	QuestionList.h
)


link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

include_directories(
	${OpenCV_INCLUDE_DIRS}

)


target_link_libraries(Projekt_kompetencyjny
	sfml-graphics sfml-window sfml-system
	${OpenCV_LIBS}
)



