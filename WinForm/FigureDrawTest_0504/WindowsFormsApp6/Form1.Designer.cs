namespace WindowsFormsApp6
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
            this.종료XToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.색상CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.빨간색RToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.녹색GToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.파란색BToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.색상다이얼로그ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.도형타입TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.사각형ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.타원ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.옵션OToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.모달MToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.모달리스ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.파일FToolStripMenuItem,
            this.색상CToolStripMenuItem,
            this.도형타입TToolStripMenuItem,
            this.옵션OToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 파일FToolStripMenuItem
            // 
            this.파일FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.종료XToolStripMenuItem});
            this.파일FToolStripMenuItem.Name = "파일FToolStripMenuItem";
            this.파일FToolStripMenuItem.Size = new System.Drawing.Size(68, 24);
            this.파일FToolStripMenuItem.Text = "파일(F)";
            // 
            // 종료XToolStripMenuItem
            // 
            this.종료XToolStripMenuItem.Name = "종료XToolStripMenuItem";
            this.종료XToolStripMenuItem.Size = new System.Drawing.Size(133, 26);
            this.종료XToolStripMenuItem.Text = "종료(X)";
            this.종료XToolStripMenuItem.Click += new System.EventHandler(this.종료XToolStripMenuItem_Click);
            // 
            // 색상CToolStripMenuItem
            // 
            this.색상CToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.빨간색RToolStripMenuItem,
            this.녹색GToolStripMenuItem,
            this.파란색BToolStripMenuItem,
            this.색상다이얼로그ToolStripMenuItem});
            this.색상CToolStripMenuItem.Name = "색상CToolStripMenuItem";
            this.색상CToolStripMenuItem.Size = new System.Drawing.Size(71, 24);
            this.색상CToolStripMenuItem.Text = "색상(C)";
            // 
            // 빨간색RToolStripMenuItem
            // 
            this.빨간색RToolStripMenuItem.Name = "빨간색RToolStripMenuItem";
            this.빨간색RToolStripMenuItem.Size = new System.Drawing.Size(189, 26);
            this.빨간색RToolStripMenuItem.Text = "빨간색(R)";
            this.빨간색RToolStripMenuItem.Click += new System.EventHandler(this.빨간색RToolStripMenuItem_Click);
            // 
            // 녹색GToolStripMenuItem
            // 
            this.녹색GToolStripMenuItem.Name = "녹색GToolStripMenuItem";
            this.녹색GToolStripMenuItem.Size = new System.Drawing.Size(189, 26);
            this.녹색GToolStripMenuItem.Text = "녹   색(G)";
            this.녹색GToolStripMenuItem.Click += new System.EventHandler(this.녹색GToolStripMenuItem_Click);
            // 
            // 파란색BToolStripMenuItem
            // 
            this.파란색BToolStripMenuItem.Name = "파란색BToolStripMenuItem";
            this.파란색BToolStripMenuItem.Size = new System.Drawing.Size(189, 26);
            this.파란색BToolStripMenuItem.Text = "파란색(B)";
            this.파란색BToolStripMenuItem.Click += new System.EventHandler(this.파란색BToolStripMenuItem_Click);
            // 
            // 색상다이얼로그ToolStripMenuItem
            // 
            this.색상다이얼로그ToolStripMenuItem.Name = "색상다이얼로그ToolStripMenuItem";
            this.색상다이얼로그ToolStripMenuItem.Size = new System.Drawing.Size(189, 26);
            this.색상다이얼로그ToolStripMenuItem.Text = "색상다이얼로그";
            this.색상다이얼로그ToolStripMenuItem.Click += new System.EventHandler(this.색상다이얼로그ToolStripMenuItem_Click);
            // 
            // 도형타입TToolStripMenuItem
            // 
            this.도형타입TToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.사각형ToolStripMenuItem,
            this.타원ToolStripMenuItem});
            this.도형타입TToolStripMenuItem.Name = "도형타입TToolStripMenuItem";
            this.도형타입TToolStripMenuItem.Size = new System.Drawing.Size(104, 24);
            this.도형타입TToolStripMenuItem.Text = "도형 타입(&T)";
            // 
            // 사각형ToolStripMenuItem
            // 
            this.사각형ToolStripMenuItem.Name = "사각형ToolStripMenuItem";
            this.사각형ToolStripMenuItem.Size = new System.Drawing.Size(100, 26);
            this.사각형ToolStripMenuItem.Text = "25";
            this.사각형ToolStripMenuItem.Click += new System.EventHandler(this.사각형ToolStripMenuItem_Click);
            // 
            // 타원ToolStripMenuItem
            // 
            this.타원ToolStripMenuItem.Name = "타원ToolStripMenuItem";
            this.타원ToolStripMenuItem.Size = new System.Drawing.Size(100, 26);
            this.타원ToolStripMenuItem.Text = "50";
            this.타원ToolStripMenuItem.Click += new System.EventHandler(this.타원ToolStripMenuItem_Click);
            // 
            // 옵션OToolStripMenuItem
            // 
            this.옵션OToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.모달MToolStripMenuItem,
            this.모달리스ToolStripMenuItem});
            this.옵션OToolStripMenuItem.Name = "옵션OToolStripMenuItem";
            this.옵션OToolStripMenuItem.Size = new System.Drawing.Size(73, 24);
            this.옵션OToolStripMenuItem.Text = "옵션(O)";
            // 
            // 모달MToolStripMenuItem
            // 
            this.모달MToolStripMenuItem.Name = "모달MToolStripMenuItem";
            this.모달MToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.모달MToolStripMenuItem.Text = "모달(&M)...";
            this.모달MToolStripMenuItem.Click += new System.EventHandler(this.모달MToolStripMenuItem_Click);
            // 
            // 모달리스ToolStripMenuItem
            // 
            this.모달리스ToolStripMenuItem.Name = "모달리스ToolStripMenuItem";
            this.모달리스ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.모달리스ToolStripMenuItem.Text = "모달리스";
            this.모달리스ToolStripMenuItem.Click += new System.EventHandler(this.모달리스ToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseClick);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseUp);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 파일FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 종료XToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 색상CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 빨간색RToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 녹색GToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 파란색BToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 색상다이얼로그ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 도형타입TToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 사각형ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 타원ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 옵션OToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 모달MToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 모달리스ToolStripMenuItem;
    }
}

