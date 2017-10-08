using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Hawkeye_PTZController
{
    public class UDPSocketForRelayServerComm
    {
        public UDPSocketForRelayServerComm(int nHostPort)
        {
            udpClient = new UdpClient(nHostPort);
        }

        //릴레이 서버한테 받은 패킷 
        private Queue<byte[]> queuePacketFromRelayServer = new Queue<byte[]>();

        private Queue<byte[]>[] arrQueuePacketFromRelayServer = { new Queue<byte[]>(), new Queue<byte[]>(), new Queue<byte[]>(), new Queue<byte[]>(), new Queue<byte[]>() };
        public byte[] PopPacket(int nCh)
        {
            if (arrQueuePacketFromRelayServer[nCh - 1].Count() == 0)
                return null;
            return arrQueuePacketFromRelayServer[nCh - 1].Dequeue();
        }
        public int GetNumberOfPacket(int nCh)
        {
            return arrQueuePacketFromRelayServer[nCh - 1].Count();
        }



        /*
        public int GetNumberOfPacket()
        {
            return queuePacketFromRelayServer.Count();
        }
        public byte[] PopPacket()
        {
            return queuePacketFromRelayServer.Dequeue();
        }
        */
        //public Queue<IPEndPoint> queueIPEndPointFromRelayServer = new Queue<IPEndPoint>();

        private UdpClient udpClient = null;
        public void SendToRelayServer(int nCh, byte[] packet)
        {
            int nPort = 20000 + nCh;

            IPEndPoint remote = new IPEndPoint(IPAddress.Loopback, nPort);
            udpClient.Send(packet, packet.Length, remote);
        }
        /*
        public byte[] ReceiveFromRelayServer(int nCh)
        {
            queueFromRelayServer.Dequeue();
        }
        */
        public void CreateUDPSocket()
        {
            Task.Run(() =>
            {
                while (true)
                {
                    var from = new IPEndPoint(IPAddress.Any, 0);//패킷을 수신하면 보낸 놈의 IP, Port를 담을 객체
                    try
                    {
                        Console.WriteLine("recv blocking");
                        var recvBuffer = udpClient.Receive(ref from);

                        //20001~20005
                        int nPort = from.Port;
                        int nCh = nPort - 21000;

                        arrQueuePacketFromRelayServer[nCh - 1].Enqueue(recvBuffer);

                        //릴레이서버로부터 받은 패킷
                        //채널 포드 별로 구분해서 저장해야됨!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        //queuePacketFromRelayServer.Enqueue(recvBuffer);
                        //queueIPEndPointFromRelayServer.Enqueue(from);
                        //string str = Encoding.UTF8.GetString(recvBuffer);
                        //Console.WriteLine("receive" + str.Length + " " + str);
                    }
                    catch (Exception e)
                    {
                        System.Console.WriteLine(e.Message);
                        Thread.Sleep(5000);

                    }
                    Thread.Sleep(1);
                }
            });



        }
    }
}
