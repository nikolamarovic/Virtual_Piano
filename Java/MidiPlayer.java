package Projekat2;

import java.awt.Color;

import javax.sound.midi.MidiChannel;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Synthesizer;

public class MidiPlayer extends Thread {
	private static final int DEFAULT_INSTRUMENT = 1;
	private boolean working = false;
	private int startCounter = 0;
	private CompositionGraphics composition;
	public MidiPlayer(CompositionGraphics c) throws MidiUnavailableException {
		this(DEFAULT_INSTRUMENT); 	
		setComposition(c);
	}
	public void setComposition(CompositionGraphics c) {composition = c;}
	
	private MidiChannel channel; 
	
	public MidiPlayer() throws MidiUnavailableException {
		this(DEFAULT_INSTRUMENT); 	
	}
	public MidiPlayer(int instrument) throws MidiUnavailableException {channel = getChannel(instrument);}
	
	public void play(final int note) { channel.noteOn(note, 50); }
	
	public void release(final int note) { channel.noteOff(note, 50);}
	
	public void play(final int note, final long length) throws InterruptedException {
		play(note);
		Thread.sleep(length);
		release(note);
	}
	
	private static MidiChannel getChannel(int instrument) throws MidiUnavailableException {
		Synthesizer synthesizer = MidiSystem.getSynthesizer();
		synthesizer.open(); return synthesizer.getChannels()[instrument];
	}
	
	public void run() {	
		try {
			while(!isInterrupted()) {
				synchronized(this) {
					while(working == false) {
						synchronized(this) {
							wait();
						}
					}
				}
				composition.drawNotesOneRow();
				int counter = 0;
				for(MusicSymbol s:composition.getComposition().symbols) {
						if(!working) {composition.removePanels();break;}
						try {
							if(s.getType() == MusicSymbol.Type.PAUSE) {
								if(s.getDuration().imenilac==4) {Thread.sleep(240);}
								else {Thread.sleep(120);}
							}else if(s.getType() == MusicSymbol.Type.CHORD) {
								int dur;
								if(s.get(0).getDuration().imenilac == 8){dur = 120;}
								else {dur = 240;}
								for(int i=0;i<s.getNumOfNotes();i++) {	
									String tmpS = s.get(i).getTone()+(s.get(i).getSharp()?"#":"") + s.get(i).getOctave();
									PianoGraphics.buttonsMap.get(tmpS).requestFocus();
									PianoGraphics.buttonsMap.get(tmpS).setBackground(Color.RED);
									play(s.get(i).getMidi());		
								}
								Thread.sleep(dur);
								for(int i=0;i<s.getNumOfNotes();i++) {
									String tmpS = s.get(i).getTone()+(s.get(i).getSharp()?"#":"") + s.get(i).getOctave();
									PianoGraphics.buttonsMap.get(tmpS).requestFocus();
									PianoGraphics.buttonsMap.get(tmpS).setBackground((PianoGraphics.buttonsMap.get(tmpS).isWhite()?Color.WHITE:Color.BLACK));
									release(s.get(i).getMidi());
								}
							}else {
								int dur;
								if(s.getDuration().imenilac==8) {dur = 120;}
								else {dur = 240;}
								String tmpS = s.getTone() + (s.getSharp()?"#":"") + s.getOctave();
								PianoGraphics.buttonsMap.get(tmpS).requestFocus();
								PianoGraphics.buttonsMap.get(tmpS).setBackground(Color.RED);
								play(s.getMidi(),dur);	
								PianoGraphics.buttonsMap.get(tmpS).requestFocus();
								PianoGraphics.buttonsMap.get(tmpS).setBackground((PianoGraphics.buttonsMap.get(tmpS).isWhite()?Color.WHITE:Color.BLACK));
							}
							composition.moveComposition(s);
						}catch (InterruptedException e) { }
						counter++;
				}
				if(counter == composition.getComposition().symbols.size()-1) stopPermanently();
			}
		}catch(InterruptedException e) { }
		
	}	
	public void drawComposition() {
		composition.drawNotesOneRow();
		
	}
	public void startPlaying() {
		synchronized(this) {
			working = true;
			notify();
		}
		if(startCounter==0) {start();}
		startCounter++;
	}
	public void stopTemporary() {setWorking(false);}
	public void stopPermanently() {interrupt();}
	public boolean isWorking() {return working;}
	public void setWorking(boolean working) {this.working = working;}

}