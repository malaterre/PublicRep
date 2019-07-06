using System.IO;
using demo;


/*
 * usage:
 * mkdir yeeha
 * LD_LIBRARY_PATH=. CLASSPATH=demo.jar:. java testdemo yeeha
 */

public class testdemo
{
	/*
  public static void process(File file)
    {
    string path = file.getPath();
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
    */

  public static void createNewEmptyFile(string dir)
    {
    System.IO.File.Create(@"tête.txt");
    /*
    boolean b = false;
    try
      {
      b = file.createNewFile();
      }
    catch(IOException e)
      {
System.Console.WriteLine( "Error createNewFile:" + e);
      }
      */
    }

  public static int Main(string[] args)
    {
    string directory = args[0];

    createNewEmptyFile(directory);

//    File dir = new File(directory);
//    visitAllFiles(dir);
    return 0;
    }
}
