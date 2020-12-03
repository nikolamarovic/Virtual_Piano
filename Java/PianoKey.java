package Projekat2;

import java.awt.Color;
import java.awt.Font;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JButton;
import javax.swing.SwingConstants;


class MidiStartEnd{
	private int midi;
	private long start,end;
	public MidiStartEnd(int x,long y, long z) {
		this.midi = x;
		this.start = y;
		this.end = z;
	}
	public int getMidi() {return midi;}
	public long getStart() {return start;}
	public void setEnd(int end) {this.end = end;}
	public long getEnd() {return end;}
	public String toString() {
		return midi+"["+start+","+end+"]";
	}
}
class KeyStartEnd{
	private String key;
	private long start,end;
	public KeyStartEnd(String x,long y, long z) {
		this.key = x;
		this.start = y;
		this.end = z;
	}
	public String getKey() {return key;}
	public void setEnd(int end) {this.end = end;}
	public long getStart() {return start;}
	public long getEnd() {return end;}
	public String toString() {
		return key+"["+start+","+end+"]";
	}
}


public class PianoKey extends JButton {

	private static final long serialVersionUID = 1L;
	private String description;
	private boolean isWhite;
	public static int index = 0;
	private long startCounter, endCounter;
	private int dx;
	private MidiPlayer myPlayer;
	private Checker checker;
	public PianoKey(String description,boolean isWhite,int dx, MidiPlayer player) {
		super(description);
		this.description = description;
		this.isWhite = isWhite;
		this.myPlayer = player;
		setVerticalAlignment(SwingConstants.BOTTOM);
		setFont(new Font("Tahoma",Font.BOLD,10));
		setBackground(isWhite?Color.WHITE:Color.BLACK);
		if(isWhite)setBounds(dx,1,50,161);
		else{
			setBounds(dx,1,30,120);
			setForeground(Color.WHITE);
			setBorder(null);
		}
		addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent arg0) {
				myPlayer.play(Composition.toneSharpOctaveMap.get(description));	
				PianoGraphics.buttonsMap.get(description).setBackground(Color.LIGHT_GRAY);
				if(checker!=null) checker.addSymbol(description);
				startCounter = System.currentTimeMillis()-MainGraphics.startTime;
			}
			@Override
			public void mouseReleased(MouseEvent arg0) {
				myPlayer.release(Composition.toneSharpOctaveMap.get(description));
				PianoGraphics.buttonsMap.get(description).setBackground((isWhite?Color.WHITE:Color.BLACK));
				endCounter = System.currentTimeMillis()-MainGraphics.startTime;
				PianoGraphics.playedNotesMidi.add(new MidiStartEnd(Composition.toneSharpOctaveMap.get(description),startCounter,endCounter));
				PianoGraphics.playedNotesKey.add(new KeyStartEnd(Composition.noteToKey.get(description),startCounter,endCounter));
			}
			public void mouseEntered(MouseEvent arg2) { }
		});
		
		addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e1) {playNote(e1);}
			@Override
			public void keyReleased(KeyEvent e2) {releaseNote(e2);}		
		});
	}
	
	public void playNote(String tmpS,int tmp, int dur) throws InterruptedException {
		PianoGraphics.buttonsMap.get(tmpS).requestFocus();
		PianoGraphics.buttonsMap.get(tmpS).setBackground(Color.lightGray);
		if(dur!=0)myPlayer.play(tmp,dur);
		
		PianoGraphics.buttonsMap.get(tmpS).requestFocus();
		PianoGraphics.buttonsMap.get(tmpS).setBackground((isWhite?Color.WHITE:Color.BLACK));
	}
	public void releaseNote(String tmpS,int tmp) {
		PianoGraphics.buttonsMap.get(tmpS).requestFocus();
		PianoGraphics.buttonsMap.get(tmpS).setBackground((isWhite?Color.WHITE:Color.BLACK));
		myPlayer.release(tmp);
		
	}
	public void setChecker(Checker c) {
		this.checker = c;
	}
	public void playNote(KeyEvent e) {	
		String s = "" + e.getKeyChar();
		if(Composition.toneMap.containsKey(s)) {
			ToneMap tmpMap = Composition.toneMap.get(s);
			String tmpS = tmpMap.tone +  (tmpMap.sharp?"#":"") + tmpMap.octave;
			if(checker!=null)checker.addSymbol(tmpS);
			PianoGraphics.buttonsMap.get(tmpS).requestFocus();
			PianoGraphics.buttonsMap.get(tmpS).setBackground(Color.lightGray);
			Integer tmp = Composition.toneMap.get(s).midi;
			if(tmp!=null) myPlayer.play(tmp);
			startCounter = System.currentTimeMillis() - MainGraphics.startTime;
					}
	}
	public void releaseNote(KeyEvent e) {
		String s = "" + e.getKeyChar();
		if(Composition.toneMap.containsKey(s)){
			ToneMap tmpMap = Composition.toneMap.get(s);
			String tmpS = tmpMap.tone +  (tmpMap.sharp?"#":"") + tmpMap.octave;
			PianoGraphics.buttonsMap.get(tmpS).requestFocus();
			PianoGraphics.buttonsMap.get(tmpS).setBackground((isWhite?Color.WHITE:Color.BLACK));
			Integer tmp = Composition.toneMap.get(s).midi;
			if(tmp!=null) {myPlayer.release(tmp);}
			endCounter = System.currentTimeMillis() - MainGraphics.startTime;
			PianoGraphics.playedNotesMidi.add(new MidiStartEnd(tmp,startCounter,endCounter));
			PianoGraphics.playedNotesKey.add(new KeyStartEnd(s,startCounter,endCounter));
		}
	}
	public String getDescription() {return description;}
	public void setDescription(String description) {this.description = description;}
	public boolean isWhite() {return isWhite;}
	public void setWhite(boolean isWhite) {this.isWhite = isWhite;}
	public int getDx() {return dx;}
	public void setDx(int dx) {this.dx = dx;}
	public MidiPlayer getPlayer() {return myPlayer;}
	public void setPlayer(MidiPlayer player) {this.myPlayer = player;}
}
