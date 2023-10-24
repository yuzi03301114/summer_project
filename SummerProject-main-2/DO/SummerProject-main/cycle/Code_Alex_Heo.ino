
#include <SoftwareSerial.h>                           
#define rx 2                                        
#define tx 3                                       
#define relayPin1 8
#define relayPin2 9
#define relayPin3 10
#define relayPin4 11
#define relayPin5 12
#define relayPin6 13

SoftwareSerial myserial(rx, tx);                     


String inputstring = "";                              
String sensorstring = "";                            
boolean input_string_complete = false;                
boolean sensor_string_complete = false;               
float DO;                                          


void setup() {                                        
  Serial.begin(9600);                                 
  myserial.begin(9600);                               
  inputstring.reserve(10);                            
  sensorstring.reserve(30);                         
  
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  pinMode(relayPin5, OUTPUT);
  pinMode(relayPin6, OUTPUT);
}

void loop() {

  float number1 = 0;
  float number2 = 0;
  float number3 = 0;
  float number4 = 0;
  float number5 = 0;

  String receivedData = Serial.readStringUntil('\n');  // 读取接收到的数据

  // 解析接收到的数据
  int commaIndex = receivedData.indexOf(',');  // 查找逗号的位置
  int fIndex = receivedData.indexOf(';');
  int dIndex = receivedData.indexOf('_');
  int equalIndex = receivedData.indexOf('=');
  if (commaIndex != -1) {
    String number1Str = receivedData.substring(0, commaIndex);  // 提取第一个数值的字符串
    String number2Str = receivedData.substring(commaIndex + 1, fIndex);  // 提取第二个数值的字符串
    String number3Str = receivedData.substring(fIndex + 1, dIndex);  // 提取第二个数值的字符串
    String number4Str = receivedData.substring(dIndex + 1, equalIndex);  // 提取第二个数值的字符串
    String number5Str = receivedData.substring(equalIndex + 1);

    
    // 将字符串转换为浮点数
    number1 = number1Str.toFloat();
    number2 = number2Str.toFloat();
    number3 = number3Str.toFloat();
    number4 = number4Str.toFloat();
    number5 = number5Str.toFloat();

    while(true){

      digitalWrite(relayPin1, HIGH); // Water pump
      Serial.println("00");
      delay (number1 * 1000);
      digitalWrite(relayPin1, LOW); // water pump off
      Serial.println("01");
      delay (number2 * 1000); //Every off for how long
      digitalWrite(relayPin2, HIGH); //air pump on
      Serial.println("02");
      delay (number3 * 1000); // Airp on for how long
      digitalWrite(relayPin2, LOW); //air pump off
      Serial.println("03");
      delay (number4 * 1000); //off for how long
      digitalWrite(relayPin3, HIGH); //selenoid velve (discharge)
      Serial.println("04");
      delay (number5 * 1000); // selenoid veleve on for how long
      digitalWrite(relayPin3, LOW); // off the velvle (which close)
      Serial.println("05");

      String receivedD = Serial.readStringUntil('\n');  // 读取接收到的数据
        
      // 解析接收到的数据
      int commaI = receivedD.indexOf(',');  // 查找逗号的位置
      int fenIndex = receivedData.indexOf(';');
      int dashIndex = receivedData.indexOf('_');
      int eIndex = receivedData.indexOf('=');
      if (commaI != -1) {
        String number1Str = receivedData.substring(0, commaI);  // 提取第一个数值的字符串
        String number2Str = receivedData.substring(commaI + 1, fenIndex);  // 提取第二个数值的字符串
        String number3Str = receivedData.substring(fenIndex + 1, dashIndex);  // 提取第二个数值的字符串
        String number4Str = receivedData.substring(dashIndex + 1, eIndex);  // 提取第二个数值的字符串
        String number5Str = receivedData.substring(eIndex + 1);

        
        // 将字符串转换为浮点数
        number1 = number1Str.toFloat();
        number2 = number2Str.toFloat();
        number3 = number3Str.toFloat();
        number4 = number4Str.toFloat();
        number5 = number5Str.toFloat();
      }
      else{
        continue;
      }
    }

  }
      
      // put your main code here, to run repeatedly:

}
