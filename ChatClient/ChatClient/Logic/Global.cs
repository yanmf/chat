using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatClient
{
    public class Global
    {
        #region 网络相关
        public static bool SendData(TCPOutPacket tcpOutPacket)
        {
            return Program.tcpClient.SendData(tcpOutPacket);
        }
        public static bool SendData(int nID, int cmd, byte[] data)
        {
            return Program.tcpClient.SendData(TCPOutPacket.MakeTCPOutPacket(nID, cmd, data));
        }
        #endregion

        #region 日志
        private static string _ExceptionPath = AppDomain.CurrentDomain.BaseDirectory + @"Exception/";
        public static void WriteExceptionEx(string msg, Exception ex = null)
        {
            string exMsg = "";
            if (ex != null)
            {
                exMsg = ex.ToString();
            }
            try
            {
                if (!System.IO.Directory.Exists(_ExceptionPath))
                {
                    System.IO.Directory.CreateDirectory(_ExceptionPath);
                }
                StreamWriter sw = File.CreateText(_ExceptionPath + DateTime.Now.ToString("yyyyMMddHHmmssffff") + ".log");
                sw.WriteLine(msg + "\r\n" + exMsg);
                sw.Close();
                sw = null;
            }
            catch
            {

            }
        }
        #endregion
    }
}
