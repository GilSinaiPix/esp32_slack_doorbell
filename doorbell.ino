
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti WiFiMulti;

RTC_DATA_ATTR int bootCount = 0;

int wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case 1  : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case 2  : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case 3  : Serial.println("Wakeup caused by timer"); break;
    case 4  : Serial.println("Wakeup caused by touchpad"); break;
    case 5  : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.println("Wakeup was not caused by deep sleep"); break;
  }

  return wakeup_reason;
}

void slack() {
  HTTPClient http;
  http.begin("https://hooks.slack.com/services/T3B__775GLE/B9E__E4DA/Q4y7Cje___dH87NjUWSDre9U"); 
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST("{'username':'uksekell', 'text':':door::bell: KOP KOP'}");
  
  
  if(httpCode > 0) {
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  } else {
    Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  //http.end();
  Serial.println ("Slack done");
}

void setup(){
  int wr;

  // NB! if your network is open, you need to supply password here, 
  // empty string for wifi password seems not to be implemented yet
  
  const char* ssid = "WIFI SSID";
  const char* password =  "WPA ";


  Serial.begin(115200);
  delay(20); 

  bootCount++;
  
  Serial.println("Boot number: " + String(bootCount));

  wr = wakeup_reason();
  if (bootCount > 1 && wr == 1) {
    WiFiMulti.addAP(ssid, password);
    

    //WiFi.begin (ssid, password);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println (ssid);
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
    //while(WiFi.status() != WL_CONNECTED) {

        Serial.print(".");
        delay(200);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    slack();
  }

  Serial.println("Going to sleep now");  

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_14,0); //1 = High, 0 = Low
  esp_deep_sleep_start();  
}

void loop(){
  //This is not going to be called
}
