//#include <windows.h>
#include <jawt_md.h>
#include <jawt.h>
#include <jni.h>

#include "vtkRenderWindow.h"
#include "vtkJavaUtil.h"

#undef VTK_JAVA_DEBUG

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

  extern "C" {int vtkXError(Display *display, XErrorEvent *err)
  {
  char errorText[1024];
  XGetErrorText( display, err->error_code, errorText, sizeof(errorText) );
  printf( "**********************************\n" );
  printf( "X Error: %s\n", errorText );
  printf( "**********************************\n" );

  // cause a segfault
//    *(float *)(0x01) = 1.0;
    return 1;
  }}

JNIEXPORT jint  JNICALL 
Java_vtk2_vtkJPanel_RenderCreate(JNIEnv *env, jobject canvas, jobject id0)
{
    printf("Coucou\n");
#if defined(WIN32_JAWT_LOCK_HACK)
  int hash;
  WJLH_HASH_FUNC(env, canvas, hash);
  WJLH_lock_map[hash] = 0;
#endif

  JAWT awt;
  JAWT_DrawingSurface* ds;
  JAWT_DrawingSurfaceInfo* dsi;
  jint lock;

  // get the render window pointer
  vtkRenderWindow *temp0;
  temp0 = (vtkRenderWindow *)(vtkJavaGetPointerFromObject(env,id0));
  
  /* Get the AWT */
  awt.version = JAWT_VERSION_1_3;
  if (JAWT_GetAWT(env, &awt) == JNI_FALSE) 
    {
#ifndef VTK_JAVA_DEBUG
    printf("AWT Not found\n");
#endif
    return 1;
    }
  
  /* Get the drawing surface */
  ds = awt.GetDrawingSurface(env, canvas);
  if (ds == NULL) 
    {
#ifndef VTK_JAVA_DEBUG
    printf("NULL drawing surface\n");
#endif
    return 1;
    }
  
  /* Lock the drawing surface */
  lock = ds->Lock(ds);
  if((lock & JAWT_LOCK_ERROR) != 0) 
    {
#ifndef VTK_JAVA_DEBUG
    printf("Error locking surface\n");
#endif
    awt.FreeDrawingSurface(ds);
    return 1;
    }

  /* Get the drawing surface info */
  dsi = ds->GetDrawingSurfaceInfo(ds);
  if (dsi == NULL) 
    {
    printf("Error getting surface info\n");
    ds->Unlock(ds);
    awt.FreeDrawingSurface(ds);
    return 1;
    }
  
// Here is the win32 drawing code
#if defined(_WIN32) || defined(WIN32)
  temp0->Finalize();
  JAWT_Win32DrawingSurfaceInfo* dsi_win;
  dsi_win = (JAWT_Win32DrawingSurfaceInfo*)dsi->platformInfo;
  temp0->SetWindowId((void *)dsi_win->hwnd);
  temp0->SetDisplayId((void *)dsi_win->hdc);
  // also set parent id to avoid border sizes being added
  temp0->SetParentId((void *)dsi_win->hdc);
// use mac code
#elif defined(__APPLE__)
  JAWT_MacOSXDrawingSurfaceInfo* dsi_mac;
  dsi_mac = (JAWT_MacOSXDrawingSurfaceInfo*)dsi->platformInfo;
  temp0->SetWindowId(dsi_mac->cocoaViewRef);
// otherwise use X11 code
#else
  JAWT_X11DrawingSurfaceInfo* dsi_x11;
  dsi_x11 = (JAWT_X11DrawingSurfaceInfo*)dsi->platformInfo;
  temp0->SetDisplayId((void *)dsi_x11->display);
//  temp0->SetWindowId((void *)dsi_x11->drawable);
//  temp0->SetParentId((void *)dsi_x11->display);

//  temp0->SetWindowId((void *)dsi_x11->display);
//  temp0->SetDisplayId(temp0->GetGenericDisplayId());
//    if (dsi_x11->display)
//      {
//        XSynchronize(dsi_x11->display,1);
//      }
//     XSetErrorHandler(vtkXError);

#endif
  
  /* Free the drawing surface info */
  ds->FreeDrawingSurfaceInfo(dsi);
  
  /* Unlock the drawing surface */
  ds->Unlock(ds);
  
  /* Free the drawing surface */
  awt.FreeDrawingSurface(ds);

#if defined(WIN32_JAWT_LOCK_HACK)
if (WJLH_init_check == 0)
{
  WJLH_init_check = 1;
}
  WJLH_lock_map[hash] = 1;
#endif
  return 0;

}

JNIEXPORT jint  JNICALL 
Java_vtk2_vtkJPanel_Lock(JNIEnv *env, 
                       jobject canvas)
{
  JAWT awt;
  JAWT_DrawingSurface* ds;
  jint lock;

  /* Get the AWT */
  awt.version = JAWT_VERSION_1_3;
  if (JAWT_GetAWT(env, &awt) == JNI_FALSE) 
    {
#ifndef VTK_JAVA_DEBUG
    printf("AWT Not found\n");
#endif
    return 1;
    }
  
  /* Get the drawing surface */
  ds = awt.GetDrawingSurface(env, canvas);
  if (ds == NULL) 
    {
#ifndef VTK_JAVA_DEBUG
    printf("NULL drawing surface\n");
#endif
    return 1;
    }

#if defined(WIN32_JAWT_LOCK_HACK)
  int hash;
  WJLH_HASH_FUNC(env, canvas, hash);
  if (WJLH_init_check && WJLH_lock_map[hash] > WJLH_MAX_COUNT)
  {
    env->MonitorEnter(canvas);      
  }
  else
  {
#endif
  /* Lock the drawing surface */
  lock = ds->Lock(ds);
  if((lock & JAWT_LOCK_ERROR) != 0) 
    {
#ifndef VTK_JAVA_DEBUG
    printf("Error locking surface\n");
#endif
    awt.FreeDrawingSurface(ds);
    return 1;
    }
#if defined(WIN32_JAWT_LOCK_HACK)
  }
#endif

  return 0;
}

JNIEXPORT jint  JNICALL 
Java_vtk2_vtkJPanel_UnLock(JNIEnv *env, 
                         jobject canvas)
{
  JAWT awt;
  JAWT_DrawingSurface* ds;

  /* Get the AWT */
  awt.version = JAWT_VERSION_1_3;
  if (JAWT_GetAWT(env, &awt) == JNI_FALSE) 
    {
#ifndef VTK_JAVA_DEBUG
    printf("AWT Not found\n");
#endif
    return 1;
    }
  
  /* Get the drawing surface */
  ds = awt.GetDrawingSurface(env, canvas);
  if (ds == NULL) 
    {
#ifndef VTK_JAVA_DEBUG
    printf("NULL drawing surface\n");
#endif
    return 1;
    }

#if defined(WIN32_JAWT_LOCK_HACK)
  int hash;
  WJLH_HASH_FUNC(env, canvas, hash);
  if (WJLH_init_check && WJLH_lock_map[hash] > WJLH_MAX_COUNT)
  {
    env->MonitorExit(canvas);
  }
  else
  {
    if (WJLH_init_check) WJLH_lock_map[hash]++;
#endif
  /* Unlock the drawing surface */
  ds->Unlock(ds);
#if defined(WIN32_JAWT_LOCK_HACK)
  }
#endif
  
  /* Free the drawing surface */
  awt.FreeDrawingSurface(ds);

  return 0;
}

} // extern "C"
