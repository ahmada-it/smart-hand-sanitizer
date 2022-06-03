#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

SoftwareSerial ss(D6,D5); // D6 to pin 3 Arduino, D5 to pin 2 Arduino

const char* ssid = "QUEEN";
const char* password = "123queen";

#define BOTtoken "5569808553:AAGxv8W6BbdcAXoAoZoHCacxsYVs1Oa3nSI"

#define CHAT_ID "1097157888"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(9600);
  ss.begin(115200);
  WiFi.begin(ssid, password);

  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop() {
//  Serial.println("...");
  String tmpValue = "";
  String msg = "";
  while(ss.available() > 0){
    char mychar = ss.read();
    tmpValue += mychar;
    delay(10);
  }

  if(tmpValue != ""){
    
    if(WiFi.status() == WL_CONNECTED){
        if(tmpValue.charAt(0) == '@'){
          String newTmpValue = "";
          for(int i=1;i<tmpValue.length();i++){
              newTmpValue += tmpValue.charAt(i);
          }

          WiFiClient client;
          HTTPClient http;
          String url = "";
//          url += "Infrared=";
          url += tmpValue.charAt(1);
          
          Serial.println(url);
          http.begin(client,url);  
          http.GET();
          String payload = http.getString();  
          Serial.println('#' + String(payload));  
          http.end();

          if(url == "0"){
            bot.sendMessage(CHAT_ID, "Handsanitizer On!", "");
            Serial.println("Handsanitizer On!");
          }
          else{
            Serial.println("Handsanitizer Off!");
          }
        } 

    }
  }

  
  if(WiFi.status() != WL_CONNECTED){
    recon();
  }
  
   delay(50);
}

void recon(){
  while(WiFi.status() != WL_CONNECTED){

    //wifi reload connection
    WiFi.begin(ssid, password);
    delay(1000);

  }
}
