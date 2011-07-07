import demo.*;
import java.io.*;

/*
 * usage:
 * mkdir /tmp/yeeha
 * LD_LIBRARY_PATH=.:/usr/lib/jvm/java-6-openjdk/jre/lib/amd64/xawt/ CLASSPATH=demo.jar:. java testdemo /tmp/yeeha
 */

public class testdemo
{
  public static void process(File file)
    {
    String path = file.getPath();
    myfile mf = new myfile();
    boolean res = mf.open( path );
    }

  public static void visitAllFiles(File dir)
    {
    if (dir.isDirectory())
      {
      String[] children = dir.list();
      for (int i=0; i<children.length; i++)
        {
        visitAllFiles(new File(dir, children[i]));
        }
      }
    else
      {
      process(dir);
      }
    }

  public static void createNewEmptyFile(String dir)
    {
    File file = new File( dir, "tête.txt");
    boolean b = false;
    try
      {
      b = file.createNewFile();
      }
    catch(IOException e)
      {
      System.out.println("Error createNewFile:" + e);
      }
    }

  public static void main(String[] args) throws Exception
    {
    String directory = args[0];

    createNewEmptyFile(directory);

    File dir = new File(directory);
    visitAllFiles(dir);
    }
}
