using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatClient.Tcp
{
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
            TCPHandleMsgDelegate msgDelegate = FindMsgDelegate(nID);
            if (msgDelegate == null)
            {
                //未注册得时间
                return false;
            }

            return msgDelegate(nID, data, count);
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
