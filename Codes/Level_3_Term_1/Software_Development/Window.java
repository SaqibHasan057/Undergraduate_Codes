import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.*;
import java.awt.*;

public class Window
{
	private JFrame jFrame;
	private JLabel jLabel;	
	public Window(String title)
	{
		// TODO Auto-generated constructor stub
		jFrame = new JFrame(title);
		jLabel = new JLabel("HELLO");
		jFrame.setResizable(false);
		jFrame.setSize(300, 150);
		jFrame.add(jLabel);
//		jFrame.setDefaultCloseOperation(JFrame);
		jFrame.setVisible(true);
	}
	
	
	
	public void updateText(String str)
	{
		jLabel.setText(str);
	}
	
        public void updateColor(Color color)
	{
            Container c = jFrame.getContentPane();
            c.setBackground(color);
	}
        
}
