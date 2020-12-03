package Projekat2;


public abstract class MusicSymbol {
	static enum Type{PAUSE,NOTE,CHORD};
	public MusicSymbol() { }
	public abstract Fraction getDuration();
	public abstract String toString();
	public abstract Type getType();
	public abstract int getNumOfNotes();
	public abstract Note get(int i);
	public abstract int getMidi();
	public abstract String getTone();
	public abstract int getOctave();
	public abstract boolean getSharp();
}