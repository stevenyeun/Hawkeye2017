using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Hawkeye_RelayServer
{
    using AuthorityComm;
    using Hawkeye_LIB;
    using System.Runtime.InteropServices;
    using ByteQueue = Queue<byte[]>;
    class Program
    {
        //제어권 클라이언트(Authority Client)의 포트들...
        //제어권클라이언트들이 여러개의 응용프로그램, 응용프로그램 하나당 포트 하나씩 할당
        //이포트들로 PTZ 서버로 온 데이터를 전송한다.
        private static int[] arrAuthorityClientRemoteUdpPort = { 30001, 30002, 30003, 30004, 30005, 30006, 30007, 30008, 30009, 30010, 30011, 30012, 30013, 30014, 30015 };
        //

        //제어권서버 포트들.....
        private static int[] arrAuthorityServerRemoteUdpPort = { 10001, 10002, 10003, 10004, 10005 };
        private const int MAX_CHANNEL = 5;

        //제어권 클라이언트로 부터 수신받은 패킷을 담는 큐 = 제어권 서버로 보낼 패킷 큐
        private static ByteQueue[] queueSendToAuthorityServer = new ByteQueue[MAX_CHANNEL];


        // = 제어권 서버로 부터 수신받은 패킷을 담는 큐 = 제어권 클라이언트로 보낼 패킷 큐
        private static ByteQueue[] queueSendToAuthorityClient = new ByteQueue[MAX_CHANNEL];//To RelayServer(AuthorityClient)



        private static void CreateUDPSocket(int nCh, int nHostPort)
        {
            UdpClient udpServer = new UdpClient(nHostPort);
            int nChIndex = nCh - 1;

            //수신스레드
            Task.Run(() =>
            {
                while (true)
                {
                    var from = new IPEndPoint(IPAddress.Any, 0);//패킷을 수신하면 보낸 놈의 IP, Port를 담을 객체
                    try
                    {
                        Console.WriteLine("UDP Host Port {0} Recv Blocking", nHostPort);
                        var recvBuffer = udpServer.Receive(ref from);

                        //제어권 클라이언트들로부터 수신받은걸 저장한다. 제어권 서버로 보내기위해서
                        Console.WriteLine("UDP Port {0} Enqueue Received Packet", nHostPort);
                        queueSendToAuthorityServer[nChIndex].Enqueue(recvBuffer);
                        string str = Encoding.UTF8.GetString(recvBuffer);

                        Console.WriteLine("UDP Host Port {0} From Port {1}, Received Length={2}byte", nHostPort, from.Port, str.Length);
                    }
                    catch (Exception e)
                    {
                        //System.Console.WriteLine(e.Message);
                        System.Console.WriteLine("UDP Receive Exception HostPort={0} " + e.Message, nHostPort);

                    }
                    Thread.Sleep(1);
                }
            });



            //송신스레드
            //Relay ------>>>> AuthorityClient
            UdpClient udpClient = new UdpClient(nHostPort+1000);//별도 소켓을 만들어서 사용
            Task.Run(() =>
            {
                while (true)
                {
                    if( queueSendToAuthorityClient[nChIndex].Count > 0)
                    //if (queueSendToAuthorityServer[nChIndex].Count > 0)//에코모드
                    {
                        Byte[] packet = queueSendToAuthorityClient[nChIndex].Dequeue();
                        //Byte[] packet = queueSendToAuthorityServer[nChIndex].Dequeue();//에코모드

                        //제어권 서버로부터 받은 패킷을 제어권 클라이언트들에게 뿌린다.
                        for (int i = 0; i < arrAuthorityClientRemoteUdpPort.Length; i++)//모든 클라이언트로 패킷을 뿌림
                        {

                            IPEndPoint remote = new IPEndPoint(IPAddress.Loopback, arrAuthorityClientRemoteUdpPort[i]);

                            try
                            {
                                System.Console.WriteLine("UDP Send RemotePort={0}", arrAuthorityClientRemoteUdpPort[i]);
                                udpClient.Send(packet, packet.Length, remote);
                            }
                            catch (Exception e)
                            {
                                System.Console.WriteLine("UDP Send Exception RemotePort={0} " + e.Message, arrAuthorityClientRemoteUdpPort[i]);
                                Thread.Sleep(5000);
                            }
                            Thread.Sleep(1);
                        }

                     
                    }
                    Thread.Sleep(1);

                }
            });

        }

        private static void CreateTCPClient(int nCh, int nRemotePort)
        {
            const string serverIpAddr = "127.0.0.1";

            TcpClient tcpClient = null;
            NetworkStream stream = null;
            try
            {
                tcpClient = new TcpClient(serverIpAddr, nRemotePort);
                stream = tcpClient.GetStream();
                System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 원격포트={1}에 접속 성공  ", nCh, nRemotePort);
            }
            catch(Exception e)
            {
                System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 원격포트={1}에 접속 실패 " + e.Message, nCh, nRemotePort);                
            }
          
          
             

            int nChIndex = nCh - 1;

            //TCP 수신 스레드
            Task.Run(() =>
            {
                while (true)
                {
                    //var from = new IPEndPoint(IPAddress.Any, 0);//패킷을 수신하면 보낸 놈의 IP, Port를 담을 객체
                    try
                    {
                        

                        AUTHORITY_PACKET AuthPacket = new AUTHORITY_PACKET();
                        int bufferSize = Marshal.SizeOf(AuthPacket);//((PACKET_DATA)obj).TotalBytes; // 구조체에 할당된 메모리의 크기를 구한다.

                        Byte[] recvBuffer = new Byte[bufferSize];

                  
                        if (stream != null)
                        {
                            Console.WriteLine("채널={0} TCP 클라이언트 소켓 원격포트={1}으로부터 오는 패킷 대기중", nCh, nRemotePort);
                            Int32 bytes = stream.Read(recvBuffer, 0, recvBuffer.Length);
                            if(bytes == 0)
                            {
                                Thread.Sleep(1000);
                            }

                            //var recvBuffer = udpServer.Receive(ref from);

                            //제어권 서버로부터 수신받은걸 저장한다. 제어권 클라이언트(릴레이 서버)로 보내기위해서
                            Console.WriteLine("From Port {0} Enqueue Received Packet", nRemotePort);
                            queueSendToAuthorityClient[nChIndex].Enqueue(recvBuffer);
                            string str = Encoding.UTF8.GetString(recvBuffer);
                            Console.WriteLine("From Port {0} Received Length={1}byte", nRemotePort, str.Length);
                        }
                        else
                        {
                            Console.WriteLine("채널={0} TCP 클라이언트 소켓 원격 포트={1}의 스트림을 가져오지 못함.", nCh, nRemotePort);
                            Thread.Sleep(5000);
                        }
                    }
                    catch (Exception e)
                    {
                        //System.Console.WriteLine(e.Message);
                        //접속종료??
                        System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 수신 스레드 Exception 원격 포트={1}" + e.Message, nCh, nRemotePort);
                        Thread.Sleep(5000);

                    }
                    Thread.Sleep(1);
                }
            });


            //TCP 송신스레드
            //to AuthorityServer(제어권서버)    
            Task.Run(() =>
                {
                    while (true)
                    {
                        if (queueSendToAuthorityServer[nChIndex].Count > 0)//에코모드
                        {
                            Byte[] packet = queueSendToAuthorityServer[nChIndex].Dequeue();//에코모드

                            try
                            {
                                //System.Console.WriteLine("TCP Send RemotePort={0}", arrAuthorityServerRemoteUdpPort[nChIndex]);
                                
                                stream.Write(packet, 0, packet.Length);
                                System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 원격 포트={1}에 패킷 전송함", nCh, nRemotePort);
                            }
                            catch (Exception e)
                            {
                                //System.Console.WriteLine("TCP Send Exception RemotePort={0} " + e.Message, arrAuthorityServerRemoteUdpPort[nChIndex]);
                                System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 송신 스레드 Exception 원격 포트={1}" + e.Message, nCh, nRemotePort);
                            }
                            Thread.Sleep(1);

                        }
                        Thread.Sleep(1);
                    }

                });





            //TCP 재 접속 스레드
            Task.Run(() =>
            {
                while (true)
                {

                    Thread.Sleep(10000);

                    bool bConnection = false;
                    if(tcpClient == null)
                    {
                        bConnection = false;
                    }
                    else
                    {
                        if (tcpClient.Connected == false)
                            bConnection = false;
                        else
                            bConnection = true;

                    }
                    if(bConnection == false)
                    {
                        //System.Console.WriteLine("채널={0} TCP 클라이언트 호스트와 연결 끊킴", nCh);

                        try
                        {
                            tcpClient = new TcpClient(serverIpAddr, nRemotePort);
                            stream = tcpClient.GetStream();
                            System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 재 접속 성공 원격 포트={1} ", nCh, nRemotePort);
                        }
                        catch (Exception e)
                        {
                            System.Console.WriteLine("채널={0} TCP 클라이언트 소켓 재 접속 실패 원격 포트={1} " + e.Message, nCh, nRemotePort);                            
                        }

                           
                    }
                    
                }

            });
        }

        private static uint message;
        private static IntPtr handle;
        static void Main(string[] args)
        {
         

            //notifyIcon1.Visible = true;
            //notifyIcon1.ShowBalloonTip(100);

            //handle = new WindowInteropHelper(this).Handle;
            IntPtr hWndConsole = Win32API.GetConsoleWindow();
            Win32API.ShowWindow(hWndConsole, Win32API.SW_MINIMIZE);

            CreateMulticastSocket();

            //message = Win32API.RegisterWindowMessage("Hawkeye_RelayServer");

            for (int i = 0; i < MAX_CHANNEL; i++)
            {
                //Win32API.PostMessage((IntPtr)Win32API.HWND_BROADCAST, message, 0, 2);
                SendMessageToLauncher("제어권 서버 채널"+(i+1).ToString()+" 생성");
                queueSendToAuthorityServer[i] = new ByteQueue();
                queueSendToAuthorityClient[i] = new ByteQueue();
                //제어권 클라이언트(Authority Client)와 연결 할 소켓 생성
                CreateUDPSocket(i + 1, 20001 + i);

                //제어권서버와 연결할 소켓 생성
                CreateTCPClient(i + 1, 10001 + i);
            }

            SendMessageToLauncher("RelayServer Mainfunction is blocked");
            //Win32API.PostMessage((IntPtr)Win32API.HWND_BROADCAST, message, 0, 1);


#if false
            Task.Run(() =>
            {
                while (true)
                {
                    Console.Clear();
                    Thread.Sleep(10000);
                }
            });
#endif






            while (true)
            {
                ConsoleKeyInfo key = Console.ReadKey();
                if(key.Key == ConsoleKey.Q)
                {
                    break;
                }
            }
           
        }

        private static UdpClient udpMulticastClient = new UdpClient();
        private static IPEndPoint remoteEP;
        private static void SendMessageToLauncher(string msg)
        {
            byte[] buffer = null;         
            buffer = Encoding.Unicode.GetBytes(msg);
            udpMulticastClient.Send(buffer, buffer.Length, remoteEP);
        }
        private static void CreateMulticastSocket()
        {           

            IPAddress multicastaddress = IPAddress.Parse("239.0.0.222");
            udpMulticastClient.JoinMulticastGroup(multicastaddress);
            remoteEP = new IPEndPoint(multicastaddress, 2222);

#if false
            byte[] buffer = null;

            Console.WriteLine("Press ENTER to start sending message");
            Console.ReadLine();

            for (int i = 0; i <= 8000; i++)
            {
                buffer = Encoding.Unicode.GetBytes(i.ToString());
                udpMulticastClient.Send(buffer, buffer.Length, remoteEP);
                Console.WriteLine("Sent : {0}", i.ToString());
            }

            buffer = Encoding.Unicode.GetBytes("quit");
            udpMulticastClient.Send(buffer, buffer.Length, remoteEP);

            udpMulticastClient.Close();

            Console.WriteLine("All Done! Press ENTER to quit.");
            Console.ReadLine();
#endif
        }
    }
}
