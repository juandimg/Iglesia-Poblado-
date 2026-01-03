# 💳 Ventana de Gestión de Créditos

## Descripción
Ventana independiente para gestionar créditos de la Iglesia Poblado con funcionalidad completa de transacciones.

## Características

### ✨ Funcionalidades Principales
- **Saldo Actual**: Visualización en tiempo real del saldo disponible
- **Nueva Transacción**: Formulario para agregar ingresos o retiros
- **Historial Completo**: ListView con todas las transacciones registradas
- **Validación**: Verifica saldo suficiente antes de retiros
- **Edición**: Permite seleccionar y modificar transacciones

### 📋 Campos de Transacción
- **Tipo**: Ingreso o Retiro (ComboBox)
- **Monto**: Cantidad numérica (validación automática)
- **Descripción**: Texto descriptivo de la transacción
- **Fecha**: Registro automático con formato dd/MM/yyyy HH:mm

### 🎨 Interfaz
- Panel superior azul con título y botón cerrar
- GroupBox "Saldo Actual" con monto en grande (verde)
- GroupBox "Nueva Transacción" con formulario completo
- DataGridView/ListView con 5 columnas (ID, Tipo, Monto, Descripción, Fecha)
- Botones: Agregar (verde), Eliminar (rojo), Limpiar (gris)

## Integración

### Opción 1: Archivo Independiente (VentanaCreditos.cpp)
Compilar y ejecutar como aplicación separada:

```bash
# Compilar con g++
g++ -o VentanaCreditos.exe VentanaCreditos.cpp -lcomctl32 -lgdi32 -mwindows

# O con Visual Studio
cl VentanaCreditos.cpp /link comctl32.lib gdi32.lib user32.lib

# Ejecutar
VentanaCreditos.exe
```

### Opción 2: Llamar desde IglesiaPoblado.cpp
El botón "🔄 Actualizar Créditos" en la ventana principal ya está configurado para abrir la ventana de créditos.

**PowerShell (.ps1)**:
- El botón llama a la función `Show-CreditosForm`
- Ejecutar: `powershell -ExecutionPolicy Bypass -File IglesiaPoblado.ps1`

**C++ (.cpp)**:
- El botón ID 1201 llama a `MostrarVentanaCreditos()`
- Actualmente muestra un mensaje informativo
- Para integración completa, incluir código de VentanaCreditos.cpp

### Opción 3: Compilación Conjunta (CMake)
Actualizar CMakeLists.txt para incluir ambos archivos:

```cmake
# Agregar ambos archivos
add_executable(IglesiaPoblado WIN32 
    IglesiaPoblado.cpp 
    VentanaCreditos.cpp
)
```

## Datos Iniciales

La ventana incluye 3 transacciones de ejemplo:
1. **Ingreso**: $150,000 - "Saldo inicial" (01/01/2026 08:00)
2. **Ingreso**: $50,000 - "Venta de productos" (02/01/2026 10:30)

**Saldo actual inicial**: 

## Validaciones

### Agregar Transacción
- ✅ Verifica que el monto no esté vacío
- ✅ Para retiros, verifica saldo suficiente
- ✅ Actualiza saldo automáticamente
- ✅ Muestra mensaje de confirmación

### Eliminar Transacción
- ✅ Requiere selección de fila
- ✅ Solicita confirmación
- ✅ Revierte el monto al saldo
- ✅ Actualiza vista

## Uso en PowerShell

```powershell
# La función Show-CreditosForm está disponible en IglesiaPoblado.ps1
# Se llama automáticamente al hacer clic en "🔄 Actualizar Créditos"

# Características PowerShell:
# - DataGridView con 5 columnas
# - Validación de entrada numérica
# - Formateo de moneda con separador de miles
# - Eventos de selección para edición rápida
```

## Uso en C++

```cpp
// Llamar desde cualquier parte del código
MostrarVentanaCreditos(hInstance);

// O incluir directamente el código de VentanaCreditos.cpp
// y usar la función del archivo
extern void MostrarVentanaCreditos(HINSTANCE);
```

## Capturas de Pantalla (Descripción)

### Pantalla Principal
- **Header**: Fondo azul con título "💳 GESTIÓN DE CRÉDITOS"
- **Saldo**: GroupBox con monto grande en verde oscuro
- **Formulario**: GroupBox con campos Tipo, Monto, Descripción
- **Tabla**: Lista de todas las transacciones
- **Footer**: (implícito en el diseño)

## Mejoras Futuras

- 📊 Gráficos de ingresos vs retiros
- 📁 Exportar a CSV/Excel
- 🔍 Filtros por fecha o tipo
- 💾 Persistencia en base de datos
- 🖨️ Impresión de reportes
- 📧 Envío de resumen por email

## Soporte

Para dudas o soporte técnico:
- 📧 Email: juandsoftware@gmail.com
- 📞 Teléfono: 350 567 4554

---
© 2026 Iglesia Poblado - Todos los derechos reservados
