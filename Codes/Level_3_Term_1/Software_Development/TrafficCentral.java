
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class TrafficCentral 
{
	//YOU CAN ADD NEW MEMBERS

   public void green() 
   {
	  //WRITE YOUR CODES HERE
   }

   public void yellow()
   {
	   //WRITE YOUR CODES HERE	
   }
   
   public void red()
   {
	   //WRITE YOUR CODES HERE;
   }
   
   public void manual()
   {
        flag=false;
        jButtonR.setEnabled(flag);
        jButtonG.setEnabled(flag);
        jButtonY.setEnabled(flag);
        jButtonM.setText("Auto");

	   //WRITE YOUR CODES HERE
   }
   
   public void auto()
   {
        flag=true;
        jButtonR.setEnabled(flag);
        jButtonG.setEnabled(flag);
        jButtonY.setEnabled(flag);
        jButtonM.setText("Manual");

	   //WRITE YOUR CODES HERE
   }

	JFrame jFrame;
	JButton jButtonR, jButtonG, jButtonY;
    JButton jButtonM;
    boolean flag=true;
	
		
   public TrafficCentral()
   {	   
		jFrame = new JFrame("Traffic Alert Input");
		jFrame.setResizable(false);
		jFrame.setSize(200, 280);
		
		JPanel panel = new JPanel();
		jFrame.add(panel);		
		
		panel.setLayout(null);

		JLabel userLabel = new JLabel("Traffic Control");
		userLabel.setBounds(10, 10, 300, 25);
		panel.add(userLabel);


		jButtonG = new JButton("Green");
		jButtonG.setBounds(10, 80, 160, 25);
		jButtonG.addActionListener(new GreenLightButtonListener());
		panel.add(jButtonG);
		

		jButtonR = new JButton("Red");
		jButtonR.setBounds(10, 120, 160, 25);
		jButtonR.addActionListener(new RedLightButtonListener());
		panel.add(jButtonR);
		
        jButtonY = new JButton("Yellow");
		jButtonY.setBounds(10, 160, 160, 25);
		jButtonY.addActionListener(new YellowLightButtonListener());
		panel.add(jButtonY);
                
        jButtonM = new JButton("Manual");
		jButtonM.setBounds(10, 200, 160, 25);
		jButtonM.addActionListener(new UpdateModeButtonListener());
		panel.add(jButtonM);

	
		jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jFrame.setVisible(true);
   }
   
   class GreenLightButtonListener implements ActionListener 
   {
		@Override
		public void actionPerformed(ActionEvent e) 
		{
			green();
		}
   }

   class YellowLightButtonListener implements ActionListener 
   {
		@Override
		public void actionPerformed(ActionEvent e) 
		{
			yellow();
		}
   }
   
   class RedLightButtonListener implements ActionListener 
   {
		@Override
		public void actionPerformed(ActionEvent e) 
		{
			red();
		}
   }
   
   class UpdateModeButtonListener implements ActionListener 
   {
		@Override
		public void actionPerformed(ActionEvent e) 
		{
			if (flag)
                        {
                            manual();
                        }
                        else
                        {
                            auto();
                        }
                        System.out.println("flag: "+flag);
                        
                        
		}
   }
   
   public static void main(String[] args) {
	   new TrafficCentral();
   }
}