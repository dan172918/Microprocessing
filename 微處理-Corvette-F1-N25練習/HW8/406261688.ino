#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
byte Row = 0, Col = 0;

void setup() {
  pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
  pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
  pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
  pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
  pinMode(A3, OUTPUT); //A4, C4, S4,S8,S12 (*,0, #,D)

  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);

}

int delay_number = 100;
int tmp = 0;
bool keyscan( )
{
  bool keypressed = false;
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if (digitalRead(10) == LOW)   //是否按下button 1
  {
    digitalWrite(A0, HIGH);
    Col = 1; Row = 1;
    keypressed = true;
    return (keypressed);
  }
  //Read keys in row.2
  if (digitalRead(11) == LOW)   //是否按下button 4
  {
    digitalWrite(A0, HIGH);
    Col = 1; Row = 2;
    keypressed = true;
    return (keypressed);
  }
  //Read keys in row.4
  if (digitalRead(13) == LOW)   //是否按下button *
  {
    digitalWrite(A0, HIGH);
    Col = 1; Row = 4;
    keypressed = true;
    return (keypressed);
  }
  //scan col 4
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  delayMicroseconds(100);
  //Read keys in row.1
  if (digitalRead(10) == LOW)   //是否按下button A
  {
    digitalWrite(A3, HIGH);
    Col = 4; Row = 1;
    keypressed = true;
    return (keypressed);
  }
  //Read keys in row.2
  if (digitalRead(11) == LOW)   //是否按下button B
  {
    digitalWrite(A3, HIGH);
    Col = 4; Row = 2;
    keypressed = true;
    return (keypressed);
  }
  //Read keys in row.3
  if (digitalRead(12) == LOW)   //是否按下button C
  {
    digitalWrite(A3, HIGH);
    Col = 4; Row = 3;
    keypressed = true;
    return (keypressed);
  }
  //Read keys in row.4
  if (digitalRead(13) == LOW)   //是否按下button D
  {
    digitalWrite(A3, HIGH);
    Col = 4; Row = 4;
    keypressed = true;
    return (keypressed);
  }
  return (false);   //當沒按時回傳false
}

void loop() {
  byte keyindex = 0;
  if (keyscan() == true) //如果有按按鈕，則觸發
  {
    keyindex = (Row - 1) * 4 + Col; //計算目前是按哪個button
    delay(5);
    if (keyindex == 1)  //按下 button 1 顯示第一組
      lcd.print("A single HD44780U can display up to one 8 character line or two 8 character line");
    else if (keyindex == 5) //按下 button 4 顯示第二組
      lcd.print("The HD44780U has two 8-bit register, an instruction register and a data registes");
    else if (keyindex == 13) //按下 button * 開關Cursor
      if (tmp == 0) {
        lcd.noCursor();
        tmp = 1;
      }
      else {
        lcd.cursor();
        tmp = 0;
      }
    else if (keyindex == 4) //按下 button A 左移
      for (int i = 0; i < 24; i++) {
        lcd.scrollDisplayLeft();
        delay(500);
      }
    else if (keyindex == 8) //按下 button B 右移
      for (int i = 0; i < 24; i++) {
        lcd.scrollDisplayRight();
        delay(500);
      }
    else if (keyindex == 12) //按下 button C 清除
      lcd.clear();
    else if (keyindex == 16) //按下 button D 回到一開始
      lcd.home();
  }
}
