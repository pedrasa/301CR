using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Security;
using System.Windows.Forms;

/// <summary>
/// you can use this to change the textures of the pipes and the
/// flappy bird just rename the text files
/// </summary>
namespace _301CR_Level_Changer
{
    public class OpenFileDialogForm : Form
    {
        [STAThread]
        public static void Main()
        {
            Application.SetCompatibleTextRenderingDefault(false);
            Application.EnableVisualStyles();
            Application.Run(new OpenFileDialogForm());
        }

        private Button selectButton;
        private OpenFileDialog openFileDialog1;

        public OpenFileDialogForm()
        {
            openFileDialog1 = new OpenFileDialog()
            {
                FileName = "Select a png file",
                Filter = "png files (*.png)|*.png",
                Title = "Open png file"
            };

            selectButton = new Button()
            {
                Size = new Size(100, 20),
                Location = new Point(15, 15),
                Text = "Select file"
            };
            selectButton.Click += new EventHandler(selectButton_Click);
            Controls.Add(selectButton);
        }

        private void selectButton_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    var filePath = openFileDialog1.FileName;
                    string filePathText = openFileDialog1.FileName;
                    StreamWriter sw = new StreamWriter("C:\\Users\\Desktop\\Desktop\\301CR\\301CR Level Gen\\301CR Level Changer\\Texture.txt");
                    using (Stream str = openFileDialog1.OpenFile())
                    {
                        sw.WriteLine(filePathText);
                        sw.Close();

                    }
                }
                catch (SecurityException ex)
                {
                    MessageBox.Show($"Security error.\n\nError message: {ex.Message}\n\n" +
                    $"Details:\n\n{ex.StackTrace}");
                }
            }
        }
    }
}
