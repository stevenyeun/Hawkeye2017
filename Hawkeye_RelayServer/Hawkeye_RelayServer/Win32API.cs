using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Hawkeye_LIB
{
    static public class Win32API
    {
        public const int WM_COPYDATA = 0x4A;
        public const Int32 SW_MINIMIZE = 6;


        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr SendMessage(IntPtr hWnd, uint Msg, uint wParam, ref COPYDATASTRUCT lParam);
        
        public const uint HWND_BROADCAST = 0xffff;

        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        public static extern uint RegisterWindowMessage(string lpString);

        [DllImport("user32.dll", CharSet = CharSet.Unicode)]
        public static extern bool PostMessage(IntPtr hWnd, uint Msg, uint wParam, uint lParam);

        [DllImport("Kernel32.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true)]
        public static extern IntPtr GetConsoleWindow();

        [DllImport("User32.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool ShowWindow([In] IntPtr hWnd, [In] Int32 nCmdShow);

        public struct COPYDATASTRUCT
        {
            public IntPtr dwData;
            public int cbData;
            [MarshalAs(UnmanagedType.LPStr)]
            public string lpData;
        }

    }




}
