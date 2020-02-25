#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h> 

const unsigned int TRIG_PIN=5;
const unsigned int ECHO_PIN=4;

#define WIFI_SSID "LOTODA"   //Enter your WIFI SSID
#define WIFI_PASSWORD "0388187172"   //Enter your WiFi password
#define BUILTIN_LED 2
char LotodaServer[]  = "app.lotoda.vn";     //app.lotoda.vn is the default servername
int LotodaPort  = 1883;                     //1883 is the default port
char deviceId[]  = "LotodaEsp8266-0001";  //every device should have a different name
char topic[]  = "794fe7dc5d/SRF05"; //Enter <User_ID_Key> from LOTODA system, the topic should be different for each device as well
                                            //Please create this new topic on LOTODA mobile app, in this case is "lamp/power"
char User_ID_Key[]  = "794fe7dc5d";         //Enter <User_ID_Key> from LOTODA system
char Password_ID_Key[]  = "g6xrX3InCzkgoMwOEf";  //Enter <Password_ID_Key> from LOTODA system

WiFiClient wifiClient;
PubSubClient client(wifiClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  if ( !client.connected() ) {
    connect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
  
    const unsigned long duration= pulseIn(ECHO_PIN, HIGH);
    int distance= duration/29/2;
    if(duration==0){
     Serial.println("Warning: no pulse from sensor");
    } 
    else{
        Serial.print("distance to nearest object:");
        Serial.println(distance);
        Serial.println(" cm");
    }
    char distanceString[6];
    dtostrf(distance, 1, 2,distanceString);
    String key = "{\"Distance\":";
    String endkey = "}";
    String str = key + distanceString + endkey;
    char data[20];
    str.toCharArray(data, (str.length() + 1)); 
    Serial.println(data);
    client.publish(topic, data);
  }
  
 }
 void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void connect() {
  while (!client.connected()) {
    if ( WiFi.status() != WL_CONNECTED) {
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.print("Connected to ");
      Serial.println(WIFI_SSID);
    }
    client.setServer(LotodaServer, LotodaPort);
    client.setCallback(callback);
    if (client.connect(deviceId, User_ID_Key, Password_ID_Key)) {
      client.subscribe(topic);
      Serial.println("Connected to LOTODA's Server");
    } else {
      Serial.print("[FAILED] [ rc = ");
      Serial.print(client.state() );
      Serial.println(" : retrying in 5 seconds]");
      delay(5000);
    }
  }
}
