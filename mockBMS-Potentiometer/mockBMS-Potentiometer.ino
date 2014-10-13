// Global Constants
const int numBats = 6;
const int averages = 100;

int getAvgVolt(float voltage[], int bat);

void setup() {
  // Enabling pins 2 through 7 for LEDs
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  // Enabling serial to transmit voltage values
  Serial.begin(9600);
}

void loop() {
  float curVolt[numBats * averages];
  int avgVolt;
  // Reads in votage
  int batSensor0 = analogRead(A0);
  int batSensor1 = analogRead(A1);
  int batSensor2 = analogRead(A2);
  int batSensor3 = analogRead(A3);
  int batSensor4 = analogRead(A4);
  int batSensor5 = analogRead(A5);
  
  for(int i = 0; i < averages; i++) {
    // Converting integer value from analogRead into voltage
    // Grabbing 100 values for each battery before averages
    curVolt[i] = batSensor0 * (5.0 / 1023.0);                // Battery 0
    curVolt[i+(averages*1)] = batSensor1 * (5.0 / 1023.0);   // Battery 1
    curVolt[i+(averages*2)] = batSensor2 * (5.0 / 1023.0);   // Battery 2
    curVolt[i+(averages*3)] = batSensor3 * (5.0 / 1023.0);   // Battery 3
    curVolt[i+(averages*4)] = batSensor4 * (5.0 / 1023.0);   // Battery 4
    curVolt[i+(averages*5)] = batSensor5 * (5.0 / 1023.0);   // Battery 5
  }
  
  // Averaging 100 voltages for each battery
  for(int i = 0; i < numBats; i++) {
    avgVolt = getAvgVolt(curVolt, i);
    
    // Printing average voltage through serial
    Serial.print("Average voltage for battery number ");
    Serial.print(i + " is ");
    Serial.println(avgVolt);
    // Checking average voltage to make sure it is within acceptable parameters
    if(avgVolt < 2.9 || avgVolt > 4.3) {
      // If not acceptable, "kill"
      digitalWrite(i + 2, HIGH);
    }
    else {
      digitalWrite(i + 2, LOW);
    }
  }    
}

int getAvgVolt(float voltage[], int bat) {
  float avgVoltage;
  float runningSum;
  
  // Finding running sum of all voltages for a particular battery
  for(int i = 0; i < averages; i++) {
    runningSum += voltage[i+(averages*bat)];
  }
  
  // Calculating average voltage
  avgVoltage = runningSum / averages;
  
  return avgVoltage; 
}
