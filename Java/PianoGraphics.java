package Projekat2;

import java.util.ArrayList;
import java.util.HashMap;


import javax.sound.midi.MetaMessage;
import javax.sound.midi.MidiEvent;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Sequence;
import javax.sound.midi.ShortMessage;
import javax.sound.midi.SysexMessage;
import javax.sound.midi.Track;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

public class PianoGraphics extends JLayeredPane {
	private static final long serialVersionUID = 1L;
	public static ArrayList<MidiStartEnd> playedNotesMidi = new ArrayList<MidiStartEnd>();
	public static ArrayList<KeyStartEnd> playedNotesKey = new ArrayList<KeyStartEnd>();
	
	public static PianoKey [] buttons = new PianoKey[60];
	public int index;
	public static HashMap<String,PianoKey> buttonsMap = new HashMap<String,PianoKey>();
	public PianoGraphics() throws MidiUnavailableException {
		
		setBounds(0,252,1751,163);
		JLayeredPane layeredPane = new JLayeredPane();
		index = 0;
		int x = 1;
		MidiPlayer player = new MidiPlayer();

		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(1,0));
		panel.setBounds(0,0,1750,162);//panel za dirke
		
		for(int i=36;i<=95;i++) {
			String stringToMatch = Composition.midiToToneMap.get(i);
			if(!stringToMatch.contains("#")) {
				buttons[index]= new PianoKey(stringToMatch,true,x,player);
				buttonsMap.put(stringToMatch,buttons[index]);			
				layeredPane.add(buttons[index],new Integer(1));
				index++;
				x+=50;
			}else {			
				buttons[index] = new PianoKey(stringToMatch,false,x-15,player);
				buttonsMap.put(stringToMatch,buttons[index]);						
				layeredPane.add(buttons[index],new Integer(2));
				index++;
			}			
		}
		
		panel.add(layeredPane,BorderLayout.CENTER);
		add(panel,BorderLayout.CENTER);
		addMouseListener(new MouseAdapter() {
			public void mouseEntered(MouseEvent e) {
				requestFocus();
			}
		});
		setVisible(true);
	}
	public static void setChecker(Checker c) {
		for(int i=0;i<60;i++) {
			buttons[i].setChecker(c);
		}
	}
	public void exportToTxt(String name, ArrayList<KeyStartEnd> playedNotesKey) throws FileNotFoundException, UnsupportedEncodingException {
		PrintWriter writer = new PrintWriter(name, "UTF-8");
		/*for(String s:playedNotesKey) {
			writer.print(s);
			writer.print(s);
		}
		*/
		writer.close();
	}
	
	public void exportCompositionToTxt(String name, ArrayList<MusicSymbol> symbols) throws FileNotFoundException, UnsupportedEncodingException {
		PrintWriter writer = new PrintWriter(name, "UTF-8");
		int index = 0;
		while(index < symbols.size()) {
			MusicSymbol tmp = symbols.get(index);
			if(tmp.getType()==MusicSymbol.Type.PAUSE) {
				if(tmp.getDuration().imenilac == 8) writer.print(" ");
				else writer.print("|");
				index++;
			}else if(tmp.getType()==MusicSymbol.Type.CHORD) {
				writer.print("[");
				for(int i=0;i<tmp.getNumOfNotes();i++) {
					String desc  = tmp.get(i).getTone()+(tmp.get(i).getSharp()?"#":"") + tmp.get(i).getOctave();
					writer.print(Composition.noteToKey.get(desc));
					index++;
					tmp = symbols.get(index);
				}
				writer.print("]");
			}else {
				if(tmp.getDuration().imenilac==8) {
					writer.print("[");
					while(index < symbols.size() && tmp.getDuration().imenilac == 8 && tmp.getType() == MusicSymbol.Type.NOTE) {
						String desc  = tmp.getTone()+(tmp.getSharp()?"#":"") + tmp.getOctave();
						writer.print(Composition.noteToKey.get(desc));
						if(index+1 > symbols.size()-1) {
						
						}else if(symbols.get(index+1).getType() != MusicSymbol.Type.NOTE || symbols.get(index+1).getDuration().imenilac == 4){
							if(index+1==symbols.size()-1) writer.print(" ");
						}else {
							writer.print(" ");
						}
						
						index++;
						if(index<symbols.size()) tmp = symbols.get(index);
					}
					writer.print("]");
				}else {
					String desc  = tmp.getTone()+(tmp.getSharp()?"#":"") + tmp.getOctave();
					writer.print(Composition.noteToKey.get(desc));
					index++;
				}
			}
		}
		writer.close();
	}
	public void exportCompositionToMidi(String midiname, ArrayList<MusicSymbol> symbols) {
		try {
			Sequence s = new Sequence(javax.sound.midi.Sequence.PPQ,24);
			Track t = s.createTrack();
			
			
			byte[] b = {(byte)0xF0, 0x7E, 0x7F, 0x09, 0x01, (byte)0xF7};
			SysexMessage sm = new SysexMessage();
			sm.setMessage(b, 6);
			MidiEvent me = new MidiEvent(sm,(long)0);
			t.add(me);
		
			MetaMessage mt = new MetaMessage();
	        byte[] bt = {0x02, (byte)0x00, 0x00};
			mt.setMessage(0x51 ,bt, 3);
			me = new MidiEvent(mt,(long)0);
			t.add(me);
			
			mt = new MetaMessage();
			String TrackName = new String("midifile track");
			mt.setMessage(0x03 ,TrackName.getBytes(), TrackName.length());
			me = new MidiEvent(mt,(long)0);
			t.add(me);
			ShortMessage mm = new ShortMessage();
			mm.setMessage(0xB0, 0x7D,0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);
			
			mm = new ShortMessage();
			mm.setMessage(0xB0, 0x7F,0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);
			
			mm = new ShortMessage();
			mm.setMessage(0xC0, 0x00, 0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);			
			long timeToPlay = 0;
			for(MusicSymbol tmp:symbols) {
				if(tmp.getType()==MusicSymbol.Type.PAUSE) {
					if(tmp.getDuration().imenilac == 4) timeToPlay+=60;
					else timeToPlay+=30;
				}else if(tmp.getType()==MusicSymbol.Type.CHORD) {
					long old = ++timeToPlay;
					if(tmp.getDuration().imenilac == 4) timeToPlay+=60;
					else timeToPlay+=30;
					for(int i=0;i<tmp.getNumOfNotes();i++) {
						mm = new ShortMessage();
						mm.setMessage(144,tmp.get(i).getMidi(),0x60);
						me = new MidiEvent(mm,(long)old);
						t.add(me);
						mm = new ShortMessage();
						mm.setMessage(128,tmp.get(i).getMidi(),0x40);
						me = new MidiEvent(mm,(long)timeToPlay);
						t.add(me);
					}
				}else {
					mm = new ShortMessage();
					mm.setMessage(144,tmp.getMidi(),0x60);
					timeToPlay++;
					me = new MidiEvent(mm,(long)timeToPlay);
					t.add(me);
					mm = new ShortMessage();
					mm.setMessage(128,tmp.getMidi(),0x40);
					if(tmp.getDuration().imenilac == 4) timeToPlay+=60;
					else timeToPlay+=30;
					me = new MidiEvent(mm,(long)timeToPlay);
					t.add(me);
				}
			}
			mt = new MetaMessage();
	        byte[] bet = {}; // empty array
			mt.setMessage(0x2F,bet,0);
			me = new MidiEvent(mt, (long)140);
			t.add(me);
			
			File f = new File(midiname);
			MidiSystem.write(s,1,f);
		}
		catch(Exception e) { System.out.println("Greska u midi eksportu.");}
	}
	
	
	public void exportToMidi(String midiname, ArrayList<MidiStartEnd> playedNotes) {
		try {
			Sequence s = new Sequence(javax.sound.midi.Sequence.PPQ,24);
			Track t = s.createTrack();
			
			
			byte[] b = {(byte)0xF0, 0x7E, 0x7F, 0x09, 0x01, (byte)0xF7};
			SysexMessage sm = new SysexMessage();
			sm.setMessage(b, 6);
			MidiEvent me = new MidiEvent(sm,(long)0);
			t.add(me);
		
			MetaMessage mt = new MetaMessage();
	        byte[] bt = {0x02, (byte)0x00, 0x00};
			mt.setMessage(0x51 ,bt, 3);
			me = new MidiEvent(mt,(long)0);
			t.add(me);
			
			mt = new MetaMessage();
			String TrackName = new String("midifile track");
			mt.setMessage(0x03 ,TrackName.getBytes(), TrackName.length());
			me = new MidiEvent(mt,(long)0);
			t.add(me);
			ShortMessage mm = new ShortMessage();
			mm.setMessage(0xB0, 0x7D,0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);
			
			mm = new ShortMessage();
			mm.setMessage(0xB0, 0x7F,0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);
			
			mm = new ShortMessage();
			mm.setMessage(0xC0, 0x00, 0x00);
			me = new MidiEvent(mm,(long)0);
			t.add(me);
			//note start
			//long timeToPlay = 0;
			/*
			for(int cnt:playedNotes) {
				mm = new ShortMessage();
				mm.setMessage(144,cnt,0x60);
				timeToPlay++;
				me = new MidiEvent(mm,(long)timeToPlay);
				t.add(me);
				mm = new ShortMessage();
				mm.setMessage(128,cnt,0x40);
				timeToPlay+=30;
				me = new MidiEvent(mm,(long)timeToPlay);
				t.add(me);
			
			//note end
			}
			*/
			mt = new MetaMessage();
	        byte[] bet = {}; // empty array
			mt.setMessage(0x2F,bet,0);
			me = new MidiEvent(mt, (long)140);
			t.add(me);
			
			File f = new File(midiname);
			MidiSystem.write(s,1,f);
		}
		catch(Exception e) { System.out.println("Greska u midi eksportu.");}
	}
	public void checkButtons() {
		for(int i=0;i<60;i++) {
			System.out.println(buttonsMap.get(buttons[i].getDescription()).getDescription());			
		}
	}
	
}
