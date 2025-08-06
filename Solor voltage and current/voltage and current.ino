const int currentPin = A0;        // Analog pin for ACS712 current sensor
const int voltagePin = A0;        // Analog pin for voltage divider
const float Vref = 3.3;           // ESP8266 reference voltage
const float sensitivity = 0.185;  // Sensitivity for ACS712 5A version (change based on your model)
const float maxInputVoltage = 25.0; // Max voltage for solar panel (scale it for your system)

void setup() {
  Serial.begin(115200);
  delay(1000); // Give some time for initialization
  Serial.println("ACS712 and Voltage Divider setup...");
}

void loop() {
  // === Measure Current ===
  int rawCurrent = analogRead(currentPin);
  float currentVoltage = (rawCurrent * Vref) / 1023.0; // Convert ADC value to voltage
  float current = -(currentVoltage - 2.5) / sensitivity -6; // Calculate current in Amps
  
  // === Measure Voltage ===
  int rawVoltage = analogRead(voltagePin);
  float voltage = (rawVoltage * Vref) / 1023.0; // Convert ADC value to voltage
  voltage = voltage * (maxInputVoltage / Vref);  // Scale voltage according to divider

  // === Print Results ===
  Serial.print("Current: ");
  Serial.print(current, 3);  // Print current in Amps
  Serial.print(" A\t");

  Serial.print("Voltage: ");
  Serial.print(voltage, 2);  // Print voltage
  Serial.println(" V");

  delay(1000);  // Wait 1 second before next reading
}
