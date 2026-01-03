cmake_minimum_required(VERSION 3.10)

project(IglesiaPoblado)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agregar ejecutable
add_executable(IglesiaPoblado 
    WIN32
    IglesiaPoblado.cpp
)

# Enlazar librerías de Windows
target_link_libraries(IglesiaPoblado 
    comctl32
    user32
    gdi32
)
