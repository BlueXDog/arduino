#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>
#include <FirebaseJson.h>

#include <ESP8266WiFi.h>


FirebaseData firebaseData;
//current color value 
int redValue=0;
int greenValue=0;
int blueValue=0;



void connectWifi() {
  // Let us connect to WiFi
  String ssid="G-Group Hoi Truong";
  String password="Ggroup@2018";
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".......");
  Serial.println("WiFi Connected....IP Address:");
  Serial.println(WiFi.localIP());
}
void printToSerial(){
  Serial.println(".............................");
  Serial.print("red value:");
  Serial.println(redValue);
  Serial.print("green value :");
  Serial.println(greenValue);
  Serial.print("blue value:");
  Serial.println(blueValue);
  
}
void updateData(String vitri,int doam,int dobui, int nhietdo){
  FirebaseJson updateData;
  FirebaseJson infoJson;
  
  infoJson.set("doam",doam);
  infoJson.set("dobui",dobui);
  infoJson.set("nhietdo",nhietdo);
  updateData.set(vitri,infoJson);

  if (Firebase.updateNode(firebaseData, "/weatherinfo", updateData)) {

  Serial.println(firebaseData.dataPath());

  Serial.println(firebaseData.dataType());

  Serial.println(firebaseData.jsonString()); 

} else {
  Serial.println(firebaseData.errorReason());
}
}
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  connectWifi();
  Firebase.begin("https://fir-messapp-ca232.firebaseio.com/", "xkUOHsSKG68YKyCMMhWwQDtE85sjnMtmp4U94qs4");
  updateData("bachkhoa",100,100,200);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  
  if (Firebase.getInt(firebaseData, "/red")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != redValue) {
        redValue = val;
         printToSerial();
      }
    }
  }
  if (Firebase.getInt(firebaseData, "/green")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != greenValue) {
        greenValue = val;
        printToSerial();
      }
    }
  }
  if (Firebase.getInt(firebaseData, "/blue")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != blueValue) {
        blueValue = val;
        printToSerial();
      }
    }
  }

  delay(1000);
 
  
  digitalWrite(LED_BUILTIN, LOW);
}
