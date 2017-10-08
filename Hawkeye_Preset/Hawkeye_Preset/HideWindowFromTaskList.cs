﻿/*
 * Original code by Franci Penov, found in:
 *   http://stackoverflow.com/questions/357076/best-way-to-hide-a-window-from-the-alt-tab-program-switcher
 *   
 * Changes:
 *   2.Dec.2009: 
 *      Changed to work with class extension by Jari Pennanen.
 *      Added Deactivate minimize functionality.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Interop;
using System.Runtime.InteropServices;

namespace Ownskit.Applications.DrawAnywhere.Utils
{
    /// <summary>
    /// Window extension that allows to hide the window from task list.
    /// </summary>
    public static class WindowHideFromTaskListExt
    {
        /// <summary>
        /// Hide this window from task list (ALT+TAB).
        /// 
        /// <remarks>Works only if called before Loaded event of window.</remarks>
        /// </summary>
        /// <param name="window"></param>
        public static void HideFromTaskList(this Window window) {
            //window.Deactivated += new EventHandler(delegate(object sender, EventArgs e) {
            //    window.Hide();
            //});

            window.ShowInTaskbar = false;

            window.Loaded += new RoutedEventHandler(delegate(object sender, RoutedEventArgs e) {
                WindowInteropHelper wndHelper = new WindowInteropHelper(window);

                int exStyle = (int)GetWindowLong(wndHelper.Handle, (int)GetWindowLongFields.GWL_EXSTYLE);
                exStyle |= (int)ExtendedWindowStyles.WS_EX_TOOLWINDOW;

                SetWindowLong(wndHelper.Handle, (int)GetWindowLongFields.GWL_EXSTYLE, (IntPtr)exStyle);
            });

        }
        public static void HideFromTaskList2(this Window window)
        {
            //window.Deactivated += new EventHandler(delegate(object sender, EventArgs e) {
            //    window.Hide();
            //});

            window.ShowInTaskbar = false;

            window.Loaded += new RoutedEventHandler(delegate (object sender, RoutedEventArgs e) {
                WindowInteropHelper wndHelper = new WindowInteropHelper(window);

                int exStyle = (int)GetWindowLong(wndHelper.Handle, (int)GetWindowLongFields.GWL_EXSTYLE);
                exStyle |= (int)ExtendedWindowStyles.WS_EX_TOOLWINDOW;

                SetWindowLong(wndHelper.Handle, (int)GetWindowLongFields.GWL_EXSTYLE, (IntPtr)exStyle);
            });

        }

        #region Window styles
        [Flags]
        private enum ExtendedWindowStyles
        {
            // ...
            WS_EX_TOOLWINDOW = 0x00000080,
            // ...
        }

        private enum GetWindowLongFields
        {
            // ...
            GWL_EXSTYLE = (-20),
            // ...
        }

        [DllImport("user32.dll")]
        private static extern IntPtr GetWindowLong(IntPtr hWnd, int nIndex);

        private static IntPtr SetWindowLong(IntPtr hWnd, int nIndex, IntPtr dwNewLong) {
            int error = 0;
            IntPtr result = IntPtr.Zero;
            // Win32 SetWindowLong doesn't clear error on success
            SetLastError(0);

            if (IntPtr.Size == 4) {
                // use SetWindowLong
                Int32 tempResult = IntSetWindowLong(hWnd, nIndex, IntPtrToInt32(dwNewLong));
                error = Marshal.GetLastWin32Error();
                result = new IntPtr(tempResult);
            } else {
                // use SetWindowLongPtr
                result = IntSetWindowLongPtr(hWnd, nIndex, dwNewLong);
                error = Marshal.GetLastWin32Error();
            }

            if ((result == IntPtr.Zero) && (error != 0)) {
                throw new System.ComponentModel.Win32Exception(error);
            }

            return result;
        }

        [DllImport("user32.dll", EntryPoint = "SetWindowLongPtr", SetLastError = true)]
        private static extern IntPtr IntSetWindowLongPtr(IntPtr hWnd, int nIndex, IntPtr dwNewLong);

        [DllImport("user32.dll", EntryPoint = "SetWindowLong", SetLastError = true)]
        private static extern Int32 IntSetWindowLong(IntPtr hWnd, int nIndex, Int32 dwNewLong);

        private static int IntPtrToInt32(IntPtr intPtr) {
            return unchecked((int)intPtr.ToInt64());
        }

        [DllImport("kernel32.dll", EntryPoint = "SetLastError")]
        private static extern void SetLastError(int dwErrorCode);
        #endregion
    }
}
