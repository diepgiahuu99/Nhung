// Adding the necessary libraries to operate the keypad,lcd and Fingerprint sensor--//

#include <Adafruit_Fingerprint.h>
#include <Keypad.h>           
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Servo.h>
  
//include definitions for The LED pins--------------------------------------//

SoftwareSerial mySerial(12,13);      // pin #10 is IN from sensor (GREEN wire) and pin #9 is OUT from arduino (WHITE wire)
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

                            
LiquidCrystal_I2C lcd(0x27,16,2); // initialize the LCD library with the numbers of the interface pins

int cursorColumn = 0;       //this controls the cursor postition
int menu = 0;               //this controls the menu settings 
// menu 0:  Default screen
// menu 1:  Selection for default screen
// menu 2:  Login with Password
// menu 3:  Login with fingerprint
// menu 4:  Admin Method Screen 
// menu 5:  Authenicating For Admin
// menu 6:  Check the old password 
// menu 7:  Add a fingerprint
// menu 8:  Delete a fingerprint 
// menu 9:  Input the new Password
int n=0;                    // variable used to point to the bits in the keypad input array  

char password[]={'0','0','0','0'}; //initializing an array called password with variables a,b,c,d that hold the password digits
char input[4];             // an array that will contain the digits that are input
const byte ROWS = 4;       // Four rows
const byte COLS = 4;       // Four columns

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9,8,7,6 };

// Connect keypad COL0, COL1,COL2 and COL3 to these Arduino pins.
byte colPins[COLS] = {5,4,3,2}; 


// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Servo myServo;

void setup()
{
    Serial.begin(9600);
  // set the data rate for the sensor //Serial port
  finger.begin(57600);
  myServo.attach(10);
  lcd.begin();    // set up the LCD's number of columns and rows:
        // Prints a message to the LCD.
  startScreen(); 
  myServo.write(0);
}
void loop()
{
 // myServo.write(0);
  readKeypad();                 // Handles the Keypad object and switch case to read the inputs and decides the output state and leds based on the input    
} 

void readKeypad()
{
  char key = kpd.getKey();
  lcd.setCursor(cursorColumn,1);          // set the cursor to column "cursorColumn", line 1
  if(key)                          // Check for a valid key.
  {
    switch (key)
    {
      case '0':  
      {
        // Each case is a button that is pressed
      
        switch(menu)
        {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          case 0:
          {
            break;
          }
          default:
          {
            lcd.print('0');
            cursorColumn=cursorColumn+1;
            input[n]='0';
            n=n+1;           
            break;  
          }                  
        }
        break;
      }
   case '1':
    {
       switch(menu)
       {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
        case 0:
        {
          break;
        }
        case 1:
        {
         menu = 2;
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Pin: ");
         break;
        }
        case 5:
        {
         menu = 6;
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Enter old code");
         lcd.setCursor(0,1);
         break;
        }
        default:
        {
          lcd.print('1');
          cursorColumn = cursorColumn + 1;
          input[n]='1';
          n=n+1;
          break;
         }
       }
       break;
    }
   case '2':
    {
       switch(menu)
      {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
         case 0:
        {
          break;
        }
        case 1:
        {
          menu = 3;
          lcd.clear();
          fingerCheck();
          break;
        }
        case 5:
        {
         menu = 7;
         lcd.clear();
         lcd.setCursor(0,0);
         finger.getTemplateCount();
          int id = finger.templateCount+1;
          lcd.print("Add ID ");
          lcd.print(id);
          lcd.setCursor(0,1);
          lcd.print("Waiting ");
         break;
        }
        default:
        {
          lcd.print('2');
          cursorColumn=cursorColumn+1;
          input[n]='2';
          n=n+1;
          break;
        }    
       }
     break;
    }
   case '3':
    {
       switch(menu)
        {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          case 0:
          {
            break;
          }
          case 5:
          {
           menu = 8;
           deleteEvent();
           break;
          }
          default:
          {
            lcd.print('3');
            cursorColumn=cursorColumn+1;
            input[n]='3';
            n=n+1;
            break;         
          }
        }
        break;
    }
    case '4':
    {
       switch(menu)
        {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          case 0:
          {
            break;
          }
          default:
          {
            lcd.print('4');
            cursorColumn=cursorColumn+1;
            input[n]='4';
            n=n+1;
            break;         
          }
        }
        break;
    }
    
    case '5':
    {
       switch(menu)
        {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          case 0:
          {
            break;
          }
          default:
          {
            lcd.print('5');
            cursorColumn=cursorColumn+1;
            input[n]='5';
            n=n+1;
            break;         
          }
        }
        break;
    }
    
  case '6':
    {
       switch(menu)
        {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          case 0:
          {
            break;
          }
          default:
          {
            lcd.print('6');
            cursorColumn=cursorColumn+1;
            input[n]='6';
            n=n+1;
            break;         
          }
        }
        break;
    }
   case '7':
    {
       switch(menu)
        {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          case 0:
          {
            break;
          }
          default:
          {
            lcd.print('7');
            cursorColumn=cursorColumn+1;
            input[n]='7';
            n=n+1;
            break;         
          }
        }
        break;
    }
   case '8':
    {
       switch(menu)
        {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          case 0:
          {
            break;
          }
          default:
          {
            lcd.print('8');
            cursorColumn=cursorColumn+1;
            input[n]='8';
            n=n+1;
            break;         
          }
        }
        break;
    }
   case '9':
    {
       switch(menu)
        {                          // the value of "menu" determines the setting parameter and what each button does in that setting  
          case 0:
          {
            break;
          }
          default:
          {
            lcd.print('9');
            cursorColumn=cursorColumn+1;
            input[n]='9';
            n=n+1;
            break;         
          }
        }
        break;
    }
  case 'A':
    {
        if(menu == 0)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          askForSelectionInAuthenicationMenu();
          lcd.setCursor(0,1);
          menu= 1;
        }
        break;
    }
  case 'B':
    {
        if(menu == 0)
        {
          lcd.clear();
          lcd.print("Scan for Admin");
          delay(2000);
          menu= 4;
        }
    }
  case 'C':
    {
        break;   
    }
  case 'D':
    {
        reset();
        break;
    }  
  case '*':
    {
        switch(menu)
        {
          case 0:
          break;
          case 8:
          {
              lcd.clear();
              int id = convertCharAndInt(input);
              lcd.clear();
              lcd.print("Deleting ");
              lcd.print(id);
              delay(2000);
              int flag = deleteFingerprint(id);
              if( flag == 1)
              {            
                lcd.clear();
                lcd.print("Delete ");
                lcd.print(id);
                lcd.setCursor(0,1);
                lcd.print("Successfully");
                reset();
              }
              else 
              {
                lcd.clear();
                lcd.print("Some Error");                
                lcd.setCursor(0,1);
                lcd.print("Cant delete ");
                delay(500);
                lcd.clear();
                lcd.print("Go back to");                
                lcd.setCursor(0,1);
                lcd.print("Admin Method ");
                menu = 5;                
              }
              break;
          }
        }
        break;
    }
  default:
      {
        break;
      } 
    }
  } 
  
  switch(menu)
  {
      case 2:
      {
        if(n>3)
        {
          doorlockCheck();    //calls the function to check whether the code that was input matches the code that is stored
        }
        break;
      }
      case 3:
      {
        if(getFingerprintIDez() != -1)
        {     
          reset();
        }
        break;
      }
      case 4:
      {
        authenicateAdministrator();
        break;
      }
      case 6:
      {
        if(n > 3)
        {
          if(oldCodeCheck() == true)
          {
            menu=9;
          }
        }
         break;
      }
      case 7:
      {
        getFingerprintEnroll();
      }
      case 9:
      {
          if( n>3)
          {
            changeToNewCode(password,input);
            delay(250); 
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Pass Changed");
            delay(1000);  
            reset();
          }
      }
  }
}
int convertCharAndInt(char A[4])
{
  int tempNum = 0;
  int tempCount = 0;
  for (int i = n - 1; i >= 0; i--)
  {
      int temp = 1;
      for (int j = 0; j < tempCount; j++)
      {
          temp = temp * 10;
      }
      tempNum += (int)(A[i] - 48) * temp;
      tempCount++;
  }
  return tempNum;
}

void startScreen()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A Authenicating");
    lcd.setCursor(0,1);
    lcd.print("B Admin Methods");  
}
void deleteEvent()
{
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Input ID");
     lcd.setCursor(0,1);
     lcd.print("You want to delete");
     delay(1500);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Enter by * ");
     lcd.setCursor(0,1);
      n=0;
      for(int i=0;i<4;i++)
      {
        input[i]='h';
      }         
}
void askForSelectionInAdminMethod()
{
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("1-Change Pass");
       lcd.setCursor(0,1);
       lcd.print("2-Add 3-Delele");
}
void authenicateAdministrator()
{
  int idadmin = getFingerprintIDez();
  if(idadmin != 1 && idadmin != 2 )
    {     
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" Not Exactly ! ");
      lcd.setCursor(0,1);
      lcd.print("Try Again");
    }
    else 
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hello Admin! ");
      delay(1000);
      menu = 5; 
      askForSelectionInAdminMethod();
    }
}
void askForSelectionInAuthenicationMenu()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1 - Password");  //prints when the user wants to enter the code
  lcd.setCursor(0,1);
  lcd.print("2 - Fingerprint");
}
boolean checkCode(char *a,char *b)
{  
  Serial.print("Pass");       
  for(int i=0;i< 4 ;i++)
  {
    Serial.print(a[i]);
  }
  delay(1000);
  //The function to check whether the contents of the first parameter,an array, match the                                               //match the contents of the second parameter, also an array.
  for(int p=0; p<4; p++) 
  {
    if(a[p]!=b[p]) return false;
  }
  return true;
}

int changeToNewCode(char *a, char *b)
{
  for(int p=0; p<4; p++)
  {
    a[p]=b[p];
  } 
  n=0;
}

int doorlockCheck()
{
  if(n > 3)
  {
   delay(1000);
   if(checkCode(password,input) == true)
   {
     delay(250);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Correct!"); 
     myServo.write(90);
     delay(7500);
     myServo.write(0);
     reset();
   }
   else
   {
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Invalid pass !"); 
    
    delay(2000); 
    reset();
    }  
     cursorColumn=0;
     n=0;
  }
}

bool oldCodeCheck()
{
   if(checkCode(password,input) == true)
   {
     delay(250);  
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Correct!"); 
     delay(300);
      n=0;
      for(int i=0;i<4;i++)
      {
        input[i]='r';
      }
     lcd.clear();
     lcd.print("Enter new pass: ");
     lcd.setCursor(0,1);
     return true;
   }
   else
    {
     delay(250);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Invalid pass!"); 
     delay(2000);
     return false;
     } 
}

void reset()
{
  int i;
  cursorColumn=0;
  startScreen();
  menu=0;
  n=0;
  for(int i=0;i<4;i++)
  {
    input[i]='h';
  }
}

void fingerCheck()
{
  if (finger.verifyPassword()) 
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Found sensor!");
  }
  else 
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Fingersensor not found :(");
    while (1);
  }
  lcd.setCursor(0,1);
  lcd.print("Waiting..."); 
  return ;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() 
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!

  if(menu!=4)
  {
    lcd.clear();
    lcd.print("Found ID #"); lcd.print(finger.fingerID); 
    lcd.setCursor(0,1);    
    lcd.print("Confidence "); lcd.print(finger.confidence);
    myServo.write(90);
    delay(7500);
    myServo.write(0);
    reset();
  }
  return finger.fingerID; 
}

uint8_t deleteFingerprint(uint8_t id) 
{
  uint8_t p = -1;
  
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) 
  {
    //Serial.println("Deleted!");
    return 1;
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
   //Serial.println("Communication error");
   return p;
  } 
  else if (p == FINGERPRINT_BADLOCATION)
  {
    //Serial.println("Could not delete in that location");
    return p;
  } 
  else if (p == FINGERPRINT_FLASHERR) 
  {
    //Serial.println("Error writing to flash");
    return p;
  }
  else 
  {
    //Serial.print("Unknown error: 0x"); //Serial.println(p, HEX);
    return p;
  }   
}

uint8_t getFingerprintEnroll() 
{

  int p = -1;
  finger.getTemplateCount();
  int id = finger.templateCount+1;
  //Serial.print("Waiting for valid finger to enroll as #"); 
  //Serial.println(id);
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p) 
  {
    case FINGERPRINT_OK:
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      break;
    default:
      //Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) 
  {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }

  lcd.clear();
  lcd.print("Remove finger");
  //Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER)
  {
    p = finger.getImage();
  }
  //Serial.print("ID "); //Serial.println(id);
  p = -1;
  lcd.clear();
  lcd.print("Place same finger again");
  //Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) 
  {
    p = finger.getImage();
    switch (p) 
  {
    case FINGERPRINT_OK:
      //Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      //Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      //Serial.println("Imaging error");
      break;
    default:
      //Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p)
  {
    case FINGERPRINT_OK:
      //Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      //Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Could not find fingerprint features");
      return p;
    default:
      //Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  //Serial.print("Creating model for #");  //Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) 
  {
    //Serial.println("Prints matched!");
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR) 
  {
    ////Serial.println("Communication error");
    return p;
  } 
  else if (p == FINGERPRINT_ENROLLMISMATCH) 
  {
    //Serial.println("Fingerprints did not match");
    return p;
  } 
  else 
  {
    //Serial.println("Unknown error");
    return p;
  }   
  
  //Serial.print("ID ");
  //Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK)
  {
    //Serial.println("Stored!");
  } 
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    //Serial.println("Communication error");
    return p;
  } 
  else if (p == FINGERPRINT_BADLOCATION) 
  {
    //Serial.println("Could not store in that location");
    return p;
  } 
  else if (p == FINGERPRINT_FLASHERR)
  {
    //Serial.println("Error writing to flash");
    return p;
  } 
  else 
  {
    //Serial.println("Unknown error");
    return p;
  }   
  lcd.clear();
  lcd.print("Add Successfully");
  lcd.setCursor(0,1);
  lcd.print("Identity no: ");
  lcd.print(id);
  delay(6000);
  reset();
}
