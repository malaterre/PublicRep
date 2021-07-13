using System;
using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;

namespace _1
{
    internal sealed class SafeHandleC : SafeHandleZeroOrMinusOneIsInvalid
    {
        public SafeHandleC() : base(ownsHandle: true)
        {
        }

        protected override bool ReleaseHandle()
        {
            Program.ns_delete(handle);
            return true;
        }
    }

    class Program
    {
      private const string NativeLibraryName = "p.so.0";

        [DllImport(NativeLibraryName, CharSet = CharSet.Ansi, BestFitMapping = false, ThrowOnUnmappableChar = true, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        internal static extern SafeHandleC ns_create();
        [DllImport(NativeLibraryName, CharSet = CharSet.Ansi, BestFitMapping = false, ThrowOnUnmappableChar = true, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void ns_delete(IntPtr c);
        [DllImport(NativeLibraryName, CharSet = CharSet.Ansi, BestFitMapping = false, ThrowOnUnmappableChar = true, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        internal static extern string ns_get(SafeHandleC c);

        static void Main(string[] args)
        {
           SafeHandleC c = Program.ns_create();
           for (int i = 0; i < 5; i++)
            {
            string ts = Program.ns_get(c);
            Console.WriteLine($"{ts}");
            }
        }
    }
}
