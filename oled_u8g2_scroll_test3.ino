//#include <ArduinoSTL.h>


/*
  HelloWorld.ino
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
*/
//#include <stdio.h> 
//#include <Arduino.h>
#include <U8g2lib.h>


//#ifdef U8X8_HAVE_HW_SPI
//#include <SPI.h>
//#endif
//#ifdef U8X8_HAVE_HW_I2C
//#include <Wire.h>
//#endif

#define ARRAY_SIZE(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
//U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

using namespace std;

//String message = "";
//vector<String> v;

// 128x64, u8g2_font_6x13_t_hebrew 폰트 화면 설정
#define MAX_LINES 9
int gCurLines = 0; // 현재 라인 수. 0 부터 시작하는 걸로.
int gMaxLines = MAX_LINES; // font에 따른 max line 수. -> 폰트에 따라 계산할 수도. 
String gMsgArray[MAX_LINES];
String gStrSpace = "";
u8g2_uint_t initX = 2;
u8g2_uint_t gLineGap = 8; //pixel

// test 용 변수
int gInt = 1;

void setup(void) {
  u8g2.begin();
  // 화면 초기화
  initScreen();

  Serial.begin(9600);
}

/*
  fix font
  u8g2_font_6x12_t_symbols
  u8g2_font_profont11_tf
  u8g2_font_profont12_tf
  u8g2_font_6x13_t_hebrew
  u8g2_font_5x8_tf
 */
 


void loop(void) {

  // make message
  String tempMessage = String(gInt++) + "\r\n" + "x";
  logScreen(tempMessage);
   
  delay(1000);
}

void initScreen() {
  u8g2.setContrast(0);         
  u8g2.setFont(u8g2_font_5x8_tf);
  u8g2.setFontMode(0);  
}

void logScreen(String tempMessage) {
  int arrySize = 1;
  int index = tempMessage.indexOf("\n");
  while(index > -1) {
    arrySize++;
    index = tempMessage.indexOf("\n", index+1);
  }

  String msgArray[arrySize];
  int count = 0;
  int preIdx = -1;
  int postIdx = tempMessage.indexOf("\n"); 
  while(postIdx > -1) {
    msgArray[count] = tempMessage.substring(preIdx+1, postIdx);
    msgArray[count].trim();
    count++;    
    preIdx = postIdx;
    postIdx = tempMessage.indexOf("\n", preIdx+1);
   }
   
   msgArray[count] = tempMessage.substring(preIdx); //.trim();    
   msgArray[count].trim();  

   for(int i = 0; i < arrySize; i++) {
    logLineScreen(msgArray[i]);
   }
}

void logLineScreen(String tempMessage) {
  if(gCurLines < gMaxLines) {
    gMsgArray[gCurLines++] = tempMessage;    
    // 나머지 라인 초기화
    for(int i = gCurLines; i < gMaxLines; i++) {
      gMsgArray[i] = gStrSpace;
    }  
  } else {
    // 라인 스크롤
    for(int i = 1; i < gMaxLines; i++) { 
      gMsgArray[i-1] = gMsgArray[i];
    }
    // 마지막 라인 설정
    gMsgArray[gMaxLines-1] = tempMessage;
  } 

  displayLogScreen();
}

void displayLogScreen() {
  u8g2_uint_t lines[gMaxLines];
  for(int i = 0; i < gMaxLines; i++) {
    lines[i] = gLineGap * (i + 1);
  }

  char* msg[5];
  for(int i = 0; i < gMaxLines; i++) {
    msg[i] = gMsgArray[i].c_str();
  }
  
  u8g2.firstPage();
  do {    
    for(int i = 0; i < gMaxLines; i++) {
      u8g2.drawStr(initX, lines[i], msg[i]);      
    }
  } while ( u8g2.nextPage() );
}
