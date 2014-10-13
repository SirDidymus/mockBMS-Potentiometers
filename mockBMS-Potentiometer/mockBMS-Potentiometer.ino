// Global Constants
const int NUMB_BATTERIES = 6;
const int NUM_NUM_AVERAGES= 100;
const int MIN_VOLTAGE = 2.9;
const int MAX_VOLTAGE = 4.3;

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
  float curVolt[NUMB_BATTERIES * NUM_AVERAGES];
  int avgVolt;
  // Reads in votage
  int batSensor0 = analogRead(A0);
  int batSensor1 = analogRead(A1);
  int batSensor2 = analogRead(A2);
  int batSensor3 = analogRead(A3);
  int batSensor4 = analogRead(A4);
  int batSensor5 = analogRead(A5);
  
  for(int i = 0; i < NUM_AVERAGES; i++) {
    // Converting integer value from analogRead into voltage
    // Grabbing 100 values for each battery before NUM_AVERAGES
    curVolt[i] = batSensor0 * (5.0 / 1023.0);                // Battery 0
    curVolt[i+(NUM_AVERAGES*1)] = batSensor1 * (5.0 / 1023.0);   // Battery 1
    curVolt[i+(NUM_AVERAGES*2)] = batSensor2 * (5.0 / 1023.0);   // Battery 2
    curVolt[i+(NUM_AVERAGES*3)] = batSensor3 * (5.0 / 1023.0);   // Battery 3
    curVolt[i+(NUM_AVERAGES*4)] = batSensor4 * (5.0 / 1023.0);   // Battery 4
    curVolt[i+(NUM_AVERAGES*5)] = batSensor5 * (5.0 / 1023.0);   // Battery 5
  }
  
  // Averaging 100 voltages for each battery
  for(int i = 0; i < ; i++) {
    avgVolt = getAvgVolt(curVolt, i);
    
    // Printing average voltage through serial
    Serial.print("Average voltage for battery number ");
    Serial.print(i + " is ");
    Serial.println(avgVolt);
    // Checking average voltage to make sure it is within acceptable parameters
    if(avgVolt < MIN_VOLTAGE || avgVolt > MAX_VOLTAGE) {
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
  for(int i = 0; i < NUM_AVERAGES; i++) {
    runningSum += voltage[i+(NUM_AVERAGES*bat)];
  }
  
  // Calculating average voltage
  avgVoltage = runningSum / NUM_AVERAGES;
  
  return avgVoltage; 
}
