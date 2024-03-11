
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
ESP8266WebServer server;
#include <SoftwareSerial.h>  
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//nazev wifi site a jeji heslo
char* ssid = "PC-1";
char* password = "qwertzuiop";

int port = 443;
double hladinaP;
double kapacitaP;
double teplotaP;
double vlhkostP;
String data;
String myString;
String str;

// sensors
double sensor1; 
float sensor2;
float sensor3;
float sensor4;

 
float data1; 
int data2; 
int data3; 
int data4; 
char buff[100];
unsigned long wait = 0;

// nastaveni url adresy pro zobrazeni dat na web strance
const char* serverName = "http://192.168.137.62/sensordata/post-esp-data.php";
//klic k overeni komunikace
String apiKeyValue = "tPmAT5Ab3j7F9";

void setup()
{
  WiFi.begin(ssid,password);
  Serial.begin(115200);

  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{  
  //precteni odeslaneho retezce z koncentratoru pres seriovou linku    
  data = Serial.readString();
  Serial.println(data);
  Serial.println("-----------------------------");
  data.toCharArray(buff,30);
  
  myString = buff;
  Serial.println("-------------buff.message----------------");
  Serial.println(myString);
  Serial.println("-----------------------------");
  //rozdeleni retezce unikatnim znakem pomoci funkce getValue() na jednotlive promenne
  String l = getValue(myString, ',', 0); // sensor1
  String m = getValue(myString, ',', 1); // sensor2
  String n = getValue(myString, ',', 2); // sensor3
  String o = getValue(myString, ',', 3); // sensor4
  
  data1 = l.toInt();
  data2 = m.toInt();
  data3 = n.toInt();
  data4 = o.toInt();
  
  sensor1 = data1; 
  sensor2 = data2; 
  sensor3 = data3; 
  sensor4 = data4;
//vytisk prijatych dat
  Serial.println("*********data************"); 
  Serial.println(sensor1);  
  Serial.println(sensor2);
  Serial.println(sensor3);
  Serial.println(sensor4);
   //overeni statusu pripojeni k WiFi
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    WiFiClient client;
    
    // url adresa pro zahajeni http protokolu
    http.begin(client,"http://192.168.137.1/sensordata/post-esp-data.php");
    
    //urceni zobrazovaneho kontentu
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    //priprava http POST pozadavku
    String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + String(sensor1) + "&value2=" + String(sensor2) + "&value3=" + String(sensor3) + "&value4=" + String(sensor4);
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);
    //zobrazeni stavovych kodu
  if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    //ukonceni http
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //odeslani http POST pozadavku kazdych 30 sekund
  delay(30000);  
}
//funkce pro ziskani dat z retezce pomoci oddelovaciho znaku
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
