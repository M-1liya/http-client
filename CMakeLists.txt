cmake_minimum_required(VERSION 3.10)

# Название вашего проекта
project(HttpClient)

# Стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включаем директорию с заголовочными файлами
include_directories(${CMAKE_SOURCE_DIR}/src)

# Добавляем исполняемый файл
add_executable(client 
    src/client.cpp 
    src/Requests/Request.cpp)

# Подключаем библиотеку curl
find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(client ${CURL_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find the CURL library and development files.")
endif()