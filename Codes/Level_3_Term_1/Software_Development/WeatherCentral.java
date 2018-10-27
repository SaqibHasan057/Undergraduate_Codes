import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class WeatherCentral 
{
   private int temperature;


   public void updateCentralTemperature(int temp) {
      this.temperature = temp;
   }


	JFrame jFrame;
	JButton jButton;
	JTextField jTextField;
		
   public WeatherCentral()
   {
	   // TODO Auto-generated constructor stub
		jFrame = new JFrame("Weather Central");
		jFrame.setResizable(false);
		jFrame.setSize(200, 150);
		
		JPanel panel = new JPanel();
		jFrame.add(panel);		
		
		panel.setLayout(null);

		JLabel userLabel = new JLabel("Enter Temperature in Kelvin");
		userLabel.setBounds(10, 10, 300, 25);
		panel.add(userLabel);

		 jTextField = new JTextField(20);
		 jTextField.setBounds(10, 40, 160, 25);
		panel.add(jTextField);

		jButton = new JButton("Submit");
		jButton.setBounds(40, 80, 80, 25);
		jButton.addActionListener(new ButtonListener());
		panel.add(jButton);
		
		jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jFrame.setVisible(true);
   }
   
   class ButtonListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) 
		{
			String input = jTextField.getText();
			//if(input!=null)
			//	System.out.println(input);
			try
			{
				updateCentralTemperature(Integer.parseInt(input));
				System.out.println("Central Temperature Updated to: "+input);
			}
			catch(Exception ex){;}
			//JOptionPane.showMessageDialog(null, "login button has been pressed");
		}
	}
   

}