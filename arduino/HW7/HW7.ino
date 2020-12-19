#include <LiquidCrystal.h>
int speakerPin = D3; 
char notes[] = "gee fdd cdefggg gee fdd cegge   dddddef eeeeefg gee fdd ceggc   ccc";
int length = sizeof(notes);
int tempo = 300;
byte Row=0, Col=0;

void setup() {
  pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)                                   
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
  pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
  pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
  pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
  pinMode(A3, OUTPUT); //A4, C4, S4,S8,S12 (*,0, #,D)
  
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);

  pinMode(speakerPin, OUTPUT);
} 

void loop() {
  static int keypressedcount=0;
  byte keyindex=0;
  if(keyscan()==true) 
  {
    keyindex=(Row-1)*4+Col;
    for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(tempo); // rest
      } else {
        playNote(speakerPin,notes[i],tempo,keyindex);
      }
      delay(tempo/10);
    }

    digitalWrite(A0,LOW);
    digitalWrite(A1,LOW);
    digitalWrite(A2,LOW);
    digitalWrite(A3,LOW);
    delayMicroseconds(100);
  } 
}

void playNote(int OutputPin, char note, int duration,int scale) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b'};
  int tones1[] = { 261, 294, 330, 349, 392, 440, 494};
  int tones2[] = { 523, 554, 659, 698, 784, 880, 988};
  int tones3[] = { 1046, 1175, 1318, 1397, 1568, 1760, 1976};
  for (int i = 0; i < 7; i++) {
    if (names[i] == note) {
      if(scale == 1)
        tone(OutputPin,tones1[i], duration);
      else if(scale == 2)
        tone(OutputPin,tones2[i], duration);
      else
        tone(OutputPin,tones3[i], duration);
      delay(duration);
      noTone(OutputPin);
    }
  }
}

bool keyscan( )
{
  Row=0;Col=0;
  bool keypressed = false;
  //scan col1
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=1;
      keypressed = true;
      return(keypressed);
  }
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=1;
      keypressed = true;
      return(keypressed);
  }

  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=1;
      keypressed = true;
      return(keypressed);
  }
  return(false);
}
