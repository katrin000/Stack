cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

set(PROJECT_NAME Videneva_Stack)
project(${PROJECT_NAME})#название проекта

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/LibImage) #ƒобавл€ем директорию "${CMAKE_CURRENT_SOURCE_DIR}/LibImage" в дополн€емые каталоги включаемых файлов
#${CMAKE_CURRENT_SOURCE_DIR} - стандартна€ переменна€ с адресом рабочей директории

add_subdirectory(samples)#основной исполн€емый файл
add_subdirectory(gtest)#библиотека тестировани€
add_subdirectory(test)#создает ещЄ один исполн€емый файл с самими тестами