#define LATCH_DIO D15
#define CLK_DIO D14
#define DATA_DIO 2
#define BUTTON1 BT1
#define BUTTON2 BT2
#define BUTTON3 BT3
#define BUTTON4 BT4
const byte SEGMENT_MAP[] = {0x3F, 0x06, 0x3C, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0X7F, 0X6F, 0X77, 0X7C, 0X39};  //8:dot  7:g  6:f  5:e  4:d  3:c  2:b  1:a
const byte SEGMENT_SELECT[] = {0xFE, 0xFD, 0xFB, 0xF7};   //7段顯示器位置
int i = 3;
void setup ()
{
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
}
void loop()
{
  if (i > -1)                     //數字8往左移
    for (; i > -1; i--)
    {
      WriteNumberToSegment(i , 8);
      delay(1000);
    }
  if (!digitalRead(BUTTON1))      //按鍵1輸出3印在最右側
  {
    WriteNumberToSegment(3 , 3);
  }
  if (!digitalRead(BUTTON2))      //按鍵2輸出3印在最右側的左邊一個位置
  {
    WriteNumberToSegment(2 , 3);
  }
  if (!digitalRead(BUTTON3))      //按鍵3輸出5印在最左側的右邊一個位置
  {
    WriteNumberToSegment(1 , 5);
  }
  if (!digitalRead(BUTTON4))      //按鍵4輸出6印在最左側
  {
    WriteNumberToSegment(0 , 6);
  }
}

void WriteNumberToSegment(byte Segment, byte Value)
{
  digitalWrite(LATCH_DIO, LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO, HIGH);
}

