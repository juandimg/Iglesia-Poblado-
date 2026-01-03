using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Drawing;

namespace IglesiaPoblado
{
    // Formulario de Login
    public class LoginForm : Form
    {
        private TextBox txtUsuario;
        private TextBox txtPassword;
        private Button btnLogin;
        private Button btnCancelar;
        private Label lblTitle;
        private Label lblUsuario;
        private Label lblPassword;
        private Panel panelTop;

        // Base de datos simple de usuarios
        private Dictionary<string, string> usuarios = new Dictionary<string, string>()
        {
            { "1", "1234567890" },
       
        };

        public string UsuarioLogueado { get; private set; }

        public LoginForm()
        {
            ConfigurarVentana();
            CrearControles();
        }

        private void ConfigurarVentana()
        {
            this.Text = "Inicio de Sesión - Iglesia Poblado";
            this.Size = new Size(420, 340);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.BackColor = Color.FromArgb(240, 240, 240);
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
        }

        private void CrearControles()
        {
            // Panel superior
            panelTop = new Panel();
            panelTop.BackColor = Color.FromArgb(0, 120, 215);
            panelTop.Size = new Size(420, 60);
            panelTop.Location = new Point(0, 0);
            this.Controls.Add(panelTop);

            // Título
            lblTitle = new Label();
            lblTitle.Text = "🔐 IGLESIA POBLADO";
            lblTitle.Font = new Font("Arial", 16, FontStyle.Bold);
            lblTitle.ForeColor = Color.White;
            lblTitle.Size = new Size(420, 60);
            lblTitle.TextAlign = ContentAlignment.MiddleCenter;
            panelTop.Controls.Add(lblTitle);

            // Etiqueta Usuario
            lblUsuario = new Label();
            lblUsuario.Text = "Usuario:";
            lblUsuario.Location = new Point(50, 90);
            lblUsuario.Size = new Size(80, 20);
            lblUsuario.Font = new Font("Arial", 10, FontStyle.Bold);
            this.Controls.Add(lblUsuario);

            // Campo Usuario
            txtUsuario = new TextBox();
            txtUsuario.Location = new Point(50, 115);
            txtUsuario.Size = new Size(300, 25);
            txtUsuario.Font = new Font("Arial", 11);
            this.Controls.Add(txtUsuario);

            // Etiqueta Contraseña
            lblPassword = new Label();
            lblPassword.Text = "Contraseña:";
            lblPassword.Location = new Point(50, 155);
            lblPassword.Size = new Size(100, 20);
            lblPassword.Font = new Font("Arial", 10, FontStyle.Bold);
            this.Controls.Add(lblPassword);

            // Campo Contraseña
            txtPassword = new TextBox();
            txtPassword.Location = new Point(50, 180);
            txtPassword.Size = new Size(300, 25);
            txtPassword.Font = new Font("Arial", 11);
            txtPassword.PasswordChar = '●';
            txtPassword.KeyDown += TxtPassword_KeyDown;
            this.Controls.Add(txtPassword);

            // Botón Iniciar Sesión
            btnLogin = new Button();
            btnLogin.Text = "Iniciar Sesión";
            btnLogin.Location = new Point(50, 230);
            btnLogin.Size = new Size(140, 35);
            btnLogin.Font = new Font("Arial", 10, FontStyle.Bold);
            btnLogin.BackColor = Color.FromArgb(0, 120, 215);
            btnLogin.ForeColor = Color.White;
            btnLogin.FlatStyle = FlatStyle.Flat;
            btnLogin.Cursor = Cursors.Hand;
            btnLogin.Click += BtnLogin_Click;
            this.Controls.Add(btnLogin);

            // Botón Cancelar
            btnCancelar = new Button();
            btnCancelar.Text = "Cancelar";
            btnCancelar.Location = new Point(210, 230);
            btnCancelar.Size = new Size(140, 35);
            btnCancelar.Font = new Font("Arial", 10);
            btnCancelar.BackColor = Color.FromArgb(220, 220, 220);
            btnCancelar.FlatStyle = FlatStyle.Flat;
            btnCancelar.Cursor = Cursors.Hand;
            btnCancelar.Click += BtnCancelar_Click;
            this.Controls.Add(btnCancelar);
        }

        private void BtnLogin_Click(object sender, EventArgs e)
        {
            string usuario = txtUsuario.Text;
            string password = txtPassword.Text;

            if (usuarios.ContainsKey(usuario) && usuarios[usuario] == password)
            {
                UsuarioLogueado = usuario;
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
            else
            {
                MessageBox.Show(
                    "Usuario o contraseña incorrectos. Intente nuevamente.\n\nUsuarios de prueba:\nadmin / admin123\nusuario / pass123\niglesia / poblado2024",
                    "Error de Autenticación",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error
                );
                txtPassword.Clear();
                txtPassword.Focus();
            }
        }

        private void BtnCancelar_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void TxtPassword_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                BtnLogin_Click(sender, e);
            }
        }
    }

    // Formulario Principal
    public class MainForm : Form
    {
        private Button btnInfo;
        private Button btnProductos;
        private Button btnContacto;
        private Button btnCerrarSesion;
        private Label lblWelcome;
        private Label lblTitle;
        private Panel panelTop;
        private FlowLayoutPanel panelButtons;
        private string usuarioActual;

        public MainForm(string usuario)
        {
            this.usuarioActual = usuario;
            ConfigurarVentana();
            CrearControles();
        }

        private void ConfigurarVentana()
        {
            this.Text = "Iglesia Poblado - Aplicación Principal";
            this.Size = new Size(720, 540);
            this.MinimumSize = new Size(600, 400);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.BackColor = Color.White;
        }

        private void CrearControles()
        {
            // Panel superior
            panelTop = new Panel();
            panelTop.BackColor = Color.FromArgb(0, 120, 215);
            panelTop.Dock = DockStyle.Top;
            panelTop.Height = 60;
            this.Controls.Add(panelTop);

            // Etiqueta de bienvenida
            lblWelcome = new Label();
            lblWelcome.Text = $"Bienvenido, {usuarioActual}!";
            lblWelcome.Font = new Font("Arial", 14, FontStyle.Bold);
            lblWelcome.ForeColor = Color.White;
            lblWelcome.Size = new Size(500, 30);
            lblWelcome.Location = new Point(20, 15);
            panelTop.Controls.Add(lblWelcome);

            // Botón cerrar sesión
            btnCerrarSesion = new Button();
            btnCerrarSesion.Text = "Cerrar Sesión";
            btnCerrarSesion.Size = new Size(120, 35);
            btnCerrarSesion.Location = new Point(570, 12);
            btnCerrarSesion.Font = new Font("Arial", 9);
            btnCerrarSesion.BackColor = Color.FromArgb(200, 50, 50);
            btnCerrarSesion.ForeColor = Color.White;
            btnCerrarSesion.FlatStyle = FlatStyle.Flat;
            btnCerrarSesion.Cursor = Cursors.Hand;
            btnCerrarSesion.Click += BtnCerrarSesion_Click;
            panelTop.Controls.Add(btnCerrarSesion);

            // Título principal
            lblTitle = new Label();
            lblTitle.Text = "🏛️ Tienda Iglesia Poblado";
            lblTitle.Font = new Font("Arial", 18, FontStyle.Bold);
            lblTitle.Size = new Size(600, 50);
            lblTitle.Location = new Point(50, 100);
            lblTitle.TextAlign = ContentAlignment.MiddleCenter;
            this.Controls.Add(lblTitle);

            // Panel de botones
            panelButtons = new FlowLayoutPanel();
            panelButtons.Location = new Point(110, 180);
            panelButtons.Size = new Size(500, 280);
            panelButtons.FlowDirection = FlowDirection.TopDown;
            this.Controls.Add(panelButtons);

            // Botón Información
            btnInfo = new Button();
            btnInfo.Text = "📋 Ver Información";
            btnInfo.Size = new Size(500, 50);
            btnInfo.Font = new Font("Arial", 12);
            btnInfo.BackColor = Color.FromArgb(0, 120, 215);
            btnInfo.ForeColor = Color.White;
            btnInfo.FlatStyle = FlatStyle.Flat;
            btnInfo.Cursor = Cursors.Hand;
            btnInfo.Margin = new Padding(0, 0, 0, 10);
            btnInfo.Click += BtnInfo_Click;
            panelButtons.Controls.Add(btnInfo);

            // Botón Productos
            btnProductos = new Button();
            btnProductos.Text = "🛒 Ver Productos";
            btnProductos.Size = new Size(500, 50);
            btnProductos.Font = new Font("Arial", 12);
            btnProductos.BackColor = Color.FromArgb(40, 167, 69);
            btnProductos.ForeColor = Color.White;
            btnProductos.FlatStyle = FlatStyle.Flat;
            btnProductos.Cursor = Cursors.Hand;
            btnProductos.Margin = new Padding(0, 0, 0, 10);
            btnProductos.Click += BtnProductos_Click;
            panelButtons.Controls.Add(btnProductos);

            // Botón Contacto
            btnContacto = new Button();
            btnContacto.Text = "📞 Contacto";
            btnContacto.Size = new Size(500, 50);
            btnContacto.Font = new Font("Arial", 12);
            btnContacto.BackColor = Color.FromArgb(255, 193, 7);
            btnContacto.ForeColor = Color.Black;
            btnContacto.FlatStyle = FlatStyle.Flat;
            btnContacto.Cursor = Cursors.Hand;
            btnContacto.Click += BtnContacto_Click;
            panelButtons.Controls.Add(btnContacto);
        }

        private void BtnInfo_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                $"Iglesia Poblado - Tienda Religiosa\n\nUsuario actual: {usuarioActual}\nFecha: {DateTime.Now:dd/MM/yyyy HH:mm}\n\nOfrecemos artículos religiosos, libros, souvenirs y más.",
                "Información",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information
            );
        }

        private void BtnProductos_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                "Productos disponibles:\n\n✝️ Biblias y libros religiosos\n🕯️ Velas y candelas\n📿 Rosarios y cruces\n🖼️ Cuadros e imágenes religiosas\n🎁 Souvenirs y regalos\n\n¡Visítanos para más detalles!",
                "Catálogo de Productos",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information
            );
        }

        private void BtnContacto_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                "Contacto:\n\n📍 Dirección: Iglesia Poblado\n📞 Teléfono: (XXX) XXX-XXXX\n📧 Email: info@iglesiapoblado.com\n🌐 Web: www.iglesiapoblado.com\n\n¡Esperamos verte pronto!",
                "Información de Contacto",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information
            );
        }

        private void BtnCerrarSesion_Click(object sender, EventArgs e)
        {
            DialogResult resultado = MessageBox.Show(
                "¿Está seguro de que desea cerrar sesión?",
                "Cerrar Sesión",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question
            );

            if (resultado == DialogResult.Yes)
            {
                this.Close();
            }
        }

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // Mostrar formulario de login
            LoginForm loginForm = new LoginForm();
            DialogResult result = loginForm.ShowDialog();

            if (result == DialogResult.OK)
            {
                // Si el login fue exitoso, mostrar aplicación principal
                Application.Run(new MainForm(loginForm.UsuarioLogueado));
            }
            else
            {
                MessageBox.Show(
                    "Sesión cancelada. La aplicación se cerrará.",
                    "Aviso",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information
                );
            }
        }
    }
}
