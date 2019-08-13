using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ChatClient.Tcp
{
    public class TCPClientManager
    {
        private Thread _ReceiveThread;
        private TCPPacket _TCPPacket;
        private string _IP;
        private int _Port;
        private Socket _Socket;


        public TCPClientManager(string ip, int port)
        {
            _IP = ip;
            _Port = port;
            _TCPPacket = new TCPPacket();
        }
        ~TCPClientManager()
        {
            Close();
        }

        public void InitTcpClient()
        {
            Connect();
            CreateReceiveThread();
        }

        public void Close()
        {
            _ReceiveThread.Abort();
            _Socket.Close();
            _Socket = null;
        }

        static void StartReceive(Object obj)
        {
            TCPClientManager tcpClient = obj as TCPClientManager;
            byte[] recBytes = new byte[TCPPacket.RECV_MAX_SIZE];
            while (true)
            {
                try
                {
                    if (tcpClient._Socket == null)
                    {
                        continue;
                    }
                    int byteSize = tcpClient._Socket.Receive(recBytes, recBytes.Length, 0);
                    if (byteSize <= 0)
                    {
                        continue;
                    }
                    tcpClient._TCPPacket.WriteData(recBytes, 0, byteSize);
                }
                catch (Exception ex)
                {
                    
                }
            }
        }

        private void CreateReceiveThread()
        {
            _ReceiveThread = new Thread(StartReceive);

            _ReceiveThread.Start(this);
        }
        private void Connect()
        {
            if (_Socket != null) 
            {
                Close();
            }
            IPAddress ip = IPAddress.Parse(_IP);
            IPEndPoint ipe = new IPEndPoint(ip, _Port);

            _Socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _Socket.Connect(ipe);
        }


    }
}
