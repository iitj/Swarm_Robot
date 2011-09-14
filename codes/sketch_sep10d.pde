//This code tests the obstacle avoidance of the Beaglebot without memory
//Version 4

int mot_pin[4] = {26,28,32,30};
int led_pin[5] = {36,38,40,42,44};
int sense[5] = {A5,A6,A7,A4,A9};
/*A4 - 3
  A6 - 1
  A7 - 2
  A9 - 4
  A5 - 0
  These are the pins for the Sonar Sensors
*/
void setup()
{
  int i;
  for(i=0;i<4;i++)
  {  
    pinMode(mot_pin[i],OUTPUT);
  }
  i = 0;
  for(i=0;i<5;i++)
  { 
    pinMode(led_pin[i],OUTPUT);
  }
  i = 0;
  for(i=0;i<5;i++)
  {
    pinMode(sense[i],INPUT);
  }  
  Serial.begin(9600); 
  //This sets up all the pins connected to the Arduino and starts the Serial Communication
}
void rot(int motor,int sta)
{
  int pins[2];
  int statu[2];
  if(motor == 1)
  {
    pins[0] = 26;
    pins[1] = 28;
  }
  else if(motor == 2)
  {
    pins[0] = 30;
    pins[1] = 32;
  }
  else
  {
  }
  
  
  if(sta == 0)
  {
    statu[0] = LOW;
    statu[1] = LOW;
  }
  else if(sta == 1)
  {
    statu[0] = HIGH;
    statu[1] = LOW;
  }
  else if(sta == 2)
  {
    statu[0] = LOW;
    statu[1] = HIGH;
  }
  else
  {
  }
  
  digitalWrite(pins[0], statu[0]);
  digitalWrite(pins[1], statu[1]);
}

void mot(int stat)
{
  //This function enables the functioning of motors in a single command
  //mot(0) - Stop
  //mot(1) - Forward
  //mot(2) - Reverse
  //mot(3) - Right Turn
  //mot(4) - Left Turn
  if(stat == 0)
  {
    rot(1,0);
    rot(2,0);
  }
  else if(stat == 1)
  {
    rot(1,1);
    rot(2,1);
  }
  else if(stat == 2)
  {
    rot(1,2);
    rot(2,2);
  }
  else if(stat == 3)
  {
    rot(1,1);
    rot(2,2);
  }
  else if(stat == 4)
  {
    rot(1,2);
    rot(2,1);
  }
  else 
  {
    rot(1,0);
    rot(2,0);
  }
}
float sen_read[5];
int i,j;
float sleft,sright,s,temp,mx;
int mindex,minindex;


void loop()
{
  //This takes the average of the sensor readings.
  //There is a lot of disturbance in the sensor analog voltage, when the bot is moving
  //This code takes the average of 50 values and gives a threshold of 20 for sensor reading
  //These values are entirely experimental, each can adopt their own values
  for(i=0;i<5;i++)
  {
    for(j=0;j<50;j++)
    {
      sen_read[i] = temp + analogRead(sense[i]);
      temp = sen_read[i];
    }
    sen_read[i]=(sen_read[i])/50;
    temp=0;
  }
  minindex=0;
  for(i=0;i<5;i++)
    {
      if(sen_read[minindex] > sen_read[i])
      {
        minindex = i;
      }
    }
  if(sen_read[2]>30 && sen_read[minindex]>15)
  {
    mot(1);
    delay(100);
  }
  else if(sen_read[2]>30 && sen_read[minindex]<15)
  {
    //Here the robot moves back on obstacle detectance
    mot(2);
    delay(400);
    mot(0);
    if(minindex == 0 || minindex == 1)
    {
      mot(3);
      delay(400);
      mot(1);
      delay(1000);
      mot(4);
      delay(400);
    }
    else if(minindex == 3 || minindex == 4)
    {
      mot(4);
      delay(400);
      mot(1);
      delay(1000);
      mot(3);
      delay(400);
    }
    else
    {
      mot(0);
    }
  }
  
  else if(sen_read[2]<30)
  {
    //Here the robot moves back on obstacle detectance
    mot(2);
    delay(400);
    mot(0);
    for(i=0;i<5;i++)
    {
      for(j=0;j<50;j++)
      {
        sen_read[i] = temp + analogRead(sense[i]);
        temp = sen_read[i];
      }
    sen_read[i]=(sen_read[i])/50;
    temp=0;
    }
    //Then it reads from the sensors again
    //It searches the largest sensor reading.
    //Rotates in the direction of that sensor
    mindex = 0;
    for(i=0;i<5;i++)
    {
      if(sen_read[mindex] < sen_read[i])
      {
        mindex = i;
      }
    }
    
    if(sen_read[mindex] > 40)
    {
      if(mindex == 0 || mindex == 1)
      {
        mot(3);
        delay(400);
        mot(0);
      }
      else if(mindex == 3 || mindex == 4)
      {
        mot(4);
        delay(400);
        mot(0);
      }
      else if(mindex == 2)
      {
        mot(4);
        delay(1000);
        mot(0);
      }
      else
      {
        mot(0);
      }
    }
    else if(sen_read[mindex] < 40)
    {
      mot(4);
      delay(1000);
      mot(1);
      delay(400);
    }
    else
    {
      mot(0);
    }
  }
}
  
