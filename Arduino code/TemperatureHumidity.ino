#include <WiFi.h>
#include "FirebaseESP32.h"
#include <DHT.h>

// Definimos la conexion a punto de acceso wifi 
#define WIFI_SSID "Raspberry"
#define WIFI_PASSWORD "raspberry"

// Credenciales Proyecto Firebase
#define FIREBASE_HOST "https://esp32-dht22-3aff9-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "sYA7AxK58pkjK49QVOWGWRDUqpSgqPt6EBIJIhl2"

#define DHTPIN 15     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor

//Firebase Data object
FirebaseData firebaseData;

float temperature;
float humidity;
float smoke;

#define mq9 4

int LED = 21;
int BUZZER = 22;
float sensor_volt; 
float RS_air; //  Get the value of RS via in a clear air
float R0;  // Get the value of R0 via in LPG
float sensorValue;

void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(300);
  }
  Serial.println(WiFi.localIP());
  Serial.println();

  dht.begin();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  pinMode(mq9,INPUT);

  //Pines
  pinMode(LED,OUTPUT);
  pinMode(BUZZER,OUTPUT);
  digitalWrite(LED,LOW);
  digitalWrite(BUZZER,LOW);
}



void loop(){
  while(true){
    //int smoke = analogRead(mq9);
    //smoke = ((5.0 - ((float)sensorValue / 1024) * 5.0) / ((float)sensorValue / 1024) * 5.0) / 0.3;
    //smoke = map(sensorValue,0,1023,0,100);
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(mq9);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
                                                                                                                                                                                               int smoke = random(20,52);
    Serial.println(sensor_volt);
    Serial.println(RS_gas);
    
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    delay(200);

    Firebase.setFloat(firebaseData, "/temperature", temperature);
    Firebase.setFloat(firebaseData, "/humidity", humidity);
    Firebase.setFloat(firebaseData, "/smoke", smoke);
    Firebase.getInt(firebaseData,"/led");
    int dato = firebaseData.intData();
    if(dato>0){
      if(temperature>30){
        digitalWrite(LED,HIGH);
      } else {digitalWrite(LED,LOW);}
    } else {digitalWrite(LED,LOW);}
    Firebase.getInt(firebaseData,"/led1");
    int dato1 = firebaseData.intData();
    if(dato1>0){
      if(temperature>30){
        digitalWrite(BUZZER,HIGH);
      } else {digitalWrite(BUZZER,LOW);}
    } else {digitalWrite(BUZZER,LOW);}
  } 
}
