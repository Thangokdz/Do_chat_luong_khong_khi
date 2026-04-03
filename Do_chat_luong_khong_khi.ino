#include <Wire.h>
#include <Servo.h>

Servo fanServo;

// cảm biến
#define MQ135 A0
#define DUST_SENSOR A1
#define LED_DUST 7

// nút
#define BUTTON_POWER 2
#define BUTTON_FAN 3

// relay quạt
#define RELAY_FAN 8

// servo
#define SERVO_PIN 9

// LED MQ
#define MQ_GREEN 4
#define MQ_RED 6

// LED Dust
#define D_GREEN 10
#define D_RED 12

// ngưỡng
int gasThreshold = 300;
int dustThreshold = 300;

bool systemON = false;
bool fanON = false;
bool sensorEnable = true;

unsigned long lastRead = 0;

unsigned long powerPressTime = 0;
unsigned long fanPressTime = 0;

bool powerHandled = false;
bool fanHandled = false;

int gasValue = 0;
int dustValue = 0;

void setup()
{
  pinMode(LED_DUST, OUTPUT);

  pinMode(BUTTON_POWER, INPUT_PULLUP);
  pinMode(BUTTON_FAN, INPUT_PULLUP);

  pinMode(RELAY_FAN, OUTPUT);

  pinMode(MQ_GREEN,OUTPUT);
  pinMode(MQ_RED,OUTPUT);

  pinMode(D_GREEN,OUTPUT);
  pinMode(D_RED,OUTPUT);

  fanServo.attach(SERVO_PIN);
  fanServo.write(95);   // góc ban đầu
  delay(500);          // cho servo ổn định

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop()
{
  checkButtons();

  if(systemON && sensorEnable)
  {
    if(millis() - lastRead > 2000)
    {
      readSensors();
      displayStatus();
      lastRead = millis();
    }
  }
  else if(!systemON)
  { lcd.setCursor(0,0);
    lcd.print("Dang tat ");
    lcd.setCursor(0,1);
    lcd.print("kich hoat lai   ");
    delay(500);
  }
}

void checkButtons()
{
  bool powerState = digitalRead(BUTTON_POWER);
  bool fanState = digitalRead(BUTTON_FAN);

  // ===== NÚT POWER =====
  if(powerState == LOW)
  {
    if(powerPressTime == 0)
      powerPressTime = millis();

    if(millis() - powerPressTime >= 500 && !powerHandled)
    {
      systemON = !systemON;
      powerHandled = true;

      if(systemON)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("He thong dang");
        lcd.setCursor(0,1);
        lcd.print("chay...");

        sensorEnable = true;   // bật lại sensor ngay

        delay(1500);
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("He thong tat");
        // tắt relay quạt
        digitalWrite(RELAY_FAN, LOW);

        // tắt LED MQ
        digitalWrite(MQ_GREEN, LOW);
        digitalWrite(MQ_RED, LOW);

        // tắt LED Dust
        digitalWrite(D_GREEN, LOW);
        digitalWrite(D_RED, LOW);

        // servo quay về vị trí đóng
        fanServo.write(95);

        // dừng đọc sensor
        sensorEnable = false;

        delay(1000);
      }
    }
  }
  else
  {
    powerPressTime = 0;
    powerHandled = false;
  }

  // ===== NÚT FAN =====
  if(fanState == LOW)
  {
    if(fanPressTime == 0)
      fanPressTime = millis();

    if(millis() - fanPressTime >= 500 && !fanHandled)
    {
      fanON = !fanON;
      fanHandled = true;

      if(fanON)
      {
        digitalWrite(RELAY_FAN,HIGH);

        lcd.clear();
        lcd.print("Mo cua quat");

        fanServo.write(0);
        delay(1000);
        // fanServo.write(50);
        // delay(1500);
        // fanServo.write(0);
        // delay(700);
       
      }
      else
      {
        digitalWrite(RELAY_FAN,LOW);

        lcd.clear();
        lcd.print("Dong cua quat");

        fanServo.write(95);
        delay(1500);
      }
    }
  }
  else
  {
    fanPressTime = 0;
    fanHandled = false;
  }
}

void readSensors()
{
  gasValue = analogRead(MQ135);

  digitalWrite(LED_DUST, LOW);
  delayMicroseconds(280);

  dustValue = analogRead(DUST_SENSOR);

  delayMicroseconds(40);
  digitalWrite(LED_DUST, HIGH);
}

void displayStatus()
{
  bool gasDanger = gasValue > gasThreshold;
  bool dustDanger = dustValue > dustThreshold;

  lcd.clear();

  if(!gasDanger && !dustDanger)
  {
    lcd.print("Khong khi tot");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("Khong khi o nhiem");
  }

  setMQColor(gasValue);
  setDustColor(dustValue);
}

void setMQColor(int value)
{
  if(value < gasThreshold)
  {
    digitalWrite(MQ_GREEN,HIGH);
    digitalWrite(MQ_RED,LOW);
  }
  else
  {
    digitalWrite(MQ_GREEN,LOW);
    digitalWrite(MQ_RED,HIGH);
  }
}

void setDustColor(int value)
{
  if(value < dustThreshold)
  {
    digitalWrite(D_GREEN,HIGH);
    digitalWrite(D_RED,LOW);
  }
  else
  {
    digitalWrite(D_GREEN,LOW);
    digitalWrite(D_RED,HIGH);
  }
}