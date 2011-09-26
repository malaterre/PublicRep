package test;

import java.awt.Window;
import java.awt.Component;

public class Transparency
{
   static boolean libLoaded = false;
   /**
    * Sets the transparency for a window.
    * @param hwnd Handle for the window.
    * @param opacity Transparency level, from 0.0 to 1.0.
    * 1.0 is completely transparent. 0.0 is completely opaque.
    */
   private static native void setTransparency( long hwnd, float opacity );

   /**
    * Get the window handle for the component.
    * @param component
    * @return HWND value obtained from the OS.
    */
   private static native long getWindowHandle( Component component );

   static
   {
      try
      {
         System.loadLibrary("transJNI");
         libLoaded = true;
      }
      catch ( Exception e )
      {
         e.printStackTrace();
         libLoaded = false;
      }
   }

   /**
    * @param window The window whose opacity will be adjusted.
    * @param opacity The opacity level, from 0.0 (opaque) to 1.0 (completely transparent).
    */
   public void setWindowOpacity(Window window, float opacity)
   {
      if ( !libLoaded )
      {
         return;
      }

      if ( !window.isVisible() )
      {
         return;
      }
      long hwnd = getWindowHandle( window );
      setTransparency(hwnd, opacity);

   }

}
