#define SIZE 16
int myLeds[SIZE] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15   // D3 is 3, it is also the speakerPin
};

// 將每個腳位模式設為OUTPUT，除了第3個
void setup() {               
  for(int i = 0; i < SIZE; i++){
    if (myLeds[i] != D3) pinMode(myLeds[i], OUTPUT);
  }    
}

void loop() {
  for (int i = 0; i < 3; ++i) {
    LedsMapping(0x0);             // 全亮
    delay(300);
    LedsMapping(0xFFFF);          // 全暗
    delay(300);
  }

  for (int i = 0; i < 5; ++i) {
    LedsMapping(0x5555);          // light on all LED's at odd postions 5 = 0b0101
    delay(300);
    LedsMapping(0xAAAA);          // light on all LED's at even postions A = 0b1010
    delay(300);
  }
  for (int i = 0; i < 2; ++i) {
    LowToHigh(200);               //從右到左
    delay(300);
    HighToLow(200);               //從左到右
    delay(300);
  }
}

void LedsMapping(unsigned value)
{
  unsigned tmp = value & 0xFFFF;

  for (int i = 0; i < SIZE; ++i) {
    if (tmp & 0x1) 
      digitalWrite(myLeds[i], HIGH);    // led off
    else
      digitalWrite(myLeds[i], LOW);     // led on
    tmp >>= 1;
  }
}

void LowToHigh(unsigned due)
{
  unsigned val = 0xFFFE;      //0b1111 1111 1111 1110

  for (int i = 0; i < SIZE; ++i) {
    LedsMapping(val);
    delay(due);
    val <<= 1;                //左移
    val |= 0x01;              //因為移動，所以最右要滅掉
  }
}

void HighToLow(unsigned due)
{
  unsigned val = 0x7FFF;      //0b0111 1111 1111 1111

  for (int i = 0; i < SIZE; ++i) {
    LedsMapping(val);
    delay(due);
    val >>= 1;                //右移
    val |= 0x8000;            //因為移動，所以最左要滅掉
  }
}

