/*Code written by RajenChhetry _ Version 2.0 _ Detection of heart rate in BMP and display of ECG signal
Assam University(TSSOT)
email : rajenchhetry.square.bnc@gmail.com */

int UpperThreshold = 518;
int LowerThreshold = 490;
int reading = 0;
float BPM = 0.0;
bool IgnoreReading = false;   //bool(data type) holds one of two values_true or false
bool FirstPulseDetected = false;
unsigned long FirstPulseTime = 0;
unsigned long SecondPulseTime = 0;
unsigned long PulseInterval = 0;
const unsigned long delayTime = 10;
const unsigned long delayTime2 = 1000;
const unsigned long baudRate = 9600;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;

void setup(){
  Serial.begin(baudRate);
  pinMode(9, OUTPUT);  // For LED blink 
  digitalWrite(9, LOW);
}

void loop(){
  unsigned long currentMillis = millis();    // Get current time
  if(myTimer1(delayTime, currentMillis) == 1)  // First event
{

    reading = analogRead(0); // Heart beat leading edge detected.

    if(reading > UpperThreshold && IgnoreReading == false)
  {
      if(FirstPulseDetected == false)
     {
        FirstPulseTime = millis();
        FirstPulseDetected = true;
      }
        else
      {
        SecondPulseTime = millis();
        PulseInterval = SecondPulseTime - FirstPulseTime;
        FirstPulseTime = SecondPulseTime;
      }
      IgnoreReading = true;
      digitalWrite(9, HIGH);
    }
    if(reading < LowerThreshold && IgnoreReading == true)  // Heart beat trailing edge detected.
  {
      IgnoreReading = false;
      digitalWrite(9, LOW);
    }      
    BPM = (1.0/PulseInterval) * 60.0 * 1000; // Calculate Beats Per Minute.
  }
  if(myTimer2(delayTime2, currentMillis) == 1) // Second event
{
    Serial.print(reading);
    Serial.print("\t");
    Serial.print(PulseInterval);
    Serial.print("\t");
    Serial.print(BPM);
    Serial.println(" BPM");
    Serial.flush();
  }
}
int myTimer1(long delayTime, long currentMillis)  // First event timer
{
  if(currentMillis - previousMillis >= delayTime)   {previousMillis = currentMillis;return 1;}
  else{return 0;}
}
int myTimer2(long delayTime2, long currentMillis)  // Second event timer
{
  if(currentMillis - previousMillis2 >= delayTime2)  {previousMillis2 = currentMillis;return 1;}
  else{return 0;}
}