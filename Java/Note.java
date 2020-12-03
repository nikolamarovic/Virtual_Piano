package Projekat2;

public class Note extends MusicSymbol {
	private Type type;
	protected Fraction duration;
	protected boolean sharp = false;
	protected int midi = -1;
	protected int octave = -1;
	protected String tone = ".";
	public Note(Fraction duration, boolean sharp, int midi, int octave, String tone) {
		this.duration = duration;
		this.sharp = sharp;
		this.midi = midi;
		this.octave = octave;
		this.tone = tone;
		type = Type.NOTE;
	}

	@Override
	public Fraction getDuration() {return duration;}

	public String getTone() { return this.tone;}
	
	public int getOctave() {return this.octave;}

	public boolean getSharp() {return this.sharp;}

	public int getMidi() {return this.midi;}
	
	public Type getType() {return type;}

	public void setType(Type type) {this.type = type;}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(tone);
		sb.append((getSharp()?"#":""));
		sb.append(octave);
		return sb.toString();
	}

	@Override
	public int getNumOfNotes() {
		return 1;
	}

	@Override
	public Note get(int i) {
		return null;
	}
}
