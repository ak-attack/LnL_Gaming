//Game Console 
//=================================================================================================================================
//=================================================================================================================================
//=================================================================================================================================



//Piezo Music Code
//NOTE: This code has been adapted from the arduino_songs Github here:
//https://github.com/robsoncouto/arduino-songs/tree/master
//=================================================================================================================================

//Piano Notes to Tones
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


int melody1[] = {
  // Take on me, by A-ha
  // Score available at https://musescore.com/user/27103612/scores/4834399
  // Arranged by Edward Truong

  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8,
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  
};

//controls song pacing (faster/slower)
int tempo1 = 140;


void playMelody(int melody[], int melodySize, int tempo, const int buzzer) {
  int notes = melodySize / sizeof(melody[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}


//Game Control
//=================================================================================================================================
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

//Serial data received from Processing app
int processingData = 0; 

//Piezo connected to pin 9
const int buzzer = 9; 

//Console buttons
int button1 = 0; //quit
int button2 = 0; //extreme
int button3 = 0; //normal
int button4 = 0; //easy

//Player Scores
int player1Score = 0;
int player2Score = 0;


void setup() {
  Serial.begin(9600);

  lcd.clear();
  lcd.setCursor(0,0);

  //piezo
  pinMode(buzzer, OUTPUT);

  //buttons
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  //use music to indicate ACM port
  // playMelody(melody1,sizeof(melody1),tempo1,buzzer); //play menu music
}


void loop() {

  //Buttons 
  //--------------------------------------------------------------------
  //read buttons 
  button1 = digitalRead(A0);
  button2 = digitalRead(A1);
  button3 = digitalRead(A2);
  button4 = digitalRead(A3);

  if (button1 == HIGH) {
    noTone(buzzer);
    Serial.write(104); //quit
  }
  else if (button2 == HIGH) {
    noTone(buzzer);
    Serial.write(103); //extreme
  }
  else if (button3 == HIGH) {
    noTone(buzzer);
    Serial.write(102); //normal
  }
  else if (button4 == HIGH) {
    noTone(buzzer);
    Serial.write(101); //easy
  }
  else {
    noTone(buzzer);
  }


  //Read Serial Data From Processing App
  //--------------------------------------------------------------------
  if (Serial.available()) {
    processingData = Serial.read();
  }
  switch(processingData) {
    //numerical keyboard keys act as piano
    case '1':
    tone(buzzer,NOTE_C4);
    break;
    case '2':
    tone(buzzer,NOTE_D4);
    break;
    case '3':
    tone(buzzer,NOTE_E4);
    break;
    case '4':
    tone(buzzer,NOTE_F4);
    break;
    case '5':
    tone(buzzer,NOTE_G4);
    break;
    case '6':
    tone(buzzer,NOTE_A5);
    break;
    case '7':
    tone(buzzer,NOTE_B5);
    break;
    case '8':
    tone(buzzer,NOTE_C5);
    break;
    case '9':
    tone(buzzer,NOTE_D5);
    break;
    case '0':
    tone(buzzer,NOTE_E5);
    break;

    //increment player 1 score, play sound
    case 1:
    player1Score += 1;
    tone(buzzer,500);
    break;

    //increment player 2 score, play sound
    case 2:
    player2Score += 1;
    tone(buzzer,1000);
    break;

    //play player 1 hit sound
    case 3:
    tone(buzzer,1500);
    break;

    //play player 2 hit sound
    case 4:
    tone(buzzer,2000);
    break;
    
    //reset game
    case 5:
    player1Score = 0;
    player2Score = 0;
    break;

    //exiting music
    case 6:
    playMelody(melody1,sizeof(melody1),tempo1,buzzer); //play menu music
    break;
  }

  ///Liquid Crystal Display
  //--------------------------------------------------------------------
  lcd.clear();
  lcd.setCursor(0,0);
  String LCD_SCORE = "Score:" + String(player1Score) + "-" + String(player2Score) + " /10";
  lcd.print(LCD_SCORE);

  //Reset
  //--------------------------------------------------------------------
  delay(100);
  noTone(buzzer);
  processingData = 0;
}
