#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "comctl32.lib")

// Estructura para transacciones de créditos
struct Transaccion {
    int id;
    std::wstring tipo;        // "Ingreso" o "Retiro"
    double monto;
    std::wstring descripcion;
    std::wstring fecha;
};

// Variables globales
std::vector<Transaccion> transacciones;
double saldoActual = 150000.0;
HWND hVentanaCreditos = NULL;

// IDs de controles
#define IDC_TXT_SALDO 2001
#define IDC_TXT_MONTO 2002
#define IDC_COMBO_TIPO 2003
#define IDC_TXT_DESCRIPCION 2004
#define IDC_BTN_AGREGAR_TRANSACCION 2005
#define IDC_BTN_ELIMINAR_TRANSACCION 2006
#define IDC_BTN_LIMPIAR_TRANSACCION 2007
#define IDC_LISTVIEW_TRANSACCIONES 2008
#define IDC_BTN_CERRAR_CREDITOS 2009
#define IDC_LBL_SALDO 2010

// Prototipos de funciones
LRESULT CALLBACK VentanaCreditosProc(HWND, UINT, WPARAM, LPARAM);
void InicializarTransacciones();
void ActualizarSaldo(HWND hwnd);
std::wstring FormatearMoneda(double monto);
std::wstring ObtenerFechaActual();

// Función para formatear moneda
std::wstring FormatearMoneda(double monto) {
    std::wostringstream oss;
    oss << L"$" << std::fixed << std::setprecision(0) << monto;
    return oss.str();
}

// Función para obtener fecha actual
std::wstring ObtenerFechaActual() {
    SYSTEMTIME st;
    GetLocalTime(&st);
    wchar_t fecha[50];
    wsprintf(fecha, L"%02d/%02d/%04d %02d:%02d", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);
    return std::wstring(fecha);
}

// Inicializar transacciones de ejemplo
void InicializarTransacciones() {
    transacciones.clear();
    transacciones.push_back({1, L"Ingreso", 150000.0, L"Saldo inicial", L"01/01/2026 08:00"});
    transacciones.push_back({2, L"Ingreso", 50000.0, L"Venta de productos", L"02/01/2026 10:30"});
    transacciones.push_back({3, L"Retiro", 20000.0, L"Compra de inventario", L"02/01/2026 15:45"});
    saldoActual = 180000.0;
}

// Actualizar el saldo mostrado
void ActualizarSaldo(HWND hwnd) {
    std::wstring saldo = FormatearMoneda(saldoActual);
    SetWindowText(GetDlgItem(hwnd, IDC_TXT_SALDO), saldo.c_str());
}

// Mostrar ventana de créditos
void MostrarVentanaCreditos(HINSTANCE hInstance) {
    if (hVentanaCreditos) {
        SetForegroundWindow(hVentanaCreditos);
        return;
    }
    
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = VentanaCreditosProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(245, 245, 245));
    wc.lpszClassName = L"VentanaCreditosClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClassEx(&wc);
    
    hVentanaCreditos = CreateWindowEx(0, L"VentanaCreditosClass", 
        L"💳 Gestión de Créditos - Iglesia Poblado",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 950, 650,
        NULL, NULL, hInstance, NULL);
    
    ShowWindow(hVentanaCreditos, SW_SHOW);
    UpdateWindow(hVentanaCreditos);
}

// Procedimiento de ventana de créditos
LRESULT CALLBACK VentanaCreditosProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hListView, hTxtMonto, hComboTipo, hTxtDescripcion, hTxtSaldo, hLblSaldo;
    static HFONT hFont, hTitleFont, hBigFont;
    
    switch (msg) {
        case WM_CREATE: {
            InitCommonControls();
            InicializarTransacciones();
            
            // Fuentes
            hTitleFont = CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
            
            hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            hBigFont = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            
            // Panel superior
            HWND hTopPanel = CreateWindow(L"STATIC", L"",
                WS_CHILD | WS_VISIBLE | SS_BLACKRECT,
                0, 0, 950, 70, hwnd, NULL, NULL, NULL);
            
            // Título
            HWND hTitulo = CreateWindow(L"STATIC", L"💳 GESTIÓN DE CRÉDITOS",
                WS_CHILD | WS_VISIBLE,
                20, 20, 600, 30, hwnd, NULL, NULL, NULL);
            SendMessage(hTitulo, WM_SETFONT, (WPARAM)hTitleFont, TRUE);
            
            // Botón cerrar
            CreateWindow(L"BUTTON", L"✖ Cerrar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                830, 17, 100, 35, hwnd, (HMENU)IDC_BTN_CERRAR_CREDITOS, NULL, NULL);
            
            // Panel de saldo actual
            HWND hGroupSaldo = CreateWindow(L"BUTTON", L"Saldo Actual",
                WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                20, 90, 300, 100, hwnd, NULL, NULL, NULL);
            SendMessage(hGroupSaldo, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            hLblSaldo = CreateWindow(L"STATIC", L"",
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                30, 120, 280, 50, hwnd, (HMENU)IDC_LBL_SALDO, NULL, NULL);
            SendMessage(hLblSaldo, WM_SETFONT, (WPARAM)hBigFont, TRUE);
            
            hTxtSaldo = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | ES_CENTER,
                340, 130, 200, 40, hwnd, (HMENU)IDC_TXT_SALDO, NULL, NULL);
            SendMessage(hTxtSaldo, WM_SETFONT, (WPARAM)hBigFont, TRUE);
            
            // GroupBox para nueva transacción
            HWND hGroupBox = CreateWindow(L"BUTTON", L"Nueva Transacción",
                WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                20, 210, 910, 140, hwnd, NULL, NULL, NULL);
            SendMessage(hGroupBox, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Tipo de transacción
            CreateWindow(L"STATIC", L"Tipo:",
                WS_CHILD | WS_VISIBLE,
                40, 240, 80, 20, hwnd, NULL, NULL, NULL);
            hComboTipo = CreateWindow(L"COMBOBOX", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
                40, 265, 150, 200, hwnd, (HMENU)IDC_COMBO_TIPO, NULL, NULL);
            SendMessage(hComboTipo, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hComboTipo, CB_ADDSTRING, 0, (LPARAM)L"Ingreso");
            SendMessage(hComboTipo, CB_ADDSTRING, 0, (LPARAM)L"Retiro");
            SendMessage(hComboTipo, CB_SETCURSEL, 0, 0);
            
            // Monto
            CreateWindow(L"STATIC", L"Monto:",
                WS_CHILD | WS_VISIBLE,
                210, 240, 80, 20, hwnd, NULL, NULL, NULL);
            hTxtMonto = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
                210, 265, 150, 30, hwnd, (HMENU)IDC_TXT_MONTO, NULL, NULL);
            SendMessage(hTxtMonto, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Descripción
            CreateWindow(L"STATIC", L"Descripción:",
                WS_CHILD | WS_VISIBLE,
                380, 240, 100, 20, hwnd, NULL, NULL, NULL);
            hTxtDescripcion = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                380, 265, 300, 30, hwnd, (HMENU)IDC_TXT_DESCRIPCION, NULL, NULL);
            SendMessage(hTxtDescripcion, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            // Botones de acción
            HWND hBtnAgregar = CreateWindow(L"BUTTON", L"➕ Agregar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                40, 305, 130, 35, hwnd, (HMENU)IDC_BTN_AGREGAR_TRANSACCION, NULL, NULL);
            
            HWND hBtnEliminar = CreateWindow(L"BUTTON", L"🗑️ Eliminar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                180, 305, 130, 35, hwnd, (HMENU)IDC_BTN_ELIMINAR_TRANSACCION, NULL, NULL);
            
            HWND hBtnLimpiar = CreateWindow(L"BUTTON", L"🔄 Limpiar",
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                320, 305, 130, 35, hwnd, (HMENU)IDC_BTN_LIMPIAR_TRANSACCION, NULL, NULL);
            
            // ListView para transacciones
            hListView = CreateWindow(WC_LISTVIEW, L"",
                WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | WS_BORDER,
                20, 370, 910, 220, hwnd, (HMENU)IDC_LISTVIEW_TRANSACCIONES, NULL, NULL);
            ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            
            // Configurar columnas del ListView
            LVCOLUMN lvc = {0};
            lvc.mask = LVCF_TEXT | LVCF_WIDTH;
            
            lvc.pszText = (LPWSTR)L"ID";
            lvc.cx = 50;
            ListView_InsertColumn(hListView, 0, &lvc);
            
            lvc.pszText = (LPWSTR)L"Tipo";
            lvc.cx = 100;
            ListView_InsertColumn(hListView, 1, &lvc);
            
            lvc.pszText = (LPWSTR)L"Monto";
            lvc.cx = 120;
            ListView_InsertColumn(hListView, 2, &lvc);
            
            lvc.pszText = (LPWSTR)L"Descripción";
            lvc.cx = 400;
            ListView_InsertColumn(hListView, 3, &lvc);
            
            lvc.pszText = (LPWSTR)L"Fecha";
            lvc.cx = 190;
            ListView_InsertColumn(hListView, 4, &lvc);
            
            // Cargar transacciones existentes
            for (size_t i = 0; i < transacciones.size(); i++) {
                LVITEM lvi = {0};
                lvi.mask = LVIF_TEXT;
                lvi.iItem = i;
                
                wchar_t id[10];
                _itow_s(transacciones[i].id, id, 10, 10);
                lvi.pszText = id;
                ListView_InsertItem(hListView, &lvi);
                
                ListView_SetItemText(hListView, i, 1, (LPWSTR)transacciones[i].tipo.c_str());
                
                std::wstring monto = FormatearMoneda(transacciones[i].monto);
                ListView_SetItemText(hListView, i, 2, (LPWSTR)monto.c_str());
                
                ListView_SetItemText(hListView, i, 3, (LPWSTR)transacciones[i].descripcion.c_str());
                ListView_SetItemText(hListView, i, 4, (LPWSTR)transacciones[i].fecha.c_str());
            }
            
            // Actualizar saldo inicial
            ActualizarSaldo(hwnd);
            
            break;
        }
        
        case WM_COMMAND: {
            if (LOWORD(wParam) == IDC_BTN_CERRAR_CREDITOS) {
                DestroyWindow(hwnd);
            } else if (LOWORD(wParam) == IDC_BTN_AGREGAR_TRANSACCION) {
                wchar_t monto[50], descripcion[256];
                GetWindowText(hTxtMonto, monto, 50);
                GetWindowText(hTxtDescripcion, descripcion, 256);
                
                if (wcslen(monto) == 0) {
                    MessageBox(hwnd, L"Por favor ingrese el monto", 
                        L"Campo requerido", MB_OK | MB_ICONWARNING);
                    return 0;
                }
                
                int idx = SendMessage(hComboTipo, CB_GETCURSEL, 0, 0);
                wchar_t tipo[50];
                SendMessage(hComboTipo, CB_GETLBTEXT, idx, (LPARAM)tipo);
                
                double montoDouble = _wtof(monto);
                
                // Actualizar saldo
                if (wcscmp(tipo, L"Ingreso") == 0) {
                    saldoActual += montoDouble;
                } else {
                    if (montoDouble > saldoActual) {
                        MessageBox(hwnd, L"Saldo insuficiente para realizar el retiro", 
                            L"Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                    saldoActual -= montoDouble;
                }
                
                Transaccion nueva;
                nueva.id = transacciones.size() + 1;
                nueva.tipo = tipo;
                nueva.monto = montoDouble;
                nueva.descripcion = (wcslen(descripcion) > 0) ? descripcion : L"Sin descripción";
                nueva.fecha = ObtenerFechaActual();
                transacciones.push_back(nueva);
                
                // Agregar a ListView
                int pos = ListView_GetItemCount(hListView);
                LVITEM lvi = {0};
                lvi.mask = LVIF_TEXT;
                lvi.iItem = pos;
                wchar_t id[10];
                _itow_s(nueva.id, id, 10, 10);
                lvi.pszText = id;
                ListView_InsertItem(hListView, &lvi);
                
                ListView_SetItemText(hListView, pos, 1, (LPWSTR)nueva.tipo.c_str());
                ListView_SetItemText(hListView, pos, 2, (LPWSTR)FormatearMoneda(nueva.monto).c_str());
                ListView_SetItemText(hListView, pos, 3, (LPWSTR)nueva.descripcion.c_str());
                ListView_SetItemText(hListView, pos, 4, (LPWSTR)nueva.fecha.c_str());
                
                // Actualizar saldo
                ActualizarSaldo(hwnd);
                
                MessageBox(hwnd, L"Transacción agregada exitosamente", 
                    L"Éxito", MB_OK | MB_ICONINFORMATION);
                
                // Limpiar campos
                SetWindowText(hTxtMonto, L"");
                SetWindowText(hTxtDescripcion, L"");
                SendMessage(hComboTipo, CB_SETCURSEL, 0, 0);
                
            } else if (LOWORD(wParam) == IDC_BTN_ELIMINAR_TRANSACCION) {
                int sel = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);
                if (sel == -1) {
                    MessageBox(hwnd, L"Por favor seleccione una transacción para eliminar", 
                        L"Selección requerida", MB_OK | MB_ICONWARNING);
                    return 0;
                }
                
                if (MessageBox(hwnd, L"¿Está seguro de eliminar esta transacción?\n\nEsto revertirá el monto al saldo.", 
                    L"Confirmar eliminación", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                    
                    // Revertir el saldo
                    if (sel < transacciones.size()) {
                        if (transacciones[sel].tipo == L"Ingreso") {
                            saldoActual -= transacciones[sel].monto;
                        } else {
                            saldoActual += transacciones[sel].monto;
                        }
                        transacciones.erase(transacciones.begin() + sel);
                    }
                    
                    ListView_DeleteItem(hListView, sel);
                    ActualizarSaldo(hwnd);
                    
                    MessageBox(hwnd, L"Transacción eliminada exitosamente", 
                        L"Éxito", MB_OK | MB_ICONINFORMATION);
                }
                
            } else if (LOWORD(wParam) == IDC_BTN_LIMPIAR_TRANSACCION) {
                SetWindowText(hTxtMonto, L"");
                SetWindowText(hTxtDescripcion, L"");
                SendMessage(hComboTipo, CB_SETCURSEL, 0, 0);
            }
            break;
        }
        
        case WM_NOTIFY: {
            if (wParam == IDC_LISTVIEW_TRANSACCIONES) {
                LPNMHDR pnmh = (LPNMHDR)lParam;
                if (pnmh->code == LVN_ITEMCHANGED) {
                    LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;
                    if (pnmv->uNewState & LVIS_SELECTED) {
                        int sel = pnmv->iItem;
                        wchar_t buffer[256];
                        
                        ListView_GetItemText(hListView, sel, 1, buffer, 256);
                        int count = SendMessage(hComboTipo, CB_GETCOUNT, 0, 0);
                        for (int i = 0; i < count; i++) {
                            wchar_t tipoBuffer[50];
                            SendMessage(hComboTipo, CB_GETLBTEXT, i, (LPARAM)tipoBuffer);
                            if (wcscmp(tipoBuffer, buffer) == 0) {
                                SendMessage(hComboTipo, CB_SETCURSEL, i, 0);
                                break;
                            }
                        }
                        
                        ListView_GetItemText(hListView, sel, 2, buffer, 256);
                        std::wstring montoStr = buffer;
                        if (montoStr[0] == L'$') montoStr = montoStr.substr(1);
                        SetWindowText(hTxtMonto, montoStr.c_str());
                        
                        ListView_GetItemText(hListView, sel, 3, buffer, 256);
                        SetWindowText(hTxtDescripcion, buffer);
                    }
                }
            }
            break;
        }
        
        case WM_DESTROY:
            hVentanaCreditos = NULL;
            DeleteObject(hFont);
            DeleteObject(hTitleFont);
            DeleteObject(hBigFont);
            break;
        
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Función principal (para prueba independiente)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MostrarVentanaCreditos(hInstance);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
