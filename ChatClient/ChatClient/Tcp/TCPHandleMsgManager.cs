using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatClient
{
    enum MSGCMDS
    {
        CMD_LOGIN       =       0x100,//登录
        CMD_CREATE      =       0x200,//注册
        CMD_CHAT        =       0x300,//聊天
        CMD_FRIEND      =       0x400,//好友
    }
    public class TCPHandleMsgManager
    {
        /// <summary>
        /// 消息回调
        /// </summary>
        /// <param name="cmd"></param>
        public delegate bool TCPHandleMsgDelegate(int nID, byte[] data, int count);

        private static Dictionary<int, TCPHandleMsgDelegate> TCPHandleMsgDelegateDict = new Dictionary<int, TCPHandleMsgDelegate>();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="nID"></param>
        /// <param name="data"></param>
        /// <param name="count"></param>
        /// <returns></returns>
        public static bool HandleMsg(int nID, byte[] data, int count)
        {
            TCPHandleMsgDelegate msgDelegate = FindMsgDelegate(nID & 0xff00);
            if (msgDelegate == null)
            {
                //未注册得时间
                return false;
            }

            return msgDelegate(nID & 0x00ff, data, count);
        }

        public static TCPHandleMsgDelegate FindMsgDelegate(int nID)
        {
            TCPHandleMsgDelegate tryMsgDelegate;
            if (!TCPHandleMsgDelegateDict.TryGetValue(nID, out tryMsgDelegate))
            {
                return null;
            }
            return tryMsgDelegate;
        }

        /// <summary>
        /// 
        /// </summary>
        public static void AddMsgDelegate(int nID, TCPHandleMsgDelegate msgDelegate)
        {
            TCPHandleMsgDelegate tryMsgDelegate;
            if (!TCPHandleMsgDelegateDict.TryGetValue(nID, out tryMsgDelegate))
            {
                TCPHandleMsgDelegateDict.Add(nID, msgDelegate);
            }
            else
            {
                tryMsgDelegate += msgDelegate;
            }
        }
    }
}
