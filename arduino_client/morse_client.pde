/*
 * A simple sketch that uses WiServer to check for new tweets, and prints them every 30 seconds
 */
#define USE_SERIAL    1  // Should we initialize and use the serial? (0/1)
#define USE_WIRELESS  1  // Should we initialize and use the wireless? (0/1)

/* Networks */
#define HOME    0
#define SCHOOL  1

#define NETWORK  HOME  // which network are we on?

#include "async_output.h"

#if USE_WIRELESS
  #include <WiServer.h>
  
  #define WIRELESS_MODE_INFRA	1
  #define WIRELESS_MODE_ADHOC	2
  
  // Wireless configuration parameters ----------------------------------------
    #include "home.h"   // Enable me if on the Home network
    //#include "school.h" // Enable me if on the School network
  // End of wireless configuration parameters ----------------------------------------
  
  bool firstRun = true;
  
  // Set the IP Address for the server
  uint8 server_ip[] = {192,147,173,116}; // nyx.cs.wallawalla.edu
  
  // Create a request that gets the latest Tweets
  GETrequest checkNewResults(server_ip, 80,
                             "www.paulbellamy.com",
                             "/twitter.php?pass=QUt3zyps");
  
  // Variable Declarations ----------------------------------------
  
  // Variables used in processResults
  #define IN_HEADERS 0
  #define IN_BODY    1
  #define IN_FOOTERS 2
  byte processingState = IN_HEADERS;
  char headerBuf[4];
  
  // Variables used in urlDecode
  char *hexstr = {"__"};
  
  // Variables used for sendMyPage
  char buffer[32];
  prog_char trainingKey[] PROGMEM = "/training?p=";
  prog_char trainingPassword[] PROGMEM = "pa55word";
  prog_char dataKey[] PROGMEM = "&d=";
  PROGMEM const char *header_strings[] = 	   // change "string_table" name to suit
  {   
    trainingKey,
    trainingPassword,
    dataKey };
  
  // End of Variable Declarations ---------------------------------
  
  // Skip all headers of the HTTP response.
  void processResults(char* data, int len) {    
    //Serial.println("ProcessingData...");
    
    // Skip the first request
    if (len == 0) {
      firstRun = false;
      processingState = IN_HEADERS;
    }
    
    if (firstRun) {
      return;
    }
    
    // Skip the header
    byte i=0;
    while (i < len && processingState == IN_HEADERS) {
      headerBuf[3] = headerBuf[2];
      headerBuf[2] = headerBuf[1];
      headerBuf[1] = headerBuf[0];
      headerBuf[0] = data[0];
      data++;
      
      //Serial.print(headerBuf[0]);
      if ((headerBuf[0] == '\n') && (headerBuf[1] == '\r') && (headerBuf[2] == '\n') && (headerBuf[3] == '\r')) {
        processingState = IN_BODY;
      }
      
      i++;
    }
    
    
    // Print until we finish with the body
    while (i < len && processingState == IN_BODY) {
      headerBuf[3] = headerBuf[2];
      headerBuf[2] = headerBuf[1];
      headerBuf[1] = headerBuf[0];
      headerBuf[0] = data[0];    
      data++;
      
      #if USE_SERIAL
        Serial.print(headerBuf[0]);
      #endif
      outputChar(headerBuf[0]);
      
      if ((headerBuf[0] == '\n') && (headerBuf[1] == '\r') && (headerBuf[2] == '\n') && (headerBuf[3] == '\r')) {
        processingState = IN_FOOTERS;
      }
      
      i++;
    }
    
    //Serial.println("\nDoneProcessingData...");
  }
  
  char *urlDecode( char *result, const char *encodedData, byte len) {
    byte i;
    char *ptr = (char *)encodedData;
    for (i = 0; i < len-1; i++) {
      if (ptr[0] == '%') {
        ptr++;
        
        // Copy the hex string
        hexstr = strncpy(hexstr, ptr, 2);
        hexstr[2] = '\0';
        
        // Advance the pointer
        ptr = &ptr[1];
        
        // Convert hex to ascii
        result[i] = (char)strtol(hexstr, NULL, 16);
      } else {
        result[i] = ptr[0];
      }
      ptr++;
    }
    result[i] = '\0';
    
    return result;
  }
  
  int counter = 0;
  
  // Check the training password, then outputs
  boolean sendMyPage(char *URL) {
    //WiServer.println("<h1>It Works!</h1>");
    
    strcpy_P(buffer,  (char*)pgm_read_word(&(header_strings[0])));
    if (strstr(URL, buffer) == URL) {
      URL += strlen(buffer);
      
      //WiServer.println("<h2>Got '/training?p='</h2><br />");
      
      strcpy_P(buffer,  (char*)pgm_read_word(&(header_strings[1])));
      if (strstr(URL, buffer) == URL) {
        URL += strlen(buffer);
              
        //WiServer.Println("<h2>Got password.</h2><br />");
        
        strcpy_P(buffer,  (char*)pgm_read_word(&(header_strings[2])));
        if (strstr(URL, buffer) == URL) {
          URL += strlen(buffer);
        
          //WiServer.Println("<h2>Got data.</h2><br />");  
          counter++;
          //WiServer.Print("Counter: "); WiServer.println(counter);
          
          urlDecode(buffer, URL, 32);
          #if USE_SERIAL
            Serial.println(buffer);
          #endif

          //WiServer.print(buffer);
          //WiServer.println("<br />");

          outputString(buffer);

          memset(buffer, 0, sizeof(char)*strlen(buffer));

          /*
          WiServer.print("outputQ: ");
          for (int i=outputQ->frontPosition; i < (outputQ->frontPosition+outputQ->currentSize) % outputQ->maxSize; i = (i + 1) % outputQ->maxSize) {
            WiServer.print(outputQ->storage[i]); WiServer.print(' ');
          }
          WiServer.println(' ');
          */
          
          return true;
        }
      }
    }
    return true;
  }
#endif

void setup() {
  #if USE_SERIAL
    // Enable Serial output
    Serial.begin(9600);
    //establishContact();
  #endif
  
  // ask WiServer to generate log messages (optional)
  //WiServer.enableVerboseMode(true);
  
  // Initialize WiServer (we'll pass NULL for the page serving function since we don't need to serve web pages) 
  #if USE_SERIAL
    Serial.println("Initializing WiServer.");
  #endif
  #if USE_WIRELESS
    WiServer.init(sendMyPage);
  #endif
  
  // Initialize our output stuff
  initializeOutput();

  // Have the processResults function called when data is returned by the server
  #if USE_WIRELESS
    checkNewResults.setReturnFunc(processResults);
  #endif
  #if USE_SERIAL
    Serial.println("Output Function set.");
  #endif
}

// Time (in millis) when the server should be checked next
unsigned long previousMillis = 0;
unsigned long interval = 60000; // interval to check (milliseconds)

// For Serial processing
byte inByte = 0; // incoming serial byte.

void loop() {
  #if USE_WIRELESS
    // Run WiServer
    WiServer.server_task();
  #endif
  
  #if USE_SERIAL
    // if we got something on serial...
    if (Serial.available() > 0) {
      // get the incoming byte
      inByte = Serial.read();
      Serial.print(inByte);
      outputChar(inByte); // non-buffered for now
    }
  #endif
  
  #if USE_WIRELESS
    // Check if it's time to check the server
    if (millis() - previousMillis > interval) {
      // Check again in another interval
      previousMillis = millis();
      
      //Serial.print("Checking Server: loopCount: ");
      //Serial.println(loopCount++);
      //Serial.print("Address: paulbellamy.com");
      //Serial.println(URL);
      checkNewResults.submit();
    }
  #endif
  
  outputRunAsync();
}
