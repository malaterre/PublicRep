//#include <windows.h>
#include <jawt_md.h>
#include <jawt.h>
#include <jni.h>

// Don't mangle names for the JVM
extern "C" {

#if 0
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                                 )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#endif

/**
 * Gets the window handle for the Java window.
 * Procedure for obtaining the handle:
 *   1. Get the structure (JAWT) that contains the native methods. 
 *   2. Get the drawing surface (JAWT_DrawingSurface).
 *   3. Using the drawing surface, get the drawing surface info (JAWT_DrawingSurfaceInfo).
 *   4. Get the drawing info that's specific to Win32 (JAWT_Win32DrawingSurfaceInfo).
 *   5. Using the drawing surface info, get the hwnd.
 */
/*
 * Class:     test_Transparency
 * Method:    getWindowHandle
 * Signature: (Ljava/awt/Component;)J
 */
JNIEXPORT jlong JNICALL Java_test_Transparency_getWindowHandle
  (JNIEnv * env, jclass cls, jobject component)
{
   JAWT awt;
   JAWT_DrawingSurface* ds;
   JAWT_DrawingSurfaceInfo* dsi;
//   JAWT_Win32DrawingSurfaceInfo* dsi_win;
   JAWT_X11DrawingSurfaceInfo* dsi_win;
   jint dsLock;
   jboolean result = JNI_FALSE;

   // Get the AWT
   awt.version = JAWT_VERSION_1_4;
   result = JAWT_GetAWT(env, &awt);


   if ( result == JNI_FALSE )
   {
      printf( "%s:%i -  JAWT_GetAWT() failed.\n", __FILE__, __LINE__ );
      return 0;
   }

   // Get the drawing surface
   ds = awt.GetDrawingSurface(env, component);

   if ( ds == NULL )
   {
      printf( "%s:%i -  GetDrawingSurface() failed.\n", __FILE__, __LINE__ );
      return 0;
   }

   dsLock = ds->Lock(ds);

   // Get the drawing surface info
   dsi = ds->GetDrawingSurfaceInfo(ds);


   // Get the platform-specific drawing info
   //dsi_win = (JAWT_Win32DrawingSurfaceInfo*)dsi->platformInfo;
   dsi_win = (JAWT_X11DrawingSurfaceInfo*)dsi->platformInfo;


   //HWND handle = dsi_win->hwnd;
  int handle = 0;

   ds->FreeDrawingSurfaceInfo(dsi);
   ds->Unlock(ds);
   awt.FreeDrawingSurface(ds);

   return (jlong)handle;
}

void printLastError()
{
#if 0
    LPTSTR pszMessage;
    DWORD dwLastError = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dwLastError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&pszMessage,
        0, NULL );

    // Display the error message
    wprintf(L"failed with error %d: %s\n", dwLastError, pszMessage);

    LocalFree(pszMessage);
#endif

}

/*
 * Class:     test_Transparency
 * Method:    setTransparency
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_test_Transparency_setTransparency
  (JNIEnv * env, jclass cls, jlong windowHandle, jfloat alpha)
{
#if 0
   HWND hwnd = (HWND)windowHandle;

   // Get the current window style
   LONG currentStyle = GetWindowLong(hwnd, GWL_EXSTYLE);


   if ( currentStyle == 0 )
   {
      printf( "Error calling GetWindowLong() ");
      printLastError();

   }

   if ( alpha == 0 )
   {
      // No transparency.
      // Remove WS_EX_LAYERED from this window style
      SetWindowLong(hwnd, GWL_EXSTYLE, currentStyle & ~WS_EX_LAYERED);
   }
   else
   {
      // Calculate the transparency value. Should be in the range 0-255
      unsigned char transparency = (unsigned char)(255 * alpha);

      // Set window style to WS_EX_LAYERED. This is required for windows to be transparent.
      SetWindowLong(hwnd, GWL_EXSTYLE, currentStyle | WS_EX_LAYERED );

      // set the transparency level
      SetLayeredWindowAttributes(hwnd, 0, transparency, LWA_ALPHA);
   }
#endif
}


} // extern "C"
