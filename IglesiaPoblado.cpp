#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include "resource.h"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Estructuras
struct Usuario {
    std::wstring nombre;
    std::wstring password;
};

struct Producto {
    int id;
    std::wstring nombre;
    double precio;
    std::wstring categoria;
    int stock;
};

// Variables globales
std::map<std::wstring, std::wstring> usuarios;
std::vector<Producto> productos;
std::wstring usuarioActual;
HWND hMainWindow = NULL;
HWND hInventarioWindow = NULL;

// Prototipos de funciones
LRESULT CALLBACK LoginWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK InventarioWndProc(HWND, UINT, WPARAM, LPARAM);
void InicializarDatos();
void MostrarVentanaLogin(HINSTANCE);
void MostrarVentanaPrincipal(HINSTANCE);
void MostrarVentanaInventario(HINSTANCE);
void MostrarVentanaCreditos(HINSTANCE);
void CrearTarjetaProducto(HWND, const Producto&, int, int);
std::wstring FormatearPrecio(double);

// IDs de controles
#define IDC_EDIT_USUARIO 1001
#define IDC_EDIT_PASSWORD 1002
#define IDC_BTN_LOGIN 1003
#define IDC_BTN_CANCELAR 1004
#define IDC_BTN_CERRAR_SESION 1005
#define IDC_BTN_INVENTARIO 1006
#define IDC_BTN_TOGGLE_PANEL 1007
#define IDC_EDIT_BUSCAR 1008
#define IDC_BTN_BUSCAR 1009
#define IDC_PANEL_PRODUCTOS 1010
#define IDC_EDIT_NOMBRE 1011
#define IDC_EDIT_PRECIO 1012
#define IDC_COMBO_CATEGORIA 1013
#define IDC_EDIT_STOCK 1014
#define IDC_BTN_AGREGAR 1015
#define IDC_BTN_MODIFICAR 1016
#define IDC_BTN_ELIMINAR 1017
#define IDC_BTN_LIMPIAR 1018
#define IDC_LISTVIEW_INVENTARIO 1019
#define IDC_BTN_CERRAR_INV 1020

// Punto de entrada
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    InicializarDatos();
    MostrarVentanaLogin(hInstance);
    return 0;
}

// Inicializar datos
void InicializarDatos() {
    usuarios[L"poblado"] = L"poblado26";
    usuarios[L"Juan Diego"] = L"Esognare2020.";
    
    productos.push_back({1, L"Biblia Reina Valera", 45000, L"Libros", 50});
    productos.push_back({2, L"Rosario de Plata", 35000, L"Accesorios", 30});
    productos.push_back({3, L"Cruz de Madera", 25000, L"Decoración", 40});
    productos.push_back({4, L"Velas Aromáticas (Pack 6)", 18000, L"Velas", 100});
    productos.push_back({5, L"Imagen Virgen María 30cm", 55000, L"Imágenes", 20});
    productos.push_back({6, L"Libro Oraciones Diarias", 28000, L"Libros", 35});
    productos.push_back({7, L"Medalla San Benito", 15000, L"Accesorios", 60});
    productos.push_back({8, L"Cuadro Sagrado Corazón", 42000, L"Decoración", 25});
    productos.push_back({9, L"Velas Blancas (Pack 12)", 22000, L"Velas", 80});
    productos.push_back({10, L"Estampas Religiosas (Set)", 8000, L"Souvenirs", 120});
}

// Formatear precio
std::wstring FormatearPrecio(double precio) {
    std::wostringstream oss;
    oss << L"$" << std::fixed << std::setprecision(0) << precio;
    return oss.str();
}

// Ventana de Login
void MostrarVentanaLogin(HINSTANCE hInstance) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = LoginWndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
    wc.lpszClassName = L"LoginWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClassEx(&wc);
    
    HWND hwnd = CreateWindowEx(0, L"LoginWindow", L"Inicio de Sesión - Tienda Iglesia Poblado",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 420, 340,
        NULL, NULL, hInstance, NULL);
    
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK LoginWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEditUsuario, hEditPassword;
    static HFONT hFont, hTitleFont;
    
    switch (msg) {
        case WM_CREATE: {
            InitCommonControls();
            
            // Fuentes
            hTitleFont = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
            
            hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            // Título
            HWND hTitle = CreateWindow(L"STATIC", L"TIENDA IGLESIA POBLADO",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                0, 20, 400, 40, hwnd, NULL, NULL, NULL);
            SendMessage(hTitle, WM_SETFONT, (WPARAM)hTitleFont, TRUE);
            
            // Etiquetas y campos
            CreateWindow(L"STATIC", L"Usuario:", WS_CHILD | WS_VISIBLE,
                50, 90, 80, 20, hwnd, NULL, NULL, NULL);
            
            hEditUsuario = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                50, 115, 300, 25, hwnd, (HMENU)IDC_EDIT_USUARIO, NULL, NULL);
            SendMessage(hEditUsuario, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            CreateWindow(L"STATIC", L"Contraseña:", WS_CHILD | WS_VISIBLE,
                50, 155, 100, 20, hwnd, NULL, NULL, NULL);
            
            hEditPassword = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD | ES_AUTOHSCROLL,
                50, 180, 300, 25, hwnd, (HMENU)IDC_EDIT_PASSWORD, NULL, NULL);
            SendMessage(hEditPassword, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Botones
            HWND hBtnLogin = CreateWindow(L"BUTTON", L"Iniciar Sesión",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                50, 230, 140, 35, hwnd, (HMENU)IDC_BTN_LOGIN, NULL, NULL);
            SendMessage(hBtnLogin, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            HWND hBtnCancelar = CreateWindow(L"BUTTON", L"Cancelar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                210, 230, 140, 35, hwnd, (HMENU)IDC_BTN_CANCELAR, NULL, NULL);
            SendMessage(hBtnCancelar, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            break;
        }
        
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_BTN_LOGIN) {
                wchar_t usuario[256], password[256];
                GetWindowText(GetDlgItem(hwnd, IDC_EDIT_USUARIO), usuario, 256);
                GetWindowText(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), password, 256);
                
                std::wstring strUsuario(usuario);
                std::wstring strPassword(password);
                
                if (usuarios.find(strUsuario) != usuarios.end() && 
                    usuarios[strUsuario] == strPassword) {
                    usuarioActual = strUsuario;
                    DestroyWindow(hwnd);
                    MostrarVentanaPrincipal(GetModuleHandle(NULL));
                } else {
                    MessageBox(hwnd, L"Usuario o contraseña incorrectos", 
                        L"Error", MB_OK | MB_ICONERROR);
                }
            } else if (LOWORD(wParam) == IDC_BTN_CANCELAR) {
                PostQuitMessage(0);
            }
            break;
        }
        
        case WM_DESTROY:
            DeleteObject(hFont);
            DeleteObject(hTitleFont);
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Ventana Principal
void MostrarVentanaPrincipal(HINSTANCE hInstance) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = MainWndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(245, 245, 245));
    wc.lpszClassName = L"MainWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClassEx(&wc);
    
    hMainWindow = CreateWindowEx(0, L"MainWindow", L"Iglesia Poblado - Aplicación Principal",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1100, 650,
        NULL, NULL, hInstance, NULL);
    
    ShowWindow(hMainWindow, SW_SHOW);
    UpdateWindow(hMainWindow);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HFONT hFont, hTitleFont, hBigFont;
    static HWND hPanelProductos, hEditBuscar, hReloj;
    static int contadorVisitas = 1234;
    static int productosVendidos = 876;
    
    switch (msg) {
        case WM_CREATE: {
            InitCommonControls();
            
            // Fuentes
            hTitleFont = CreateFont(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
            
            hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            hBigFont = CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            // Panel superior azul
            HWND hTopPanel = CreateWindow(L"STATIC", L"",
                WS_CHILD | WS_VISIBLE | SS_BLACKRECT,
                0, 0, 1100, 70, hwnd, NULL, NULL, NULL);
            
            // Título de bienvenida
            std::wstring titulo = L"👤 Bienvenido, " + usuarioActual + L"!";
            HWND hWelcome = CreateWindow(L"STATIC", titulo.c_str(),
                WS_CHILD | WS_VISIBLE,
                20, 10, 500, 30, hwnd, NULL, NULL, NULL);
            SendMessage(hWelcome, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Reloj en tiempo real
            SYSTEMTIME st;
            GetLocalTime(&st);
            wchar_t timeStr[50];
            wsprintf(timeStr, L"🕐 %02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
            hReloj = CreateWindow(L"STATIC", timeStr,
                WS_CHILD | WS_VISIBLE,
                20, 40, 200, 25, hwnd, NULL, NULL, NULL);
            SendMessage(hReloj, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Timer para actualizar reloj cada segundo
            SetTimer(hwnd, 1, 1000, NULL);
            
            // Botón cerrar sesión
            HWND hBtnCerrar = CreateWindow(L"BUTTON", L"🚪 Cerrar Sesión",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                940, 15, 140, 40, hwnd, (HMENU)IDC_BTN_CERRAR_SESION, NULL, NULL);
            
            // Panel lateral izquierdo oscuro (estadísticas)
            HWND hPanelLateral = CreateWindow(L"STATIC", L"",
                WS_CHILD | WS_VISIBLE | SS_BLACKRECT,
                0, 70, 250, 580, hwnd, NULL, NULL, NULL);
            
            // GroupBox para Créditos (similar al del inventario)
            HWND hGroupBoxCreditos = CreateWindow(L"BUTTON", L"💳 Gestión de Créditos",
                WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                10, 80, 230, 120, hwnd, NULL, NULL, NULL);
            SendMessage(hGroupBoxCreditos, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Créditos disponibles - Etiqueta
            CreateWindow(L"STATIC", L"Créditos Disponibles:",
                WS_CHILD | WS_VISIBLE,
                25, 115, 200, 20, hwnd, NULL, NULL, NULL);
            
            // Créditos disponibles - Cuadro de texto
            HWND hTxtCreditos = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"150000",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER | ES_CENTER,
                25, 140, 200, 35, hwnd, (HMENU)1200, NULL, NULL);
            SendMessage(hTxtCreditos, WM_SETFONT, (WPARAM)hBigFont, TRUE);
            
            // Botón inventario en panel lateral
            HWND hBtnInventario = CreateWindow(L"BUTTON", L"📦 Gestión Inventario",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                20, 220, 210, 45, hwnd, (HMENU)IDC_BTN_INVENTARIO, NULL, NULL);
            SendMessage(hBtnInventario, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Botón actualizar créditos
            HWND hBtnActualizar = CreateWindow(L"BUTTON", L"🔄 Actualizar Créditos",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                20, 280, 210, 45, hwnd, (HMENU)1201, NULL, NULL);
            SendMessage(hBtnInventario, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Área principal - Título
            HWND hTitulo = CreateWindow(L"STATIC", L"🏪 Tienda Iglesia Poblado",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                280, 90, 800, 40, hwnd, NULL, NULL, NULL);
            SendMessage(hTitulo, WM_SETFONT, (WPARAM)hTitleFont, TRUE);
            
            // Barra de búsqueda
            CreateWindow(L"STATIC", L"🔍 Buscar Producto:",
                WS_CHILD | WS_VISIBLE,
                280, 150, 180, 25, hwnd, NULL, NULL, NULL);
            
            hEditBuscar = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                470, 148, 400, 28, hwnd, (HMENU)IDC_EDIT_BUSCAR, NULL, NULL);
            SendMessage(hEditBuscar, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            CreateWindow(L"BUTTON", L"🔎 Buscar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                880, 146, 100, 32, hwnd, (HMENU)IDC_BTN_BUSCAR, NULL, NULL);
            
            // ScrollView para productos
            hPanelProductos = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"",
                WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER,
                280, 200, 800, 400, hwnd, (HMENU)IDC_PANEL_PRODUCTOS, NULL, NULL);
            
            // Cargar productos en tarjetas
            int x = 10, y = 10;
            for (size_t i = 0; i < productos.size() && i < 8; i++) {
                CrearTarjetaProducto(hPanelProductos, productos[i], x, y);
                x += 230;
                if (x > 570) {
                    x = 10;
                    y += 190;
                }
            }
            
            // FOOTER CON SOPORTE
            HWND hFooter = CreateWindow(L"STATIC", L"",
                WS_CHILD | WS_VISIBLE | SS_BLACKRECT,
                0, 600, 1100, 50, hwnd, NULL, NULL, NULL);
            
            // Información de soporte
            HWND hSoporte = CreateWindow(L"STATIC", L"📞 Soporte: soporte@iglesiapoblado.com | Tel: (601) 123-4567",
                WS_CHILD | WS_VISIBLE,
                20, 615, 600, 25, hwnd, NULL, NULL, NULL);
            SendMessage(hSoporte, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Botón de ayuda
            HWND hBtnAyuda = CreateWindow(L"BUTTON", L"❓ Ayuda",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                650, 608, 100, 35, hwnd, (HMENU)1100, NULL, NULL);
            
            // Copyright
            HWND hCopyright = CreateWindow(L"STATIC", L"© 2026 Iglesia Poblado",
                WS_CHILD | WS_VISIBLE | SS_RIGHT,
                880, 615, 200, 25, hwnd, NULL, NULL, NULL);
            
            break;
        }
        
        case WM_TIMER: {
            // Actualizar reloj cada segundo
            if (wParam == 1) {
                SYSTEMTIME st;
                GetLocalTime(&st);
                wchar_t timeStr[50];
                wsprintf(timeStr, L"🕐 %02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
                SetWindowText(hReloj, timeStr);
            }
            break;
        }
        
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_BTN_CERRAR_SESION) {
                if (MessageBox(hwnd, L"¿Está seguro de cerrar sesión?", 
                    L"Confirmar", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                    KillTimer(hwnd, 1);
                    DestroyWindow(hwnd);
                    MostrarVentanaLogin(GetModuleHandle(NULL));
                }
            } else if (LOWORD(wParam) == IDC_BTN_INVENTARIO) {
                MostrarVentanaInventario(GetModuleHandle(NULL));
            } else if (LOWORD(wParam) == IDC_BTN_BUSCAR) {
                wchar_t busqueda[256];
                GetWindowText(hEditBuscar, busqueda, 256);
                std::wstring strBusqueda = busqueda;
                
                if (strBusqueda.empty()) {
                    MessageBox(hwnd, L"Ingrese un término de búsqueda", 
                        L"Campo vacío", MB_OK | MB_ICONINFORMATION);
                } else {
                    // Buscar productos que coincidan
                    int encontrados = 0;
                    for (const auto& prod : productos) {
                        if (prod.nombre.find(strBusqueda) != std::wstring::npos) {
                            encontrados++;
                        }
                    }
                    
                    wchar_t resultado[256];
                    wsprintf(resultado, L"Se encontraron %d productos con '%s'", encontrados, busqueda);
                    MessageBox(hwnd, resultado, L"Resultado de búsqueda", MB_OK | MB_ICONINFORMATION);
                }
            } else if (LOWORD(wParam) == 1100) {
                // Botón de ayuda
                MessageBox(hwnd, 
                    L"Centro de Soporte - Iglesia Poblado\n\n"
                    L"📧 Email: soporte@iglesiapoblado.com\n"
                    L"📞 Teléfono: (601) 123-4567\n"
                    L"⏰ Horario: Lunes a Viernes 8:00 AM - 6:00 PM\n\n"
                    L"¿Necesitas ayuda?\n"
                    L"• Gestión de inventario\n"
                    L"• Búsqueda de productos\n"
                    L"• Reportes y estadísticas\n"
                    L"• Configuración de cuenta\n\n"
                    L"¡Estamos aquí para ayudarte!",
                    L"Centro de Soporte", MB_OK | MB_ICONINFORMATION);
            } else if (LOWORD(wParam) == 1201) {
                // Botón actualizar créditos - Abrir ventana de créditos
                MostrarVentanaCreditos(GetModuleHandle(NULL));
            }
            break;
        }
        
        case WM_DESTROY:
            KillTimer(hwnd, 1);
            DeleteObject(hFont);
            DeleteObject(hTitleFont);
            DeleteObject(hBigFont);
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void CrearTarjetaProducto(HWND parent, const Producto& prod, int x, int y) {
    // Panel de tarjeta
    HWND hCard = CreateWindow(L"BUTTON", L"",
        WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
        x, y, 220, 180, parent, NULL, NULL, NULL);
    
    // Icono
    const wchar_t* icono = L"📦";
    if (prod.categoria == L"Libros") icono = L"📖";
    else if (prod.categoria == L"Velas") icono = L"🕯️";
    else if (prod.categoria == L"Accesorios") icono = L"📿";
    else if (prod.categoria == L"Decoración") icono = L"🖼️";
    else if (prod.categoria == L"Imágenes") icono = L"✝️";
    else if (prod.categoria == L"Souvenirs") icono = L"🎁";
    
    CreateWindow(L"STATIC", icono,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        x + 10, y + 10, 200, 40, parent, NULL, NULL, NULL);
    
    // Nombre
    CreateWindow(L"STATIC", prod.nombre.c_str(),
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        x + 10, y + 60, 200, 40, parent, NULL, NULL, NULL);
    
    // Precio
    std::wstring precio = FormatearPrecio(prod.precio);
    HWND hPrecio = CreateWindow(L"STATIC", precio.c_str(),
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        x + 10, y + 105, 200, 25, parent, NULL, NULL, NULL);
    
    // Categoría
    std::wstring cat = L"[" + prod.categoria + L"]";
    CreateWindow(L"STATIC", cat.c_str(),
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        x + 10, y + 135, 200, 20, parent, NULL, NULL, NULL);
}

// Ventana de Inventario
void MostrarVentanaInventario(HINSTANCE hInstance) {
    if (hInventarioWindow) {
        SetForegroundWindow(hInventarioWindow);
        return;
    }
    
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = InventarioWndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(245, 245, 245));
    wc.lpszClassName = L"InventarioWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClassEx(&wc);
    
    hInventarioWindow = CreateWindowEx(0, L"InventarioWindow", 
        L"Gestión de Inventario - Iglesia Poblado",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600,
        NULL, NULL, hInstance, NULL);
    
    ShowWindow(hInventarioWindow, SW_SHOW);
    UpdateWindow(hInventarioWindow);
}

LRESULT CALLBACK InventarioWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hListView, hEditNombre, hEditPrecio, hComboCategoria, hEditStock;
    static HFONT hFont, hTitleFont;
    
    switch (msg) {
        case WM_CREATE: {
            InitCommonControls();
            
            // Fuentes
            hTitleFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
            
            hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            // Panel superior verde
            HWND hTopPanel = CreateWindow(L"STATIC", L"",
                WS_CHILD | WS_VISIBLE | SS_BLACKRECT,
                0, 0, 1000, 60, hwnd, NULL, NULL, NULL);
            
            // Título
            HWND hTitulo = CreateWindow(L"STATIC", L"📦 GESTIÓN DE INVENTARIO",
                WS_CHILD | WS_VISIBLE,
                20, 15, 600, 30, hwnd, NULL, NULL, NULL);
            SendMessage(hTitulo, WM_SETFONT, (WPARAM)hTitleFont, TRUE);
            
            // Botón cerrar
            CreateWindow(L"BUTTON", L"✖ Cerrar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                880, 12, 100, 35, hwnd, (HMENU)IDC_BTN_CERRAR_INV, NULL, NULL);
            
            // GroupBox para formulario
            HWND hGroupBox = CreateWindow(L"BUTTON", L"Agregar / Editar Producto",
                WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                20, 80, 960, 150, hwnd, NULL, NULL, NULL);
            SendMessage(hGroupBox, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Campos del formulario
            // Nombre
            CreateWindow(L"STATIC", L"Nombre:",
                WS_CHILD | WS_VISIBLE,
                40, 110, 80, 20, hwnd, NULL, NULL, NULL);
            hEditNombre = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                40, 135, 250, 25, hwnd, (HMENU)IDC_EDIT_NOMBRE, NULL, NULL);
            SendMessage(hEditNombre, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Precio
            CreateWindow(L"STATIC", L"Precio:",
                WS_CHILD | WS_VISIBLE,
                310, 110, 80, 20, hwnd, NULL, NULL, NULL);
            hEditPrecio = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
                310, 135, 150, 25, hwnd, (HMENU)IDC_EDIT_PRECIO, NULL, NULL);
            SendMessage(hEditPrecio, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Categoría
            CreateWindow(L"STATIC", L"Categoría:",
                WS_CHILD | WS_VISIBLE,
                480, 110, 100, 20, hwnd, NULL, NULL, NULL);
            hComboCategoria = CreateWindow(L"COMBOBOX", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
                480, 135, 180, 200, hwnd, (HMENU)IDC_COMBO_CATEGORIA, NULL, NULL);
            SendMessage(hComboCategoria, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hComboCategoria, CB_ADDSTRING, 0, (LPARAM)L"Libros");
            SendMessage(hComboCategoria, CB_ADDSTRING, 0, (LPARAM)L"Accesorios");
            SendMessage(hComboCategoria, CB_ADDSTRING, 0, (LPARAM)L"Decoración");
            SendMessage(hComboCategoria, CB_ADDSTRING, 0, (LPARAM)L"Velas");
            SendMessage(hComboCategoria, CB_ADDSTRING, 0, (LPARAM)L"Imágenes");
            SendMessage(hComboCategoria, CB_ADDSTRING, 0, (LPARAM)L"Souvenirs");
            
            // Stock
            CreateWindow(L"STATIC", L"Stock:",
                WS_CHILD | WS_VISIBLE,
                680, 110, 80, 20, hwnd, NULL, NULL, NULL);
            hEditStock = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
                680, 135, 100, 25, hwnd, (HMENU)IDC_EDIT_STOCK, NULL, NULL);
            SendMessage(hEditStock, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Botones de acción
            HWND hBtnAgregar = CreateWindow(L"BUTTON", L"➕ Agregar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                40, 180, 120, 35, hwnd, (HMENU)IDC_BTN_AGREGAR, NULL, NULL);
            
            HWND hBtnModificar = CreateWindow(L"BUTTON", L"✏️ Modificar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                170, 180, 120, 35, hwnd, (HMENU)IDC_BTN_MODIFICAR, NULL, NULL);
            
            HWND hBtnEliminar = CreateWindow(L"BUTTON", L"🗑️ Eliminar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                300, 180, 120, 35, hwnd, (HMENU)IDC_BTN_ELIMINAR, NULL, NULL);
            
            HWND hBtnLimpiar = CreateWindow(L"BUTTON", L"🔄 Limpiar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                430, 180, 120, 35, hwnd, (HMENU)IDC_BTN_LIMPIAR, NULL, NULL);
            
            // Crear ListView
            hListView = CreateWindow(WC_LISTVIEW, L"",
                WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | WS_BORDER,
                20, 250, 960, 300, hwnd, (HMENU)IDC_LISTVIEW_INVENTARIO, NULL, NULL);
            ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            
            // Configurar columnas
            LVCOLUMN lvc = {0};
            lvc.mask = LVCF_TEXT | LVCF_WIDTH;
            
            lvc.pszText = (LPWSTR)L"ID";
            lvc.cx = 50;
            ListView_InsertColumn(hListView, 0, &lvc);
            
            lvc.pszText = (LPWSTR)L"Nombre";
            lvc.cx = 350;
            ListView_InsertColumn(hListView, 1, &lvc);
            
            lvc.pszText = (LPWSTR)L"Precio";
            lvc.cx = 150;
            ListView_InsertColumn(hListView, 2, &lvc);
            
            lvc.pszText = (LPWSTR)L"Categoría";
            lvc.cx = 200;
            ListView_InsertColumn(hListView, 3, &lvc);
            
            lvc.pszText = (LPWSTR)L"Stock";
            lvc.cx = 150;
            ListView_InsertColumn(hListView, 4, &lvc);
            
            // Cargar datos
            for (size_t i = 0; i < productos.size(); i++) {
                LVITEM lvi = {0};
                lvi.mask = LVIF_TEXT;
                lvi.iItem = i;
                
                wchar_t id[10];
                _itow_s(productos[i].id, id, 10, 10);
                lvi.pszText = id;
                ListView_InsertItem(hListView, &lvi);
                
                ListView_SetItemText(hListView, i, 1, (LPWSTR)productos[i].nombre.c_str());
                
                std::wstring precio = FormatearPrecio(productos[i].precio);
                ListView_SetItemText(hListView, i, 2, (LPWSTR)precio.c_str());
                
                ListView_SetItemText(hListView, i, 3, (LPWSTR)productos[i].categoria.c_str());
                
                wchar_t stock[10];
                _itow_s(productos[i].stock, stock, 10, 10);
                ListView_SetItemText(hListView, i, 4, stock);
            }
            
            break;
        }
        
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_BTN_CERRAR_INV) {
                DestroyWindow(hwnd);
            } else if (LOWORD(wParam) == IDC_BTN_AGREGAR) {
                wchar_t nombre[256], precio[50], stock[50];
                GetWindowText(hEditNombre, nombre, 256);
                GetWindowText(hEditPrecio, precio, 50);
                GetWindowText(hEditStock, stock, 50);
                
                if (wcslen(nombre) == 0) {
                    MessageBox(hwnd, L"Por favor ingrese el nombre del producto", 
                        L"Campo requerido", MB_OK | MB_ICONWARNING);
                    return 0;
                }
                
                int idx = SendMessage(hComboCategoria, CB_GETCURSEL, 0, 0);
                wchar_t categoria[100];
                SendMessage(hComboCategoria, CB_GETLBTEXT, idx, (LPARAM)categoria);
                
                Producto nuevo;
                nuevo.id = productos.size() + 1;
                nuevo.nombre = nombre;
                nuevo.precio = _wtof(precio);
                nuevo.categoria = (idx >= 0) ? categoria : L"Sin categoría";
                nuevo.stock = _wtoi(stock);
                productos.push_back(nuevo);
                
                // Agregar a ListView
                int pos = ListView_GetItemCount(hListView);
                LVITEM lvi = {0};
                lvi.mask = LVIF_TEXT;
                lvi.iItem = pos;
                wchar_t id[10];
                _itow_s(nuevo.id, id, 10, 10);
                lvi.pszText = id;
                ListView_InsertItem(hListView, &lvi);
                
                ListView_SetItemText(hListView, pos, 1, (LPWSTR)nuevo.nombre.c_str());
                ListView_SetItemText(hListView, pos, 2, (LPWSTR)FormatearPrecio(nuevo.precio).c_str());
                ListView_SetItemText(hListView, pos, 3, (LPWSTR)nuevo.categoria.c_str());
                wchar_t stockStr[10];
                _itow_s(nuevo.stock, stockStr, 10, 10);
                ListView_SetItemText(hListView, pos, 4, stockStr);
                
                MessageBox(hwnd, L"Producto agregado exitosamente", 
                    L"Éxito", MB_OK | MB_ICONINFORMATION);
                
                // Limpiar campos
                SetWindowText(hEditNombre, L"");
                SetWindowText(hEditPrecio, L"");
                SetWindowText(hEditStock, L"0");
                SendMessage(hComboCategoria, CB_SETCURSEL, -1, 0);
                
            } else if (LOWORD(wParam) == IDC_BTN_MODIFICAR) {
                int sel = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
                if (sel == -1) {
                    MessageBox(hwnd, L"Por favor seleccione un producto para modificar", 
                        L"Selección requerida", MB_OK | MB_ICONWARNING);
                    return 0;
                }
                
                wchar_t nombre[256], precio[50], stock[50];
                GetWindowText(hEditNombre, nombre, 256);
                GetWindowText(hEditPrecio, precio, 50);
                GetWindowText(hEditStock, stock, 50);
                
                int idx = SendMessage(hComboCategoria, CB_GETCURSEL, 0, 0);
                wchar_t categoria[100];
                SendMessage(hComboCategoria, CB_GETLBTEXT, idx, (LPARAM)categoria);
                
                ListView_SetItemText(hListView, sel, 1, nombre);
                ListView_SetItemText(hListView, sel, 2, (LPWSTR)FormatearPrecio(_wtof(precio)).c_str());
                ListView_SetItemText(hListView, sel, 3, categoria);
                ListView_SetItemText(hListView, sel, 4, stock);
                
                // Actualizar vector
                if (sel < productos.size()) {
                    productos[sel].nombre = nombre;
                    productos[sel].precio = _wtof(precio);
                    productos[sel].categoria = categoria;
                    productos[sel].stock = _wtoi(stock);
                }
                
                MessageBox(hwnd, L"Producto modificado exitosamente", 
                    L"Éxito", MB_OK | MB_ICONINFORMATION);
                
            } else if (LOWORD(wParam) == IDC_BTN_ELIMINAR) {
                int sel = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
                if (sel == -1) {
                    MessageBox(hwnd, L"Por favor seleccione un producto para eliminar", 
                        L"Selección requerida", MB_OK | MB_ICONWARNING);
                    return 0;
                }
                
                if (MessageBox(hwnd, L"¿Está seguro de eliminar este producto?", 
                    L"Confirmar eliminación", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                    ListView_DeleteItem(hListView, sel);
                    if (sel < productos.size()) {
                        productos.erase(productos.begin() + sel);
                    }
                    MessageBox(hwnd, L"Producto eliminado exitosamente", 
                        L"Éxito", MB_OK | MB_ICONINFORMATION);
                }
                
            } else if (LOWORD(wParam) == IDC_BTN_LIMPIAR) {
                SetWindowText(hEditNombre, L"");
                SetWindowText(hEditPrecio, L"");
                SetWindowText(hEditStock, L"0");
                SendMessage(hComboCategoria, CB_SETCURSEL, -1, 0);
            }
            break;
        }
        
        case WM_NOTIFY: {
            if (wParam == IDC_LISTVIEW_INVENTARIO) {
                LPNMHDR pnmh = (LPNMHDR)lParam;
                if (pnmh->code == LVN_ITEMCHANGED) {
                    LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
                    if (pnmv->uNewState & LVIS_SELECTED) {
                        int sel = pnmv->iItem;
                        wchar_t buffer[256];
                        
                        ListView_GetItemText(hListView, sel, 1, buffer, 256);
                        SetWindowText(hEditNombre, buffer);
                        
                        ListView_GetItemText(hListView, sel, 2, buffer, 256);
                        // Remover $ del precio
                        std::wstring precioStr = buffer;
                        if (precioStr[0] == L'$') precioStr = precioStr.substr(1);
                        SetWindowText(hEditPrecio, precioStr.c_str());
                        
                        ListView_GetItemText(hListView, sel, 3, buffer, 256);
                        int count = SendMessage(hComboCategoria, CB_GETCOUNT, 0, 0);
                        for (int i = 0; i < count; i++) {
                            wchar_t catBuffer[100];
                            SendMessage(hComboCategoria, CB_GETLBTEXT, i, (LPARAM)catBuffer);
                            if (wcscmp(catBuffer, buffer) == 0) {
                                SendMessage(hComboCategoria, CB_SETCURSEL, i, 0);
                                break;
                            }
                        }
                        
                        ListView_GetItemText(hListView, sel, 4, buffer, 256);
                        SetWindowText(hEditStock, buffer);
                    }
                }
            }
            break;
        }
        
        case WM_DESTROY:
            hInventarioWindow = NULL;
            DeleteObject(hFont);
            DeleteObject(hTitleFont);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Ventana de Créditos
void MostrarVentanaCreditos(HINSTANCE hInstance) {
    // Importar el procedimiento de ventana de VentanaCreditos.cpp
    // Para integración completa, se debe incluir el código de VentanaCreditos.cpp aquí
    // o compilar ambos archivos juntos
    
    MessageBox(NULL, 
        L"Para usar la ventana de créditos, compile VentanaCreditos.cpp junto con este archivo.\n\n"
        L"O ejecute directamente VentanaCreditos.exe como aplicación independiente.\n\n"
        L"La ventana de créditos incluye:\n"
        L"• Saldo actual con formato\n"
        L"• Registro de transacciones (Ingreso/Retiro)\n"
        L"• Historial completo con fecha y hora\n"
        L"• Validación de saldo para retiros\n"
        L"• Agregar, eliminar y modificar transacciones",
        L"Ventana de Créditos", MB_OK | MB_ICONINFORMATION);
}
