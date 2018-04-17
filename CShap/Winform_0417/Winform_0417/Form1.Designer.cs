namespace Winform_0417
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.serverConnetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.serverDisConnectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.programExitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(504, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.serverConnetToolStripMenuItem,
            this.serverDisConnectToolStripMenuItem,
            this.toolStripSeparator1,
            this.programExitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(44, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // serverConnetToolStripMenuItem
            // 
            this.serverConnetToolStripMenuItem.Name = "serverConnetToolStripMenuItem";
            this.serverConnetToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.serverConnetToolStripMenuItem.Text = "ServerConnet";
            this.serverConnetToolStripMenuItem.Click += new System.EventHandler(this.serverConnetToolStripMenuItem_Click);
            // 
            // serverDisConnectToolStripMenuItem
            // 
            this.serverDisConnectToolStripMenuItem.Name = "serverDisConnectToolStripMenuItem";
            this.serverDisConnectToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.serverDisConnectToolStripMenuItem.Text = "ServerDisConnect";
            this.serverDisConnectToolStripMenuItem.Click += new System.EventHandler(this.serverDisConnectToolStripMenuItem_Click);
            // 
            // programExitToolStripMenuItem
            // 
            this.programExitToolStripMenuItem.Name = "programExitToolStripMenuItem";
            this.programExitToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.programExitToolStripMenuItem.Text = "ProgramExit";
            this.programExitToolStripMenuItem.Click += new System.EventHandler(this.programExitToolStripMenuItem_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 31);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(479, 407);
            this.textBox1.TabIndex = 1;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(13, 445);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(368, 25);
            this.textBox2.TabIndex = 2;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(388, 445);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(103, 25);
            this.button1.TabIndex = 3;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(213, 6);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(504, 484);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem serverConnetToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem serverDisConnectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem programExitToolStripMenuItem;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    }
}

