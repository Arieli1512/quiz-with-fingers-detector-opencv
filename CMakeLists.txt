cmake_minimum_required(VERSION 3.3.1)

project(Projekt_kompetencyjny)

set(OpenCV_DIR "C:/pk/build")
set(CMAKE_CXX_STANDARD 14)
set(SFML_INCLUDE_DIR "./SFML/include")
set(SFML_LIBRARY_DIR "./SFML/lib")


find_package(OpenCV 4.5.0 REQUIRED)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(Projekt_kompetencyjny
	src/main.cpp
	src/FingersDetector.cpp
	src/FingersDetector.h
	src/Question.cpp
	src/Question.h
	src/QuestionList.cpp
	src/QuestionList.h
	src/StartupScreen.cpp
	src/StartupScreen.h
	src/WaitingScreen.cpp
	src/WaitingScreen.h
	src/CategoryScreen.cpp
	src/CategoryScreen.h
	src/GameScreen.cpp
	src/GameScreen.h
	src/EndingScreen.cpp
	src/EndingScreen.h
	src/Screen.cpp
	src/Screen.h
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



