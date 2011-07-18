import demo.*;
import java.io.*;

/*
 * usage:
 * LD_LIBRARY_PATH=. java -cp demo.jar:. testdemo 
 */

public class testdemo
{
  public static void main(String[] args) throws Exception
    {
{
    myenum2 e = new myenum2();
    if( e.equals( myenum2.TheType.THE_END ) )
      {
      System.out.println( "THE_END" );
      }
    else
      {
      System.out.println( "not THE_END" );
      }
}
{
    myenum2 e = new myenum2( myenum2.TheType.FOO4 );
    if( e.equals( myenum2.TheType.FOO4 ) )
      {
      System.out.println( "FOO4" );
      }
    else
      {
      System.out.println( "not FOO4" );
      }
}
    }
}
