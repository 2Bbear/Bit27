namespace Thread_0416
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

       

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
           
             SuspendLayout();
            // 
            // listBox2
            // 
             listBox2.FormattingEnabled = true;
             listBox2.ItemHeight = 15;
             listBox2.Location = new System.Drawing.Point(13, 13);
             listBox2.Name = "listBox2";
             listBox2.Size = new System.Drawing.Size(187, 559);
             listBox2.TabIndex = 0;
            // 
            // listBox3
            // 
             listBox3.FormattingEnabled = true;
             listBox3.ItemHeight = 15;
             listBox3.Location = new System.Drawing.Point(268, 13);
             listBox3.Name = "listBox3";
             listBox3.Size = new System.Drawing.Size(187, 559);
             listBox3.TabIndex = 1;
            // 
            // listBox4
            // 
             listBox4.FormattingEnabled = true;
             listBox4.ItemHeight = 15;
             listBox4.Location = new System.Drawing.Point(500, 13);
             listBox4.Name = "listBox4";
             listBox4.Size = new System.Drawing.Size(187, 559);
             listBox4.TabIndex = 2;
            // 
            // Form1
            // 
             AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
             AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
             ClientSize = new System.Drawing.Size(800, 610);
             Controls.Add( listBox4);
             Controls.Add( listBox3);
             Controls.Add( listBox2);
             Name = "Form1";
             Text = "Form1";
             ResumeLayout(false);

        }


        #endregion
        public static System.Windows.Forms.ListBox listBox1 = new System.Windows.Forms.ListBox();
        private static System.Windows.Forms.ListBox listBox3 = new System.Windows.Forms.ListBox();
        private static System.Windows.Forms.ListBox listBox4 = new System.Windows.Forms.ListBox();
        private static System.Windows.Forms.ListBox listBox2 = new System.Windows.Forms.ListBox();
    }
}

