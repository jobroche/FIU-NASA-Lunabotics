#include "WiFly.h"
#include "Credentials.h"
#include "Sabertooth.h"

Server server(80);
Sabertooth saberTooth;


void setup() {
  
 WiFly.begin();

  if (!WiFly.join(ssid, passphrase)) {while (1) {Serial.println("Error joining wireless");}}

  Serial.begin(9600);
  Serial.print("IP: ");
  Serial.println(WiFly.ip());
  
  server.begin();
  
}


void loop() {  
  
  Client client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean current_line_is_blank = true;
    String requestString;
    while (client.connected()) {
      
      if (client.available()) {
        
        char c = client.read();        
        if (requestString.length() < 30){requestString.concat(c);} //read http headers and store them within requestString
        
        // if we've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so we can send a reply
        
        if (c == '\n' && current_line_is_blank) {
          
          if (requestString.indexOf("/MoveForward") > 0){saberTooth.setSpeed(100);}
          if (requestString.indexOf("/MoveLeft") > 0){Serial.println("moving left");}
          if (requestString.indexOf("/MoveRight") > 0){Serial.println("moving right");}
          if (requestString.indexOf("/MoveReverse") > 0){Serial.println("moving reverse");}
          if (requestString.indexOf("/Stop") > 0){saberTooth.setSpeed(0);}
          
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          
          client.println("<input type=\"button\" value=\"forward\" onclick=\"window.location.href='/MoveForward'\">");
          client.println("<input type=\"button\" value=\"left\" onclick=\"window.location.href='/MoveLeft'\">");       
          client.println("<input type=\"button\" value=\"right\" onclick=\"window.location.href='/MoveRight'\">");   
          client.println("<input type=\"button\" value=\"back\" onclick=\"window.location.href='/MoveReverse'\">"); 
          client.println("<input type=\"button\" value=\"stop\" onclick=\"window.location.href='/Stop'\">");        
             
           break;
         
        }
        if (c == '\n') {
          // we're starting a new line
          current_line_is_blank = true;
        } else if (c != '\r') {
          // we've gotten a character on the current line
          current_line_is_blank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(100);
    client.stop();
  }
}
