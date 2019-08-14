namespace ChatClient
{
    partial class Login
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.user_test = new System.Windows.Forms.TextBox();
            this.password_test = new System.Windows.Forms.TextBox();
            this.create_user = new System.Windows.Forms.Button();
            this.login_b = new System.Windows.Forms.Button();
            this.label_user = new System.Windows.Forms.Label();
            this.label_password = new System.Windows.Forms.Label();
            this.user_name_err = new System.Windows.Forms.ErrorProvider(this.components);
            this.user_pwd_err = new System.Windows.Forms.ErrorProvider(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.user_name_err)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.user_pwd_err)).BeginInit();
            this.SuspendLayout();
            // 
            // user_test
            // 
            this.user_test.Location = new System.Drawing.Point(180, 156);
            this.user_test.MaxLength = 100;
            this.user_test.Name = "user_test";
            this.user_test.Size = new System.Drawing.Size(100, 21);
            this.user_test.TabIndex = 0;
            this.user_test.Text = "yanmf";
            // 
            // password_test
            // 
            this.password_test.Location = new System.Drawing.Point(180, 194);
            this.password_test.MaxLength = 6;
            this.password_test.Name = "password_test";
            this.password_test.PasswordChar = '*';
            this.password_test.ShortcutsEnabled = false;
            this.password_test.Size = new System.Drawing.Size(100, 21);
            this.password_test.TabIndex = 1;
            this.password_test.Text = "123456";
            // 
            // create_user
            // 
            this.create_user.Location = new System.Drawing.Point(317, 154);
            this.create_user.Name = "create_user";
            this.create_user.Size = new System.Drawing.Size(100, 23);
            this.create_user.TabIndex = 2;
            this.create_user.Text = "注册账号";
            this.create_user.UseVisualStyleBackColor = true;
            this.create_user.Click += new System.EventHandler(this.create_user_Click);
            // 
            // login_b
            // 
            this.login_b.Location = new System.Drawing.Point(317, 194);
            this.login_b.Name = "login_b";
            this.login_b.Size = new System.Drawing.Size(100, 23);
            this.login_b.TabIndex = 3;
            this.login_b.Text = "登录";
            this.login_b.UseVisualStyleBackColor = true;
            this.login_b.Click += new System.EventHandler(this.login_Click);
            // 
            // label_user
            // 
            this.label_user.AutoSize = true;
            this.label_user.Location = new System.Drawing.Point(133, 159);
            this.label_user.Name = "label_user";
            this.label_user.Size = new System.Drawing.Size(41, 12);
            this.label_user.TabIndex = 4;
            this.label_user.Text = "账号：";
            // 
            // label_password
            // 
            this.label_password.AutoSize = true;
            this.label_password.Font = new System.Drawing.Font("宋体", 9F);
            this.label_password.Location = new System.Drawing.Point(133, 199);
            this.label_password.Name = "label_password";
            this.label_password.Size = new System.Drawing.Size(41, 12);
            this.label_password.TabIndex = 5;
            this.label_password.Text = "密码：";
            // 
            // user_name_err
            // 
            this.user_name_err.ContainerControl = this;
            // 
            // user_pwd_err
            // 
            this.user_pwd_err.ContainerControl = this;
            // 
            // Login
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(651, 449);
            this.Controls.Add(this.label_password);
            this.Controls.Add(this.label_user);
            this.Controls.Add(this.login_b);
            this.Controls.Add(this.create_user);
            this.Controls.Add(this.password_test);
            this.Controls.Add(this.user_test);
            this.Name = "Login";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.user_name_err)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.user_pwd_err)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox user_test;
        private System.Windows.Forms.TextBox password_test;
        private System.Windows.Forms.Button create_user;
        private System.Windows.Forms.Button login_b;
        private System.Windows.Forms.Label label_user;
        private System.Windows.Forms.Label label_password;
        private System.Windows.Forms.ErrorProvider user_name_err;
        private System.Windows.Forms.ErrorProvider user_pwd_err;
    }
}

