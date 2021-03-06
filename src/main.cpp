#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define DELAY_TIME_TICK 150
#define CS_PIN 15
#define MAX_LOOPS 1000000
#define END_WRITE_LOOP 1
#define US_TO_S 1000000

// function definitions
void serial_wait_command(uint8_t);
void print_single_parameter(String, uint16_t);
// constant definitions
unsigned int timeStartTick = 0;
int timeTotalTick = 0;
unsigned int timeEndTick = 0;
uint16_t deltaSlice = 0;
unsigned int total_loops = 0;
unsigned int grand_total_loops = 0;
char readBuffer[20];
bool write_data = true;
bool first_loop = true;
char output[100];
void setup()
{
  Serial.begin(4608000);
  while (!Serial)
    ; // wait until the Serial terminal communicates back
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
  serial_wait_command((DELAY_TIME_TICK * MAX_LOOPS * END_WRITE_LOOP) / US_TO_S);
  while (!Serial.available())
    ; // wait for a response from the host PC
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
      print_single_parameter("t", 0);
      print_single_parameter("a", 0);
      print_single_parameter("b", 0);
      print_single_parameter("c", 0);
      print_single_parameter("d", 0);
      print_single_parameter("e", 0);
      print_single_parameter("f", 0);
      print_single_parameter("g", 0);
      print_single_parameter("h", 0);
    }
    else
    {
      print_single_parameter("t", deltaSlice);
      print_single_parameter("a", deltaSlice);
      print_single_parameter("b", deltaSlice);
      print_single_parameter("c", deltaSlice);
      print_single_parameter("d", deltaSlice);
      print_single_parameter("e", deltaSlice);
      print_single_parameter("f", deltaSlice);
      print_single_parameter("g", deltaSlice);
      print_single_parameter("h", deltaSlice);
      if (deltaSlice > 220)
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

void print_single_parameter(String identifier, uint16_t value)
{
  Serial.print(identifier);
  Serial.print(value, BIN);
}