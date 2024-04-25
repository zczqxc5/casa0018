#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> // 添加 Servo 库
LiquidCrystal_I2C lcd (0x3f, 20, 4);
Servo servo; // 声明 Servo 对象
 
// const int sampleWindow = 50;
// unsigned int sample;
 
#define SENSOR_PIN A0
#define SERVO_PIN 16 // 设置 Servo 连接的引脚
 
void setup ()
{
  pinMode(SENSOR_PIN, INPUT);
  // pinMode(PIN_QUIET, OUTPUT);
  // pinMode(PIN_MODERATE, OUTPUT);
  // pinMode(PIN_LOUD, OUTPUT);
  
  // digitalWrite(PIN_QUIET, LOW);
  // digitalWrite(PIN_MODERATE, LOW);
  // digitalWrite(PIN_LOUD, LOW);
  
  servo.attach(SERVO_PIN); // 将 Servo 连接到指定引脚
  servo.write(0); // 初始位置
  
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
 
void loop ()
{
  //read ref voltage
  float ref_volt = 3.3/1000.0;
  
  //preallocate
  //float db1;
  // char db[4];

  
  // // read and convert analog data to dB
  //   db1 = (analogRead(SENSOR_PIN)/1024.0)*ref_volt*50.0;    
  //   dtostrf(db1,1,2,db);
  //   Serial.println(db);
//     strcat(ble_dat,db_str);
//     ble.write(ble_dat);
//     delay(80);
//     ble.write("e");
//   delay(125);
// }



  // unsigned long startMillis = millis();
  // float peakToPeak = 0;
  // unsigned int signalMax = 0;
  // unsigned int signalMin = 1024;
  
  // while (millis() - startMillis < sampleWindow)
  // {
  //   sample = analogRead(SENSOR_PIN);
  //   if (sample < 1024)
  //   {
  //     if (sample > signalMax)
  //     {
  //       signalMax = sample;
  //     }
  //     else if (sample < signalMin)
  //     {
  //       signalMin = sample;
  //     }
  //   }
  // }
 
  // peakToPeak = signalMax - signalMin;
  // int db = map(peakToPeak, 20, 900, 49.5, 90);
  // // Serial.println(peakToPeak);
  // // Serial.println(signalMax);
  // // Serial.println(signalMin);
  // Serial.println(sample);
  int sensorValue = analogRead(SENSOR_PIN);

  // 将传感器值映射到 0-1023 范围内
  // float voltage = sensorValue * (5.0 / 1023.0);

  // // 使用声音传感器的灵敏度和参考电压进行分贝计算
  // float db = 20 * log10(voltage / 0.005);
  float db = (sensorValue + 83.2073) / 11.003;

  lcd.setCursor(0, 0);
  lcd.print("Loudness: ");
  Serial.println(db);
  lcd.print(db);
  lcd.print("dB");
  
  if (db < 31)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: Rest");
    // digitalWrite(PIN_QUIET, HIGH);
    // digitalWrite(PIN_MODERATE, LOW);
    // digitalWrite(PIN_LOUD, LOW);
    servo.write(90); // 在 Quiet 水平下停止舵机
  }
  else if (db >= 31 && db < 59)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: Work");
    // digitalWrite(PIN_QUIET, LOW);
    // digitalWrite(PIN_MODERATE, HIGH);
    // digitalWrite(PIN_LOUD, LOW);
    // 在 Moderate 水平下循环旋转舵机
    for (int angle = 0; angle <= 180; angle += 1)
    {
      servo.write(angle);
      delay(15);
    }
    for (int angle = 180; angle >= 0; angle -= 1)
    {
      servo.write(angle);
      delay(15);
    }
  }
  else if (db >= 59)
  {
    lcd.setCursor(0, 1);
    lcd.print("Status: Noisy");
    // digitalWrite(PIN_QUIET, LOW);
    // digitalWrite(PIN_MODERATE, LOW);
    // digitalWrite(PIN_LOUD, HIGH);
    // 在 High 水平下随机移动舵机
    int randomAngle = random(0, 180);
    servo.write(randomAngle);
    delay(15); 
  }
  
  delay(1800);
  lcd.clear();
}
// long readVcc() {
//   // Read 1.1V reference against AVcc
//   // set the reference to Vcc and the measurement to the internal 1.1V reference
//   #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
//     ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
//   #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
//     ADMUX = _BV(MUX5) | _BV(MUX0);
//   #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
//     ADMUX = _BV(MUX3) | _BV(MUX2);
//   #else
//     ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
//   #endif  

//   delay(2); // Wait for Vref to settle
//   ADCSRA |= _BV(ADSC); // Start conversion
//   while (bit_is_set(ADCSRA,ADSC)); // measuring

//   uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
//   uint8_t high = ADCH; // unlocks both

//   long result = (high<<8) | low;

//   result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
//   return result; // Vcc in millivolts
// }
