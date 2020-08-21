namespace WindowsFormsApplication1
{
    partial class Calc
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.inputBox = new System.Windows.Forms.TextBox();
            this.equal = new System.Windows.Forms.PictureBox();
            this.openBraket = new System.Windows.Forms.PictureBox();
            this.subtract = new System.Windows.Forms.PictureBox();
            this.summ = new System.Windows.Forms.PictureBox();
            this.closeBraket = new System.Windows.Forms.PictureBox();
            this.mult = new System.Windows.Forms.PictureBox();
            this.div = new System.Windows.Forms.PictureBox();
            this.zero = new System.Windows.Forms.PictureBox();
            this.point = new System.Windows.Forms.PictureBox();
            this.three = new System.Windows.Forms.PictureBox();
            this.two = new System.Windows.Forms.PictureBox();
            this.one = new System.Windows.Forms.PictureBox();
            this.six = new System.Windows.Forms.PictureBox();
            this.five = new System.Windows.Forms.PictureBox();
            this.four = new System.Windows.Forms.PictureBox();
            this.nine = new System.Windows.Forms.PictureBox();
            this.eight = new System.Windows.Forms.PictureBox();
            this.seven = new System.Windows.Forms.PictureBox();
            this.ln = new System.Windows.Forms.PictureBox();
            this.cos = new System.Windows.Forms.PictureBox();
            this.sqrt = new System.Windows.Forms.PictureBox();
            this.del = new System.Windows.Forms.PictureBox();
            this.sin = new System.Windows.Forms.PictureBox();
            this.delete = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.equal)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.openBraket)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.subtract)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.summ)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.closeBraket)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mult)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.div)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.zero)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.point)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.three)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.two)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.one)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.six)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.five)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.four)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nine)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.eight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.seven)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ln)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cos)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sqrt)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.del)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.delete)).BeginInit();
            this.SuspendLayout();
            // 
            // inputBox
            // 
            this.inputBox.BackColor = System.Drawing.SystemColors.HotTrack;
            this.inputBox.Cursor = System.Windows.Forms.Cursors.WaitCursor;
            this.inputBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.inputBox.Location = new System.Drawing.Point(7, 5);
            this.inputBox.Name = "inputBox";
            this.inputBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.inputBox.Size = new System.Drawing.Size(498, 44);
            this.inputBox.TabIndex = 0;
            this.inputBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.inputBox.UseWaitCursor = true;
            // 
            // equal
            // 
            this.equal.Cursor = System.Windows.Forms.Cursors.Hand;
            this.equal.Image = global::WindowsFormsApplication1.Properties.Resources.равн;
            this.equal.Location = new System.Drawing.Point(511, 193);
            this.equal.Name = "equal";
            this.equal.Size = new System.Drawing.Size(84, 122);
            this.equal.TabIndex = 27;
            this.equal.TabStop = false;
            this.equal.Click += new System.EventHandler(this.equal_Click);
            // 
            // openBraket
            // 
            this.openBraket.Cursor = System.Windows.Forms.Cursors.Hand;
            this.openBraket.Image = global::WindowsFormsApplication1.Properties.Resources.лев;
            this.openBraket.Location = new System.Drawing.Point(511, 65);
            this.openBraket.Name = "openBraket";
            this.openBraket.Size = new System.Drawing.Size(84, 58);
            this.openBraket.TabIndex = 26;
            this.openBraket.TabStop = false;
            this.openBraket.Click += new System.EventHandler(this.openBraket_Click);
            // 
            // subtract
            // 
            this.subtract.Cursor = System.Windows.Forms.Cursors.Hand;
            this.subtract.Image = global::WindowsFormsApplication1.Properties.Resources.мин;
            this.subtract.Location = new System.Drawing.Point(421, 193);
            this.subtract.Name = "subtract";
            this.subtract.Size = new System.Drawing.Size(84, 58);
            this.subtract.TabIndex = 25;
            this.subtract.TabStop = false;
            this.subtract.Click += new System.EventHandler(this.subtract_Click);
            // 
            // summ
            // 
            this.summ.Cursor = System.Windows.Forms.Cursors.Hand;
            this.summ.Image = global::WindowsFormsApplication1.Properties.Resources.плюс;
            this.summ.Location = new System.Drawing.Point(421, 257);
            this.summ.Name = "summ";
            this.summ.Size = new System.Drawing.Size(84, 58);
            this.summ.TabIndex = 25;
            this.summ.TabStop = false;
            this.summ.Click += new System.EventHandler(this.summ_Click);
            // 
            // closeBraket
            // 
            this.closeBraket.Cursor = System.Windows.Forms.Cursors.Hand;
            this.closeBraket.Image = global::WindowsFormsApplication1.Properties.Resources.прав;
            this.closeBraket.Location = new System.Drawing.Point(511, 129);
            this.closeBraket.Name = "closeBraket";
            this.closeBraket.Size = new System.Drawing.Size(84, 58);
            this.closeBraket.TabIndex = 25;
            this.closeBraket.TabStop = false;
            this.closeBraket.Click += new System.EventHandler(this.closeBraket_Click);
            // 
            // mult
            // 
            this.mult.Cursor = System.Windows.Forms.Cursors.Hand;
            this.mult.Image = global::WindowsFormsApplication1.Properties.Resources.умн;
            this.mult.Location = new System.Drawing.Point(421, 129);
            this.mult.Name = "mult";
            this.mult.Size = new System.Drawing.Size(84, 58);
            this.mult.TabIndex = 24;
            this.mult.TabStop = false;
            this.mult.Click += new System.EventHandler(this.mult_Click);
            // 
            // div
            // 
            this.div.Cursor = System.Windows.Forms.Cursors.Hand;
            this.div.Image = global::WindowsFormsApplication1.Properties.Resources.дел;
            this.div.Location = new System.Drawing.Point(421, 65);
            this.div.Name = "div";
            this.div.Size = new System.Drawing.Size(84, 58);
            this.div.TabIndex = 23;
            this.div.TabStop = false;
            this.div.Click += new System.EventHandler(this.div_Click);
            // 
            // zero
            // 
            this.zero.Cursor = System.Windows.Forms.Cursors.Hand;
            this.zero.Image = global::WindowsFormsApplication1.Properties.Resources._0;
            this.zero.Location = new System.Drawing.Point(103, 257);
            this.zero.Name = "zero";
            this.zero.Size = new System.Drawing.Size(198, 58);
            this.zero.TabIndex = 22;
            this.zero.TabStop = false;
            this.zero.Click += new System.EventHandler(this.zero_Click);
            // 
            // point
            // 
            this.point.Cursor = System.Windows.Forms.Cursors.Hand;
            this.point.Image = global::WindowsFormsApplication1.Properties.Resources.точ;
            this.point.Location = new System.Drawing.Point(307, 257);
            this.point.Name = "point";
            this.point.Size = new System.Drawing.Size(97, 58);
            this.point.TabIndex = 21;
            this.point.TabStop = false;
            this.point.Click += new System.EventHandler(this.point_Click);
            // 
            // three
            // 
            this.three.Cursor = System.Windows.Forms.Cursors.Hand;
            this.three.Image = global::WindowsFormsApplication1.Properties.Resources._3;
            this.three.Location = new System.Drawing.Point(309, 193);
            this.three.Name = "three";
            this.three.Size = new System.Drawing.Size(97, 58);
            this.three.TabIndex = 20;
            this.three.TabStop = false;
            this.three.Click += new System.EventHandler(this.three_Click);
            // 
            // two
            // 
            this.two.Cursor = System.Windows.Forms.Cursors.Hand;
            this.two.Image = global::WindowsFormsApplication1.Properties.Resources._2;
            this.two.Location = new System.Drawing.Point(206, 193);
            this.two.Name = "two";
            this.two.Size = new System.Drawing.Size(97, 58);
            this.two.TabIndex = 19;
            this.two.TabStop = false;
            this.two.Click += new System.EventHandler(this.two_Click);
            // 
            // one
            // 
            this.one.Cursor = System.Windows.Forms.Cursors.Hand;
            this.one.Image = global::WindowsFormsApplication1.Properties.Resources._1;
            this.one.Location = new System.Drawing.Point(103, 193);
            this.one.Name = "one";
            this.one.Size = new System.Drawing.Size(97, 58);
            this.one.TabIndex = 18;
            this.one.TabStop = false;
            this.one.Click += new System.EventHandler(this.one_Click);
            // 
            // six
            // 
            this.six.Cursor = System.Windows.Forms.Cursors.Hand;
            this.six.Image = global::WindowsFormsApplication1.Properties.Resources._6;
            this.six.Location = new System.Drawing.Point(309, 129);
            this.six.Name = "six";
            this.six.Size = new System.Drawing.Size(97, 58);
            this.six.TabIndex = 17;
            this.six.TabStop = false;
            this.six.Click += new System.EventHandler(this.six_Click);
            // 
            // five
            // 
            this.five.Cursor = System.Windows.Forms.Cursors.Hand;
            this.five.Image = global::WindowsFormsApplication1.Properties.Resources._5;
            this.five.Location = new System.Drawing.Point(206, 129);
            this.five.Name = "five";
            this.five.Size = new System.Drawing.Size(97, 58);
            this.five.TabIndex = 16;
            this.five.TabStop = false;
            this.five.Click += new System.EventHandler(this.five_Click);
            // 
            // four
            // 
            this.four.Cursor = System.Windows.Forms.Cursors.Hand;
            this.four.Image = global::WindowsFormsApplication1.Properties.Resources._4;
            this.four.Location = new System.Drawing.Point(103, 129);
            this.four.Name = "four";
            this.four.Size = new System.Drawing.Size(97, 58);
            this.four.TabIndex = 15;
            this.four.TabStop = false;
            this.four.Click += new System.EventHandler(this.four_Click);
            // 
            // nine
            // 
            this.nine.Cursor = System.Windows.Forms.Cursors.Hand;
            this.nine.Image = global::WindowsFormsApplication1.Properties.Resources._9;
            this.nine.Location = new System.Drawing.Point(309, 65);
            this.nine.Name = "nine";
            this.nine.Size = new System.Drawing.Size(97, 58);
            this.nine.TabIndex = 14;
            this.nine.TabStop = false;
            this.nine.Click += new System.EventHandler(this.nine_Click);
            // 
            // eight
            // 
            this.eight.Cursor = System.Windows.Forms.Cursors.Hand;
            this.eight.Image = global::WindowsFormsApplication1.Properties.Resources._8;
            this.eight.Location = new System.Drawing.Point(206, 65);
            this.eight.Name = "eight";
            this.eight.Size = new System.Drawing.Size(97, 58);
            this.eight.TabIndex = 13;
            this.eight.TabStop = false;
            this.eight.Click += new System.EventHandler(this.eight_Click);
            // 
            // seven
            // 
            this.seven.Cursor = System.Windows.Forms.Cursors.Hand;
            this.seven.Image = global::WindowsFormsApplication1.Properties.Resources._7;
            this.seven.Location = new System.Drawing.Point(103, 65);
            this.seven.Name = "seven";
            this.seven.Size = new System.Drawing.Size(97, 58);
            this.seven.TabIndex = 12;
            this.seven.TabStop = false;
            this.seven.Click += new System.EventHandler(this.seven_Click);
            // 
            // ln
            // 
            this.ln.Cursor = System.Windows.Forms.Cursors.Hand;
            this.ln.Image = global::WindowsFormsApplication1.Properties.Resources.лог;
            this.ln.Location = new System.Drawing.Point(12, 268);
            this.ln.Name = "ln";
            this.ln.Size = new System.Drawing.Size(75, 47);
            this.ln.TabIndex = 10;
            this.ln.TabStop = false;
            this.ln.Click += new System.EventHandler(this.ln_Click);
            // 
            // cos
            // 
            this.cos.Cursor = System.Windows.Forms.Cursors.Hand;
            this.cos.Image = global::WindowsFormsApplication1.Properties.Resources.кос;
            this.cos.Location = new System.Drawing.Point(12, 166);
            this.cos.Name = "cos";
            this.cos.Size = new System.Drawing.Size(75, 47);
            this.cos.TabIndex = 6;
            this.cos.TabStop = false;
            this.cos.Click += new System.EventHandler(this.cos_Click);
            // 
            // sqrt
            // 
            this.sqrt.Cursor = System.Windows.Forms.Cursors.Hand;
            this.sqrt.Image = global::WindowsFormsApplication1.Properties.Resources.корень;
            this.sqrt.Location = new System.Drawing.Point(12, 217);
            this.sqrt.Name = "sqrt";
            this.sqrt.Size = new System.Drawing.Size(75, 47);
            this.sqrt.TabIndex = 5;
            this.sqrt.TabStop = false;
            this.sqrt.Click += new System.EventHandler(this.sqrt_Click);
            // 
            // del
            // 
            this.del.Cursor = System.Windows.Forms.Cursors.Hand;
            this.del.Image = global::WindowsFormsApplication1.Properties.Resources.С;
            this.del.Location = new System.Drawing.Point(19, 55);
            this.del.Name = "del";
            this.del.Size = new System.Drawing.Size(75, 52);
            this.del.TabIndex = 4;
            this.del.TabStop = false;
            this.del.Click += new System.EventHandler(this.del_Click);
            // 
            // sin
            // 
            this.sin.Cursor = System.Windows.Forms.Cursors.Hand;
            this.sin.Image = global::WindowsFormsApplication1.Properties.Resources.Синус;
            this.sin.Location = new System.Drawing.Point(12, 113);
            this.sin.Name = "sin";
            this.sin.Size = new System.Drawing.Size(75, 47);
            this.sin.TabIndex = 2;
            this.sin.TabStop = false;
            this.sin.Click += new System.EventHandler(this.sin_Click);
            // 
            // delete
            // 
            this.delete.Cursor = System.Windows.Forms.Cursors.Hand;
            this.delete.ErrorImage = global::WindowsFormsApplication1.Properties.Resources.стереть;
            this.delete.Image = global::WindowsFormsApplication1.Properties.Resources.стереть;
            this.delete.InitialImage = global::WindowsFormsApplication1.Properties.Resources.стереть;
            this.delete.Location = new System.Drawing.Point(522, 6);
            this.delete.Name = "delete";
            this.delete.Size = new System.Drawing.Size(73, 43);
            this.delete.TabIndex = 1;
            this.delete.TabStop = false;
            this.delete.Click += new System.EventHandler(this.delete_Click);
            // 
            // Calc
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(605, 324);
            this.Controls.Add(this.equal);
            this.Controls.Add(this.openBraket);
            this.Controls.Add(this.subtract);
            this.Controls.Add(this.summ);
            this.Controls.Add(this.closeBraket);
            this.Controls.Add(this.mult);
            this.Controls.Add(this.div);
            this.Controls.Add(this.zero);
            this.Controls.Add(this.point);
            this.Controls.Add(this.three);
            this.Controls.Add(this.two);
            this.Controls.Add(this.one);
            this.Controls.Add(this.six);
            this.Controls.Add(this.five);
            this.Controls.Add(this.four);
            this.Controls.Add(this.nine);
            this.Controls.Add(this.eight);
            this.Controls.Add(this.seven);
            this.Controls.Add(this.ln);
            this.Controls.Add(this.cos);
            this.Controls.Add(this.sqrt);
            this.Controls.Add(this.del);
            this.Controls.Add(this.sin);
            this.Controls.Add(this.delete);
            this.Controls.Add(this.inputBox);
            this.Name = "Calc";
            this.Text = "Калькулятор";
            ((System.ComponentModel.ISupportInitialize)(this.equal)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.openBraket)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.subtract)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.summ)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.closeBraket)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mult)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.div)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.zero)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.point)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.three)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.two)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.one)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.six)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.five)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.four)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nine)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.eight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.seven)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ln)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cos)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sqrt)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.del)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.delete)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox inputBox;
        private System.Windows.Forms.PictureBox delete;
        private System.Windows.Forms.PictureBox sin;
        private System.Windows.Forms.PictureBox sqrt;
        private System.Windows.Forms.PictureBox cos;
        private System.Windows.Forms.PictureBox ln;
        private System.Windows.Forms.PictureBox seven;
        private System.Windows.Forms.PictureBox eight;
        private System.Windows.Forms.PictureBox nine;
        private System.Windows.Forms.PictureBox four;
        private System.Windows.Forms.PictureBox five;
        private System.Windows.Forms.PictureBox six;
        private System.Windows.Forms.PictureBox one;
        private System.Windows.Forms.PictureBox two;
        private System.Windows.Forms.PictureBox three;
        private System.Windows.Forms.PictureBox point;
        private System.Windows.Forms.PictureBox zero;
        private System.Windows.Forms.PictureBox div;
        private System.Windows.Forms.PictureBox mult;
        private System.Windows.Forms.PictureBox closeBraket;
        private System.Windows.Forms.PictureBox subtract;
        private System.Windows.Forms.PictureBox summ;
        private System.Windows.Forms.PictureBox openBraket;
        private System.Windows.Forms.PictureBox equal;
        private System.Windows.Forms.PictureBox del;
    }
}

