

#include <Ethernet.h>
#include <SPI.h>
#include <LedControl.h>


// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.nepalgoldrate.com";
String realData;

EthernetClient client;
int refreshVar = 1;
unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers



// Pin 7 to Data In, 6 to Clk, 5 to LOAD, number of devices is 6
// to display 48 bit data we used 6 max2719 module in cascading mode

LedControl lc = LedControl(7, 6, 5, 8);


String incomingData;
String Data,Led1, Led2, Led3, Led4, Led5;
char led1[9], led2[9], led3[9], led4[9], led5[9], data[9];
//char led2[8]
bool doneParsing = false;



void setup() {

	Serial.begin(115200);

  // Initialize the 6 Max2719 devices

  for (int k = 0; k < 6; k++) {
    lc.shutdown(k, false);  // Enable display
    lc.setIntensity(k, 15); // Set brightness level (0 is min, 15 is max)
    lc.clearDisplay(k);

  }
	// start the Ethernet connection:
	if (Ethernet.begin(mac) == 0) {
		Serial.println("Failed to configure Ethernet using DHCP");
		// no point in carrying on, so do nothing forevermore:
		while (true);
	}
	// give the Ethernet shield a second to initialize:
	delay(1000);
	Serial.println("connecting...");
	Serial.println(Ethernet.localIP());



	
	// put your setup code here, to run once:


}


void loop() {


	if (client.available()) {
		char c = client.read();
		Serial.write(c);
		incomingData += c;
	}

	// if ten seconds have passed since your last connection,
  // then connect again and send data:
	if (millis() - lastConnectionTime > postingInterval) {
		httpRequest();
    int index = incomingData.indexOf("$",1);
    realData = incomingData.substring(index,index+50);
    incomingData = "";
    
		doneParsing = false;
	}

	if (doneParsing != true) {

		parsingString();
		refreshVar = 1;
	}
	// adding a cocndition if the string parsing is done and no new data is available it continue to display the last data
	if (doneParsing == true && refreshVar == 1) {
		Serial.print("Display Data on MAx7219");
		refreshVar = 0;
   led12(0,0,Data,false);
   led12(1,0,Led1,false);
   led12(2,0,Led3,false);
   led12(3,0,Led4,false);
   led12(4,0,led5,false);

		
	}
	Serial.println();
	delay(1000);
  // put your main code here, to run repeatedly:

}
void parsingString(void) {

	if (realData.startsWith("$")) {
		int firstIndex = realData.indexOf(",", 2);
		Data = realData.substring(2, firstIndex);
		Serial.print("First Data is ");
		Serial.println(Data);
		delay(100);
		// For LED 1
		int secIndex = realData.indexOf(",", firstIndex+1);
		Led1 = realData.substring(firstIndex+1, secIndex);
		Serial.print("second Data is ");
		Serial.println(Led1);
		delay(100);
		// For LED 2
		int thirdIndex = realData.indexOf(",", secIndex+1);
	
		Led2 = realData.substring(secIndex+1, thirdIndex);
		Serial.print("third Data is ");
		Serial.println(Led2);
		delay(100);
		// For LED 3
		int fourthIndex = realData.indexOf(",", thirdIndex+1);
		Led3 = realData.substring(thirdIndex+1, fourthIndex);
		Serial.print("Fourth Data is ");
		Serial.println(Led3);
		delay(100);

		// For LED 4
		int fifthIndex = realData.indexOf(",", fourthIndex+1);
//		Serial.printf("fifth index value is %d\t", fifthIndex);
		Led4 = realData.substring(fourthIndex+1, fifthIndex);
		Serial.print("Fifth Data is ");
		Serial.println(Led4);
		delay(100);
		// For LED 5
	
		Led5 = realData.substring(fifthIndex+1, incomingData.length());
		Serial.print("\t \t sixth Data is ");
		Serial.println(Led5);
		delay(100);
		doneParsing = true;
	}
}
void httpRequest() {
	// close any connection before send a new request.
	// This will free the socket on the WiFi shield
	client.stop();

	// if there's a successful connection:
	if (client.connect(server, 80)) {
		Serial.println("connecting...");
		// send the HTTP PUT request:
		String feedback = "";
		client.println("GET /parsa.php?status=1 HTTP/1.1");
		client.println("Host: www.nepalgoldrate.com");
		client.println("User-Agent: Mozilla/5.0");
		client.println("Connection: close");
		feedback = client.println();

		// note the time that the connection was made:
		lastConnectionTime = millis();
	}
	else {
		// if you couldn't make a connection:
		Serial.println("connection failed");
	}
}
void led12(int module, int place, String datas, boolean dot)
{
  for(int i=place;datas[i]!='\0';i++)
  {
    lc.setDigit(module,7-i,int(datas[i])-48, false);
  } 
   
}

