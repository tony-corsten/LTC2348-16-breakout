#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define DELAY_TIME_TICK 50
#define CS_PIN 15
#define MAX_LOOPS 100
#define END_WRITE_LOOP 1000
#define US_TO_S 1000000

// function definitions
void serial_wait_command(uint8_t);
// constant definitions
const int chipSelect = BUILTIN_SDCARD;
bool switchVal = false;
unsigned int timeStartTick = 0;
int timeTotalTick = 0;
unsigned int timeEndTick = 0;
unsigned int deltaSlice = 0;
unsigned int total_loops = 0;
unsigned int grand_total_loops = 0;
char readBuffer[20];
bool write_data = true;
bool first_loop = true;
void setup()
{
  Serial.begin(921600);
  while (!Serial); // wait until the Serial terminal communicates back
  delay(2000);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  //analogWriteFrequency(2, 100000);
  //analogWrite(2, 127);
  digitalWriteFast(0, LOW);
  serial_wait_command((2 * DELAY_TIME_TICK * MAX_LOOPS * END_WRITE_LOOP) / US_TO_S);
  while (!Serial.available()); // wait for a response from the host PC
}

void loop()
{
  // put your main code here, to run repeatedly:
  timeStartTick = micros();
  deltaSlice = timeStartTick - timeEndTick;
  timeEndTick = timeStartTick;
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0xff);
  SPI.transfer(0x00);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0x00);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0x00);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0x00);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0x00);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0x00);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0x00);
  SPI.transfer(0xff);
  SPI.transfer(0xff);
  SPI.transfer(0x00);
  SPI.transfer(0xff);
  digitalWrite(CS_PIN, HIGH);
  if (write_data)
  {
    if (first_loop)
    {
      first_loop = false;
      Serial.print("0 "); 
    }
    else
    {
      Serial.print(deltaSlice);
      Serial.print(" ");
      if (deltaSlice > 100)
      {
        digitalWriteFast(0, HIGH);
        //write_data = false;
      }
      digitalWriteFast(0, LOW);
    }
    total_loops++;
    if (total_loops == MAX_LOOPS)
    {
      Serial.println("");
      total_loops = 0;
      grand_total_loops++;
    }
  }
  if (grand_total_loops == END_WRITE_LOOP)
  {
    write_data = false;
  }

  timeTotalTick = DELAY_TIME_TICK - (micros() - timeStartTick);
  if (timeTotalTick > 0)
  {
    delayMicroseconds(timeTotalTick);
  }
  //delayMicroseconds(100);
}
/* 
 *  sends a serial command to the host PC to wait prior to sending data. 
 *  This seems to eliminate slow serial sending at the start of a bitstream.
 */
void serial_wait_command(uint8_t wait_time)
{
  Serial.print("Wait: ");
  Serial.println(wait_time);
}