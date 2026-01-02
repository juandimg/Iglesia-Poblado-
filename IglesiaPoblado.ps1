Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing

# Crear el formulario principal
$form = New-Object System.Windows.Forms.Form
$form.Text = "Iglesia Poblado - Aplicación"
$form.ClientSize = New-Object System.Drawing.Size(600, 400)  # Tamaño más pequeño y apropiado
$form.MinimumSize = New-Object System.Drawing.Size(400, 300)  # Tamaño mínimo
$form.MaximumSize = New-Object System.Drawing.Size(2000, 2000)  # Tamaño máximo
$form.StartPosition = "CenterScreen"
$form.BackColor = [System.Drawing.Color]::White
$form.FormBorderStyle = "Sizable"  # Permite redimensionar
$form.MaximizeBox = $true  # Permite maximizar

# Crear etiqueta de bienvenida
$label = New-Object System.Windows.Forms.Label
$label.Text = "Bienvenido a la tienda Iglesia Poblado"
$label.Font = New-Object System.Drawing.Font("Arial", 14, [System.Drawing.FontStyle]::Bold)
$label.AutoSize = $false
$label.Size = New-Object System.Drawing.Size(500, 40)
$label.Location = New-Object System.Drawing.Point(50, 100)
$label.TextAlign = "MiddleCenter"
$label.Anchor = "Top"
$form.Controls.Add($label)

# Crear botón (centrado)
$button = New-Object System.Windows.Forms.Button
$button.Text = "¡Haz clic aquí!"
$button.Size = New-Object System.Drawing.Size(200, 50)
$button.Location = New-Object System.Drawing.Point(200, 200)
$button.Font = New-Object System.Drawing.Font("Arial", 12)
$button.BackColor = [System.Drawing.Color]::FromArgb(0, 120, 215)
$button.ForeColor = [System.Drawing.Color]::White
$button.FlatStyle = "Flat"
$button.Cursor = [System.Windows.Forms.Cursors]::Hand
$button.Anchor = "None"  # Mantiene el botón centrado

# Evento del botón
$button.Add_Click({
    [System.Windows.Forms.MessageBox]::Show(
        "¡Botón presionado! Bienvenido a la Iglesia Poblado.",
        "Mensaje",
        [System.Windows.Forms.MessageBoxButtons]::OK,
        [System.Windows.Forms.MessageBoxIcon]::Information
    )
})

$form.Controls.Add($button)

# Mostrar el formulario
$form.ShowDialog() | Out-Null
