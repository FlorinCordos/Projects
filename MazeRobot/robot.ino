#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "TRSensors.h"
#include <Wire.h>

#define PWMA   6           //Left Motor Speed pin (ENA)
#define AIN2   A0          //Motor-L forward (IN2).
#define AIN1   A1          //Motor-L backward (IN1)
#define PWMB   5           //Right Motor Speed pin (ENB)
#define BIN1   A2          //Motor-R forward (IN3)
#define BIN2   A3          //Motor-R backward (IN4)
#define PIN 7
#define NUM_SENSORS 5
#define OLED_RESET 9
#define OLED_SA0   8
#define Addr  0x20

Adafruit_SSD1306 display(OLED_RESET, OLED_SA0);

TRSensors trs =   TRSensors();
unsigned int sensorValues[NUM_SENSORS];
unsigned int position;
uint16_t i, j;
byte value;
unsigned long lasttime = 0;
Adafruit_NeoPixel RGB = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

void PCF8574Write(byte data);
byte PCF8574Read();
uint32_t Wheel(byte WheelPos);

int last_proportional=0;
int integral=0;
int derivative=0;
int spd=150;

void setup() {
  delay(1000);
  Wire.begin();
  pinMode(PWMA,OUTPUT);                     
  pinMode(AIN2,OUTPUT);      
  pinMode(AIN1,OUTPUT);
  pinMode(PWMB,OUTPUT);       
  pinMode(AIN1,OUTPUT);     
  pinMode(AIN2,OUTPUT);  
  SetSpeeds(0,0);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  display.clearDisplay();
  display.setTextSize(2.5);
  display.setTextColor(WHITE);
  display.setCursor(45,0);
  display.println("Maze");
  display.setCursor(35,25);
  display.println("Runner");
  display.setTextSize(1);
  display.setCursor(10,55);
  display.println("Press to calibrate");
  display.display();
  
  while(value != 0xEF)  //wait button pressed
  {
    PCF8574Write(0x1F | PCF8574Read());
    value = PCF8574Read() | 0xE0;
  }
 /* 
  RGB.begin();
  RGB.setPixelColor(0,0x00FF00 );
  RGB.setPixelColor(1,0x00FF00 );
  RGB.setPixelColor(2,0x00FF00 );
  RGB.setPixelColor(3,0x00FF00);
  RGB.show();*/ 
  delay(500);
  for (int i = 0; i < 100; i++)  // make the calibration take about 10 seconds
  {
    if(i<25 || i >= 75)
    { 
      SetSpeeds(50,-50);
    }
    else
    { 
        SetSpeeds(-50,50);
    }
    trs.calibrate();       // reads all sensors 100 times
  }
  SetSpeeds(0,0); 
  RGB.setPixelColor(0,0x0000FF );
  RGB.setPixelColor(1,0x0000FF );
  RGB.setPixelColor(2,0x0000FF );
  RGB.setPixelColor(3,0x0000FF);
  RGB.show(); // Initialize all pixels to 'off'
  
  value = 0;
  while(value != 0xEF)  //wait button pressed
  {
    PCF8574Write(0x1F | PCF8574Read());
    value = PCF8574Read() | 0xE0;
    position = trs.readLine(sensorValues)/200;
    display.clearDisplay();
    display.setCursor(0,25);
    display.println("Calibration Done !!!");
    display.setCursor(0,55);
    for (int i = 0; i < 21; i++)
    {
      display.print('_');
    }
    display.setCursor(position*6,55);
    display.print("");
    display.display();
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45,0);
  display.println("Maze");
  display.setCursor(35,25);
  display.println("Runner");
  display.setTextSize(3);
  display.setCursor(40,30);
  display.println("Go!");
  display.display();
  delay(500);
}
/*
void follow_segment()
{
  int last_proportional = 0;
  long integral=0;

  while(1)
  {
    unsigned int position = trs.readLine(sensorValues);

    int proportional = ((int)position) - 2000;//era 2100

    int derivative = proportional - last_proportional;
    integral += proportional;

    last_proportional = proportional;

   int power_difference = proportional/20 + integral/10000 + derivative*3/2; //sau derivative*10

    const int maximum = 60; // the maximum speed
    if (power_difference > maximum)
      power_difference = maximum;
    if (power_difference < -maximum)
      power_difference = - maximum;

    if (power_difference < 0)
    {
      //SetSpeeds(maximum+power_difference,maximum);
      analogWrite(PWMA,maximum + power_difference);
      analogWrite(PWMB,maximum)
    }
    else
    {
      //SetSpeeds(maximum,maximum-power_difference);
      analogWrite(PWMA,maximum);
      analogWrite(PWMB,maximum - power_difference);
    }
   if(millis() - lasttime >100)
   {
    if (sensorValues[1] < 150 && sensorValues[2] < 150 && sensorValues[3] < 150)
    {
      // There is no line visible ahead, and we didn't see any
      // intersection.  Must be a dead end.
    //  SetSpeeds(0,0);
      return;
    }
    else if (sensorValues[0] > 600 || sensorValues[4] > 600)
    {
      // Found an intersection.
    //  SetSpeeds(0, 0);
      return;
    }
   }
  }
}
*/

void follow_segment(){
  int i;       // Control function
  int power_difference = 0;
  float Kp, Ki, Kd;
  unsigned int position;
  int derivative, proportional;

  while(1){
    unsigned int position = trs.readLine(sensorValues);
    proportional=((int)position-3000);

    derivative = proportional - last_proportional;
    integral = integral+proportional;

    last_proportional = proportional;
    // use the tutorial to set initial values of Kp, Ki, and Kd
    Kp = 100; 
    Ki = 0;
    Kd = 0;

    power_difference = proportional*Kp + integral*Ki + derivative*Kd;
    const int maximum = spd/2 + 30;
    if(power_difference > maximum)
      power_difference = maximum;
    if(power_difference < -maximum)
      power_difference = (-1*maximum);

      if (power_difference < 0)
    {
      //SetSpeeds(maximum+power_difference,maximum);
      analogWrite(PWMA,maximum + power_difference);
      analogWrite(PWMB,maximum);
    }
    else
    {
      //SetSpeeds(maximum,maximum-power_difference);
      analogWrite(PWMA,maximum);
      analogWrite(PWMB,maximum - power_difference);
    }
    trs.readLine(sensorValues);

     if (sensorValues[1] < 10 && sensorValues[2] < 10 && sensorValues[3] < 10)
    {
      // There is no line visible ahead, and we didn't see any
      // intersection.  Must be a dead end.
    //  SetSpeeds(0,0);
      return;
    }
    else if (sensorValues[0] > 500 || sensorValues[4] > 500)
    {
      // Found an intersection.
    //  SetSpeeds(0, 0);
      return;
    }
  }
}

/*
void follow_segment()
{
  int i;       // Control function
  int power_difference = 0;
  float Kp, Ki, Kd;
  unsigned int position;
  int derivative, proportional;
  while(1){
    position=trs.readLine(sensorValues);
    proportional = ((int)position - 3000);
    derivative = proportional - last_proportional;
    integral = integral+proportional;
    last_proportional = proportional;
    // use the tutorial to set initial values of Kp, Ki, and Kd
    Kp = 60; 
    Ki = 30;
    Kd = 40;

   power_difference = proportional*Kp + integral*Ki + derivative*Kd;
    const int max = spd/2 + 30;
    if(power_difference > max)
     power_difference = max;
    if(power_difference < -max)
     power_difference = (-1*max);
    if(power_difference < 0)
    SetSpeeds(max+power_difference,max);
    else
    SetSpeeds(max,max-power_difference);
    trs.readLine(sensorValues);
    if(sensorValues[0]==HIGH && sensorValues[1]==HIGH && sensorValues[2]==HIGH && sensorValues[3]==HIGH && sensorValues[4]==HIGH)
    return;
    else if(sensorValues[0]==LOW || sensorValues[5]==LOW)
    return;
  }
}
*/

void turn(unsigned char dir)
{
  {
    switch(dir)
    {
    case 'L':
      // Turn left.
      SetSpeeds(-80, 80);
      delay(190);
      break;
    case 'R':
      // Turn right.
      SetSpeeds(80, -80);
      delay(190);
      break;
    case 'B':
      // Turn around.
      SetSpeeds(80, -80);
      delay(400);
      break;
    case 'S':
      // Don't do anything!
      break;
    }
  }
  SetSpeeds(0, 0);
  lasttime = millis();   
}


char path[100] = "";
unsigned char path_length = 0; // the length of the path

unsigned char select_turn(unsigned char found_left, unsigned char found_straight, unsigned char found_right)
{

    if((path[path_length-1]=='R' && path[path_length-2]=='R' && path[path_length-3]=='R')||(path[path_length-1]=='L' && path[path_length-2]=='L' && path[path_length-3]=='L'))
  {
    if(path[path_length-1]=='L')
     return 'R';
    else if(path[path_length-1]=='R')
     return 'L';
    else{
      return 'S';
    }
  }
   if (found_left)
    return 'L';
  else if (found_straight)
    return 'S';
  else if (found_right)
    return 'R';
  else
    return 'B';
}

void simplify_path()
{
  // only simplify the path if the second-to-last turn was a 'B'
  if (path_length < 3 || path[path_length-2] != 'B')
    return;

  int total_angle = 0;
  int i;
  for (i = 1; i <= 3; i++)
  {
    switch (path[path_length - i])
    {
    case 'R':
      total_angle += 90;
      break;
    case 'L':
      total_angle += 270;
      break;
    case 'B':
      total_angle += 180;
      break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  total_angle = total_angle % 360;

  // Replace all of those turns with a single one.
  switch (total_angle)
  {
  case 0:
    path[path_length - 3] = 'S';
    break;
  case 90:
    path[path_length - 3] = 'R';
    break;
  case 180:
    path[path_length - 3] = 'B';
    break;
  case 270:
    path[path_length - 3] = 'L';
    break;
  }

  // The path is now two steps shorter.
  path_length -= 2;
}

void loop() {
  while (1)
  {
    follow_segment();
    // Drive straight a bit.  This helps us in case we entered the
    // intersection at an angle.
    // Note that we are slowing down - this prevents the robot
    // from tipping forward too much.
    SetSpeeds(20, 20);
    delay(50);

    // These variables record whether the robot has seen a line to the
    // left, straight ahead, and right, whil examining the current
    // intersection.
    unsigned char found_left = 0;
    unsigned char found_straight = 0;
    unsigned char found_right = 0;

    // Now read the sensors and check the intersection type.
   trs.readLine(sensorValues);

    // Check for left and right exits.
    if (sensorValues[0] > 350 || sensorValues[1] > 350)
      found_left = 1;
    if (sensorValues[3] > 350  || sensorValues[4] > 350)
      found_right = 1;

    // Drive straight a bit more - this is enough to line up our
    // wheels with the intersection.
    SetSpeeds(20, 20);
    delay(200);

    // Check for a straight exit.
    trs.readLine(sensorValues);
    if (sensorValues[1] < 100 || sensorValues[2] > 300 || sensorValues[3] < 100 && (sensorValues[0] < 100 && sensorValues[4] < 100))
      found_straight = 1;

    // Check for the ending spot.
    // If all three middle sensors are on dark black, we have
    // solved the maze.
    if (sensorValues[1] > 500 && sensorValues[2] > 500 && sensorValues[3] > 500)
    {
      SetSpeeds(0, 0);
      break;
    }

    // Intersection identification is complete.
    // If the maze has been solved, we can follow the existing
    // path.  Otherwise, we need to learn the solution.
    unsigned char dir = select_turn(found_left, found_straight, found_right);

    // Make the turn indicated by the path.
    turn(dir);

    // Store the intersection in the path variable.
    path[path_length] = dir;
    path_length++;

    // You should check to make sure that the path_length does not
    // exceed the bounds of the array.  We'll ignore that in this
    // example.

    // Simplify the learned path.
    simplify_path();

    // Display the path on the LCD.
   // display_path();
  }

  // Solved the maze!

  // Now enter an infinite loop - we can re-run the maze as many
  // times as we want to.
  while (1)
  {
    // Beep to show that we solved the maze.
    SetSpeeds(0, 0);
   // OrangutanBuzzer::play(">>a32");
    Serial.println("End !!!");
    // Wait for the user to press a button, while displaying
    // the solution.
    delay(500);

    value = 0;
    while(value != 0xEF)  //wait button pressed
    {
      PCF8574Write(0x1F | PCF8574Read());
      value = PCF8574Read() | 0xE0;
    }
    delay(1000);

    // Re-run the maze.  It's not necessary to identify the
    // intersections, so this loop is really simple.
    int i;
    for (i = 0; i < path_length; i++)
    {
      follow_segment();

      // Drive straight while slowing down, as before.
      SetSpeeds(30, 30);
      delay(40);
      SetSpeeds(30, 30);
      delay(150);

      // Make a turn according to the instruction stored in
      // path[i].
      turn(path[i]);
    }

    // Follow the last segment up to the finish.
    follow_segment();

    // Now we should be at the finish!  Restart the loop.
  }
}

void SetSpeeds(int Aspeed,int Bspeed)
{
  if(Aspeed < 0)
  {
    digitalWrite(AIN1,HIGH);
    digitalWrite(AIN2,LOW);
    analogWrite(PWMA,-Aspeed);      
  }
  else
  {
    digitalWrite(AIN1,LOW); 
    digitalWrite(AIN2,HIGH);
    analogWrite(PWMA,Aspeed);  
  }
  
  if(Bspeed < 0)
  {
    digitalWrite(BIN1,HIGH);
    digitalWrite(BIN2,LOW);
    analogWrite(PWMB,-Bspeed);      
  }
  else
  {
    digitalWrite(BIN1,LOW); 
    digitalWrite(BIN2,HIGH);
    analogWrite(PWMB,Bspeed);  
  }
}

void PCF8574Write(byte data)
{
  Wire.beginTransmission(Addr);
  Wire.write(data);
  Wire.endTransmission(); 
}

byte PCF8574Read()
{
  int data = -1;
  Wire.requestFrom(Addr, 1);
  if(Wire.available()) {
    data = Wire.read();
  }
  return data;
}