#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display

const int thumb = A0;	//flexPin10k		// Pin connected to voltage divider output
const int lady = A4;  //flexPin15k
const int ring = A3;
const int middle = A2;
const int index = A1;

const float VCC = 5;			// voltage at Ardunio 5V line
const float R_DIV = 10000.0;	// resistor used to create a voltage divider

const float flatResistancet = 148000.0;	// thumb resistance when flat
const float bendResistancet = 160000.0;	// thumb resistance at 90 deg

const float flatResistancei = 15000.0;	// index resistance when flat
const float bendResistancei = 60000.0;	// index resistance at 90 deg

const float flatResistancem = 13000.0;	// middle resistance when flat
const float bendResistancem = 50000.0;	// middle resistance at 90 deg

// const float flatResistancer = 72000.0;	// ring resistance when flat
// const float bendResistancer = 87000.0;	// ring resistance at 90 deg

const float flatResistancer = 15000.0;	// ring resistance when flat
const float bendResistancer = 60000.0;	// ring resistance at 90 deg

const float flatResistancel = 162000.0;	// lady resistance when flat
const float bendResistancel = 180000.0;	// lady resistance at 90 deg
//FR=Flat Resistance  
//BR=Bend Resistance
//thumbFR = 148k  //thumbBR = 160k
//indexFR = 15k   //indexBR = 60k
//middleFR= 13k   //middleBR= 50k
//ringFR  = 72k   //ringBR  = 87k
//ladyFR  = 162k  //ladyBR  = 180k

// const int thumbT = 200;
const int thumbT = -530;
const int indexT = 40;
const int middleT = 20; 
const int ringT = 5;
const int ladyT = 130;
void setup() {
 
  pinMode(thumb, INPUT); 
  pinMode(lady, INPUT); 
  pinMode(ring, INPUT); 
  pinMode(middle, INPUT);
	pinMode(index, INPUT);
  pinMode(2,OUTPUT);
  Serial.begin(9600); // Initialize serial communication for debugging (optional)
       lcd.init();

}

void loop() {
  digitalWrite(2,HIGH);
  int ADCthumb = analogRead(thumb);
  int ADClady = analogRead(lady);
  int ADCring = analogRead(ring);
  int ADCmiddle = analogRead(middle);
  int ADCindex = analogRead(index);


	float Vthumb = ADCthumb * VCC / 1023.0;
	float Vlady = ADClady * VCC / 1023.0;
	float Vring = ADCring * VCC / 1023.0;
	float Vmiddle = ADCmiddle * VCC / 1023.0;
	float Vindex = ADCindex * VCC / 1023.0;

	float Rthumb = R_DIV * (VCC / Vthumb - 1.0);
	float Rlady = R_DIV * (VCC / Vlady - 1.0);
	float Rring = R_DIV * (VCC / Vring - 1.0);
	float Rmiddle = R_DIV * (VCC / Vmiddle - 1.0);
	float Rindex = R_DIV * (VCC / Vindex - 1.0);
 
  float anglethumb = map(Rthumb, flatResistancet, bendResistancet, 0, 90.0);
	float anglelady = map(Rlady, flatResistancel, bendResistancel, 0, 90.0);
	float anglering = map(Rring, flatResistancer, bendResistancer, 0, 90.0);
	float anglemiddle = map(Rmiddle, flatResistancem, bendResistancem, 0, 90.0);
	float angleindex = map(Rindex, flatResistancei, bendResistancei, 0, 90.0);

	Serial.println("thumb finger Bend: " + String(anglethumb) + " degrees");
	Serial.println("index finger Bend: " + String(angleindex) + " degrees");
	Serial.println("middle finger Bend: " + String(anglemiddle) + " degrees");
	Serial.println("ring finger Bend: " + String(anglering) + " degrees");
	// Serial.println("lady finger Bend: " + String(anglelady) + " degrees");
	Serial.println();



  const int bendthumb = anglethumb < thumbT;
  // const int bendthumb = anglethumb > thumbT;
  const int bendindex = angleindex > indexT;
  const int bendmiddle = anglemiddle > middleT;
  const int bendring = anglering > ringT;
  const int bendlady = anglelady > ladyT;

  // const int relaxthumb = anglethumb < thumbT;
  const int relaxthumb = anglethumb > thumbT;
  const int relaxindex = angleindex < indexT;
  const int relaxmiddle = anglemiddle < middleT;
  const int relaxring = anglering < ringT;
  const int relaxlady = anglelady < ladyT;

 // const int ultabendthumb = anglethumb < 1000;

  if((relaxthumb) && (bendlady) && (bendring) && (bendmiddle) && (bendindex)){
    lcd.clear();
  lcd.backlight();
    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("A");
    Serial.println("A");
  }//A
    if((bendthumb) && (relaxlady) && (relaxring) && (relaxmiddle) && (relaxindex)){
  lcd.clear();         
  lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("B");
    Serial.println("B");
  }//B
    if((bendthumb) && (relaxlady) && (relaxring) && (relaxmiddle) && (relaxindex)){
  lcd.clear();         
  lcd.backlight();    lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
    lcd.print("C");
    Serial.println("C");
  }//C       //O
    if((bendthumb) && (bendlady) && (bendring) && (bendmiddle) && (relaxindex)){
   lcd.clear();         
   lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("D");
    Serial.println("D");
  }//D
    if((bendthumb) && (bendlady) && (bendring) && (bendmiddle) && (bendindex)){
    lcd.init();
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("E");
    Serial.println("E");
  }//E // M
    if((bendthumb) && (relaxlady) && (relaxring) && (relaxmiddle) & (bendindex)){
  lcd.clear();         
  lcd.backlight();    lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
    lcd.print("F");
    Serial.println("F");
  }//F
    if((relaxthumb) && (bendlady) && (bendring) && (bendmiddle) && (relaxindex)){
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("G");
    Serial.println("G");
  }//G
// ////gyro 
    if((bendthumb) && (bendlady) && (bendring) && (relaxmiddle) && (relaxindex)){
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("H");
    Serial.println("H");
  }//H
  //gyro
    if( (bendthumb) && (relaxlady) && (bendring) && (bendmiddle) && (bendindex)){
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("I");
    Serial.println("I");
  }//I
    if((relaxthumb) && (relaxlady) && (bendring) && (bendmiddle) && (bendindex)){
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("J");
    Serial.println("J");
  }//J
// //gyro
    if((relaxthumb) && (bendlady) && (bendring) && (relaxmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("K");
    Serial.println("K");
  }//K
    if((relaxthumb) && (bendlady) && (bendring) && (bendmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("L");
    Serial.println("L");
  }//L
    if((bendthumb) && (bendlady) && (bendring) && (bendmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
    lcd.print("M");
    Serial.println("M");
  }//M //E //N
    if((bendthumb) && (bendlady) && (bendring) && (bendmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
    lcd.print("N");
    Serial.println("N");
  }//N
    if((bendthumb) && (bendlady) && (bendring) && (relaxmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
    lcd.print("O");
    Serial.println("O");
  }//O //C
    if((relaxthumb) && (bendlady) && (bendring) && (relaxmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("P");
    Serial.println("P");
  }//P
// //gyro
    if((relaxthumb) && (bendlady) && (bendring) && (bendmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(3,0);   //Set cursor to character 2 on line 0
    lcd.print("Q");
    Serial.println("Q");
  }//Q //G //Q
// //gyro
    if((relaxthumb) && (bendlady) && (bendring) && (relaxmiddle) && (relaxindex) ){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("R");
    Serial.println("R");
  }//R
    if((bendthumb) && (bendlady) && (bendring) && (bendmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(4,0);   //Set cursor to character 2 on line 0
    lcd.print("S");
    Serial.println("S");
  }//S // M //N
    if((bendthumb) && (bendlady) && (bendring) && (bendmiddle) && (bendindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("T");
    Serial.println("T");
   }//T
    if((bendthumb) && (bendlady) && (bendring) && (relaxmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("U");
    Serial.println("U");
  }//U
    if((bendthumb) && (bendlady) && (bendring) && (relaxmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
    lcd.print("V");
    Serial.println("V");
  }//V
    if((bendthumb) && (bendlady) && (relaxring) && (relaxmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("W");
    Serial.println("W");
  }//W
    if((bendthumb) && (bendlady) && (bendring) && (bendmiddle) && (bendindex)){
    Serial.println("X");
  }//X
//gyro
    if((relaxthumb) && (relaxlady) && (bendring) && (bendmiddle) && (bendring)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
    lcd.print("Y");
    Serial.println("Y");
  }//Y
//gyro
    if((bendthumb) && (bendlady) && (bendring) && (bendmiddle) && (relaxindex)){
    
    lcd.clear();         
    lcd.backlight();    lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
    lcd.print("Z");
    Serial.println("Z");
  }//Z
  
  delay(1000); // Add a small delay to avoid rapid repeated detections
}