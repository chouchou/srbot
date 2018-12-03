#define NO_SAMPLES 20

int ir_sensors[] = {0, 1, 2, 3, 4, 5};
int samples[NO_SAMPLES];

void setup() {
  Serial.begin(9600);

}

void loop() {
  for (int i = 0; i < 6; i++) {
    Serial.print("Sampling sensor: ");
    Serial.println(i);
    sample(i);
    Serial.print("The average is: ");
    Serial.println(average());

  }

}

void sample(int sensor) {
  for (int i = 0; i < NO_SAMPLES; i++) {
    samples[i] = analogRead(ir_sensors[sensor]);
    delay(200);
  }
}

void displaySamples() {
  for (int i = 0; i < NO_SAMPLES; i++)
  {
    Serial.print(samples[i]);
    Serial.print(' ');
  }
  Serial.print('\n');
}

int average() {
  int total = 0;
  int average = 0;
  for (int i = 0; i < NO_SAMPLES; i++)
  {
    total = total + samples[i];
  }
  return average = (int)(total / NO_SAMPLES);
}

