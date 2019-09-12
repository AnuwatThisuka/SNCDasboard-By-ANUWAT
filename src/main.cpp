#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid     = "iPhone";
const char* password = "Anuwat096279";
const char* host = "172.20.10.4";
char auth[] = "ONBkinvEfvLm661cyF-lCw8z4Sr56xgv";

#define BLYNK_PRINT Serial
const int inputcount = 4;
int val1;
int count = 0;
int press = 0;

//int Led = 2;

int xxx = 0;
int i = 0;
int j = 0;
int Status;
const int inputMachine1 = 13;
int buttonState = 0;
BLYNK_CONNECTED()
{
  Blynk.syncAll();
}
WidgetLED Machine1(V0);
WidgetLED Machine2(V1);
WidgetLED Machine3(V2);
WidgetLCD Lcd(V5);

// Config Firebase
/*
#define FIREBASE_HOST "dashboard-snc-demo.firebaseio.com"
#define FIREBASE_AUTH "vivMlWc4wwQmLvKmbojDNnef7ZXhU5aTBcheyweO"*/


void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(inputMachine1, INPUT); 
  pinMode(inputcount, INPUT);
  Blynk.begin(auth, "ssid", "pass");
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT;)
  pinMode(15,OUTPUT);
  digitalWrite(2,HIGH);
  digitalWrite(15,LOW);
  digitalWrite(4,HIGH;)
int value = 0;
//Fuction สถานะการทำงานของเครื่อง
void OnMachine1()
{
  buttonState = digitalRead(inputMachine1);
  if (buttonState == LOW)
  {
    Machine1.on();
    Serial.println("ON");
  }
  else
  {
    Machine1.off();
    Serial.println("OFF");
}
}
//Fuction นับค่าจากเครื่องจักร
void count1()
{
  if (digitalRead(4) == 1)
  {
    if (press == 0)
    {
      count++;
      Lcd.clear();
      Lcd.print(0, 0,"Bending work");
      Lcd.print(0, 1, count);
      press = 1;
    }
  }
  else
  {
    press = 0;
  }
}
void CounterTest(){
  Serial.print("Counter");
  j++;
  //j++;
}
void loop() {
  count1();
  CounterTest();
  OnMachine1();
  Blynk.run();
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

    //ส่งค่าไปยัง Mysql
  delay(2000);
  String url = "/sncdashboard/To_databases.php?";
  url += "Machine1=";
  url += j++;
  url += "&Machine2=";
  url += j++;
  url += "&Machine3=";
  url += j++;
  url += "&StatusMachine1=";
  url += "on";
  url += "&StatusMachine2=";
  url += "on";
  url += "&StatusMachine3=";
  url += "on";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
    Serial.println();
    if(line.indexOf("บันทึกสำเร็จ") != -1)
    {
      Serial.println("success");
    } else if(line.indexOf("บันทึกสำเร็จ") != -1)
    {
      Serial.println("success");
    }
  }
  Serial.println("success");
  Serial.println("closing connection");
  delay(500);
}