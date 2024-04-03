#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>

#define TRIGGER_PIN D1  // Replace D1 with the pin you are using

//----------------------------------------------------------

//const char* TOKEN       =        "CvhLABdOIePBpux83mKU";  // enter access token of your ThingsBoard Device
//const char* THINGSBOARD_SERVER = "demo.thingsboard.io";

const char* mqtt_broker = "73d972e132fd49e8a46eda35bc71821a.s1.eu.hivemq.cloud";
const int mqtt_port =8883;
const char* mqtt_username = "hivemq_test";
const char* mqtt_password = "Idunknow1";
//-----------------------------------------------------
const char* topic_sub = "test";

static const char *root_ca PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";

//----------------------------------------------------
uint16_t THINGSBOARD_PORT = 1883U;

uint32_t MAX_MESSAGE_SIZE = 256U;


// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD   115200

//--------------------------------------------------
int var = 1;
bool subscribed = false;
typedef union exchange
{
    float fl;
    uint8_t seg[4];
}Convert;

//-------------------------------------------------------------
  float weight_t;
 static Convert bmi;

 static Convert Scale[4];

uint8_t STM32_Buffer[24];
uint8_t Head_count,Tail_count = 0;

  
// Initialize ThingsBoard client
WiFiClientSecure espClient;
// Initialize ThingsBoard instance
PubSubClient client(espClient);
// the Wifi radio's status
int status = WL_IDLE_STATUS;
 static Convert weight;

 

//-----------------------------------------------------------
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "hivemq_test", "Idunknow1")) {
      Serial.println("connected");

      client.subscribe("test");   // subscribe the topics here

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");   // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//--------------------------------------------------------------------------------
void callback(char* topic, byte* payload, unsigned int length) {
  String incommingMessage = "";
  for (int i = 0; i < length; i++) incommingMessage+=(char)payload[i];

  Serial.println("Message arrived ["+String(topic)+"]"+incommingMessage);

//  //--- check the incomming message
//    if( strcmp(topic,"led_state") == 0){
//     if (incommingMessage.equals("1")) digitalWrite(led, HIGH);   // Turn the LED on
//     else digitalWrite(led, LOW);  // Turn the LED off
//  }

}
//-------------------------------------------------------------------------------
void publishMessage(const char* topic, String payload , boolean retained){
  if (client.publish(topic, payload.c_str(), true))
      Serial.println("Message publised ["+String(topic)+"]: "+payload);
}

//---------------------------------------------------------------------------

void STM32_Uart_Buffer(uint8_t Buffer_temp)
{

  if(Head_count == 24)
  {
    Head_count = 0;
  }
    STM32_Buffer[Head_count] = Buffer_temp;
   Head_count++;
}

//-------------------------------------------------------------------------

uint8_t STM32_Uart_Return()
{
   uint8_t Wifi_temp;  
  if(Tail_count == 24)
  {
    Tail_count = 0;
  }
  Wifi_temp = STM32_Buffer[Tail_count];
  Tail_count++;
  return Wifi_temp;
}

//--------------------------------------------------------------------------
void STM32_Msg(Convert *Convert_temp)
{
  for(int i = 0;i<4;i++)
  {
    Convert_temp->seg[i] =STM32_Uart_Return();
  }
}

 //------------------------------------------------------------------------
void setup() {
    Serial.begin(115200);
//    Serial1.begin(115200);
    pinMode(TRIGGER_PIN, INPUT_PULLUP);  // Set the trigger pin as an input with internal pull-up resistor
    // Other setup code

  #ifdef ESP8266
    espClient.setInsecure();
  #else
    espClient.setCACert(root_ca);      // enable this line and the the "certificate" code for secure connection
  #endif
    
    client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
}


void loop() {
    // Read the state of the trigger pin
    delay(1000);
 
    int triggerState = digitalRead(TRIGGER_PIN);
//-----------------------------------------------------------------------------
    // Check if the trigger pin is LOW (button pressed)
    if (triggerState == LOW) {
        // Clear WiFiManager's saved configuration
        WiFiManager wifiManager;
        wifiManager.resetSettings();
        
        // Start the configuration portal
        wifiManager.startConfigPortal("ESP8266_AP");
        
        // After configuration, the loop continues here
       
        Serial.println("IP address: " + WiFi.localIP().toString());
    }
    //-------------------------------------------------------------------------
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
       WiFiManager wifiManager;
        wifiManager.resetSettings();
        
        // Start the configuration portal
        wifiManager.startConfigPortal("ESP8266_AP");
        
        // After configuration, the loop continues here
       
        Serial.println("IP address: " + WiFi.localIP().toString());
  }
  
  //-------------------------------------------------------------------------------
       if (!client.connected()) reconnect(); // check if client is connected
      client.loop();
//    if (!tb.connected()) {
//    subscribed = false;
//    // Connect to the ThingsBoard
//    Serial.print("Connecting to: ");
//    Serial.print(THINGSBOARD_SERVER);
//    Serial.print(" with token ");
//    Serial.println(TOKEN);
//    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
//      Serial.println("Failed to connect");
//      return;
//    }
//    }


      if (Serial.available()) {
    Serial.print("Received data: ");
    
    for(int i = 0;i<24;i++)
    {
      uint8_t Data_in = Serial.read();
      STM32_Uart_Buffer(Data_in);
    }
     STM32_Msg(&weight);
     STM32_Msg(&bmi);
     for(int i = 0;i<4;i++)
     {
      STM32_Msg(&Scale[i]);
     }

     
      DynamicJsonDocument doc(1024);
      
    doc["weight"] = weight.fl;
    doc["bmi"] = bmi.fl;
    doc["Scale0"] = Scale[0].fl;
    doc["Scale1"] = Scale[1].fl;
    doc["Scale2"] = Scale[2].fl;
    doc["Scale3"] = Scale[3].fl;
     
   
    char mqtt_message[128]; 
    
  serializeJson(doc, mqtt_message);
  
  Serial.print(mqtt_message);
  publishMessage("test", mqtt_message, true);
  }



//  tb.sendTelemetryFloat("weight", weight_t);
//  tb.loop();
}
