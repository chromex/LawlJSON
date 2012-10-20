cmake_minimum_required (VERSION 2.6)

project (LawlJSON)

set (${PROJECT_NAME}_SRC
	"source/LawlJSON.cpp"
	"source/LawlJSON_Lexer.cpp"
	"source/LawlJSON_Tokens.cpp"
	"source/LawlJSON_Test.cpp"
	"source/LawlJSON_Types.cpp"
	"source/Main.cpp"
)

set (${PROJECT_NAME}_INC
	"source/LawlJSON.h"
	"source/LawlJSON_Exception.h"
	"source/LawlJSON_Lexer.h"
	"source/LawlJSON_Settings.h"
	"source/LawlJSON_Test.h"
	"source/LawlJSON_Tokens.h"
	"source/LawlJSON_Types.h"
)

source_group ("Source Files" FILES ${${PROJECT_NAME}_SRC})
source_group ("Header Files" FILES ${${PROJECT_NAME}_INC})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/build)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/build)

add_executable (${PROJECT_NAME} ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_INC})