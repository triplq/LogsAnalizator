cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(LogsAnalizator)


add_executable(main main.cpp logentry.cpp)

add_custom_command(TARGET main POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/Resources"
		"$<TARGET_FILE_DIR:main>/Resources"
)