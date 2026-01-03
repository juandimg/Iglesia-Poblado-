Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

# Base de datos simple de usuarios (en producción usar encriptación)
$usuarios = @{
    "poblado" = "poblado26"
    "Juan Diego" = "Esognare2020."

}

# Función para mostrar el formulario de login
function Show-LoginForm {
    $loginForm = New-Object System.Windows.Forms.Form
    $loginForm.Text = "Inicio de Sesión - Tienda Iglesia Poblado"
    $loginForm.ClientSize = New-Object System.Drawing.Size(400, 300)
    $loginForm.StartPosition = "CenterScreen"
    $loginForm.BackColor = [System.Drawing.Color]::FromArgb(240, 240, 240)
    $loginForm.FormBorderStyle = "FixedDialog"
    $loginForm.MaximizeBox = $false
    $loginForm.MinimizeBox = $false

    # Panel superior con título
    $panelTop = New-Object System.Windows.Forms.Panel
    $panelTop.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
    $panelTop.Size = New-Object System.Drawing.Size(400, 60)
    $panelTop.Location = New-Object System.Drawing.Point(0, 0)
    $loginForm.Controls.Add($panelTop)

    # Título
    $lblTitle = New-Object System.Windows.Forms.Label
    $lblTitle.Text = "TIENDA IGLESIA POBLADO"
    $lblTitle.Font = New-Object System.Drawing.Font("Segoe UI Emoji", 16, [System.Drawing.FontStyle]::Bold)
    $lblTitle.ForeColor = [System.Drawing.Color]::White
    $lblTitle.AutoSize = $false
    $lblTitle.Size = New-Object System.Drawing.Size(400, 60)
    $lblTitle.TextAlign = "MiddleCenter"
    $panelTop.Controls.Add($lblTitle)

    # Etiqueta de Usuario
    $lblUsuario = New-Object System.Windows.Forms.Label
    $lblUsuario.Text = "Usuario:"
    $lblUsuario.Location = New-Object System.Drawing.Point(50, 90)
    $lblUsuario.Size = New-Object System.Drawing.Size(80, 20)
    $lblUsuario.Font = New-Object System.Drawing.Font("Arial", 10, [System.Drawing.FontStyle]::Bold)
    $loginForm.Controls.Add($lblUsuario)

    # Campo de texto para Usuario
    $txtUsuario = New-Object System.Windows.Forms.TextBox
    $txtUsuario.Location = New-Object System.Drawing.Point(50, 115)
    $txtUsuario.Size = New-Object System.Drawing.Size(300, 25)
    $txtUsuario.Font = New-Object System.Drawing.Font("Arial", 11)
    $loginForm.Controls.Add($txtUsuario)

    # Etiqueta de Contraseña
    $lblPassword = New-Object System.Windows.Forms.Label
    $lblPassword.Text = "Contraseña:"
    $lblPassword.Location = New-Object System.Drawing.Point(50, 155)
    $lblPassword.Size = New-Object System.Drawing.Size(100, 20)
    $lblPassword.Font = New-Object System.Drawing.Font("Arial", 10, [System.Drawing.FontStyle]::Bold)
    $loginForm.Controls.Add($lblPassword)

    # Campo de texto para Contraseña
    $txtPassword = New-Object System.Windows.Forms.TextBox
    $txtPassword.Location = New-Object System.Drawing.Point(50, 180)
    $txtPassword.Size = New-Object System.Drawing.Size(300, 25)
    $txtPassword.Font = New-Object System.Drawing.Font("Arial", 12)
    $txtPassword.PasswordChar = "*"
    $loginForm.Controls.Add($txtPassword)

    # Botón de Iniciar Sesión
    $btnLogin = New-Object System.Windows.Forms.Button
    $btnLogin.Text = "Iniciar Sesión"
    $btnLogin.Location = New-Object System.Drawing.Point(50, 230)
    $btnLogin.Size = New-Object System.Drawing.Size(140, 35)
    $btnLogin.Font = New-Object System.Drawing.Font("Arial", 10, [System.Drawing.FontStyle]::Bold)
    $btnLogin.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
    $btnLogin.ForeColor = [System.Drawing.Color]::White
    $btnLogin.FlatStyle = "Flat"
    $btnLogin.Cursor = [System.Windows.Forms.Cursors]::Hand
    $loginForm.Controls.Add($btnLogin)

    # Botón de Cancelar
    $btnCancelar = New-Object System.Windows.Forms.Button
    $btnCancelar.Text = "Cancelar"
    $btnCancelar.Location = New-Object System.Drawing.Point(210, 230)
    $btnCancelar.Size = New-Object System.Drawing.Size(140, 35)
    $btnCancelar.Font = New-Object System.Drawing.Font("Arial", 10)
    $btnCancelar.BackColor = [System.Drawing.Color]::FromArgb(220, 220, 220)
    $btnCancelar.FlatStyle = "Flat"
    $btnCancelar.Cursor = [System.Windows.Forms.Cursors]::Hand
    $loginForm.Controls.Add($btnCancelar)

    # Variable para guardar el resultado del login
    $loginForm.Tag = $false

    # Evento del botón Iniciar Sesión
    $btnLogin.Add_Click({
        $usuario = $txtUsuario.Text
        $password = $txtPassword.Text

        if ($usuarios.ContainsKey($usuario) -and $usuarios[$usuario] -eq $password) {
            $loginForm.Tag = $usuario
            $loginForm.Close()
        } else {
            [System.Windows.Forms.MessageBox]::Show(
                [System.Windows.Forms.MessageBoxButtons]::OK,
                [System.Windows.Forms.MessageBoxIcon]::Error
            )
            $txtPassword.Clear()
            $txtPassword.Focus()
        }
    })

    # Evento del botón Cancelar
    $btnCancelar.Add_Click({
        $loginForm.Close()
    })

    # Permitir presionar Enter para iniciar sesión
    $txtPassword.Add_KeyDown({
        if ($_.KeyCode -eq "Enter") {
            $btnLogin.PerformClick()
        }
    })

    # Mostrar el formulario de login
    $loginForm.ShowDialog() | Out-Null
    return $loginForm.Tag
}

# Función para mostrar la gestión de créditos
function Show-CreditosForm {
    $formCreditos = New-Object System.Windows.Forms.Form
    $formCreditos.Text = " Detalle de Créditos - Iglesia Poblado"
    $formCreditos.ClientSize = New-Object System.Drawing.Size(950, 650)
    $formCreditos.StartPosition = "CenterScreen"
    $formCreditos.BackColor = [System.Drawing.Color]::FromArgb(245, 245, 245)
    $formCreditos.FormBorderStyle = "Sizable"
    $formCreditos.MinimumSize = New-Object System.Drawing.Size(900, 600)



    # Panel superior
    $panelTopCred = New-Object System.Windows.Forms.Panel
    $panelTopCred.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
    $panelTopCred.Dock = "Top"
    $panelTopCred.Height = 70
    $formCreditos.Controls.Add($panelTopCred)

    # Título
    $lblTituloCred = New-Object System.Windows.Forms.Label
    $lblTituloCred.Text = " DETALLE DE CRÉDITOS"
    $lblTituloCred.Font = New-Object System.Drawing.Font("Segoe UI Emoji", 18, [System.Drawing.FontStyle]::Bold)
    $lblTituloCred.ForeColor = [System.Drawing.Color]::White
    $lblTituloCred.AutoSize = $false
    $lblTituloCred.Size = New-Object System.Drawing.Size(600, 70)
    $lblTituloCred.Location = New-Object System.Drawing.Point(20, 0)
    $lblTituloCred.TextAlign = "MiddleLeft"
    $panelTopCred.Controls.Add($lblTituloCred)

    # Botón cerrar
    $btnCerrarCred = New-Object System.Windows.Forms.Button
    $btnCerrarCred.Text = "✖ Cerrar"
    $btnCerrarCred.Size = New-Object System.Drawing.Size(100, 35)
    $btnCerrarCred.Location = New-Object System.Drawing.Point(830, 17)
    $btnCerrarCred.Font = New-Object System.Drawing.Font("Arial", 9, [System.Drawing.FontStyle]::Bold)
    $btnCerrarCred.BackColor = [System.Drawing.Color]::FromArgb(220, 53, 69)
    $btnCerrarCred.ForeColor = [System.Drawing.Color]::White
    $btnCerrarCred.FlatStyle = "Flat"
    $btnCerrarCred.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelTopCred.Controls.Add($btnCerrarCred)

  
    # GroupBox Nueva Transacción
    $groupTransaccion = New-Object System.Windows.Forms.GroupBox
    $groupTransaccion.Text = "Nueva Transacción"
    $groupTransaccion.Location = New-Object System.Drawing.Point(20, 190)
    $groupTransaccion.Size = New-Object System.Drawing.Size(910, 140)
    $groupTransaccion.Font = New-Object System.Drawing.Font("Arial", 11, [System.Drawing.FontStyle]::Bold)
    $formCreditos.Controls.Add($groupTransaccion)

    # Tipo
    $lblTipo = New-Object System.Windows.Forms.Label
    $lblTipo.Text = "Tipo:"
    $lblTipo.Location = New-Object System.Drawing.Point(20, 30)
    $lblTipo.Size = New-Object System.Drawing.Size(80, 20)
    $lblTipo.Font = New-Object System.Drawing.Font("Arial", 10)
    $groupTransaccion.Controls.Add($lblTipo)

    $cmbTipo = New-Object System.Windows.Forms.ComboBox
    $cmbTipo.Location = New-Object System.Drawing.Point(20, 55)
    $cmbTipo.Size = New-Object System.Drawing.Size(150, 25)
    $cmbTipo.Font = New-Object System.Drawing.Font("Arial", 10)
    $cmbTipo.DropDownStyle = "DropDownList"
    $cmbTipo.Items.AddRange(@("Ingreso", "Retiro"))
    $cmbTipo.SelectedIndex = 0
    $groupTransaccion.Controls.Add($cmbTipo)

    # Monto
    $lblMonto = New-Object System.Windows.Forms.Label
    $lblMonto.Text = "Monto:"
    $lblMonto.Location = New-Object System.Drawing.Point(190, 30)
    $lblMonto.Size = New-Object System.Drawing.Size(80, 20)
    $lblMonto.Font = New-Object System.Drawing.Font("Arial", 10)
    $groupTransaccion.Controls.Add($lblMonto)

    $txtMonto = New-Object System.Windows.Forms.TextBox
    $txtMonto.Location = New-Object System.Drawing.Point(190, 55)
    $txtMonto.Size = New-Object System.Drawing.Size(150, 25)
    $txtMonto.Font = New-Object System.Drawing.Font("Arial", 10)
    $groupTransaccion.Controls.Add($txtMonto)

    # Descripción
    $lblDescripcion = New-Object System.Windows.Forms.Label
    $lblDescripcion.Text = "Descripción:"
    $lblDescripcion.Location = New-Object System.Drawing.Point(360, 30)
    $lblDescripcion.Size = New-Object System.Drawing.Size(100, 20)
    $lblDescripcion.Font = New-Object System.Drawing.Font("Arial", 10)
    $groupTransaccion.Controls.Add($lblDescripcion)

    $txtDescripcion = New-Object System.Windows.Forms.TextBox
    $txtDescripcion.Location = New-Object System.Drawing.Point(360, 55)
    $txtDescripcion.Size = New-Object System.Drawing.Size(300, 25)
    $txtDescripcion.Font = New-Object System.Drawing.Font("Arial", 10)
    $groupTransaccion.Controls.Add($txtDescripcion)

    # Botones
    $btnAgregarTrans = New-Object System.Windows.Forms.Button
    $btnAgregarTrans.Text = "➕ Agregar"
    $btnAgregarTrans.Location = New-Object System.Drawing.Point(20, 95)
    $btnAgregarTrans.Size = New-Object System.Drawing.Size(130, 35)
    $btnAgregarTrans.BackColor = [System.Drawing.Color]::FromArgb(40, 167, 69)
    $btnAgregarTrans.ForeColor = [System.Drawing.Color]::White
    $btnAgregarTrans.FlatStyle = "Flat"
    $btnAgregarTrans.Cursor = [System.Windows.Forms.Cursors]::Hand
    $groupTransaccion.Controls.Add($btnAgregarTrans)

    $btnEliminarTrans = New-Object System.Windows.Forms.Button
    $btnEliminarTrans.Text = "🗑️ Eliminar"
    $btnEliminarTrans.Location = New-Object System.Drawing.Point(160, 95)
    $btnEliminarTrans.Size = New-Object System.Drawing.Size(130, 35)
    $btnEliminarTrans.BackColor = [System.Drawing.Color]::FromArgb(220, 53, 69)
    $btnEliminarTrans.ForeColor = [System.Drawing.Color]::White
    $btnEliminarTrans.FlatStyle = "Flat"
    $btnEliminarTrans.Cursor = [System.Windows.Forms.Cursors]::Hand
    $groupTransaccion.Controls.Add($btnEliminarTrans)

    $btnLimpiarTrans = New-Object System.Windows.Forms.Button
    $btnLimpiarTrans.Text = "🔄 Limpiar"
    $btnLimpiarTrans.Location = New-Object System.Drawing.Point(300, 95)
    $btnLimpiarTrans.Size = New-Object System.Drawing.Size(130, 35)
    $btnLimpiarTrans.BackColor = [System.Drawing.Color]::FromArgb(108, 117, 125)
    $btnLimpiarTrans.ForeColor = [System.Drawing.Color]::White
    $btnLimpiarTrans.FlatStyle = "Flat"
    $btnLimpiarTrans.Cursor = [System.Windows.Forms.Cursors]::Hand
    $groupTransaccion.Controls.Add($btnLimpiarTrans)

    # DataGridView para transacciones
    $dgvTransacciones = New-Object System.Windows.Forms.DataGridView
    $dgvTransacciones.Location = New-Object System.Drawing.Point(20, 350)
    $dgvTransacciones.Size = New-Object System.Drawing.Size(910, 270)
    $dgvTransacciones.AllowUserToAddRows = $false
    $dgvTransacciones.ReadOnly = $true
    $dgvTransacciones.SelectionMode = "FullRowSelect"
    $dgvTransacciones.BackgroundColor = [System.Drawing.Color]::White
    $dgvTransacciones.BorderStyle = "Fixed3D"
    $dgvTransacciones.RowHeadersVisible = $false
    $dgvTransacciones.AutoSizeColumnsMode = "Fill"
    $formCreditos.Controls.Add($dgvTransacciones)

    # Columnas del DataGridView
    $colId = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colId.Name = "ID"
    $colId.HeaderText = "ID"
    $colId.Width = 50
    $dgvTransacciones.Columns.Add($colId)

    $colTipo = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colTipo.Name = "Tipo"
    $colTipo.HeaderText = "Tipo"
    $colTipo.Width = 100
    $dgvTransacciones.Columns.Add($colTipo)

    $colMonto = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colMonto.Name = "Monto"
    $colMonto.HeaderText = "Monto"
    $colMonto.Width = 120
    $dgvTransacciones.Columns.Add($colMonto)

    $colDesc = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colDesc.Name = "Descripcion"
    $colDesc.HeaderText = "Descripción"
    $colDesc.Width = 400
    $dgvTransacciones.Columns.Add($colDesc)

    $colFecha = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colFecha.Name = "Fecha"
    $colFecha.HeaderText = "Fecha"
    $colFecha.Width = 190
    $dgvTransacciones.Columns.Add($colFecha)

    # Agregar transacciones iniciales
    $dgvTransacciones.Rows.Add(1, "Ingreso", "$150,000", "Saldo inicial", "01/01/2026 08:00")
    $dgvTransacciones.Rows.Add(2, "Ingreso", "$50,000", "Venta de productos", "02/01/2026 10:30")
    $dgvTransacciones.Rows.Add(3, "Retiro", "$20,000", "Compra de inventario", "02/01/2026 15:45")

    # Función para actualizar saldo
    function Actualizar-Saldo {
        $lblSaldoValor.Text = "`${0:N0}" -f $script:saldoActual
    }

    # Evento agregar transacción
    $btnAgregarTrans.Add_Click({
        if ([string]::IsNullOrWhiteSpace($txtMonto.Text)) {
            [System.Windows.Forms.MessageBox]::Show("Por favor ingrese el monto", "Campo requerido", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Warning)
            return
        }

        $monto = [int]$txtMonto.Text
        $tipo = $cmbTipo.SelectedItem
        $desc = if ([string]::IsNullOrWhiteSpace($txtDescripcion.Text)) { "Sin descripción" } else { $txtDescripcion.Text }
        $fecha = Get-Date -Format "dd/MM/yyyy HH:mm"

        if ($tipo -eq "Ingreso") {
            $script:saldoActual += $monto
        } else {
            if ($monto -gt $script:saldoActual) {
                [System.Windows.Forms.MessageBox]::Show("Saldo insuficiente para realizar el retiro", "Error", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Error)
                return
            }
            $script:saldoActual -= $monto
        }

        $dgvTransacciones.Rows.Add($script:transaccionId, $tipo, "`${0:N0}" -f $monto, $desc, $fecha)
        $script:transaccionId++
        
        Actualizar-Saldo
        
        [System.Windows.Forms.MessageBox]::Show("Transacción agregada exitosamente", "Éxito", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Information)
        
        $txtMonto.Clear()
        $txtDescripcion.Clear()
        $cmbTipo.SelectedIndex = 0
    })

    # Evento eliminar transacción
    $btnEliminarTrans.Add_Click({
        if ($dgvTransacciones.SelectedRows.Count -eq 0) {
            [System.Windows.Forms.MessageBox]::Show("Por favor seleccione una transacción para eliminar", "Selección requerida", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Warning)
            return
        }

        $resultado = [System.Windows.Forms.MessageBox]::Show("¿Está seguro de eliminar esta transacción?`n`nEsto revertirá el monto al saldo.", "Confirmar eliminación", [System.Windows.Forms.MessageBoxButtons]::YesNo, [System.Windows.Forms.MessageBoxIcon]::Question)

        if ($resultado -eq "Yes") {
            $fila = $dgvTransacciones.SelectedRows[0]
            $tipo = $fila.Cells["Tipo"].Value
            $montoStr = $fila.Cells["Monto"].Value -replace '[\$,]', ''
            $monto = [int]$montoStr

            if ($tipo -eq "Ingreso") {
                $script:saldoActual -= $monto
            } else {
                $script:saldoActual += $monto
            }

            $dgvTransacciones.Rows.Remove($fila)
            Actualizar-Saldo

            [System.Windows.Forms.MessageBox]::Show("Transacción eliminada exitosamente", "Éxito", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Information)
        }
    })

    # Evento limpiar
    $btnLimpiarTrans.Add_Click({
        $txtMonto.Clear()
        $txtDescripcion.Clear()
        $cmbTipo.SelectedIndex = 0
    })

    # Evento cerrar
    $btnCerrarCred.Add_Click({
        $formCreditos.Close()
    })

    # Evento de selección en el grid
    $dgvTransacciones.Add_SelectionChanged({
        if ($dgvTransacciones.SelectedRows.Count -gt 0) {
            $fila = $dgvTransacciones.SelectedRows[0]
            $cmbTipo.SelectedItem = $fila.Cells["Tipo"].Value
            $montoStr = $fila.Cells["Monto"].Value -replace '[\$,]', ''
            $txtMonto.Text = $montoStr
            $txtDescripcion.Text = $fila.Cells["Descripcion"].Value
        }
    })

    $formCreditos.ShowDialog() | Out-Null
}

# Función para mostrar la ventana de inventario
function Show-InventarioForm {
    param($usuarioActual)

    $formInventario = New-Object System.Windows.Forms.Form
    $formInventario.Text = "Gestión de Inventario - Iglesia Poblado"
    $formInventario.ClientSize = New-Object System.Drawing.Size(1000, 600)
    $formInventario.StartPosition = "CenterScreen"
    $formInventario.BackColor = [System.Drawing.Color]::FromArgb(245, 245, 245)
    $formInventario.FormBorderStyle = "Sizable"
    $formInventario.MinimumSize = New-Object System.Drawing.Size(800, 500)

    # Panel superior
    $panelTopInv = New-Object System.Windows.Forms.Panel
    $panelTopInv.BackColor = [System.Drawing.Color]::FromArgb(40, 167, 69)
    $panelTopInv.Dock = "Top"
    $panelTopInv.Height = 60
    $formInventario.Controls.Add($panelTopInv)

    # Título
    $lblTituloInv = New-Object System.Windows.Forms.Label
    $lblTituloInv.Text = "📦 GESTIÓN DE INVENTARIO"
    $lblTituloInv.Font = New-Object System.Drawing.Font("Segoe UI Emoji", 16, [System.Drawing.FontStyle]::Bold)
    $lblTituloInv.ForeColor = [System.Drawing.Color]::White
    $lblTituloInv.AutoSize = $false
    $lblTituloInv.Size = New-Object System.Drawing.Size(600, 60)
    $lblTituloInv.Location = New-Object System.Drawing.Point(20, 0)
    $lblTituloInv.TextAlign = "MiddleLeft"
    $panelTopInv.Controls.Add($lblTituloInv)

    # Botón cerrar
    $btnCerrarInv = New-Object System.Windows.Forms.Button
    $btnCerrarInv.Text = "✖ Cerrar"
    $btnCerrarInv.Size = New-Object System.Drawing.Size(100, 35)
    $btnCerrarInv.Location = New-Object System.Drawing.Point(880, 12)
    $btnCerrarInv.Font = New-Object System.Drawing.Font("Arial", 9, [System.Drawing.FontStyle]::Bold)
    $btnCerrarInv.BackColor = [System.Drawing.Color]::FromArgb(220, 53, 69)
    $btnCerrarInv.ForeColor = [System.Drawing.Color]::White
    $btnCerrarInv.FlatStyle = "Flat"
    $btnCerrarInv.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelTopInv.Controls.Add($btnCerrarInv)

    # Panel de formulario para agregar productos
    $panelForm = New-Object System.Windows.Forms.GroupBox
    $panelForm.Text = "Agregar / Editar Producto"
    $panelForm.Location = New-Object System.Drawing.Point(20, 80)
    $panelForm.Size = New-Object System.Drawing.Size(960, 150)
    $panelForm.Font = New-Object System.Drawing.Font("Arial", 10, [System.Drawing.FontStyle]::Bold)
    $formInventario.Controls.Add($panelForm)

    # Nombre del producto
    $lblNombre = New-Object System.Windows.Forms.Label
    $lblNombre.Text = "Nombre:"
    $lblNombre.Location = New-Object System.Drawing.Point(20, 30)
    $lblNombre.Size = New-Object System.Drawing.Size(80, 20)
    $panelForm.Controls.Add($lblNombre)

    $txtNombre = New-Object System.Windows.Forms.TextBox
    $txtNombre.Location = New-Object System.Drawing.Point(20, 55)
    $txtNombre.Size = New-Object System.Drawing.Size(250, 25)
    $txtNombre.Font = New-Object System.Drawing.Font("Arial", 10)
    $panelForm.Controls.Add($txtNombre)

    # Precio
    $lblPrecio = New-Object System.Windows.Forms.Label
    $lblPrecio.Text = "Precio:"
    $lblPrecio.Location = New-Object System.Drawing.Point(290, 30)
    $lblPrecio.Size = New-Object System.Drawing.Size(80, 20)
    $panelForm.Controls.Add($lblPrecio)

    $txtPrecio = New-Object System.Windows.Forms.TextBox
    $txtPrecio.Location = New-Object System.Drawing.Point(290, 55)
    $txtPrecio.Size = New-Object System.Drawing.Size(150, 25)
    $txtPrecio.Font = New-Object System.Drawing.Font("Arial", 10)
    $panelForm.Controls.Add($txtPrecio)

    # Categoría
    $lblCategoria = New-Object System.Windows.Forms.Label
    $lblCategoria.Text = "Categoría:"
    $lblCategoria.Location = New-Object System.Drawing.Point(460, 30)
    $lblCategoria.Size = New-Object System.Drawing.Size(80, 20)
    $panelForm.Controls.Add($lblCategoria)

    $cmbCategoria = New-Object System.Windows.Forms.ComboBox
    $cmbCategoria.Location = New-Object System.Drawing.Point(460, 55)
    $cmbCategoria.Size = New-Object System.Drawing.Size(180, 25)
    $cmbCategoria.Font = New-Object System.Drawing.Font("Arial", 10)
    $cmbCategoria.DropDownStyle = "DropDownList"
    $cmbCategoria.Items.AddRange(@("Libros", "Accesorios", "Decoración", "Velas", "Imágenes", "Souvenirs"))
    $panelForm.Controls.Add($cmbCategoria)

    # Stock
    $lblStock = New-Object System.Windows.Forms.Label
    $lblStock.Text = "Stock:"
    $lblStock.Location = New-Object System.Drawing.Point(660, 30)
    $lblStock.Size = New-Object System.Drawing.Size(80, 20)
    $panelForm.Controls.Add($lblStock)

    $txtStock = New-Object System.Windows.Forms.TextBox
    $txtStock.Location = New-Object System.Drawing.Point(660, 55)
    $txtStock.Size = New-Object System.Drawing.Size(100, 25)
    $txtStock.Font = New-Object System.Drawing.Font("Arial", 10)
    $txtStock.Text = "0"
    $panelForm.Controls.Add($txtStock)

    # Botones de acción
    $btnAgregar = New-Object System.Windows.Forms.Button
    $btnAgregar.Text = "➕ Agregar"
    $btnAgregar.Location = New-Object System.Drawing.Point(20, 100)
    $btnAgregar.Size = New-Object System.Drawing.Size(120, 35)
    $btnAgregar.BackColor = [System.Drawing.Color]::FromArgb(40, 167, 69)
    $btnAgregar.ForeColor = [System.Drawing.Color]::White
    $btnAgregar.FlatStyle = "Flat"
    $btnAgregar.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelForm.Controls.Add($btnAgregar)

    $btnModificar = New-Object System.Windows.Forms.Button
    $btnModificar.Text = "✏️ Modificar"
    $btnModificar.Location = New-Object System.Drawing.Point(150, 100)
    $btnModificar.Size = New-Object System.Drawing.Size(120, 35)
    $btnModificar.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
    $btnModificar.ForeColor = [System.Drawing.Color]::White
    $btnModificar.FlatStyle = "Flat"
    $btnModificar.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelForm.Controls.Add($btnModificar)

    $btnEliminar = New-Object System.Windows.Forms.Button
    $btnEliminar.Text = "🗑️ Eliminar"
    $btnEliminar.Location = New-Object System.Drawing.Point(280, 100)
    $btnEliminar.Size = New-Object System.Drawing.Size(120, 35)
    $btnEliminar.BackColor = [System.Drawing.Color]::FromArgb(220, 53, 69)
    $btnEliminar.ForeColor = [System.Drawing.Color]::White
    $btnEliminar.FlatStyle = "Flat"
    $btnEliminar.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelForm.Controls.Add($btnEliminar)

    $btnLimpiar = New-Object System.Windows.Forms.Button
    $btnLimpiar.Text = "🔄 Limpiar"
    $btnLimpiar.Location = New-Object System.Drawing.Point(410, 100)
    $btnLimpiar.Size = New-Object System.Drawing.Size(120, 35)
    $btnLimpiar.BackColor = [System.Drawing.Color]::FromArgb(108, 117, 125)
    $btnLimpiar.ForeColor = [System.Drawing.Color]::White
    $btnLimpiar.FlatStyle = "Flat"
    $btnLimpiar.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelForm.Controls.Add($btnLimpiar)

    # DataGridView para mostrar inventario
    $dgvInventario = New-Object System.Windows.Forms.DataGridView
    $dgvInventario.Location = New-Object System.Drawing.Point(20, 250)
    $dgvInventario.Size = New-Object System.Drawing.Size(960, 300)
    $dgvInventario.BackgroundColor = [System.Drawing.Color]::White
    $dgvInventario.AllowUserToAddRows = $false
    $dgvInventario.AllowUserToDeleteRows = $false
    $dgvInventario.ReadOnly = $true
    $dgvInventario.SelectionMode = "FullRowSelect"
    $dgvInventario.MultiSelect = $false
    $dgvInventario.AutoSizeColumnsMode = "Fill"
    $formInventario.Controls.Add($dgvInventario)

    # Crear columnas
    $colId = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colId.Name = "ID"
    $colId.HeaderText = "ID"
    $colId.Width = 50
    $dgvInventario.Columns.Add($colId)

    $colNombre = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colNombre.Name = "Nombre"
    $colNombre.HeaderText = "Nombre del Producto"
    $dgvInventario.Columns.Add($colNombre)

    $colPrecio = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colPrecio.Name = "Precio"
    $colPrecio.HeaderText = "Precio"
    $colPrecio.DefaultCellStyle.Format = "C0"
    $dgvInventario.Columns.Add($colPrecio)

    $colCategoria = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colCategoria.Name = "Categoria"
    $colCategoria.HeaderText = "Categoría"
    $dgvInventario.Columns.Add($colCategoria)

    $colStock = New-Object System.Windows.Forms.DataGridViewTextBoxColumn
    $colStock.Name = "Stock"
    $colStock.HeaderText = "Stock"
    $dgvInventario.Columns.Add($colStock)

    # Cargar productos existentes
    $id = 1
    foreach ($prod in $script:productos) {
        $dgvInventario.Rows.Add($id, $prod.Nombre, $prod.Precio, $prod.Categoria, (Get-Random -Minimum 0 -Maximum 100))
        $id++
    }

    # Eventos de botones
    $btnAgregar.Add_Click({
        if ([string]::IsNullOrWhiteSpace($txtNombre.Text)) {
            [System.Windows.Forms.MessageBox]::Show("Por favor ingrese el nombre del producto", "Campo requerido", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Warning)
            return
        }
        
        $nuevoId = $dgvInventario.Rows.Count + 1
        $precio = if ([string]::IsNullOrWhiteSpace($txtPrecio.Text)) { 0 } else { [int]$txtPrecio.Text }
        $categoria = if ($cmbCategoria.SelectedItem) { $cmbCategoria.SelectedItem } else { "Sin categoría" }
        $stock = if ([string]::IsNullOrWhiteSpace($txtStock.Text)) { 0 } else { [int]$txtStock.Text }
        
        $dgvInventario.Rows.Add($nuevoId, $txtNombre.Text, $precio, $categoria, $stock)
        
        # Agregar al catálogo global
        $script:productos += @{Nombre=$txtNombre.Text; Precio=$precio; Categoria=$categoria}
        
        [System.Windows.Forms.MessageBox]::Show("Producto agregado exitosamente", "Éxito", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Information)
        
        # Limpiar campos
        $txtNombre.Clear()
        $txtPrecio.Clear()
        $txtStock.Text = "0"
        $cmbCategoria.SelectedIndex = -1
    })

    $btnModificar.Add_Click({
        if ($dgvInventario.SelectedRows.Count -eq 0) {
            [System.Windows.Forms.MessageBox]::Show("Por favor seleccione un producto para modificar", "Selección requerida", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Warning)
            return
        }
        
        $fila = $dgvInventario.SelectedRows[0]
        $fila.Cells["Nombre"].Value = $txtNombre.Text
        $fila.Cells["Precio"].Value = [int]$txtPrecio.Text
        $fila.Cells["Categoria"].Value = $cmbCategoria.SelectedItem
        $fila.Cells["Stock"].Value = [int]$txtStock.Text
        
        [System.Windows.Forms.MessageBox]::Show("Producto modificado exitosamente", "Éxito", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Information)
    })

    $btnEliminar.Add_Click({
        if ($dgvInventario.SelectedRows.Count -eq 0) {
            [System.Windows.Forms.MessageBox]::Show("Por favor seleccione un producto para eliminar", "Selección requerida", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Warning)
            return
        }
        
        $resultado = [System.Windows.Forms.MessageBox]::Show("¿Está seguro de eliminar este producto?", "Confirmar eliminación", [System.Windows.Forms.MessageBoxButtons]::YesNo, [System.Windows.Forms.MessageBoxIcon]::Question)
        
        if ($resultado -eq "Yes") {
            $dgvInventario.Rows.Remove($dgvInventario.SelectedRows[0])
            [System.Windows.Forms.MessageBox]::Show("Producto eliminado exitosamente", "Éxito", [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Information)
        }
    })

    $btnLimpiar.Add_Click({
        $txtNombre.Clear()
        $txtPrecio.Clear()
        $txtStock.Text = "0"
        $cmbCategoria.SelectedIndex = -1
    })

    $btnCerrarInv.Add_Click({
        $formInventario.Close()
    })

    # Evento de selección en el grid
    $dgvInventario.Add_SelectionChanged({
        if ($dgvInventario.SelectedRows.Count -gt 0) {
            $fila = $dgvInventario.SelectedRows[0]
            $txtNombre.Text = $fila.Cells["Nombre"].Value
            $txtPrecio.Text = $fila.Cells["Precio"].Value
            $cmbCategoria.SelectedItem = $fila.Cells["Categoria"].Value
            $txtStock.Text = $fila.Cells["Stock"].Value
        }
    })

    $formInventario.ShowDialog() | Out-Null
}

# Función para mostrar la aplicación principal
function Show-MainApp {
    param($usuarioActual)

    # Variables globales de la aplicación
    $script:contadorVisitas = Get-Random -Minimum 750 -Maximum 1500
    $script:productosVendidos = Get-Random -Minimum 500 -Maximum 2000
    
    # Catálogo de productos
    $script:productos = @(
        @{Nombre="Biblia Reina Valera"; Precio=45000; Categoria="Libros"},
        @{Nombre="Rosario de Plata"; Precio=35000; Categoria="Accesorios"},
        @{Nombre="Cruz de Madera"; Precio=25000; Categoria="Decoración"},
        @{Nombre="Velas Aromáticas (Pack 6)"; Precio=18000; Categoria="Velas"},
        @{Nombre="Imagen Virgen María 30cm"; Precio=55000; Categoria="Imágenes"},
        @{Nombre="Libro Oraciones Diarias"; Precio=28000; Categoria="Libros"},
        @{Nombre="Medalla San Benito"; Precio=15000; Categoria="Accesorios"},
        @{Nombre="Cuadro Sagrado Corazón"; Precio=42000; Categoria="Decoración"},
        @{Nombre="Velas Blancas (Pack 12)"; Precio=22000; Categoria="Velas"},
        @{Nombre="Estampas Religiosas (Set)"; Precio=8000; Categoria="Souvenirs"}
    )

    $form = New-Object System.Windows.Forms.Form
    $form.Text = "Iglesia Poblado - Aplicación Principal"
    $form.ClientSize = New-Object System.Drawing.Size(1100, 650)
    $form.MinimumSize = New-Object System.Drawing.Size(900, 600)
    $form.StartPosition = "CenterScreen"
    $form.BackColor = [System.Drawing.Color]::FromArgb(245, 245, 245)
    $form.FormBorderStyle = "Sizable"
    $form.MaximizeBox = $true

    # Panel superior con info de usuario
    $panelTop = New-Object System.Windows.Forms.Panel
    $panelTop.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
    $panelTop.Dock = "Top"
    $panelTop.Height = 70
    $form.Controls.Add($panelTop)

    # Etiqueta de bienvenida con nombre de usuario
    $lblWelcome = New-Object System.Windows.Forms.Label
    $lblWelcome.Text = "👤 Bienvenido, $usuarioActual!"
    $lblWelcome.Font = New-Object System.Drawing.Font("Segoe UI Emoji", 14, [System.Drawing.FontStyle]::Bold)
    $lblWelcome.ForeColor = [System.Drawing.Color]::White
    $lblWelcome.AutoSize = $false
    $lblWelcome.Size = New-Object System.Drawing.Size(400, 30)
    $lblWelcome.Location = New-Object System.Drawing.Point(20, 10)
    $panelTop.Controls.Add($lblWelcome)

    # Reloj en tiempo real
    $lblReloj = New-Object System.Windows.Forms.Label
    $lblReloj.Text = "🕐 " + (Get-Date -Format "HH:mm:ss")
    $lblReloj.Font = New-Object System.Drawing.Font("Segoe UI Emoji", 11)
    $lblReloj.ForeColor = [System.Drawing.Color]::White
    $lblReloj.AutoSize = $false
    $lblReloj.Size = New-Object System.Drawing.Size(150, 25)
    $lblReloj.Location = New-Object System.Drawing.Point(20, 40)
    $panelTop.Controls.Add($lblReloj)

    # Timer para actualizar el reloj
    $timer = New-Object System.Windows.Forms.Timer
    $timer.Interval = 1000
    $timer.Add_Tick({
        $lblReloj.Text = "🕐 " + (Get-Date -Format "HH:mm:ss")
    })
    $timer.Start()

    # Botón de cerrar sesión
    $btnCerrarSesion = New-Object System.Windows.Forms.Button
    $btnCerrarSesion.Text = "🚪 Cerrar Sesión"
    $btnCerrarSesion.Size = New-Object System.Drawing.Size(140, 40)
    $btnCerrarSesion.Location = New-Object System.Drawing.Point(940, 15)
    $btnCerrarSesion.Font = New-Object System.Drawing.Font("Arial", 9, [System.Drawing.FontStyle]::Bold)
    $btnCerrarSesion.BackColor = [System.Drawing.Color]::FromArgb(220, 53, 69)
    $btnCerrarSesion.ForeColor = [System.Drawing.Color]::White
    $btnCerrarSesion.FlatStyle = "Flat"
    $btnCerrarSesion.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelTop.Controls.Add($btnCerrarSesion)

    # Panel lateral izquierdo con estadísticas
    $panelLateral = New-Object System.Windows.Forms.Panel
    $panelLateral.BackColor = [System.Drawing.Color]::FromArgb(52, 58, 64)
    $panelLateral.Dock = "Left"
    $panelLateral.Width = 250
    $form.Controls.Add($panelLateral)

    # Botón flotante para mostrar panel (aparece cuando está oculto)
    $btnMostrarPanel = New-Object System.Windows.Forms.Button
    $btnMostrarPanel.Text = "▶"
    $btnMostrarPanel.Size = New-Object System.Drawing.Size(30, 60)
    $btnMostrarPanel.Location = New-Object System.Drawing.Point(0, 150)
    $btnMostrarPanel.Font = New-Object System.Drawing.Font("Arial", 14, [System.Drawing.FontStyle]::Bold)
    $btnMostrarPanel.BackColor = [System.Drawing.Color]::FromArgb(108, 117, 125)
    $btnMostrarPanel.ForeColor = [System.Drawing.Color]::White
    $btnMostrarPanel.FlatStyle = "Flat"
    $btnMostrarPanel.Cursor = [System.Windows.Forms.Cursors]::Hand
    $btnMostrarPanel.Visible = $false
    $form.Controls.Add($btnMostrarPanel)

    # Botón para ocultar panel (dentro del panel lateral)
    $btnTogglePanel = New-Object System.Windows.Forms.Button
    $btnTogglePanel.Text = "◀"
    $btnTogglePanel.Size = New-Object System.Drawing.Size(40, 40)
    $btnTogglePanel.Location = New-Object System.Drawing.Point(200, 10)
    $btnTogglePanel.Font = New-Object System.Drawing.Font("Arial", 14, [System.Drawing.FontStyle]::Bold)
    $btnTogglePanel.BackColor = [System.Drawing.Color]::FromArgb(108, 117, 125)
    $btnTogglePanel.ForeColor = [System.Drawing.Color]::White
    $btnTogglePanel.FlatStyle = "Flat"
    $btnTogglePanel.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelLateral.Controls.Add($btnTogglePanel)

    # Evento para mostrar/ocultar panel lateral
    $btnTogglePanel.Add_Click({
        if ($panelLateral.Width -eq 250) {
            $panelLateral.Width = 0
            $btnMostrarPanel.Visible = $true
            $btnMostrarPanel.BringToFront()
        } else {
            $panelLateral.Width = 250
            $btnMostrarPanel.Visible = $false
        }
    })

    # Evento del botón flotante
    $btnMostrarPanel.Add_Click({
        $panelLateral.Width = 250
        $btnMostrarPanel.Visible = $false
    })

    # GroupBox para Créditos (similar al del inventario)
    $groupBoxCreditos = New-Object System.Windows.Forms.GroupBox
    $groupBoxCreditos.Text = "💳 Gestión de Créditos"
    $groupBoxCreditos.Location = New-Object System.Drawing.Point(10, 70)
    $groupBoxCreditos.Size = New-Object System.Drawing.Size(230, 120)
    $groupBoxCreditos.Font = New-Object System.Drawing.Font("Arial", 10, [System.Drawing.FontStyle]::Bold)
    $groupBoxCreditos.ForeColor = [System.Drawing.Color]::Gold
    $panelLateral.Controls.Add($groupBoxCreditos)

    # CAMPO DE CRÉDITOS - Etiqueta
    $lblCreditosTitulo = New-Object System.Windows.Forms.Label
    $lblCreditosTitulo.Text = "Créditos Disponibles:"
    $lblCreditosTitulo.Font = New-Object System.Drawing.Font("Arial", 9)
    $lblCreditosTitulo.ForeColor = [System.Drawing.Color]::White
    $lblCreditosTitulo.AutoSize = $false
    $lblCreditosTitulo.Size = New-Object System.Drawing.Size(210, 20)
    $lblCreditosTitulo.Location = New-Object System.Drawing.Point(10, 30)
    $lblCreditosTitulo.TextAlign = "TopLeft"
    $groupBoxCreditos.Controls.Add($lblCreditosTitulo)

    # CAMPO DE CRÉDITOS - Cuadro de texto
    $txtCreditos = New-Object System.Windows.Forms.TextBox
    $txtCreditos.Location = New-Object System.Drawing.Point(10, 55)
    $txtCreditos.Size = New-Object System.Drawing.Size(210, 30)
    $txtCreditos.Font = New-Object System.Drawing.Font("Arial", 14, [System.Drawing.FontStyle]::Bold)
    $txtCreditos.Text = "150000"
    $txtCreditos.TextAlign = "Center"
    $txtCreditos.BackColor = [System.Drawing.Color]::White
    $txtCreditos.ForeColor = [System.Drawing.Color]::DarkGreen
    $groupBoxCreditos.Controls.Add($txtCreditos)

    # Botón Ir a Inventario
    $btnIrInventario = New-Object System.Windows.Forms.Button
    $btnIrInventario.Text = "📦 Ir a Inventario"
    $btnIrInventario.Location = New-Object System.Drawing.Point(30, 210)
    $btnIrInventario.Size = New-Object System.Drawing.Size(190, 40)
    $btnIrInventario.Font = New-Object System.Drawing.Font("Arial", 9, [System.Drawing.FontStyle]::Bold)
    $btnIrInventario.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
    $btnIrInventario.ForeColor = [System.Drawing.Color]::White
    $btnIrInventario.FlatStyle = "Flat"
    $btnIrInventario.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelLateral.Controls.Add($btnIrInventario)

    # Botón de actualizar créditos
    $btnActualizar = New-Object System.Windows.Forms.Button
    $btnActualizar.Text = "🔄 Actualizar Créditos"
    $btnActualizar.Location = New-Object System.Drawing.Point(30, 270)
    $btnActualizar.Size = New-Object System.Drawing.Size(190, 40)
    $btnActualizar.Font = New-Object System.Drawing.Font("Arial", 9)
    $btnActualizar.BackColor = [System.Drawing.Color]::FromArgb(40, 167, 69)
    $btnActualizar.ForeColor = [System.Drawing.Color]::White
    $btnActualizar.FlatStyle = "Flat"
    $btnActualizar.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelLateral.Controls.Add($btnActualizar)

    # Evento actualizar créditos - Abrir ventana de créditos
    $btnActualizar.Add_Click({
        Show-CreditosForm
    })

    # Panel central principal
    $panelCentral = New-Object System.Windows.Forms.Panel
    $panelCentral.Dock = "Fill"
    $panelCentral.BackColor = [System.Drawing.Color]::White
    $form.Controls.Add($panelCentral)

    # Título principal
    $lblTitulo = New-Object System.Windows.Forms.Label
    $lblTitulo.Text = "🏛️ Tienda Iglesia Poblado"
    $lblTitulo.Font = New-Object System.Drawing.Font("Segoe UI Emoji", 20, [System.Drawing.FontStyle]::Bold)
    $lblTitulo.AutoSize = $false
    $lblTitulo.Size = New-Object System.Drawing.Size(800, 40)
    $lblTitulo.Location = New-Object System.Drawing.Point(20, 15)
    $lblTitulo.TextAlign = "MiddleCenter"
    $panelCentral.Controls.Add($lblTitulo)

    # Barra de búsqueda
    $lblBuscar = New-Object System.Windows.Forms.Label
    $lblBuscar.Text = "🔍 Buscar Producto:"
    $lblBuscar.Location = New-Object System.Drawing.Point(30, 70)
    $lblBuscar.Size = New-Object System.Drawing.Size(150, 25)
    $lblBuscar.Font = New-Object System.Drawing.Font("Arial", 10, [System.Drawing.FontStyle]::Bold)
    $panelCentral.Controls.Add($lblBuscar)

    $txtBuscar = New-Object System.Windows.Forms.TextBox
    $txtBuscar.Location = New-Object System.Drawing.Point(180, 68)
    $txtBuscar.Size = New-Object System.Drawing.Size(450, 25)
    $txtBuscar.Font = New-Object System.Drawing.Font("Arial", 11)
    $panelCentral.Controls.Add($txtBuscar)

    $btnBuscar = New-Object System.Windows.Forms.Button
    $btnBuscar.Text = "Buscar"
    $btnBuscar.Location = New-Object System.Drawing.Point(640, 66)
    $btnBuscar.Size = New-Object System.Drawing.Size(100, 30)
    $btnBuscar.Font = New-Object System.Drawing.Font("Arial", 10)
    $btnBuscar.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
    $btnBuscar.ForeColor = [System.Drawing.Color]::White
    $btnBuscar.FlatStyle = "Flat"
    $btnBuscar.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelCentral.Controls.Add($btnBuscar)

    # Panel con scroll para mostrar productos en tarjetas
    $panelProductos = New-Object System.Windows.Forms.FlowLayoutPanel
    $panelProductos.Location = New-Object System.Drawing.Point(30, 110)
    $panelProductos.Size = New-Object System.Drawing.Size(750, 200)
    $panelProductos.AutoScroll = $true
    $panelProductos.FlowDirection = "LeftToRight"
    $panelProductos.WrapContents = $true
    $panelProductos.BackColor = [System.Drawing.Color]::FromArgb(248, 249, 250)
    $panelProductos.BorderStyle = "FixedSingle"
    $panelCentral.Controls.Add($panelProductos)

    # Función para crear tarjeta de producto
    function Create-ProductCard {
        param($producto, $index)
        
        $card = New-Object System.Windows.Forms.Panel
        $card.Size = New-Object System.Drawing.Size(220, 180)
        $card.BackColor = [System.Drawing.Color]::White
        $card.BorderStyle = "FixedSingle"
        $card.Margin = New-Object System.Windows.Forms.Padding(5)
        $card.Cursor = [System.Windows.Forms.Cursors]::Hand
        
        # Icono según categoría
        $icono = switch ($producto.Categoria) {
            "Libros" { "📖" }
            "Velas" { "🕯️" }
            "Accesorios" { "📿" }
            "Decoración" { "🖼️" }
            "Imágenes" { "✝️" }
            "Souvenirs" { "🎁" }
            default { "📦" }
        }
        
        # Icono del producto
        $lblIcono = New-Object System.Windows.Forms.Label
        $lblIcono.Text = $icono
        $lblIcono.Font = New-Object System.Drawing.Font("Segoe UI Emoji", 32)
        $lblIcono.AutoSize = $false
        $lblIcono.Size = New-Object System.Drawing.Size(220, 60)
        $lblIcono.TextAlign = "MiddleCenter"
        $lblIcono.Location = New-Object System.Drawing.Point(0, 5)
        $card.Controls.Add($lblIcono)
        
        # Nombre del producto
        $lblNombreProd = New-Object System.Windows.Forms.Label
        $lblNombreProd.Text = $producto.Nombre
        $lblNombreProd.Font = New-Object System.Drawing.Font("Arial", 9, [System.Drawing.FontStyle]::Bold)
        $lblNombreProd.AutoSize = $false
        $lblNombreProd.Size = New-Object System.Drawing.Size(200, 40)
        $lblNombreProd.TextAlign = "TopCenter"
        $lblNombreProd.Location = New-Object System.Drawing.Point(10, 70)
        $card.Controls.Add($lblNombreProd)
        
        # Precio
        $lblPrecioProd = New-Object System.Windows.Forms.Label
        $lblPrecioProd.Text = "`$$($producto.Precio.ToString('N0'))"
        $lblPrecioProd.Font = New-Object System.Drawing.Font("Arial", 12, [System.Drawing.FontStyle]::Bold)
        $lblPrecioProd.ForeColor = [System.Drawing.Color]::FromArgb(40, 167, 69)
        $lblPrecioProd.AutoSize = $false
        $lblPrecioProd.Size = New-Object System.Drawing.Size(200, 25)
        $lblPrecioProd.TextAlign = "MiddleCenter"
        $lblPrecioProd.Location = New-Object System.Drawing.Point(10, 115)
        $card.Controls.Add($lblPrecioProd)
        
        # Categoría
        $lblCategoriaProd = New-Object System.Windows.Forms.Label
        $lblCategoriaProd.Text = "[$($producto.Categoria)]"
        $lblCategoriaProd.Font = New-Object System.Drawing.Font("Arial", 8, [System.Drawing.FontStyle]::Italic)
        $lblCategoriaProd.ForeColor = [System.Drawing.Color]::Gray
        $lblCategoriaProd.AutoSize = $false
        $lblCategoriaProd.Size = New-Object System.Drawing.Size(200, 20)
        $lblCategoriaProd.TextAlign = "MiddleCenter"
        $lblCategoriaProd.Location = New-Object System.Drawing.Point(10, 145)
        $card.Controls.Add($lblCategoriaProd)
        
        # Efecto hover
        $card.Add_MouseEnter({
            $this.BackColor = [System.Drawing.Color]::FromArgb(230, 240, 255)
        })
        $card.Add_MouseLeave({
            $this.BackColor = [System.Drawing.Color]::White
        })
        
        # Click en la tarjeta
        $card.Add_Click({
            [System.Windows.Forms.MessageBox]::Show(
                "Producto: $($producto.Nombre)`nPrecio: `$$($producto.Precio.ToString('N0'))`nCategoría: $($producto.Categoria)",
                "Detalles del Producto",
                [System.Windows.Forms.MessageBoxButtons]::OK,
                [System.Windows.Forms.MessageBoxIcon]::Information
            )
        })
        
        return $card
    }

    # Cargar productos en tarjetas
    $index = 0
    foreach ($prod in $script:productos) {
        $tarjeta = Create-ProductCard -producto $prod -index $index
        $panelProductos.Controls.Add($tarjeta)
        $index++
    }

    # Evento de búsqueda - actualizar tarjetas
    $btnBuscar.Add_Click({
        $termino = $txtBuscar.Text.ToLower()
        $panelProductos.Controls.Clear()
        
        if ([string]::IsNullOrWhiteSpace($termino)) {
            # Mostrar todos los productos
            $index = 0
            foreach ($prod in $script:productos) {
                $tarjeta = Create-ProductCard -producto $prod -index $index
                $panelProductos.Controls.Add($tarjeta)
                $index++
            }
        } else {
            # Filtrar productos
            $encontrados = $script:productos | Where-Object { 
                $_.Nombre.ToLower().Contains($termino) -or $_.Categoria.ToLower().Contains($termino) 
            }
            
            if ($encontrados) {
                $index = 0
                foreach ($prod in $encontrados) {
                    $tarjeta = Create-ProductCard -producto $prod -index $index
                    $panelProductos.Controls.Add($tarjeta)
                    $index++
                }
            } else {
                # Mostrar mensaje de no encontrados
                $lblNoEncontrado = New-Object System.Windows.Forms.Label
                $lblNoEncontrado.Text = "❌ No se encontraron productos"
                $lblNoEncontrado.Font = New-Object System.Drawing.Font("Arial", 12, [System.Drawing.FontStyle]::Bold)
                $lblNoEncontrado.ForeColor = [System.Drawing.Color]::Gray
                $lblNoEncontrado.AutoSize = $false
                $lblNoEncontrado.Size = New-Object System.Drawing.Size(700, 180)
                $lblNoEncontrado.TextAlign = "MiddleCenter"
                $panelProductos.Controls.Add($lblNoEncontrado)
            }
        }
    })

    # Panel de botones principales
    $panelBotones = New-Object System.Windows.Forms.FlowLayoutPanel
    $panelBotones.Location = New-Object System.Drawing.Point(30, 330)
    $panelBotones.Size = New-Object System.Drawing.Size(780, 240)
    $panelBotones.FlowDirection = "LeftToRight"
    $panelBotones.WrapContents = $true
    $panelCentral.Controls.Add($panelBotones)

    # Crear botones con efectos hover
    
    $btnInfo = $null
    $btnProductos = $null
    $btnContacto = $null

    foreach ($btnConfig in $botones) {
        $btn = New-Object System.Windows.Forms.Button
        $btn.Text = $btnConfig.Texto
        $btn.Size = New-Object System.Drawing.Size($btnConfig.Ancho, $btnConfig.Alto)
        $btn.Font = New-Object System.Drawing.Font("Segoe UI Emoji", 11, [System.Drawing.FontStyle]::Bold)
        $btn.BackColor = $btnConfig.Color
        $btn.ForeColor = if ($btnConfig.Texto -eq "📞 Contacto") { [System.Drawing.Color]::Black } else { [System.Drawing.Color]::White }
        $btn.FlatStyle = "Flat"
        $btn.Cursor = [System.Windows.Forms.Cursors]::Hand
        $btn.Margin = New-Object System.Windows.Forms.Padding(5)
        $btn.Tag = $btnConfig.Color
        
        # Efectos hover
        $btn.Add_MouseEnter({
            $this.BackColor = [System.Drawing.Color]::FromArgb(
                [Math]::Min(255, $this.Tag.R + 30),
                [Math]::Min(255, $this.Tag.G + 30),
                [Math]::Min(255, $this.Tag.B + 30)
            )
        })
        $btn.Add_MouseLeave({
            $this.BackColor = $this.Tag
        })
        
        $panelBotones.Controls.Add($btn)
        
        # Guardar referencias
        if ($btnConfig.Texto -eq "📋 Información") { $btnInfo = $btn }
        elseif ($btnConfig.Texto -eq "🛒 Productos") { $btnProductos = $btn }
        elseif ($btnConfig.Texto -eq "📞 Contacto") { $btnContacto = $btn }
    }

    # Eventos de botones
    $btnInfo.Add_Click({
        [System.Windows.Forms.MessageBox]::Show(
            "Iglesia Poblado - Tienda Religiosa`n`nUsuario actual: $usuarioActual`nFecha: $(Get-Date -Format 'dd/MM/yyyy HH:mm')`n`nOfrecemos artículos religiosos, libros, souvenirs y más.",
            "Información",
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Information
        )
    })

    $btnProductos.Add_Click({
        [System.Windows.Forms.MessageBox]::Show(
            "Productos disponibles:`n`n✝️ Biblias y libros religiosos`n🕯️ Velas y candelas`n📿 Rosarios y cruces`n🖼️ Cuadros e imágenes religiosas`n🎁 Souvenirs y regalos`n`n¡Visítanos para más detalles!",
            "Catálogo de Productos",
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Information
        )
    })

    $btnContacto.Add_Click({
        [System.Windows.Forms.MessageBox]::Show(
            "Contacto:`n`n📍 Dirección: Iglesia Poblado`n📞 Teléfono: (XXX) XXX-XXXX`n📧 Email: info@iglesiapoblado.com`n🌐 Web: www.iglesiapoblado.com`n`n¡Esperamos verte pronto!",
            "Información de Contacto",
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Information
        )
    })

    $btnCerrarSesion.Add_Click({
        $resultado = [System.Windows.Forms.MessageBox]::Show(
            "¿Está seguro de que desea cerrar sesión?",
            "Cerrar Sesión",
            [System.Windows.Forms.MessageBoxButtons]::YesNo,
            [System.Windows.Forms.MessageBoxIcon]::Question
        )
        if ($resultado -eq "Yes") {
            $form.Close()
        }
    })

    # Evento botón inventario
    $btnIrInventario.Add_Click({
        Show-InventarioForm -usuarioActual $usuarioActual
    })

    # FOOTER CON SOPORTE
    $panelFooter = New-Object System.Windows.Forms.Panel
    $panelFooter.BackColor = [System.Drawing.Color]::FromArgb(52, 58, 64)
    $panelFooter.Dock = "Bottom"
    $panelFooter.Height = 50
    $form.Controls.Add($panelFooter)
    $panelFooter.BringToFront()

    # Información de soporte
    $lblSoporte = New-Object System.Windows.Forms.Label
    $lblSoporte.Text = "📞 Soporte: juandsoftware@gmail.com | Tel: 350 567 4554"
    $lblSoporte.Font = New-Object System.Drawing.Font("Arial", 10)
    $lblSoporte.ForeColor = [System.Drawing.Color]::White
    $lblSoporte.AutoSize = $false
    $lblSoporte.Size = New-Object System.Drawing.Size(600, 50)
    $lblSoporte.Location = New-Object System.Drawing.Point(20, 0)
    $lblSoporte.TextAlign = "MiddleLeft"
    $panelFooter.Controls.Add($lblSoporte)

    # Botón de ayuda
    $btnAyuda = New-Object System.Windows.Forms.Button
    $btnAyuda.Text = "❓ Ayuda"
    $btnAyuda.Size = New-Object System.Drawing.Size(100, 35)
    $btnAyuda.Location = New-Object System.Drawing.Point(650, 8)
    $btnAyuda.Font = New-Object System.Drawing.Font("Arial", 9, [System.Drawing.FontStyle]::Bold)
    $btnAyuda.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
    $btnAyuda.ForeColor = [System.Drawing.Color]::White
    $btnAyuda.FlatStyle = "Flat"
    $btnAyuda.Cursor = [System.Windows.Forms.Cursors]::Hand
    $panelFooter.Controls.Add($btnAyuda)

    # Copyright
    $lblCopyright = New-Object System.Windows.Forms.Label
    $lblCopyright.Text = "© 2026 Iglesia Poblado"
    $lblCopyright.Font = New-Object System.Drawing.Font("Arial", 9)
    $lblCopyright.ForeColor = [System.Drawing.Color]::LightGray
    $lblCopyright.AutoSize = $false
    $lblCopyright.Size = New-Object System.Drawing.Size(200, 50)
    $lblCopyright.Location = New-Object System.Drawing.Point(880, 0)
    $lblCopyright.TextAlign = "MiddleRight"
    $panelFooter.Controls.Add($lblCopyright)

    # Evento del botón de ayuda
    $btnAyuda.Add_Click({
        [System.Windows.Forms.MessageBox]::Show(
            "Centro de Soporte - Iglesia Poblado`n`n📧 Email: juandsoftware@gmail.com`n📞 Teléfono: 350 567 4554`n¿Necesitas ayuda?`n• Gestión de inventario`n• Búsqueda de productos`n• • Configuración de cuenta`n`n¡Estamos aquí para ayudarte!",
            "Centro de Soporte",
            [System.Windows.Forms.MessageBoxButtons]::OK,
            [System.Windows.Forms.MessageBoxIcon]::Information
        )
    })

    # Mostrar el formulario
    $form.ShowDialog() | Out-Null
}

# Flujo principal de la aplicación
$usuarioLogueado = Show-LoginForm

if ($usuarioLogueado) {
    Show-MainApp -usuarioActual $usuarioLogueado
} else {
    [System.Windows.Forms.MessageBox]::Show(
        "Sesión cancelada. La aplicación se cerrará.",
        "Aviso",
        [System.Windows.Forms.MessageBoxButtons]::OK,
        [System.Windows.Forms.MessageBoxIcon]::Information
    )
}
