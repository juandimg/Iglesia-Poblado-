#include <windows.h>
#include <string>

// Procedimiento de ventana para manejar mensajes
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Punto de entrada de la aplicación
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Registrar la clase de ventana
    const wchar_t CLASS_NAME[] = L"IglesiaPobladoApp";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    // Crear la ventana
    HWND hwnd = CreateWindowEx(
        0,                              // Estilo extendido
        CLASS_NAME,                     // Nombre de clase
        L"Iglesia Poblado - Aplicación", // Título de la ventana
        WS_OVERLAPPEDWINDOW,            // Estilo de ventana
        CW_USEDEFAULT, CW_USEDEFAULT,   // Posición
        800, 600,                       // Tamaño
        NULL,                           // Ventana padre
        NULL,                           // Menú
        hInstance,                      // Instancia
        NULL                            // Datos adicionales
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Ciclo de mensajes
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Manejo de mensajes de la ventana
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hButton;
    static HWND hLabel;

    switch (uMsg) {
    case WM_CREATE:
        // Crear un botón
        hButton = CreateWindow(
            L"BUTTON",                      // Clase predefinida
            L"¡Haz clic aquí!",            // Texto del botón
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            300, 250,                       // Posición
            200, 50,                        // Tamaño
            hwnd,                           // Ventana padre
            (HMENU)1,                       // ID del control
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
        );

        // Crear una etiqueta
        hLabel = CreateWindow(
            L"STATIC",                      // Clase predefinida
            L"Bienvenido a la tienda Iglesia Poblado",
            WS_VISIBLE | WS_CHILD | SS_CENTER,
            200, 150,                       // Posición
            400, 30,                        // Tamaño
            hwnd,                           // Ventana padre
            NULL,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL
        );
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // El botón fue presionado
            MessageBox(hwnd, L"¡Botón presionado! Bienvenido a la Iglesia Poblado.", L"Mensaje", MB_OK | MB_ICONINFORMATION);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Rellenar el fondo
            FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
            
            EndPaint(hwnd, &ps);
        }
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
