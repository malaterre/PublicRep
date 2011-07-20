import java.io.File;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

import vtk.*;

/*
 Compilation
  javac -cp /usr/share/java/vtk.jar stringdemo.java

 Usage:
  LD_LIBRARY_PATH=/usr/lib/jni java -cp /usr/share/java/vtk.jar:. stringdemo /usr/share/VTKData/Data/beach.jpg

ref:
 https://github.com/malaterre/VTK/commit/44d3e13bc1eb6725be457b1e02d66cc0fc7787db
*/
public class stringdemo
{
  static {
    System.loadLibrary("vtkCommonJava");
    System.loadLibrary("vtkFilteringJava");
    System.loadLibrary("vtkIOJava");
  }

  public static void main(String[] args) throws IOException {
    String filename = args[0];
    String utffilename = "tête.jpg";

    // Make a copy of input file:
    InputStream in = new FileInputStream(filename);
    OutputStream out = new FileOutputStream(utffilename);
    byte[] buf = new byte[1024];
    int len;
    while ((len = in.read(buf)) > 0) {
      out.write(buf, 0, len);
    }
    in.close();
    out.close();

    vtkStringArray array = new vtkStringArray();
    array.InsertNextValue( utffilename );

    vtkJPEGReader reader = new vtkJPEGReader();
    //reader.SetFileName( filename ); // ok

    // use char* API
    //reader.SetFileName( utffilename ); // not ok

    // use vtkStdString API
    reader.SetFileNames( array ); // not ok
    reader.Update();
    System.out.println( reader.GetOutput().toString() );
    }
}
