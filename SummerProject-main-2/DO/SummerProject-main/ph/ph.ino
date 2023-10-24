#include <SoftwareSerial.h>                           
#define rx 2                                         
#define tx 3                                         

#define SWITCH1 4                                    
#define SWITCH2 5                                    

SoftwareSerial myserial(rx, tx);                      

String inputstring = "";                              
String sensorstring = "";                             
boolean input_string_complete = false;                
boolean sensor_string_complete = false;               
float pH;                                             

unsigned long previousMillis1 = 0;                     
unsigned long previousMillis2 = 0;                     
const long onInterval = 1000;  // 10 seconds                  
const long offInterval = 30000;  // 5 seconds    



enum State { OFF, ON } switch1_state = OFF, switch2_state = OFF; 

void setup() {                                        
  Serial.begin(9600);                                 
  myserial.begin(9600);                               
  inputstring.reserve(10);                            
  sensorstring.reserve(30);                           
  
  pinMode(SWITCH1, OUTPUT);                           
  pinMode(SWITCH2, OUTPUT);   

  Serial.flush();                        
}

void serialEvent() {                                  
  inputstring = Serial.readStringUntil(13);           
  input_string_complete = true;                       
}

void loop() {                                         
  unsigned long currentMillis = millis();  

  float number1 = 0;
  float number2 = 0;

  String receivedData = Serial.readStringUntil('\n');  // 读取接收到的数据

  //Serial.println(receivedData);
    
  // 解析接收到的数据
  int commaIndex = receivedData.indexOf(',');  // 查找逗号的位置
  if (commaIndex != -1) {
    String number1Str = receivedData.substring(0, commaIndex);  // 提取第一个数值的字符串
    String number2Str = receivedData.substring(commaIndex + 1);  // 提取第二个数值的字符串

    
    // 将字符串转换为浮点数
    number1 = number1Str.toFloat();
    number2 = number2Str.toFloat();
  }

  //delay(3000);
  

  if(number2 > 0.00){
    
    while(true){
      Serial.print("ph:");
      Serial.println(number2);
      if (input_string_complete == true) {                
        myserial.print(inputstring);                      
        myserial.print('\r');                             
        inputstring = "";                                 
        input_string_complete = false;                    
      }

      if (myserial.available() > 0) {                     
        char inchar = (char)myserial.read();              
        sensorstring += inchar;                           
        if (inchar == '\r') {                             
          sensor_string_complete = true;                  
        }
      }

      if (sensor_string_complete == true) {               
        Serial.println(sensorstring);                     

        if (isdigit(sensorstring[0])) {                   
          pH = sensorstring.toFloat(); 
          Serial.println(pH);  

          if (pH >= number2) {                                
          // Switch1 control
            if (switch1_state == OFF && currentMillis - previousMillis1 >= offInterval) {
              switch1_state = ON;
              previousMillis1 = currentMillis;
            }
            else if (switch1_state == ON && currentMillis - previousMillis1 >= onInterval) {
              switch1_state = OFF;
              previousMillis1 = currentMillis;
            }
            switch2_state = OFF;
          }
          else if (pH <= number1) {                                
          // Switch2 control
            if (switch2_state == OFF && currentMillis - previousMillis2 >= offInterval) {
              switch2_state = ON;
              previousMillis2 = currentMillis;
            }
            else if (switch2_state == ON && currentMillis - previousMillis2 >= onInterval) {
              switch2_state = OFF;
              previousMillis2 = currentMillis;
            }
            switch1_state = OFF;
          }
          else if (pH > number1 && pH < number2) {  // if the pH is between 6 and 7
            switch1_state = OFF;
            switch2_state = OFF;
            digitalWrite(SWITCH1, switch1_state == OFF ? HIGH : LOW);  
            digitalWrite(SWITCH2, switch2_state == OFF ? HIGH : LOW);
          }     
        }

        sensorstring = "";                                
        sensor_string_complete = false;                   
      }
      String receivedD = Serial.readStringUntil('\n');  // 读取接收到的数据
        
      // 解析接收到的数据
      int commaI = receivedD.indexOf(',');  // 查找逗号的位置
      if (commaI != -1) {
        String number1S = receivedD.substring(0, commaI);  // 提取第一个数值的字符串
        String number2S = receivedD.substring(commaI + 1);  // 提取第二个数值的字符串

        
        // 将字符串转换为浮点数
        number1 = number1S.toFloat();
        number2 = number2S.toFloat();

      }
      else{
        continue;
      }
    }
  }
}