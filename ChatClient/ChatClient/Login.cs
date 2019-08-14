using Data;
using Google.Protobuf;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChatClient
{
    public partial class Login : Form
    {
        private Client client = null;
        public Login()
        {
            InitializeComponent();
        }

        private void login_Click(object sender, EventArgs e)
        {
            string user_name = user_test.Text.ToString();
            string password = password_test.Text.ToString();
            if (string.IsNullOrWhiteSpace(user_name))
            {
                user_name_err.SetError(user_test, "账号不能为空");
                return;
            }

            if (string.IsNullOrWhiteSpace(password))
            {
                user_pwd_err.SetError(password_test, "密码不能为空");
                return;
            }

            if (client != null) 
            {
                client.LogOut();
                client = null;
            }
            client = new Client(user_name, password);
        }

        private void create_user_Click(object sender, EventArgs e)
        {
            string user_name = user_test.Text.ToString();
            string password = password_test.Text.ToString();

            if (string.IsNullOrWhiteSpace(user_name))
            {
                user_name_err.SetError(user_test, "账号不能为空");
                return;
            }

            if (string.IsNullOrWhiteSpace(password))
            {
                user_pwd_err.SetError(password_test, "密码不能为空");
                return;
            }
            UserCreate userCreate = new UserCreate();
            userCreate.UserName = user_name;
            userCreate.UserPwd = password;
            Global.SendData((int)MSGCMDS.CMD_CREATE, (int)CREATECMDS.CREATE, userCreate.ToByteArray());
        }
    }
}
