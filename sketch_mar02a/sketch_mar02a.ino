#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
MDNSResponder mdns;
 
ESP8266WebServer server(80);
String webPage;
const char* ssid     = "Van Tri";      //Thay tên wifi ở đây
const char* password = "01223678660";  //Thay tên password ở đây
 
void setup() {
 
  pinMode(12, OUTPUT);  //led chân 12
  pinMode(13, OUTPUT);  //led chân 13
 
  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
  
  Serial.begin(115200);
  delay(100);
 
 
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
  
  if (mdns.begin("esp8266", WiFi.localIP())) 
    Serial.println("MDNS responder started");
 
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    //Bật led 12
    digitalWrite(12, HIGH);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    //Tắt led 12
    digitalWrite(12, LOW);
    delay(1000); 
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    //Bật led 13
    digitalWrite(13, HIGH);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    //Tắt led 13
    digitalWrite(13, LOW);
    delay(1000); 
  });
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop() {
  server.handleClient();
}
