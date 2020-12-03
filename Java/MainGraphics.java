package Projekat2;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;

import javax.sound.midi.MidiUnavailableException;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class MainGraphics extends JFrame {
	private static final long serialVersionUID = 1L;
	private boolean compositionLoaded = false, playStop = false;
	public PianoGraphics pianoGraphics;
	public static long startTime = 0;
	public Checker checker;
	public CompositionGraphics compositionGraphics;
	public JTextField compositionFilename = new JTextField(), compositionToSave = new JTextField();
	public MidiPlayer player;
	public static MiliSecondsCounter secondsCounter;
	private ArrayList<MusicSymbol> recordedSymbols = new ArrayList<MusicSymbol>();
	public MainGraphics(MidiPlayer player,CompositionGraphics compositionGraphics, PianoGraphics pianoGraphics) throws MidiUnavailableException {
		super("Virtual Piano");
		setResizable(false);
		secondsCounter = new MiliSecondsCounter();
		setBounds(0,0,1755,450);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		getContentPane().setLayout(null);
		this.player = player;
		this.compositionGraphics = compositionGraphics;
		this.pianoGraphics = pianoGraphics;
		add(pianoGraphics,BorderLayout.SOUTH);
		add(compositionGraphics, BorderLayout.CENTER);
		add(addButtonsRight());
		add(addButtonsLeft());
		add(addCenterComponents());
		setVisible(true);
	}
	JPanel addCenterComponents() {
		JLabel label1 = new JLabel("Unesite tekstualni naziv kompozicije.");
		label1.setForeground(Color.WHITE);
		label1.setFont(new Font("Helvetica Neue", Font.BOLD, 16));
		label1.setBounds(100,10,400,20);
		
		compositionFilename.setBounds(425,10,300,30);
		compositionFilename.setBackground(Color.YELLOW);
		
		
		JLabel label2 = new JLabel("Naziv pod kojim zelite da sacuvate kompoziciju.");
		label2.setForeground(Color.WHITE);
		label2.setFont(new Font("Helvetica Neue", Font.BOLD, 16));
		label2.setBounds(55,53,400,20);
		
		compositionToSave.setBounds(425,50,300,30);
		compositionToSave.setBackground(Color.YELLOW);
		
		JLabel label3 = new JLabel("Ne unositi dodatnu ekstenziju formata!");
		label3.setForeground(Color.WHITE);
		label3.setFont(new Font("Helvetica Neue", Font.BOLD, 16));
		label3.setBounds(730,53,400,20);
		
		JPanel panel = new JPanel();
		panel.setBounds(300,0,1175,92);
		panel.setLayout(null);
		panel.add(label1);
		panel.add(compositionFilename);
		panel.add(label2);
		panel.add(compositionToSave);
		panel.add(label3);
		panel.setBackground(Color.BLACK);	
		
		return panel;
	}
	JPanel addButtonsRight() {	
		JButton loadComposition= new JButton("Load composition");
		loadComposition.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				String s = compositionFilename.getText();
				if(s=="") System.out.println("Pogresan upis,pokusajte ponovo");
				else {
					compositionGraphics.getComposition().loadComposition(s);
					checker = new Checker(compositionGraphics,compositionGraphics.getMyComposition().symbols);
					PianoGraphics.setChecker(checker);
					compositionLoaded = true;
				}
			}
		});
		
		JButton nesto = new JButton("Play/Stop");
		nesto.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				if(checker!=null) {
					if(!checker.getWorking()) {
						playStop = true;
						player.drawComposition();
						checker.startPlaying();
						checker.setWorking(true);
					}else {
						checker.stopWorking();
						compositionGraphics.removePanels();
					}	
				}
			}
		});
		
		JButton txtExport = new JButton("Export to .txt");
		txtExport.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
					try {
						if(compositionLoaded) pianoGraphics.exportCompositionToTxt(compositionToSave.getText()+".txt",compositionGraphics.getComposition().symbols);
						pianoGraphics.exportCompositionToTxt(compositionToSave.getText()+".txt",recordedSymbols);	
					} catch (FileNotFoundException e) {
						
					} catch (UnsupportedEncodingException e) {
						
					}
			}
		});
		
		JButton midiExport = new JButton("Export to .midi");
		midiExport.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				String s = compositionToSave.getText();
				if(s=="") System.out.println("Unesite naziv kako zelite da sacuvate kompoziciju.");
				else {
					if(compositionLoaded) pianoGraphics.exportCompositionToMidi(compositionFilename.getText(),compositionGraphics.getComposition().symbols);
					pianoGraphics.exportCompositionToMidi(compositionToSave.getText()+".mid",recordedSymbols);
				}
			}
		});
		
		JPanel panel = new JPanel();
		panel.setBounds(0,0,300,92);
		panel.setLayout(new GridLayout(2,2));
		panel.add(loadComposition);
		panel.add(nesto);
		panel.add(midiExport);
		panel.add(txtExport);
		return panel;
	}
	
	public JPanel addButtonsLeft() {
		JButton startPlaying = new JButton("Start playing");
		startPlaying.setBounds(0,0,300,45);
		startPlaying.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				if(playStop) compositionGraphics.removePanels();
				if(compositionLoaded) {player.startPlaying();}
			}
		});
		
		JButton stopPlaying = new JButton("Stop playing");
		stopPlaying.setBounds(0,0,300,45);
		stopPlaying.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				player.stopTemporary();
			}
		});
		
		JButton startRecording = new JButton("Start recording");
		startRecording.setBounds(50,0,300,45);
		startRecording.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				PianoGraphics.playedNotesKey.removeAll(PianoGraphics.playedNotesKey);
				PianoGraphics.playedNotesMidi.removeAll(PianoGraphics.playedNotesMidi);
				secondsCounter.startRunMethod();
				secondsCounter.setWorking(true);
				startTime = System.currentTimeMillis();
			}			
		});
		
		JButton stopRecording = new JButton("Stop recording");
		stopRecording.setBounds(50,0,300,45);
		stopRecording.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				secondsCounter.stopCounting();
				fillList();
			}
		});
		
		JPanel panel = new JPanel();
		panel.setBounds(1455,0,300,92);
		panel.setLayout(new GridLayout(2,2));
		panel.add(startPlaying);
		panel.add(stopPlaying);
		panel.add(startRecording);
		panel.add(stopRecording);
		return panel;
	}
	public void fillList() {
		for(int index = 0;index<PianoGraphics.playedNotesMidi.size();index++) {
			int next = index+1;
			MidiStartEnd tmp1Midi = PianoGraphics.playedNotesMidi.get(index);
			KeyStartEnd tmp1Key = PianoGraphics.playedNotesKey.get(index);
			ToneMap tmpMap = Composition.toneMap.get("" + tmp1Key.getKey());
			boolean sharp = tmpMap.sharp;
			String tone = tmpMap.tone;
			int octave = tmpMap.octave;
			int midi = tmpMap.midi;
			if(tmp1Midi.getEnd()-tmp1Midi.getStart()>200) {
				recordedSymbols.add(new Note(new Fraction(1,4),sharp,midi,octave,tone));
			}else {
				recordedSymbols.add(new Note(new Fraction(1,8),sharp,midi,octave,tone));
			}
			if(next<PianoGraphics.playedNotesMidi.size()) {
				MidiStartEnd tmp2 = PianoGraphics.playedNotesMidi.get(next);
				if(tmp2.getStart()-tmp1Midi.getEnd() > 200) {
					recordedSymbols.add(new Pause(new Fraction(1,4)));
				}else recordedSymbols.add(new Pause(new Fraction(1,8)));
			}
		}
	}
}


