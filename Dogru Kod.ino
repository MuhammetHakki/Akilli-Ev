// Muhammet Hakkı Genç 
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

//1. Firebase veritabanı adresini, Token bilgisini ve ağ adresi bilgilerinizi giriniz.
#define FIREBASE_HOST "/" // http:// veya https:// olmadan yazın
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

FirebaseData veritabanim;
String lambadurum="0";

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Ağ Bağlantısı Oluşturuluyor");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP adresine bağlanıldı: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.reconnectWiFi(true);
 pinMode(D0,OUTPUT);
 digitalWrite(D0,HIGH);
}

void loop()
{

  if(Firebase.getString(veritabanim, "/")) //Alınacak veri tipine göre getInt, getBool, getFloat, getDouble, getString olarak kullanılabilir.
  {
    if (veritabanim.stringData().substring(0,1)!=lambadurum){ 
      lambadurum=veritabanim.stringData().substring(0,1);
    
    if (lambadurum=="1"){
      
      digitalWrite(D0,LOW);

      Serial.println("Lamba Açık");
    }
    else {
      
      digitalWrite(D0,HIGH);
      Serial.println("Lamba Kapalı");

  }}

  else{

    Serial.print("Str verisi çekilemedi, ");
    Serial.println(veritabanim.errorReason());
  }


}}
