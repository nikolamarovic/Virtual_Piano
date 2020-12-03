package Projekat2;
import java.io.*;
import java.util.*;
import java.util.regex.*;

class ToneMap{
	public boolean sharp = false;
	public int midi = -1;
	public int octave = -1;
	public String tone = ".";
	public ToneMap() { }
	public ToneMap(boolean sharp,int midi, int octave, String tone) {
		this.sharp = sharp;
		this.midi = midi;
		this.octave = octave;
		this.tone = tone;
	}
	public String toString() {
		return "" +tone + (this.sharp?"#":"") + octave + ", "+midi; 
	}
}

class ToneSharpOctave{
	public boolean sharp = false;
	public int octave = -1;
	public String tone = ".";
	public ToneSharpOctave() { } 
	public ToneSharpOctave(boolean sharp, int octave, String tone) {
		this.sharp = sharp;
		this.octave = octave;
		this.tone = tone;
	}
	public String toString() {
		return "" +tone + (this.sharp?"#":"") + octave; 
	}
}
public class Composition {
	public static Map<Integer, String> midiToToneMap;
	public static Map<String,ToneMap> toneMap;//znak u simbol
	public static Map<String,Integer> toneSharpOctaveMap;//salje opis note, a vraca midi broj
	public static Map<String,String> noteToKey;//VRACA slovo sa tastature a saljes opis note
	private Fraction duration;
	public ArrayList<MusicSymbol> symbols = new ArrayList<MusicSymbol>();
	public Composition() throws NumberFormatException, IOException {
		symbols = new ArrayList<MusicSymbol>();
		toneSharpOctaveMap = new HashMap<String,Integer>();
		toneMap = new HashMap<String, ToneMap>();
		midiToToneMap = new HashMap<Integer,String>();
		noteToKey = new HashMap<String,String>();
		loadMap();
	}
	void loadMap() throws NumberFormatException, IOException{
		try {
			BufferedReader reader = new BufferedReader(new FileReader("map.csv"));
			String line;
			String pattern = "([^,]+),([A-Z])(#?)([0-9]+),([0-9]+)";
			Pattern r = Pattern.compile(pattern);
			while((line = reader.readLine())!=null) {
				Matcher m = r.matcher(line);
				if(m.find()) {
					ToneMap data1 = new ToneMap();
					data1.sharp = m.group(3).equals("#");
					data1.octave = Integer.parseInt(m.group(4));
					data1.tone = m.group(2);
					data1.midi = Integer.parseInt(m.group(5));
					toneMap.put(m.group(1),data1);
					String s = data1.tone+(m.group(3).equals("#")?"#":"")+data1.octave;
					noteToKey.put(s,m.group(1));
					midiToToneMap.put(data1.midi, s);
					toneSharpOctaveMap.put(s,Integer.parseInt(m.group(5)));
				}else System.out.println("Don't match.");
			}
			reader.close();
		}catch(IOException e) {
			System.out.println("Greska pri otvaranju fajla.");
		}
		
	}
	public void printToneMap() {System.out.println(toneMap);}
	public boolean setDuration(Fraction raz) {
		if(raz.imenilac!=4 && raz.imenilac != 8) {
			System.out.println("Greska sa duzinom takta.\n");
			return false;
		}
		else {
			duration.imenilac = raz.imenilac;
			duration.brojilac = raz.brojilac;
			return true;
		}
	}
	public void loadComposition(String s) {
		if(symbols.removeAll(symbols));
		File file = new File(s);
		try {
			BufferedReader reader = new BufferedReader(new FileReader(file));
			String line;
			while((line = reader.readLine())!=null) {
				for(int i=0;i<line.length();i++) {
					char c = line.charAt(i);
					if(c == '[') {
						Chord tmpChord = new Chord();
						String tmpS = "";
						boolean hasSpace = false;
						for(i=i+1;line.charAt(i)!=']';i++) {
							if(line.charAt(i)==' ') hasSpace = true;
							else tmpS+=line.charAt(i);
						}
						boolean addedToChord = false;
						for(int j = 0;j<tmpS.length();j++) {
							ToneMap tmpMap = toneMap.get("" + tmpS.charAt(j));
							boolean sharp = tmpMap.sharp;
							String tone = tmpMap.tone;
							int octave = tmpMap.octave;
							int midi = tmpMap.midi;
							Fraction dur;
							if(hasSpace) {
								dur = new Fraction(1,8);
								symbols.add(new Note(new Fraction(1,8),sharp,midi,octave,tone));
							}
							else { 
								addedToChord = true;
								dur = new Fraction(1,4);
								tmpChord.addNote(new Note(dur,sharp,midi,octave,tone));
							}
						}
						if(addedToChord) symbols.add(tmpChord);
					}
					
					if(c == ' ') symbols.add(new Pause(new Fraction(1,8)));
					
					//pauza 
					if(c == '|') symbols.add(new Pause(new Fraction(1,4)));
					
					//nota 
					if(c!=' ' && c!='|' && c!='[' && c!=']') {
						ToneMap tmpMap = toneMap.get("" + c);
						boolean sharp = tmpMap.sharp;
						String tone = tmpMap.tone;
						int octave = tmpMap.octave;
						int midi = tmpMap.midi;
						symbols.add(new Note(new Fraction(1,4),sharp,midi,octave,tone));
					}
				}
			}
			reader.close();
		}catch(IOException e) {
			System.out.println("Greska pri otvaranju fajla.");
		}
	}
	public String toString() {return symbols.toString();}
}
