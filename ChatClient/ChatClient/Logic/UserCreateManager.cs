using Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChatClient
{
    enum CREATECMDS
    {
        CREATE      =       0x01,
    }

    public class UserCreateManager
    {
        private static UserCreateManager instance = new UserCreateManager();
        public static UserCreateManager getInstance()
        {
            return instance;
        }
        public void Init()
        {

        }

        private UserCreateManager()
        {
            TCPHandleMsgManager.AddMsgDelegate((int)MSGCMDS.CMD_CREATE, TCPHandleMsgDelegate);
        }

        /// <summary>
        /// 消息回调
        /// </summary>
        /// <param name="cmd"></param>
        public bool TCPHandleMsgDelegate(int nID, byte[] data, int count)
        {
            switch (nID)
            {
                case (int)CREATECMDS.CREATE:
                    UserCreateRep userCreate = UserCreateRep.Parser.ParseFrom(data, 0, count);
                    if (userCreate != null)
                    {
                        return HandleCreateCmd(userCreate);
                    }
                    break;
            }
            return false;
        }

        private bool HandleCreateCmd(UserCreateRep userCreate)
        {
            string msg = "";
            if (userCreate.ErrCode != 1)
            {
                //处理飘字
                return true;
            }
            MessageBox.Show("欢迎你！");

            return true;
        }
    }
}
