import javax.swing.JFrame;
import javax.swing.JLabel;

public class Window
{
	JFrame jFrame;
	JLabel jLabel;	
	public Window(String title)
	{
		// TODO Auto-generated constructor stub
		jFrame = new JFrame(title);
		jLabel = new JLabel("HELLO");
		jFrame.setResizable(false);
		jFrame.setSize(300, 150);
		jFrame.add(jLabel);
		jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jFrame.setVisible(true);
	}
	
	
	
	public void updateText(String str)
	{
		jLabel.setText(str);
	}
	
	/**
	 * For Testing
	 * @param args
	 */
	/*public static void main(String[] args)
	{
		Window w = new Window("DEMO");
		w.updateText("HELLO BACK");
	}*/
}
