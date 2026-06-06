// C++ code
//
const int ledPins[] = {7, 6, 5};
const int buttonPins[] = {4, 3, 2};
const int numPins = sizeof(ledPins)/sizeof(ledPins[0]);
const int buzzer = 8;
const int maxSeq = 6 ;
const int noises[] = {200, 300, 400};
int seqArray[maxSeq];
int seqLen = 0;
int blinkTime = 400;

//declarations
void start();
void winAnimation();
void loseAnimation();
void turnOffAllLeds();
void addRandom();
void showSeq();
bool inputs();
void blink(int led, int time);
void cheatSeq();

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0)); //allows for randomness by adding in noise from analog read
  pinMode(buzzer, OUTPUT);
  
  for (int i = 0; i < numPins; i++){
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP); //could also use INPUT_PULLUP
    digitalWrite(ledPins[i], LOW);
  }
  
}
//Main
void loop()
{ 
  addRandom();
  seqLen++; //adds on to sequence
  showSeq(); // shows sequence
  cheatSeq();
  delay(50);
  bool correct = inputs(); // will reutrn if players input matches the seqenece

  if (!correct) //if False or if Lost
  {
    loseAnimation();
    start();
  }

  if (seqLen == maxSeq) //checking if game has reached an end
  {
    Serial.print("WIN!!!");
    winAnimation();
    start(); //Starts new game
  }
  delay(400);
}

//Functions

void cheatSeq()
{
  for (int i = 0; i < seqLen; i++)
  {
    Serial.print(seqArray[i]); 
  }
  Serial.println( );
}

void addRandom() //Adds a random number to the seqArray
{
  int newStep = random(0, numPins);
  seqArray[seqLen] = newStep;
  //Serial.println("addRandom");
}


void showSeq()
{
  for (int i = 0; i < seqLen; i++)
  {
    int num = seqArray[i];
    blink(num, blinkTime);
    delay(400);
    //Serial.println("showSeq");
  }
}

bool inputs()
{
  //Serial.println("inputs");
  for (int i = 0; i < seqLen; i++) //i represents which loop it is on
  {
    int pressed = -1;
    while (pressed == -1)//waiting for input
    {
      for (int j = 0; j < numPins; j++) //j represents button index 
      {
        if (digitalRead(buttonPins[j]) == LOW)//button has been pressed
            {
              delay(50);
              if (digitalRead(buttonPins[j]) == LOW)
              {
                //Serial.println("button detected");
                pressed = j;
                Serial.print(j);
                blink(j, blinkTime);
                if(pressed != seqArray[i])
                {
                  Serial.println("WRONG");
                  return false;
                }
              }
            break; 
            }
      }
    }
  }
  	Serial.println();
	return true; //passing the for loop means it made it
}



void blink(int led, int time)
{
  digitalWrite(ledPins[led], HIGH);
  tone(buzzer, noises[led]);
  delay(50);
  noTone(buzzer);
  delay(time);
  
  digitalWrite(ledPins[led], LOW);
}

void start()
{
  //Serial.println("start");
  seqLen = 0;
  turnOffAllLeds();
  
  for (int i = 0; i < numPins; i++)
  {
	blink(i, blinkTime);
  }
  
}

void turnOffAllLeds() 
{
  //Serial.println("turnoffallLeds");
  for (int i = 0; i < numPins; i++)
  {
  	digitalWrite(ledPins[i], LOW);
  }
   
}


void loseAnimation()
{
  for(int i=0; i<5; i++) {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    tone(buzzer, 300);
    delay(100);
    turnOffAllLeds();
    delay(100);
  }
  //Serial.println("loseanimation");

}

void winAnimation() {
  //Serial.println("win");
  for (int k = 0; k < 3; k++)
  {
    for (int i = 0; i < numPins; i++)
    {
      digitalWrite(ledPins[i], HIGH);
      tone(buzzer, (i + 3) * 350);
      delay(150);
      turnOffAllLeds();
      noTone(buzzer);
    }
  
  delay(300);
  }
}



/*
generate sequence
for loop for length of seq (for game)
add a random to seq
show sequence (for loop for how many to show
delay
wait for inputs (while loop)
check if they match
if wrong then break and lose animation
if right continue
after for loop then win
*/
  
