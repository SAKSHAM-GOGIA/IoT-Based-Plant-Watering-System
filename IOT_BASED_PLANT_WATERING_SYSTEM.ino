#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// defining the water level sensor pins
#define water_power_pin 2
#define water_signal_pin A0

int water_level_value = 0;  //declaring the water level value = 0
int buzzer = 3;

// defining the soil moisture sensor module
int soil_sensor_pin = A2;

//defining water pump
int water_pump=11;

void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (water_power_pin, OUTPUT);    //configuring D2 pin as an output
  digitalWrite(water_power_pin, LOW);   //turning the water level sensor off
  lcd.init();
  lcd.backlight();
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(water_pump, OUTPUT);
}

void loop() {

  //WATER LEVEL SENSOR CODE:
  lcd.clear();
  digitalWrite(water_power_pin, HIGH);    //turning the water level sensor on
  delay(10);       //wait for 10 millisceonds
  water_level_value = analogRead(water_signal_pin); //reading the value of sensor
  digitalWrite(water_power_pin, LOW);               //turning the sensor off
  Serial.print("Water Level Sensor Value: ");
  Serial.print(water_level_value);
  Serial.print("\n");
  if (water_level_value < 100)
  {
    digitalWrite(buzzer, HIGH);         //if value os less than 100 then buzzer will beep
    delay(1000);
  }
  else{
    digitalWrite(buzzer, LOW);
  }

  //IDENTIFYING THE PLANT CODE:

  int a=0,b=0,c=0,d=0,x=0;
  if (digitalRead(4)==HIGH)
  {
    a=1;
  }
  if (digitalRead(5)==HIGH)
  {
    b=1;
  }
  if (digitalRead(6)==HIGH)
  {
    c=1;
  }
  if (digitalRead(7)==HIGH)
  {
    d=1;
  }
  Serial.print("A: ");
  Serial.println(a);
  Serial.print("B: ");
  Serial.println(b);
  Serial.print("C: ");
  Serial.println(c);
  Serial.print("D: ");
  Serial.println(d);
  x = 8*d + 4*c + 2*b + a;
  Serial.print("X: ");
  Serial.println(x);
  int arr[16];
  arr[0]= 50;     //Plant no. 1  -> Peace Lily
  arr[1]= 40;     //Plant no. 2  -> Aloevera
  arr[2]= 80;     //Plant no. 3  -> Flamingo Flower
  arr[3]= 50;     //Plant no. 4  -> Money Plant
  arr[4]= 40;     //Plant no. 5  -> Azalea
  arr[5]= 65;     //Plant no. 6  -> Gerbera Daisy Plant
  arr[6]= 50;     //Plant no. 7  -> Inidan Basil
  arr[7]= 30;     //Plant no. 8  -> Jade plant
  arr[8]= 40;     //Plant no. 9  -> ZZ (Zamioculcas Zamiifolia) Plant
  arr[9]= 20;     //Plant no. 10 -> Bunny Ear Cactus
  arr[10]= 40;    //Plant no. 11 -> Paddle Plant
  arr[11]= 75;    //Plant no. 12 -> Kalanchoe
  arr[12]= 70;    //Plant no. 13 -> Begonia
  arr[13]= 80;    //Plant no. 14 -> Anthurium
  arr[14]= 50;    //Plant no. 15 -> Fishtail Palm
  arr[15]= 10;    //Plant no. 16 -> Yucca Plant

  // SOIL HUMIDITY SENSOR CODE:
  int soil_sensor_value = 0;
  soil_sensor_value = 100-(analogRead(soil_sensor_pin))*0.0976;  // 100 - analogRead(soil_sensor_pin)*(1/1024)*100)
  Serial.print("Soil Sensor Value: ");
  Serial.print(soil_sensor_value);
  Serial.print("\n\n");

  lcd.setCursor(0, 0);
  lcd.print("C.Humidity: ");
  lcd.print(soil_sensor_value);
  lcd.setCursor(0, 1);
  lcd.print("R.Humidity: ");
  lcd.setCursor(12, 1);
  lcd.print(arr[x]);
  
  if (soil_sensor_value < arr[x])
  {
    digitalWrite(water_pump, HIGH);
  }
  else{
    digitalWrite(water_pump, LOW);
  }
  delay (1000);
}
