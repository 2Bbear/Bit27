namespace _0417_FormClient
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.파일ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.서버연결ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.서버연결해제ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.프로그램종료ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.기능ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.회원가입ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.로그인ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.회원탈퇴ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.로그아웃ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.회원정보수정ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.전체회원리스트얻기ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.파일ToolStripMenuItem,
            this.기능ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(7, 2, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(538, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 파일ToolStripMenuItem
            // 
            this.파일ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.서버연결ToolStripMenuItem,
            this.서버연결해제ToolStripMenuItem,
            this.toolStripMenuItem1,
            this.프로그램종료ToolStripMenuItem});
            this.파일ToolStripMenuItem.Name = "파일ToolStripMenuItem";
            this.파일ToolStripMenuItem.Size = new System.Drawing.Size(51, 24);
            this.파일ToolStripMenuItem.Text = "파일";
            // 
            // 서버연결ToolStripMenuItem
            // 
            this.서버연결ToolStripMenuItem.Name = "서버연결ToolStripMenuItem";
            this.서버연결ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.서버연결ToolStripMenuItem.Text = "서버연결...";
            this.서버연결ToolStripMenuItem.Click += new System.EventHandler(this.서버연결ToolStripMenuItem_Click);
            // 
            // 서버연결해제ToolStripMenuItem
            // 
            this.서버연결해제ToolStripMenuItem.Enabled = false;
            this.서버연결해제ToolStripMenuItem.Name = "서버연결해제ToolStripMenuItem";
            this.서버연결해제ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.서버연결해제ToolStripMenuItem.Text = "서버연결해제";
            this.서버연결해제ToolStripMenuItem.Click += new System.EventHandler(this.서버연결해제ToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(213, 6);
            // 
            // 프로그램종료ToolStripMenuItem
            // 
            this.프로그램종료ToolStripMenuItem.Name = "프로그램종료ToolStripMenuItem";
            this.프로그램종료ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.프로그램종료ToolStripMenuItem.Text = "프로그램종료";
            this.프로그램종료ToolStripMenuItem.Click += new System.EventHandler(this.프로그램종료ToolStripMenuItem_Click);
            // 
            // 기능ToolStripMenuItem
            // 
            this.기능ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.회원가입ToolStripMenuItem,
            this.회원탈퇴ToolStripMenuItem,
            this.회원정보수정ToolStripMenuItem,
            this.로그인ToolStripMenuItem,
            this.로그아웃ToolStripMenuItem,
            this.전체회원리스트얻기ToolStripMenuItem});
            this.기능ToolStripMenuItem.Name = "기능ToolStripMenuItem";
            this.기능ToolStripMenuItem.Size = new System.Drawing.Size(51, 24);
            this.기능ToolStripMenuItem.Text = "기능";
            // 
            // 회원가입ToolStripMenuItem
            // 
            this.회원가입ToolStripMenuItem.Name = "회원가입ToolStripMenuItem";
            this.회원가입ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.회원가입ToolStripMenuItem.Text = "회원가입...";
            this.회원가입ToolStripMenuItem.Click += new System.EventHandler(this.회원가입ToolStripMenuItem_Click);
            // 
            // 로그인ToolStripMenuItem
            // 
            this.로그인ToolStripMenuItem.Name = "로그인ToolStripMenuItem";
            this.로그인ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.로그인ToolStripMenuItem.Text = "로그인...";
            this.로그인ToolStripMenuItem.Click += new System.EventHandler(this.로그인ToolStripMenuItem_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(15, 71);
            this.textBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox1.Size = new System.Drawing.Size(508, 362);
            this.textBox1.TabIndex = 1;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(15, 448);
            this.textBox2.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(409, 25);
            this.textBox2.TabIndex = 2;
            // 
            // button1
            // 
            this.button1.Enabled = false;
            this.button1.Location = new System.Drawing.Point(438, 448);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(86, 29);
            this.button1.TabIndex = 3;
            this.button1.Text = "전송";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // 회원탈퇴ToolStripMenuItem
            // 
            this.회원탈퇴ToolStripMenuItem.Enabled = false;
            this.회원탈퇴ToolStripMenuItem.Name = "회원탈퇴ToolStripMenuItem";
            this.회원탈퇴ToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.회원탈퇴ToolStripMenuItem.Text = "회원탈퇴";
            this.회원탈퇴ToolStripMenuItem.Click += new System.EventHandler(this.회원탈퇴ToolStripMenuItem_Click);
            // 
            // 로그아웃ToolStripMenuItem
            // 
            this.로그아웃ToolStripMenuItem.Enabled = false;
            this.로그아웃ToolStripMenuItem.Name = "로그아웃ToolStripMenuItem";
            this.로그아웃ToolStripMenuItem.Size = new System.Drawing.Size(229, 26);
            this.로그아웃ToolStripMenuItem.Text = "로그아웃";
            // 
            // 회원정보수정ToolStripMenuItem
            // 
            this.회원정보수정ToolStripMenuItem.Enabled = false;
            this.회원정보수정ToolStripMenuItem.Name = "회원정보수정ToolStripMenuItem";
            this.회원정보수정ToolStripMenuItem.Size = new System.Drawing.Size(229, 26);
            this.회원정보수정ToolStripMenuItem.Text = "회원정보 수정";
            this.회원정보수정ToolStripMenuItem.Click += new System.EventHandler(this.회원정보수정ToolStripMenuItem_Click);
            // 
            // 전체회원리스트얻기ToolStripMenuItem
            // 
            this.전체회원리스트얻기ToolStripMenuItem.Name = "전체회원리스트얻기ToolStripMenuItem";
            this.전체회원리스트얻기ToolStripMenuItem.Size = new System.Drawing.Size(229, 26);
            this.전체회원리스트얻기ToolStripMenuItem.Text = "전체 회원 리스트얻기";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(538, 489);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 파일ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 서버연결ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 서버연결해제ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 프로그램종료ToolStripMenuItem;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ToolStripMenuItem 기능ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 회원가입ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 로그인ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 회원탈퇴ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 회원정보수정ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 로그아웃ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 전체회원리스트얻기ToolStripMenuItem;
    }
}

