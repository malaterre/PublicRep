package test;

import javax.swing.*;
import javax.swing.SwingUtilities;
import java.awt.event.*;

public class MyFrame implements ActionListener
{
   private JFrame frame;
   private Transparency trans; // = new Transparency();
   private float t = 1.0f;

   public MyFrame()
   {
      frame = new JFrame("My transparent window");
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      frame.setBounds( 10, 10, 200, 200 );

      JButton button = new JButton("My button");
      button.setBounds( 20, 20, 50, 10 );
      button.addActionListener( this );

      JPanel panel = new JPanel();
      panel.add( button );

      frame.setContentPane( panel );

      //Display the window.
      frame.setVisible(true);

      trans = new Transparency();
   }


   /**
    * @param args
    */
   public static void main( String[] args )
   {
      MyFrame f = new MyFrame();
   }

   public void actionPerformed(ActionEvent e)
   {
      t -= 0.05f;
      trans.setWindowOpacity( frame, t );
   }

}
