cmake_minimum_required(VERSION 3.15)

project(IglesiaPobladoApp VERSION 1.0 LANGUAGES CXX)

# Configurar estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agregar el ejecutable
add_executable(IglesiaPoblado WIN32 src/main.cpp)

# En Windows, vincular las bibliotecas necesarias
if(WIN32)
    target_link_libraries(IglesiaPoblado PRIVATE 
        comctl32
        user32
        gdi32
    )
endif()

# Configurar las propiedades del ejecutable
set_target_properties(IglesiaPoblado PROPERTIES
    WIN32_EXECUTABLE TRUE
)
