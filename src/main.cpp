#include <windows.h>
#include <string>
#include <map>
#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")

// IDs de controles
#define ID_USUARIO_EDIT 101
#define ID_PASSWORD_EDIT 102
#define ID_LOGIN_BUTTON 103
#define ID_CANCEL_BUTTON 104
#define ID_INFO_BUTTON 201
#define ID_PRODUCTOS_BUTTON 202
#define ID_CONTACTO_BUTTON 203
#define ID_CERRAR_SESION_BUTTON 204

// Variables globales
std::wstring usuarioActual;
std::map<std::wstring, std::wstring> usuarios = {
    {L"admin", L"admin123"},
    {L"usuario", L"pass123"},
    {L"iglesia", L"poblado2024"}
};

// Procedimientos de ventana
LRESULT CALLBACK LoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Función para crear la ventana de login
bool MostrarLogin(HINSTANCE hInstance) {
    const wchar_t LOGIN_CLASS[] = L"LoginWindow";
    
    WNDCLASS wc = {};
    wc.lpfnWndProc = LoginWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = LOGIN_CLASS;
    wc.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClass(&wc);
    
    HWND hwnd = CreateWindowEx(
        0,
        LOGIN_CLASS,
        L"Inicio de Sesión - Iglesia Poblado",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        420, 380,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    
    if (hwnd == NULL) return false;
    
    // Centrar la ventana
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int x = (GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left)) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top)) / 2;
    SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    // Ciclo de mensajes del login
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return !usuarioActual.empty();
}

// Procedimiento de ventana del login
LRESULT CALLBACK LoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hUsuario, hPassword, hBtnLogin, hBtnCancel;
    static HFONT hFont, hTitleFont;
    
    switch (uMsg) {
    case WM_CREATE:
        {
            // Crear fuentes
            hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            hTitleFont = CreateFont(26, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            // Etiqueta Usuario
            CreateWindow(L"STATIC", L"Usuario:",
                WS_VISIBLE | WS_CHILD,
                50, 100, 100, 25, hwnd, NULL,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            
            // Campo Usuario
            hUsuario = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                50, 125, 300, 30, hwnd, (HMENU)ID_USUARIO_EDIT,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SendMessage(hUsuario, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Etiqueta Contraseña
            CreateWindow(L"STATIC", L"Contraseña:",
                WS_VISIBLE | WS_CHILD,
                50, 170, 100, 25, hwnd, NULL,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            
            // Campo Contraseña
            hPassword = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | ES_PASSWORD | ES_AUTOHSCROLL,
                50, 195, 300, 30, hwnd, (HMENU)ID_PASSWORD_EDIT,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SendMessage(hPassword, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hPassword, EM_SETPASSWORDCHAR, (WPARAM)L'●', 0);
            
            // Botón Iniciar Sesión
            hBtnLogin = CreateWindow(L"BUTTON", L"Iniciar Sesión",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                50, 250, 140, 40, hwnd, (HMENU)ID_LOGIN_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SendMessage(hBtnLogin, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Botón Cancelar
            hBtnCancel = CreateWindow(L"BUTTON", L"Cancelar",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                210, 250, 140, 40, hwnd, (HMENU)ID_CANCEL_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SendMessage(hBtnCancel, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            SetFocus(hUsuario);
        }
        break;
        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Dibujar panel superior azul
            RECT rectTop = {0, 0, 420, 70};
            HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 120, 215));
            FillRect(hdc, &rectTop, hBrushBlue);
            DeleteObject(hBrushBlue);
            
            // Dibujar título
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            HFONT hOldFont = (HFONT)SelectObject(hdc, hTitleFont);
            RECT rectText = {0, 15, 420, 60};
            DrawText(hdc, L"🔐 IGLESIA POBLADO", -1, &rectText,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            SelectObject(hdc, hOldFont);
            
            EndPaint(hwnd, &ps);
        }
        break;
        
    case WM_COMMAND:
        if (LOWORD(wParam) == ID_LOGIN_BUTTON || 
            (LOWORD(wParam) == ID_PASSWORD_EDIT && HIWORD(wParam) == EN_SETFOCUS)) {
            
            if (LOWORD(wParam) == ID_LOGIN_BUTTON) {
                wchar_t usuario[100], password[100];
                GetWindowText(hUsuario, usuario, 100);
                GetWindowText(hPassword, password, 100);
                
                std::wstring user(usuario);
                std::wstring pass(password);
                
                if (usuarios.find(user) != usuarios.end() && usuarios[user] == pass) {
                    usuarioActual = user;
                    PostQuitMessage(0);
                } else {
                    MessageBox(hwnd,
                        L"Usuario o contraseña incorrectos.\n\nUsuarios de prueba:\nadmin / admin123\nusuario / pass123\niglesia / poblado2024",
                        L"Error de Autenticación",
                        MB_OK | MB_ICONERROR);
                    SetWindowText(hPassword, L"");
                    SetFocus(hPassword);
                }
            }
        }
        else if (LOWORD(wParam) == ID_CANCEL_BUTTON) {
            usuarioActual.clear();
            PostQuitMessage(0);
        }
        break;
        
    case WM_DESTROY:
        DeleteObject(hFont);
        DeleteObject(hTitleFont);
        break;
        
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Procedimiento de ventana principal
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HFONT hFont, hTitleFont, hButtonFont;
    static HWND hBtnInfo, hBtnProductos, hBtnContacto, hBtnCerrarSesion;
    
    switch (uMsg) {
    case WM_CREATE:
        {
            // Crear fuentes
            hFont = CreateFont(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            hTitleFont = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            hButtonFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            // Botón cerrar sesión
            hBtnCerrarSesion = CreateWindow(L"BUTTON", L"Cerrar Sesión",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                540, 15, 130, 35, hwnd, (HMENU)ID_CERRAR_SESION_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            
            // Botones principales
            hBtnInfo = CreateWindow(L"BUTTON", L"📋 Ver Información",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                100, 200, 500, 55, hwnd, (HMENU)ID_INFO_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SendMessage(hBtnInfo, WM_SETFONT, (WPARAM)hButtonFont, TRUE);
            
            hBtnProductos = CreateWindow(L"BUTTON", L"🛒 Ver Productos",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                100, 270, 500, 55, hwnd, (HMENU)ID_PRODUCTOS_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SendMessage(hBtnProductos, WM_SETFONT, (WPARAM)hButtonFont, TRUE);
            
            hBtnContacto = CreateWindow(L"BUTTON", L"📞 Contacto",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                100, 340, 500, 55, hwnd, (HMENU)ID_CONTACTO_BUTTON,
                (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
            SendMessage(hBtnContacto, WM_SETFONT, (WPARAM)hButtonFont, TRUE);
        }
        break;
        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // Panel superior azul
            RECT rectTop = {0, 0, 720, 70};
            HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 120, 215));
            FillRect(hdc, &rectTop, hBrushBlue);
            DeleteObject(hBrushBlue);
            
            // Texto de bienvenida
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
            RECT rectText = {20, 20, 500, 60};
            std::wstring welcome = L"Bienvenido, " + usuarioActual + L"!";
            DrawText(hdc, welcome.c_str(), -1, &rectText, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
            
            // Título principal
            SelectObject(hdc, hTitleFont);
            SetTextColor(hdc, RGB(0, 0, 0));
            RECT rectTitle = {50, 110, 650, 160};
            DrawText(hdc, L"🏛️ Tienda Iglesia Poblado", -1, &rectTitle,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            
            SelectObject(hdc, hOldFont);
            EndPaint(hwnd, &ps);
        }
        break;
        
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_INFO_BUTTON:
            {
                std::wstring msg = L"Iglesia Poblado - Tienda Religiosa\n\n";
                msg += L"Usuario actual: " + usuarioActual + L"\n\n";
                msg += L"Ofrecemos artículos religiosos, libros, souvenirs y más.";
                MessageBox(hwnd, msg.c_str(), L"Información", MB_OK | MB_ICONINFORMATION);
            }
            break;
            
        case ID_PRODUCTOS_BUTTON:
            MessageBox(hwnd,
                L"Productos disponibles:\n\n"
                L"✝️ Biblias y libros religiosos\n"
                L"🕯️ Velas y candelas\n"
                L"📿 Rosarios y cruces\n"
                L"🖼️ Cuadros e imágenes religiosas\n"
                L"🎁 Souvenirs y regalos\n\n"
                L"¡Visítanos para más detalles!",
                L"Catálogo de Productos",
                MB_OK | MB_ICONINFORMATION);
            break;
            
        case ID_CONTACTO_BUTTON:
            MessageBox(hwnd,
                L"Contacto:\n\n"
                L"📍 Dirección: Iglesia Poblado\n"
                L"📞 Teléfono: (XXX) XXX-XXXX\n"
                L"📧 Email: info@iglesiapoblado.com\n"
                L"🌐 Web: www.iglesiapoblado.com\n\n"
                L"¡Esperamos verte pronto!",
                L"Información de Contacto",
                MB_OK | MB_ICONINFORMATION);
            break;
            
        case ID_CERRAR_SESION_BUTTON:
            if (MessageBox(hwnd,
                L"¿Está seguro de que desea cerrar sesión?",
                L"Cerrar Sesión",
                MB_YESNO | MB_ICONQUESTION) == IDYES) {
                PostQuitMessage(0);
            }
            break;
        }
        break;
        
    case WM_DESTROY:
        DeleteObject(hFont);
        DeleteObject(hTitleFont);
        DeleteObject(hButtonFont);
        PostQuitMessage(0);
        break;
        
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Punto de entrada principal
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Mostrar ventana de login
    if (!MostrarLogin(hInstance)) {
        MessageBox(NULL,
            L"Sesión cancelada. La aplicación se cerrará.",
            L"Aviso",
            MB_OK | MB_ICONINFORMATION);
        return 0;
    }
    
    // Si el login fue exitoso, mostrar ventana principal
    const wchar_t MAIN_CLASS[] = L"MainWindow";
    
    WNDCLASS wc = {};
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = MAIN_CLASS;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClass(&wc);
    
    HWND hwnd = CreateWindowEx(
        0,
        MAIN_CLASS,
        L"Iglesia Poblado - Aplicación Principal",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        720, 540,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    
    if (hwnd == NULL) return 0;
    
    // Centrar la ventana
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int x = (GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left)) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top)) / 2;
    SetWindowPos(hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // Ciclo de mensajes principal
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
