#include <BlockDriver.h>
#include <FreeStack.h>
#include <MinimumSerial.h>
#include <SdFat.h>
#include <SdFatConfig.h>
#include <SysCall.h>

/**
 * List Files for sdcard.
 */

#include <SPI.h>


const int chipSelect = 10;
File myFile;
 
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
 
  Serial.print("Initializing SD card...");
 
  //SD카드 초기화 SD.begin(4) 는  CS핀번호
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  // test.txt 파일을 쓰기 위해서 Open한다.
  myFile = SD.open("test.txt", FILE_WRITE);
 
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");    //test.txt 파일에 문자열을 쓴다.
    myFile.println("가다다라~~~");    //test.txt 파일에 문자열을 쓴다.
    // close the file: 쓰기 완료한 파일을 닫아준다.
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
 
  // re-open the file for reading: 
  // test.txt 파일을 읽기 위해 다시 Open한다.
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("read test.txt:");
 
    // read from the file until there's nothing else in it:
    // test.txt 파일의 처음부터 끝까지 read하여 시리얼 모니터에 표시해준다.
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file: 읽기 완료한 파일을 닫는다.
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
void loop() {
  // nothing happens after setup
}
 


