#include <SoftwareSerial.h>                           //we have to include the SoftwareSerial library, or else we can't use it
#define rx 2                                          //define what pin rx is going to be
#define tx 3                                          //define what pin tx is going to be

SoftwareSerial myserial(rx, tx);                      //define how the soft serial port is going to work

String inputstring = "";                              //a string to hold incoming data from the PC
String sensorstring = "";                             //a string to hold the data from the Atlas Scientific product
boolean input_string_complete = false;                //have we received all the data from the PC
boolean sensor_string_complete = false;               //have we received all the data from the Atlas Scientific product
float DO;                                             //used to hold a floating point number that is the DO

const int switch1 = 4;  // Pin number for the switch

void setup() {                                        //set up the hardware
  Serial.begin(9600);                                 //set baud rate for the hardware serial port_0 to 9600
  myserial.begin(9600);                               //set baud rate for the software serial port to 9600
  inputstring.reserve(10);                            //set aside some bytes for receiving data from the PC
  sensorstring.reserve(30);                           //set aside some bytes for receiving data from Atlas Scientific product

  pinMode(switch1, OUTPUT);
}

void serialEvent() {                                  //if the hardware serial port_0 receives a char
  inputstring = Serial.readStringUntil(13);           //read the string until we see a <CR>
  input_string_complete = true;                       //set the flag used to tell if we have received a completed string from the PC
}

void loop() {                                         //here we go...

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

  if(number2 > 0.00){
    
    while(true){
      Serial.print("do:");
      Serial.println(number2);
      if (input_string_complete == true) {                //if a string from the PC has been received in its entirety
        myserial.print(inputstring);                      //send that string to the Atlas Scientific product
        myserial.print('\r');                             //add a <CR> to the end of the string
        inputstring = "";                                 //clear the string
        input_string_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
      }

      if (myserial.available() > 0) {                     //if we see that the Atlas Scientific product has sent a character
        char inchar = (char)myserial.read();              //get the char we just received
        sensorstring += inchar;                           //add the char to the var called sensorstring
        if (inchar == '\r') {                             //if the incoming character is a <CR>
          sensor_string_complete = true;                  //set the flag
        }
      }

      if (sensor_string_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
        Serial.println(sensorstring);                     //send that string to the PC's serial monitor

        if (isdigit(sensorstring[0])) {
          DO = sensorstring.toFloat();
          Serial.println(DO); 

          if (DO <= number1) {
            digitalWrite(switch1, HIGH);  // Turn on the switch
          }
          if (DO >= number2) {
            digitalWrite(switch1, LOW);   // Turn off the switch
          }
        }
        else {
          digitalWrite(switch1, LOW);    // Turn off the switch
        }

        sensorstring = "";                                //clear the string
        sensor_string_complete = false;                   //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
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
