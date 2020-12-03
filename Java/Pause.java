package Projekat2;

public class Pause extends MusicSymbol {
	protected Fraction duration;
	private Type type;
	public Pause(Fraction duration) {
		this.duration = duration;
		type = Type.PAUSE;
	}
	@Override
	public Fraction getDuration() {return duration;}

	public Type getType() {return type;}

	public void setType(Type type) {this.type = type;}

	@Override
	public String toString() {return (duration.imenilac==4?"|":" ");}
	@Override
	public int getNumOfNotes() {
		return 0;
	}
	@Override
	public Note get(int i) {
		return null;
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
