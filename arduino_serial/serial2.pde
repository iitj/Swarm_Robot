void setup()
{
	Serial.begin(9600);
}

int read1;

void loop()
{
	if(Serial.available() > 0)
	{
		read1 = Serial.read();
	}
	Serial.println(read1);
	delay(1000);
}

