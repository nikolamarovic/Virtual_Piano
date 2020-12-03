package Projekat2;

import java.util.ArrayList;


public class Chord extends MusicSymbol{
	private Type type;
	protected Fraction duration;
	protected ArrayList<Note> notes = new ArrayList<Note>();
	public Chord(Fraction duration) {
		this.duration = duration;
		type = Type.CHORD;
	}
	public Chord() {type = Type.CHORD;}

	@Override
	public Fraction getDuration() {return notes.get(0).duration;}
	
	public Note get(int i) {
		return notes.get(i);
	}
	public Type getType() {return type;}

	public void setType(Type type) {this.type = type;}
	
	void addNote(Note n) {notes.add(n);}
	
	@Override
	public String toString() {return notes.toString();}
	@Override
	public int getNumOfNotes() {
		return notes.size();
	}
	@Override
	public int getMidi() {
		// TODO Auto-generated method stub
		return 0;
	}
	@Override
	public String getTone() {
		// TODO Auto-generated method stub
		return null;
	}
	@Override
	public int getOctave() {
		// TODO Auto-generated method stub
		return 0;
	}
	@Override
	public boolean getSharp() {
		// TODO Auto-generated method stub
		return false;
	}

}
