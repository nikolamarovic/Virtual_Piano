package Projekat2;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.Rectangle;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.*;

public class CompositionGraphics extends JLayeredPane {
	private static final long serialVersionUID = 1L;
	private Composition myComposition;
	private JPanel mainPanel = new JPanel();
	public static JPanel [] oneRowComposition;
	private int x, movingIndex, index,prevIndex;
	public CompositionGraphics(Composition c) {
		setMyComposition(c);
		setBounds(0,93,1755,160);
		setBackground(Color.BLACK);
		x = 1;
		index = 0;
		prevIndex = 0;
		setVisible(true);
		addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent arg0) {}
			public void mouseEntered(MouseEvent arg0) {requestFocus();}
			public void mouseExited(MouseEvent arg0) {}
			public void mousePressed(MouseEvent arg0) {}
			public void mouseReleased(MouseEvent arg0) {}		
		});
		addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e1) {
				if (e1.getKeyCode()==39) {
					requestFocus();
					drawNotes(index);					
				}	
				if(e1.getKeyCode()==37) {
					requestFocus();
					drawNotes(prevIndex-(index-prevIndex)>0?prevIndex-=index-prevIndex:0);
				}
				if(e1.getKeyCode()==39) {
					mainPanel = new JPanel();
					mainPanel.setVisible(true);	
				}
			}		
		});
		setVisible(true);
	}
	public void removePanels() {
		for(int i=0;i<oneRowComposition.length;i++) {
			oneRowComposition[i].setVisible(false);
		}
	}
	public Composition getComposition() {return myComposition;}
	public int getMovingIndex() {return movingIndex;}
	public JPanel [] getOneRowComposition() {return oneRowComposition;}
	
	public void moveComposition(MusicSymbol s) {
		for(int cnt=0;cnt<myComposition.symbols.size();cnt++) {
			Rectangle r = oneRowComposition[cnt].getBounds();
			if(s.getDuration().imenilac == 4) {oneRowComposition[cnt].setBounds(r.x-40,r.y,r.width,r.height);}
			else {oneRowComposition[cnt].setBounds(r.x-20,r.y,r.width,r.height);}
		}	
	}
	public void drawNotesOneRow() {
		oneRowComposition  = new JPanel[myComposition.symbols.size()];
		x=0;
		for(int cnt=0;cnt<myComposition.symbols.size();cnt++) {
			MusicSymbol s = myComposition.symbols.get(cnt); 
			//PAUZE
			if(s.getType() == MusicSymbol.Type.PAUSE) {					
				JPanel panel = new JPanel();			
				if(s.getDuration().imenilac == 4) {
					panel.setBounds(x,0,40,30);
					panel.setBorder(BorderFactory.createLineBorder(Color.black));
					panel.setBackground(Color.RED);
					x+=40;
				}else {
					panel.setBackground(Color.GREEN);
					panel.setBounds(x,0,20,30);
					panel.setBorder(BorderFactory.createLineBorder(Color.black));
					x+=20;
				}
				oneRowComposition[cnt] = panel;
				add(oneRowComposition[cnt],BorderLayout.CENTER);	
				
			//AKORD
			}else if(s.getType() == MusicSymbol.Type.CHORD) {
				JPanel panel = new JPanel();	
				panel.setLayout(new GridLayout(0,1));
				if(s.getDuration().imenilac == 4) {
					panel.setBounds(x,0,40,s.getNumOfNotes()*30);
					panel.setBorder(BorderFactory.createLineBorder(Color.black));
					x+=40;
				}else {
					panel.setBounds(x,0,20,s.getNumOfNotes()*30);
					panel.setBorder(BorderFactory.createLineBorder(Color.black));
					x+=20;
				}
				for(int i=0;i<s.getNumOfNotes();i++) {
					JPanel p = new JPanel();
					p.setBorder(BorderFactory.createLineBorder(Color.black));
					if(s.getDuration().imenilac == 4) {
						p.setBackground(Color.RED);
						p.setBounds(x,i*40,40,40);
					}
					else {
						p.setBackground(Color.GREEN);
						p.setBounds(x,i*40,20,40);
					}						
					JLabel label = new JLabel(s.get(i).getTone() + (s.get(i).getSharp()?"#":"")+s.get(i).getOctave());
					p.add(label,BorderLayout.NORTH);
					panel.add(p);
				}	
				oneRowComposition[cnt] = panel;
				add(oneRowComposition[cnt],BorderLayout.CENTER);	
			}else {
				//NOTA
				JPanel panel = new JPanel();			
				if(s.getDuration().imenilac == 4) {
					panel.setBounds(x,0,40,30);
					panel.setBackground(Color.RED);
					panel.setBorder(BorderFactory.createLineBorder(Color.black));
					JLabel label = new JLabel(s.getTone() + (s.getSharp()?"#":"")+s.getOctave());
					panel.add(label);
					x+=40;
				}else {
					panel.setBackground(Color.GREEN);
					panel.setBounds(x,0,20,30);
					panel.setBorder(BorderFactory.createLineBorder(Color.black));
					JLabel label = new JLabel(s.getTone() + (s.getSharp()?"#":"")+s.getOctave());
					panel.add(label);
					x+=20;
				}
				oneRowComposition[cnt] = panel;
				add(oneRowComposition[cnt],BorderLayout.CENTER);	
				
			}
		}
		//add(oneRowComposition,BorderLayout.CENTER);
	}
	
	public void drawNotes(int prevCnt) {
		x = 0;
		mainPanel = new JPanel(); 
		mainPanel.setBounds(0,0,1750,160);
		mainPanel.setLayout(null);
		mainPanel.setVisible(true);
		System.out.println("drawNotes");
		for(int cnt=prevCnt;cnt<myComposition.symbols.size();cnt++) {			
			if(x+40<1750 && cnt<myComposition.symbols.size()) {
				MusicSymbol s = myComposition.symbols.get(cnt); 
				//PAUZE
				if(s.getType() == MusicSymbol.Type.PAUSE) {					
					JPanel panel = new JPanel();			
					if(s.getDuration().imenilac == 4) {
						panel.setBounds(x,0,40,30);
						panel.setBorder(BorderFactory.createLineBorder(Color.black));
						panel.setBackground(Color.RED);
						x+=40;
					}else {
						panel.setBackground(Color.GREEN);
						panel.setBounds(x,0,20,30);
						panel.setBorder(BorderFactory.createLineBorder(Color.black));
						x+=20;
					}
					mainPanel.add(panel,BorderLayout.CENTER);	
				//AKORD
				}else if(s.getType() == MusicSymbol.Type.CHORD) {
					JPanel panel = new JPanel();	
					panel.setLayout(new GridLayout(0,1));
					if(s.getDuration().imenilac == 4) {
						panel.setBounds(x,0,40,s.getNumOfNotes()*40);
						panel.setBorder(BorderFactory.createLineBorder(Color.black));
						x+=40;
					}else {
						panel.setBounds(x,0,20,s.getNumOfNotes()*40);
						panel.setBorder(BorderFactory.createLineBorder(Color.black));
						x+=20;
					}
					for(int i=0;i<s.getNumOfNotes();i++) {
						JPanel p = new JPanel();
						p.setBorder(BorderFactory.createLineBorder(Color.black));
						if(s.getDuration().imenilac == 4) {
							p.setBackground(Color.RED);
							p.setBounds(x,i*40,40,40);
						}
						else {
							p.setBackground(Color.GREEN);
							p.setBounds(x,i*40,20,40);
						}						
						JLabel label = new JLabel(s.get(i).getTone() + (s.get(i).getSharp()?"#":"")+s.get(i).getOctave());
						p.add(label,BorderLayout.NORTH);
						panel.add(p);
					}	
					mainPanel.add(panel,BorderLayout.CENTER);	
				}else {
					//NOTA
					JPanel panel = new JPanel();			
					if(s.getDuration().imenilac == 4) {
						panel.setBounds(x,0,40,30);
						panel.setBackground(Color.RED);
						panel.setBorder(BorderFactory.createLineBorder(Color.black));
						JLabel label = new JLabel(s.getTone() + (s.getSharp()?"#":"")+s.getOctave());
						panel.add(label);
						x+=40;
					}else {
						panel.setBackground(Color.GREEN);
						panel.setBounds(x,0,20,30);
						panel.setBorder(BorderFactory.createLineBorder(Color.black));
						JLabel label = new JLabel(s.getTone() + (s.getSharp()?"#":"")+s.getOctave());
						panel.add(label);
						x+=20;
					}
					mainPanel.add(panel,BorderLayout.CENTER);					
				}
			}else {
				add(mainPanel,BorderLayout.CENTER); 
				System.out.println(index+ " " + prevIndex);
				prevIndex = prevCnt; 
				index = cnt; 
				break;				
			}
			
			if(cnt==myComposition.symbols.size()-1) {
				JPanel line = new JPanel();
				mainPanel.add(line);
				add(mainPanel,BorderLayout.CENTER);
			}
		}
		
	}
	public Composition getMyComposition() {
		return myComposition;
	}
	public void setMyComposition(Composition myComposition) {
		this.myComposition = myComposition;
	}
}
