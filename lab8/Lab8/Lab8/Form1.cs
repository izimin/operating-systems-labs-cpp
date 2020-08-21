using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Calc : Form
    {

        public Calc()
        {
            InitializeComponent(); 
            this.KeyPreview = true;
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                equal_Click(sender, e);
            }

            if (e.KeyCode == Keys.Delete)
            {
                delete_Click(sender, e);
            }
        }

        private void zero_Click(object sender, EventArgs e)
        {
            inputBox.Text += "0";
        }

        private void one_Click(object sender, EventArgs e)
        {
            inputBox.Text += "1";
        }

        private void two_Click(object sender, EventArgs e)
        {
            inputBox.Text += "2";
        }

        private void three_Click(object sender, EventArgs e)
        {
            inputBox.Text += "3";
        }

        private void four_Click(object sender, EventArgs e)
        {
            inputBox.Text += "4";
        }

        private void five_Click(object sender, EventArgs e)
        {
            inputBox.Text += "5";
        }

        private void six_Click(object sender, EventArgs e)
        {
            inputBox.Text += "6";
        }

        private void seven_Click(object sender, EventArgs e)
        {
            inputBox.Text += "7";
        }

        private void eight_Click(object sender, EventArgs e)
        {
            inputBox.Text += "8";
        }

        private void nine_Click(object sender, EventArgs e)
        {
            inputBox.Text += "9";
        }

        private void factorial_Click(object sender, EventArgs e)
        {
            inputBox.Text = "";
        }

        private void ln_Click(object sender, EventArgs e)
        {
            inputBox.Text = "ln(";
            inputBox.SelectionStart += 3;
        }

        private void sqrt_Click(object sender, EventArgs e)
        {
            inputBox.Text = "sqrt(";
            inputBox.SelectionStart += 5;
        }

        private void cos_Click(object sender, EventArgs e)
        {
            inputBox.Text = "cos(";
            inputBox.SelectionStart += 4;
        }

        private void sin_Click(object sender, EventArgs e)
        {
            inputBox.Text = "sin(";
            inputBox.SelectionStart += 4;
        }

        private void point_Click(object sender, EventArgs e)
        {
            inputBox.Text += ",";
        }

        private void summ_Click(object sender, EventArgs e)
        {
            inputBox.Text += "+";
        }

        private void subtract_Click(object sender, EventArgs e)
        {
            inputBox.Text += "-";
        }

        private void mult_Click(object sender, EventArgs e)
        {
            inputBox.Text += "*";
        }

        private void div_Click(object sender, EventArgs e)
        {
            inputBox.Text += "/";
        }

        private void openBraket_Click(object sender, EventArgs e)
        {
            inputBox.Text += "(";
        }

        private void closeBraket_Click(object sender, EventArgs e)
        {
            inputBox.Text += ")";
        }

        private void equal_Click(object sender, EventArgs e)
        {
            try
            {
                inputBox.Text = Calculation.Calc(inputBox.Text).ToString();
            }
            catch (Exception ex) { 
                MessageBox.Show (ex.Message);
                inputBox.Text = "";
            }

        }

        private void delete_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "")
               inputBox.Text = inputBox.Text.ToString().Substring(0, inputBox.Text.ToString().Length - 1);
        }

        private void del_Click(object sender, EventArgs e)
        {
            inputBox.Text = "";
        }
    }
}
