#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define TRIGGER 5 //Pin D1
#define ECHO    4 //Pin D2

void setup() {                
  WiFi.begin("YOURWIFISSID", "YOURWIFIPASS");
 
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500); 
  }
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
}

void loop() {
      long duration;
      long distance;
      digitalWrite(TRIGGER, LOW);  
      delayMicroseconds(2); 
      
      digitalWrite(TRIGGER, HIGH);
      delayMicroseconds(10); 
      
      digitalWrite(TRIGGER, LOW);
      duration = pulseIn(ECHO, HIGH);
      distance = (duration/2) / 29.1;
      
    if(WiFi.status()== WL_CONNECTED){   
 
     HTTPClient http;    
   
     http.begin("http://192.168.0.2:5000/savedata");
     http.addHeader("Content-Type", "text/plain");  
     
     int httpCode = 0;
     httpCode = http.POST(String(distance));
     
     http.end();  
   }
   delay(300000);// 60s*5*1000ms -> 5 minute
}
