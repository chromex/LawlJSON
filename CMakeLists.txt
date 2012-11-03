cmake_minimum_required (VERSION 2.6)

project (LawlJSON)

set (${PROJECT_NAME}_SRC
	"Source/LawlJSON.cpp"
	"Source/LawlJSON_Lexer.cpp"
	"Source/LawlJSON_Tokens.cpp"
	"Source/LawlJSON_Test.cpp"
	"Source/LawlJSON_Types.cpp"
	"Source/Main.cpp"
)

set (${PROJECT_NAME}_INC
	"Source/LawlJSON.h"
	"Source/LawlJSON_Exception.h"
	"Source/LawlJSON_Lexer.h"
	"Source/LawlJSON_Settings.h"
	"Source/LawlJSON_Test.h"
	"Source/LawlJSON_Tokens.h"
	"Source/LawlJSON_Types.h"
)

source_group ("Source Files" FILES ${${PROJECT_NAME}_SRC})
source_group ("Header Files" FILES ${${PROJECT_NAME}_INC})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/build)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/build)

add_definitions(-O2)

add_executable (${PROJECT_NAME}_Test ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_INC})
add_library (${PROJECT_NAME} ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_INC})
