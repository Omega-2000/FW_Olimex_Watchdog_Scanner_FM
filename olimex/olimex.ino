#include <HardwareSerial.h>
HardwareSerial rs (1);

String msg = "";
uint32_t last_msg;
uint16_t msg_interval = 1000;

#define RELAY 32

//#define CAMERA 33
//uint32_t camera_triggered;
//uint16_t trigger_off = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  rs.begin(115200, SERIAL_8N1, 16, 17);

  pinMode(RELAY, OUTPUT);

  //pinMode(CAMERA, OUTPUT);
  //digitalWrite(CAMERA, HIGH);

  last_msg = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (rs.available()) {
    char ch = rs.read();
    Serial.print(ch);
    if (ch != '\n') {
      msg += ch;
    } else {
      //  ------------------------------------------------------------------------------------------------
      /*if (msg == "") {
        Serial.println("Camera triggered");
        digitalWrite(CAMERA, LOW);
        camera_triggered = millis();
      }*/
      //  ------------------------------------------------------------------------------------------------
      if (msg == "alive") {
        Serial.println("OK");
        last_msg = millis();
      }
      msg = "";
    }
  }
  if (millis() - last_msg > msg_interval) {
    Serial.println("");
    digitalWrite(RELAY, 1);
    delay(1000);
    digitalWrite(RELAY, 0);
    delay(5000);
    last_msg = millis();

  }
  //delay(1);

  /*if (millis() - camera_triggered > trigger_off) {  //  aggiungere controllo per entrare qua sono se camera è low --> (digitalRead(CAMERA) == LOW)
    Serial.println("Camera trigger off");
    digitalWrite(CAMERA, HIGH);
  }*/
}
