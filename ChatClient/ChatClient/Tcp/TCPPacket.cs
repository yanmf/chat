using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ChatClient.Tcp
{
    public class TCPPacket
    {
        public const int RECV_MAX_SIZE = 65535;
        public TCPPacket()
        {
            PacketBytes = new byte[RECV_MAX_SIZE];
        }
        ~TCPPacket()
        {

        }

        /// <summary>
        /// 保存接收到的数据包
        /// </summary>
        private byte[] PacketBytes = null;

        /// <summary>
        /// 获取接收缓存的指针
        /// </summary>
        /// <returns></returns>
        public byte[] GetPacketBytes()
        {
            return PacketBytes;
        }


        /// <summary>
        /// 接收到的数据包的命令ID
        /// </summary>
        private Int32 _PacketCmdID = 0;

        /// <summary>
        /// 接收到的数据包的命令ID属性
        /// </summary>
        public Int32 PacketCmdID
        {
            get
            {
                Int32 ret = 0;
                lock (this)
                {
                    ret = _PacketCmdID;
                }
                return ret;
            }
        }

        /// <summary>
        /// 接收到的数据包的命令数据长度
        /// </summary>
        private Int32 _PacketDataSize = 0;

        /// <summary>
        /// 接收到的数据包的命令数据长度属性
        /// </summary>
        public Int32 PacketDataSize
        {
            get
            {
                Int32 ret = 0;
                lock (this)
                {
                    ret = _PacketDataSize;
                }
                return ret;
            }
        }

        /// <summary>
        /// 已经接收到的命令的数据长度
        /// </summary>
        private Int32 PacketDataHaveSize = 0;

        /// <summary>
        /// 是否正在等待数据
        /// </summary>
        private bool IsWaitingData = false;

        /// <summary>
        /// 释放函数
        /// </summary>
        public void Dispose()
        {
            Reset();
        }

        /// <summary>
        /// 命令头缓冲
        /// </summary>
        private byte[] CmdHeaderBuffer = new byte[6];

        /// <summary>
        /// 已经接收到的命令头的大小
        /// </summary>
        private int CmdHeaderSize = 0;

        /// <summary>
        /// 将收到的数据写入
        /// </summary>
        /// <param name="buffer">收到的数据缓存</param>
        /// <param name="offset">从字节偏移处拷贝</param>
        /// <param name="count">写入的长度</param>
        public bool WriteData(byte[] buffer, int offset, int count)
        {
            //先锁定，否则字节流的顺序未必会是正确的顺序
            lock (this)
            {
                //一定要在系统设计时避免大的命令包，过长的数据拆分成小指令包发送
                //这个缓冲一定要避免越界, 各个分系统之间一定要设计好指定包的最大长度

                //1.首先判断当前是否正在等待数据
                if (IsWaitingData)
                {
                    int copyCount = (count >= (_PacketDataSize - PacketDataHaveSize)) ? _PacketDataSize - PacketDataHaveSize : count;
                    if (copyCount > 0)
                    {
                        CopyBytes(PacketBytes, PacketDataHaveSize, buffer, offset, copyCount);
                        PacketDataHaveSize += (Int32)copyCount;
                    }

                    //判断命令包的数据是否接收完毕, 否则继续等待
                    if (PacketDataHaveSize >= _PacketDataSize)
                    {
                        bool eventReturn = true;

                        //通知外部事件处理
                        eventReturn = TCPHandleMsgManager.HandleMsg(this.PacketCmdID, this.GetPacketBytes(), this.PacketDataSize);

                        //清空当前的状态
                        _PacketCmdID = 0;
                        _PacketDataSize = 0;
                        PacketDataHaveSize = 0;
                        IsWaitingData = false;
                        CmdHeaderSize = 0;

                        if (!eventReturn) //处理失败，要求关闭连接
                        {
                            //return false;//消息类型太多没注册，暂时屏蔽掉这个错误。
                        }

                        //处理剩余的字节
                        if (count > copyCount)
                        {
                            //改变参数
                            offset += copyCount;
                            count -= copyCount;

                            //接收数据(递归实现, 简单)
                            return WriteData(buffer, offset, count);
                        }
                    }

                    return true;
                }
                else
                {
                    //正在等待接收命令头
                    int copyLeftSize = count > (8 - CmdHeaderSize) ? (8 - CmdHeaderSize) : count;
                    CopyBytes(CmdHeaderBuffer, CmdHeaderSize, buffer, offset, copyLeftSize);
                    CmdHeaderSize += copyLeftSize;
                    if (CmdHeaderSize < 8)
                    {
                        return true; //继续等待
                    }

                    //首先读取4个字节的整数
                    _PacketDataSize = BitConverter.ToInt32(CmdHeaderBuffer, 0);

                    //再读取2个字节的指令
                    _PacketCmdID = BitConverter.ToInt32(CmdHeaderBuffer, 4);

                    if (_PacketDataSize <= 0 || _PacketDataSize >= RECV_MAX_SIZE)
                    {
                        //throw new Exception(string.Format("接收到的非法数据长度的tcp命令, Cmd={0}, Length={1} , 需要立即和服务器端断开!", (TCPGameServerCmds)_PacketCmdID, _PacketDataSize));
                        //LogManager.WriteLog(LogTypes.Error, string.Format("接收到的非法数据长度的tcp命令, Cmd={0}, Length={1}, offset={2}, count={3}", (TCPGameServerCmds)_PacketCmdID, _PacketDataSize, offset, count));
                        return false;
                    }

                    //增加偏移
                    offset += copyLeftSize;

                    //减少拷贝量
                    count -= copyLeftSize;

                    //等待数据中...
                    IsWaitingData = true;

                    //接收的字节归0
                    PacketDataHaveSize = 0;
                    _PacketDataSize -= 2; //减去命令的长度

                    //接收数据(递归实现, 简单)
                    return WriteData(buffer, offset, count);
                }
            }
        }

        /// <summary>
        /// 为不同的连接重复使用
        /// </summary>
        public void Reset()
        {
            lock (this)
            {
                _PacketCmdID = 0;
                _PacketDataSize = 0;
                PacketDataHaveSize = 0;
                IsWaitingData = false;
                CmdHeaderSize = 0;
            }
        }

        /// <summary>
        /// 字节数据拷贝
        /// </summary>
        /// <param name="copyTo">目标字节数组</param>
        /// <param name="offsetTo">目标字节数组的拷贝偏移量</param>
        /// <param name="copyFrom">源字节数组</param>
        /// <param name="offsetFrom">源字节数组的拷贝偏移量</param>
        /// <param name="count">拷贝的字节个数</param>
        public static void CopyBytes(byte[] copyTo, int offsetTo, byte[] copyFrom, int offsetFrom, int count)
        {
            /*for (int i = 0; i < count; i++)
            {
                copyTo[offsetTo + i] = copyFrom[offsetFrom + i];
            }*/
            Array.Copy(copyFrom, offsetFrom, copyTo, offsetTo, count);
        }
    }
}
