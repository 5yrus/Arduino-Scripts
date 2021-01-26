char * choices[3] = {"Rock", "Paper", "Scissors"};
char * finalResult[3] = {"You Lost", "You Won!", "It's a Tie"};

byte Human = 0, Computer = 0, FR = 0;

char result[25];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  unsigned long R;
  randomSeed(R);
}

void loop()
{
  // put your main code here, to run repeatedly:
  char choice = 'y';

  while (choice != 'N' || choice != 'n')
  {
    if (Serial.available() > 0)
    {
      choice = Serial.read();
      if (choice != '\n' || choice != '\r' || choice != '\c')
      {
        if ( (choice >= '1') && (choice <= '3') )
        {
          Throw(choice);
          Serial.println(F("Play again? Enter N or n to quit, otherwise please enter a number\n"));
        }
        else if (choice == 'y' || choice == 'Y')
          Serial.println(F("You are already playing"));

        else if (choice == 'n' || choice == 'N')
          break;
        else
          Serial.println(F("Invalid choice! Your choices are: 
                                  \n1 = Rock \n2 = Paper \n3 = Scissors 
                                   \nN/n if you want to quit playing \n"));
      }
    }
  }
  Score();
  Serial.println(F("Thank you for playing"));
  Reset();
}

void Throw(char H)
{
  bool thrown = false;
  H -= '0'; //convert ascii to decimal
  H -= 1; // instead of  1,2,3, H is now 0,1,2

  byte C = random(0, 3);

  sprintf(result, "The Computer chose: %s, You chose: %s", choices[C], choices[H]);
  Serial.println(result);

  if ( C == H)
    Serial.println(F("Its a TIE"));
  else
  {
    switch (C)
    {
      case 0:
        switch (H)
        {
          case 1:
            Serial.println(F("Paper wraps Rock, You WIN!"));
            Human++;
            break;

          case 2:
            Serial.println(F("Rock crushes Scissors, You LOSE!"));
            Computer++;
            break;
        }
        break;

      case 1:
        switch (H)
        {
          case 0:
            Serial.println(F("Paper wraps Rock, You LOSE!"));
            Computer++;
            break;

          case 2:
            Serial.println(F("Scissors cuts Paper, You WIN!"));
            Human++;
            break;
        }
        break;

      case 2:
        switch (H)
        {
          case 0:
            Serial.println(F("Rock crushes Scissors, You WIN!"));
            Human++;
            break;

          case 1:
            Serial.println(F("Scissors cuts Paper, You LOSE!"));
            Computer++;
            break;
        }
        break;
    }
  }
}

void Score()
{
  if (Human > Computer)
    FR = 1;
  else if (Human < Computer)
    FR = 0;
  else
    FR = 2;

  sprintf(result, "%s, %d to %d", finalResult[FR], Human, Computer);
  Serial.println(result);
}

void Reset()
{
  Human = 0;
  Computer = 0;
}
