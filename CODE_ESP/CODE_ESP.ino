#include<Wire.h>
#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
SocketIoClient webSocket;
const char* ssid = "PT";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char* password = "111222333";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.
 
char host[] = "192.168.1.43";  //Địa chỉ IP dịch vụ, hãy thay đổi nó theo địa chỉ IP Socket server của bạn.
int port = 3000;  
void messageEvenetHandler(const char * payload, size_t length) {
    Wire.beginTransmission(8); /* begin with device address 8 */
    Wire.write(payload);  /* sends hello slave string */
    Wire.endTransmission(); 
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Wire.begin(D1, D2);
  Serial.print("Ket noi vao mang ");
  Serial.println(ssid);
 
    //Kết nối vào mạng Wifi
    WiFi.begin(ssid, password);
 
    //Chờ đến khi đã được kết nối
    while (WiFi.status() != WL_CONNECTED) { //Thoát ra khỏi vòng 
        delay(500);
        Serial.print('.');
    }
 
    Serial.println();
    Serial.println(F("Da ket noi WiFi"));
    Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());
  webSocket.on("sttXe", messageEvenetHandler);
  webSocket.begin("192.168.1.34", 3000);
}
uint64_t messageTimestamp;
void loop() {
  webSocket.loop();
  uint64_t now = millis();
  if (now - messageTimestamp > 100) {
    messageTimestamp = now;
    // Send event
    webSocket.emit("message", "\"this is a message from the client\"");
  }
  
}
