package Projekat2;

import java.awt.BorderLayout;
import java.io.IOException;

import javax.sound.midi.MidiUnavailableException;

public class Main {
	public static void main(String[] args) throws NumberFormatException, IOException, MidiUnavailableException {
		//System.out.println(c.toString());
		Composition c = new Composition();
		PianoGraphics pianoGraphics = new PianoGraphics();
		CompositionGraphics compositionGraphics = new CompositionGraphics(c);
		MidiPlayer player = new MidiPlayer(compositionGraphics);
		MainGraphics mainGraphics = new MainGraphics(player,compositionGraphics,pianoGraphics);
		mainGraphics.add(pianoGraphics,BorderLayout.SOUTH);
		mainGraphics.add(compositionGraphics, BorderLayout.CENTER);
		
	}
}

