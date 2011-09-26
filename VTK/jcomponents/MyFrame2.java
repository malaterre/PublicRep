import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import vtk.*;
import vtk2.*;

public class MyFrame2 extends JPanel {

  public MyFrame2() {
    setLayout(new BorderLayout());
    // Create the buttons.
    vtkJPanel renWin = new vtkJPanel();
    add(renWin, BorderLayout.CENTER);
    vtkConeSource cone = new vtkConeSource();
    cone.SetResolution(8);
    vtkPolyDataMapper coneMapper = new vtkPolyDataMapper();
    coneMapper.SetInput(cone.GetOutput());
        
    vtkActor coneActor = new vtkActor();
    coneActor.SetMapper(coneMapper);
        
    renWin.GetRenderer().AddActor(coneActor);
    //AxesActor aa = new AxesActor(renWin.GetRenderer());
    //renWin.GetRenderer().AddActor(aa);
  }


  public static void main(String s[]) 
  {
    MyFrame2 panel = new MyFrame2();
    MyFrame2 panel2 = new MyFrame2();
	
    JFrame frame = new JFrame("VTK Canvas Test");
    frame.getContentPane().setLayout(new GridLayout(2,1));
    frame.addWindowListener(new WindowAdapter() 
      {
        public void windowClosing(WindowEvent e) {System.exit(0);}
      });
    frame.getContentPane().add(panel);
    frame.getContentPane().add(panel2);
    frame.pack();
    frame.setBounds(100, 100, 500, 500);
    frame.setVisible(true);
  }
}

