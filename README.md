# Aplicación de Escritorio - Iglesia Poblado

Esta es una aplicación de escritorio básica desarrollada en C++ usando Win32 API para Windows.

## 📋 Requisitos

- **Windows 10/11**
- **CMake** (versión 3.15 o superior) - [Descargar CMake](https://cmake.org/download/)
- **Compilador C++** compatible con C++17:
  - Visual Studio 2019 o superior (con C++ Desktop Development)
  - O MinGW-w64 (GCC)

## 🚀 Compilación

### Opción 1: Usando Visual Studio

1. Abre una terminal en la carpeta del proyecto
2. Ejecuta los siguientes comandos:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

3. El ejecutable estará en `build\Release\IglesiaPoblado.exe`

### Opción 2: Usando MinGW

1. Asegúrate de tener MinGW instalado y en tu PATH
2. Ejecuta:

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

3. El ejecutable estará en `build\IglesiaPoblado.exe`

## ▶️ Ejecución

Una vez compilada, simplemente ejecuta:

```bash
.\build\Release\IglesiaPoblado.exe
```

O haz doble clic en el archivo ejecutable.

## 🎯 Características

La aplicación incluye:
- Ventana principal con interfaz gráfica
- Botón interactivo
- Etiqueta de bienvenida
- Cuadro de mensaje al hacer clic en el botón

## 📁 Estructura del Proyecto

```
Iglesia Poblado/
├── src/
│   └── main.cpp          # Código fuente principal
├── CMakeLists.txt        # Configuración de CMake
└── README.md             # Este archivo
```

## 🔧 Desarrollo

Para modificar la aplicación, edita el archivo [src/main.cpp](src/main.cpp). Este archivo contiene:

- `WinMain`: Punto de entrada de la aplicación
- `WindowProc`: Manejo de eventos de la ventana (clicks, cerrar, etc.)

## 📝 Próximos Pasos

Puedes expandir esta aplicación agregando:
- Más controles (cajas de texto, listas, menús)
- Conexión a base de datos
- Recursos (iconos, imágenes)
- Múltiples ventanas
- Funcionalidades específicas para la iglesia

## 🐛 Solución de Problemas

**Error: CMake no encontrado**
- Asegúrate de tener CMake instalado y agregado al PATH del sistema

**Error al compilar**
- Verifica que tengas instalado Visual Studio con componentes de C++
- O instala MinGW-w64 para GCC en Windows

**La ventana no aparece**
- Verifica que no haya errores en la compilación
- Ejecuta desde la línea de comandos para ver mensajes de error

## 📄 Licencia

Este proyecto es para uso de la Iglesia Poblado.
