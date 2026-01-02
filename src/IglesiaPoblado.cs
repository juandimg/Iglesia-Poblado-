using System;
using System.Windows.Forms;
using System.Drawing;

namespace IglesiaPoblado
{
    public class MainForm : Form
    {
        private Button button;
        private Label label;

        public MainForm()
        {
            // Configurar la ventana
            this.Text = "Iglesia Poblado - Aplicación";
            this.Size = new Size(800, 600);
            this.StartPosition = FormStartPosition.CenterScreen;
            this.BackColor = Color.White;

            // Crear etiqueta de bienvenida
            label = new Label();
            label.Text = "Bienvenido a la aplicación de Iglesia Poblado";
            label.Font = new Font("Arial", 14, FontStyle.Bold);
            label.Size = new Size(400, 30);
            label.Location = new Point(200, 150);
            label.TextAlign = ContentAlignment.MiddleCenter;
            this.Controls.Add(label);

            // Crear botón
            button = new Button();
            button.Text = "¡Haz clic aquí!";
            button.Size = new Size(200, 50);
            button.Location = new Point(300, 250);
            button.Font = new Font("Arial", 12);
            button.BackColor = Color.FromArgb(0, 120, 215);
            button.ForeColor = Color.White;
            button.FlatStyle = FlatStyle.Flat;
            button.Cursor = Cursors.Hand;
            button.Click += Button_Click;
            this.Controls.Add(button);
        }

        private void Button_Click(object sender, EventArgs e)
        {
            MessageBox.Show(
                "¡Botón presionado! Bienvenido a la Iglesia Poblado.",
                "Mensaje",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information
            );
        }

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}
