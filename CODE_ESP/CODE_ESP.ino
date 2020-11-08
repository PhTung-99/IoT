#include<Wire.h>
#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
SocketIoClient webSocket;
const char* ssid = "PT";          //Tên mạng Wifi mà Socket server của bạn đang kết nối
const char* password = "111222333";  //Pass mạng wifi ahihi, anh em rãnh thì share pass cho mình với.
String DoAmH, NhietDoT;
float tempH, tempT;
String str, tempStr;
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
  str="";
  webSocket.loop();
  uint64_t now = millis();
  if (now - messageTimestamp > 1000) {
    messageTimestamp = now;
    
    if(DoAmH.toFloat() != tempH || NhietDoT.toFloat() != tempT )
    {
      tempStr = "{\"DoAm\":\"" + DoAmH +"\", \"NhietDo\":\"" + NhietDoT +"\"}";
      webSocket.emit("DTH11", tempStr.c_str());
      tempH = DoAmH.toFloat();
      tempT= NhietDoT.toFloat();
    }
    webSocket.emit("DTH11", tempStr.c_str());
    
    
  }
  Wire.requestFrom(8, 11); /* request & read data of size 13 from slave */
  while(Wire.available()){
    char c = Wire.read();
    str  = String(str + c);
    NhietDoT = getValue(str, ',', 0);
    DoAmH = getValue(str, ',', 1);
    
 }
}
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
