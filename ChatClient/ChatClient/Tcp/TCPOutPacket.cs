using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ChatClient
{
    public class TCPOutPacket
    {
        const int TCP_MSG_SIZE = 9;
        private byte[] _PacketBytes = null;
        private int _nID = 0x0000;
        private int _PacketSize = 0;
        public TCPOutPacket(int nID, int cmd, byte[] data)
        {
            _nID = nID | cmd;
            _PacketSize = TCP_MSG_SIZE;
            if (data != null)
            {
                _PacketSize += data.Length;
            }
            _PacketBytes = new byte[_PacketSize];
            Array.Copy(data, 0, _PacketBytes, 8, data.Length);

            Final();
        }
        private void Final()
        {
            Array.Copy(BitConverter.GetBytes(_PacketSize), 0, _PacketBytes, 0, 4);
            Array.Copy(BitConverter.GetBytes(_nID), 0, _PacketBytes, 4, 4);
        }
        public byte[] GetPacketBytes()
        {
            return _PacketBytes;
        }
        public static TCPOutPacket MakeTCPOutPacket(int nID, int cmd, byte[] data)
        {
            //TCPOutPacket tcpOutPacket = new TCPOutPacket(nID, cmd, data);
            //return tcpOutPacket;
            return new TCPOutPacket(nID, cmd, data);
        }
    }
}
