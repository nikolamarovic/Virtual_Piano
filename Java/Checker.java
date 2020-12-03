package Projekat2;

import java.util.ArrayList;

public class Checker extends Thread{
	private boolean working = false;
	private int startCounter = 0;
	public static CompositionGraphics composition;
	public static ArrayList<String> playedSymbols = new ArrayList<String>();
	private ArrayList<MusicSymbol> symbolsToPlay;
	public Checker(CompositionGraphics c, ArrayList<MusicSymbol> a) {
		this.symbolsToPlay = a;
		Checker.composition = c;
	}
	public void run() {
		try {
			while(!isInterrupted()) {
				synchronized(this){
					while(!working) {
						wait();
					}
				}
				int index = 0;
				while(index < symbolsToPlay.size()) {
					MusicSymbol s = symbolsToPlay.get(index);
					playedSymbols.removeAll(playedSymbols);
					
					if(s.getDuration().imenilac == 4) sleep(400);
					else sleep(200);	
					
					if(s.getType() == MusicSymbol.Type.PAUSE) {
						composition.moveComposition(s);	
						index++;
					}else if(s.getType() == MusicSymbol.Type.CHORD) {
						for(int x = 0;x<s.getNumOfNotes();x++) {
							if(playedNote(s.get(x))) {			
								composition.moveComposition(s);	
								index++;	
							}
						}
					}else {
						if(playedNote(s)) {			
							composition.moveComposition(s);	
							index++;
						}
					}
				}	
				interrupt();
			}
		}catch(InterruptedException e){
			
		}
	}
	public boolean allPlayedNotes(MusicSymbol s) {
		String tmpS ="" + s.getTone()+(s.getSharp()?"#":"")+s.getOctave();
		for(String tmp:playedSymbols) {
			if(!tmpS.equals(tmp)) {
				return false;
			}
		}
		return true;
	}
	
	public boolean playedNote(MusicSymbol s) {
		String tmpS ="" + s.getTone()+(s.getSharp()?"#":"")+s.getOctave();
		for(String tmp:playedSymbols) {
			if(tmpS.equals(tmp)) {
				return true;
			}
		}
		return false;
	}
	public ArrayList<MusicSymbol> getSymbols(){
		return symbolsToPlay;
	}
	public void addSymbol(String description) {
		playedSymbols.add(description);
	}
	public boolean getWorking() {return working;}
	public void stopWorking() {interrupt();}
	public void setWorking(boolean w) {this.working = w;}
	public void startPlaying() {
		synchronized(this) {
			working = true;
			notify();
		}
		if(startCounter==0) {start();}
		startCounter++;
	}
}
