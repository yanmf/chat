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
    public partial class Form1 : Form
    {
        private Client client = null;
        public Form1()
        {
            InitializeComponent();
        }

        private void login_Click(object sender, EventArgs e)
        {
            string user_id = user_test.Text.ToString();
            string password = password_test.Text.ToString();
            if (client != null) 
            {
                client.LogOut();
                client = null;
            }
            client = new Client(user_id, password);
        }
    }
}
