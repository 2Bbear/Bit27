namespace WinFormPowerPoint_0416
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
            this.파일FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.기능MToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.파일열기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.다른이름으로저장ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.프로그램종료ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.새파일ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.편집ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.프레젠테이션실행ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.프레젠테이션종료ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.페이지이동ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.이전페이지ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.파일FToolStripMenuItem,
            this.기능MToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(709, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 파일FToolStripMenuItem
            // 
            this.파일FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.새파일ToolStripMenuItem,
            this.파일열기ToolStripMenuItem,
            this.다른이름으로저장ToolStripMenuItem,
            this.toolStripSeparator1,
            this.프로그램종료ToolStripMenuItem});
            this.파일FToolStripMenuItem.Name = "파일FToolStripMenuItem";
            this.파일FToolStripMenuItem.Size = new System.Drawing.Size(68, 24);
            this.파일FToolStripMenuItem.Text = "파일(&F)";
            // 
            // 기능MToolStripMenuItem
            // 
            this.기능MToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.편집ToolStripMenuItem,
            this.이전페이지ToolStripMenuItem,
            this.페이지이동ToolStripMenuItem,
            this.프레젠테이션실행ToolStripMenuItem,
            this.프레젠테이션종료ToolStripMenuItem});
            this.기능MToolStripMenuItem.Name = "기능MToolStripMenuItem";
            this.기능MToolStripMenuItem.Size = new System.Drawing.Size(75, 24);
            this.기능MToolStripMenuItem.Text = "기능(&M)";
            // 
            // 파일열기ToolStripMenuItem
            // 
            this.파일열기ToolStripMenuItem.Name = "파일열기ToolStripMenuItem";
            this.파일열기ToolStripMenuItem.Size = new System.Drawing.Size(228, 26);
            this.파일열기ToolStripMenuItem.Text = "파일선택";
            this.파일열기ToolStripMenuItem.Click += new System.EventHandler(this.파일열기ToolStripMenuItem_Click);
            // 
            // 다른이름으로저장ToolStripMenuItem
            // 
            this.다른이름으로저장ToolStripMenuItem.Name = "다른이름으로저장ToolStripMenuItem";
            this.다른이름으로저장ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.다른이름으로저장ToolStripMenuItem.Text = "다른이름으로 저장";
            this.다른이름으로저장ToolStripMenuItem.Click += new System.EventHandler(this.다른이름으로저장ToolStripMenuItem_Click);
            // 
            // 프로그램종료ToolStripMenuItem
            // 
            this.프로그램종료ToolStripMenuItem.Name = "프로그램종료ToolStripMenuItem";
            this.프로그램종료ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.프로그램종료ToolStripMenuItem.Size = new System.Drawing.Size(228, 26);
            this.프로그램종료ToolStripMenuItem.Text = "프로그램종료";
            this.프로그램종료ToolStripMenuItem.Click += new System.EventHandler(this.프로그램종료ToolStripMenuItem_Click);
            // 
            // 새파일ToolStripMenuItem
            // 
            this.새파일ToolStripMenuItem.Name = "새파일ToolStripMenuItem";
            this.새파일ToolStripMenuItem.Size = new System.Drawing.Size(228, 26);
            this.새파일ToolStripMenuItem.Text = "새파일";
            this.새파일ToolStripMenuItem.Click += new System.EventHandler(this.새파일ToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(213, 6);
            // 
            // 편집ToolStripMenuItem
            // 
            this.편집ToolStripMenuItem.Name = "편집ToolStripMenuItem";
            this.편집ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.E)));
            this.편집ToolStripMenuItem.Size = new System.Drawing.Size(234, 26);
            this.편집ToolStripMenuItem.Text = "편집";
            this.편집ToolStripMenuItem.Click += new System.EventHandler(this.편집ToolStripMenuItem_Click);
            // 
            // 프레젠테이션실행ToolStripMenuItem
            // 
            this.프레젠테이션실행ToolStripMenuItem.Name = "프레젠테이션실행ToolStripMenuItem";
            this.프레젠테이션실행ToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F5;
            this.프레젠테이션실행ToolStripMenuItem.Size = new System.Drawing.Size(233, 26);
            this.프레젠테이션실행ToolStripMenuItem.Text = "프레젠테이션 실행";
            this.프레젠테이션실행ToolStripMenuItem.Click += new System.EventHandler(this.프레젠테이션실행ToolStripMenuItem_Click);
            // 
            // 프레젠테이션종료ToolStripMenuItem
            // 
            this.프레젠테이션종료ToolStripMenuItem.Name = "프레젠테이션종료ToolStripMenuItem";
            this.프레젠테이션종료ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.프레젠테이션종료ToolStripMenuItem.Text = "프레젠테이션 종료";
            this.프레젠테이션종료ToolStripMenuItem.Click += new System.EventHandler(this.프레젠테이션종료ToolStripMenuItem_Click);
            // 
            // 페이지이동ToolStripMenuItem
            // 
            this.페이지이동ToolStripMenuItem.Name = "페이지이동ToolStripMenuItem";
            this.페이지이동ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.Right)));
            this.페이지이동ToolStripMenuItem.Size = new System.Drawing.Size(234, 26);
            this.페이지이동ToolStripMenuItem.Text = "다음페이지";
            this.페이지이동ToolStripMenuItem.Click += new System.EventHandler(this.페이지이동ToolStripMenuItem_Click);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 15;
            this.listBox1.Location = new System.Drawing.Point(12, 46);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(142, 394);
            this.listBox1.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox1);
            this.groupBox1.Location = new System.Drawing.Point(186, 46);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(458, 394);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(6, 33);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(446, 355);
            this.textBox1.TabIndex = 0;
            // 
            // 이전페이지ToolStripMenuItem
            // 
            this.이전페이지ToolStripMenuItem.Name = "이전페이지ToolStripMenuItem";
            this.이전페이지ToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.Left)));
            this.이전페이지ToolStripMenuItem.Size = new System.Drawing.Size(234, 26);
            this.이전페이지ToolStripMenuItem.Text = "이전페이지";
            this.이전페이지ToolStripMenuItem.Click += new System.EventHandler(this.이전페이지ToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(709, 450);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 파일FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 기능MToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 파일열기ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 다른이름으로저장ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 프로그램종료ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 새파일ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem 편집ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 프레젠테이션실행ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 프레젠테이션종료ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 페이지이동ToolStripMenuItem;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.ToolStripMenuItem 이전페이지ToolStripMenuItem;
    }
}

