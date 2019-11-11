#include <WiFi.h>

const char* ssid = "SoutheastGuest";  // make sure to change it with your Wifi name
const char* password = "helpfulriver847";  // change this with your WiFi password 

WiFiServer server(80);
String header;


void setup() {

pinMode(LED_BUILTIN, OUTPUT);
pinMode(13 , OUTPUT);
pinMode(12 , OUTPUT);
pinMode(14 , OUTPUT);


Serial.begin(115200);

Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
// Print local IP address and start web server
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.begin();
}

void loop(){
WiFiClient client = server.available(); // Listen for incoming clients

if (client) { // If a new client connects,
Serial.println("New Client."); // print a message out in the serial port
String currentLine = ""; // make a String to hold incoming data from the client
while (client.connected()) 
{ // loop while the client's connected
if (client.available()) { // if there's bytes to read from the client,
char c = client.read(); // read a byte, then
Serial.write(c); // print it out the serial monitor
header += c;
if (c == '\n') { // if the byte is a newline character
// if the current line is blank, you got two newline characters in a row.
// that's the end of the client HTTP request, so send a response:
if (currentLine.length() == 0) {

client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();
client.println("<!DOCTYPE html>\n");
client.println("<html>\n");
client.println("<body>\n");
client.println("<center>\n");
client.println("<h1 style=\"color:blue;\">CY510 Fianl Project</h1>\n");
client.println("<h2 style=\"color:green;\">CY Group: ???????</h2>\n");
client.println("<h2 style=\"color:blue;\">Controlled lights by admin privlages</h2>\n");
client.println("<h2 style=\"color:red;\">Login to get a list of your controls</h2>\n");
client.println("<input>\n");
client.println("</center>\n");
client.println("</body>\n");
client.println("</html>");
break;

} 
else { // if you got a newline, then clear currentLine
currentLine = "";
}
} else if (c != '\r') { // if you got anything else but a carriage return character,
currentLine += c; // add it to the end of the currentLine
}

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /G")) {
          digitalWrite( 14 , HIGH);
        }
        
        if (currentLine.endsWith("GET /R")) {
          digitalWrite( 12 , HIGH);
        }
        if (currentLine.endsWith("GET /RL")) {
          digitalWrite( 12 , HIGH);
        }
        
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);
          digitalWrite( 13 , HIGH);
          //digitalWrite( 12 , HIGH);// GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);  
          digitalWrite( 13 , LOW);
          digitalWrite( 12 , LOW);
          digitalWrite( 14 , LOW);// GET /L turns the LED off
        }
}
}
// Clear the header variable
header = "";
// Close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
