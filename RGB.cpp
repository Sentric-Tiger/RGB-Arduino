#include "Arduino.h"
#include "RGB.h"


RGB::RGB(int pinR, int pinG, int pinB)
    : RED(pinR), GREEN(pinG), BLUE(pinB)
    {
        //Setting all the colours state to brightness
        pinMode(RED, OUTPUT);
        pinMode(BLUE, OUTPUT);
        pinMode(GREEN, OUTPUT);

    }

    RGB::~RGB()
    {
        //Empty Contructor.
    }
    // Colour varations
    void RGB::Blue()
    {
         Bstate = brightness;
         Rstate = 0;
         Gstate = 0;
        analogWrite(BLUE, Bstate);
        analogWrite(GREEN, Gstate);
        analogWrite(RED, Rstate);
    }
    void RGB::Green()
    {
        Bstate = 0;
        Rstate = 0;
        Gstate = brightness;
        analogWrite(BLUE, Bstate);
        analogWrite(GREEN, Gstate);
        analogWrite(RED, Rstate);
    }
    void RGB::Red()
    {
      Bstate = 0;
      Rstate = brightness;
      Gstate = 0;
      analogWrite(BLUE, Bstate);
      analogWrite(GREEN, Gstate);
      analogWrite(RED, Rstate);
    }
    void RGB::White()
    {
        Bstate = brightness;
        Rstate = brightness;
        Gstate = brightness;
        analogWrite(BLUE, Bstate);
        analogWrite(GREEN, Gstate);
        analogWrite(RED, Rstate);
    }
    void RGB::Yellow()
    {
        Bstate = 0;
        Gstate = brightness;
        Rstate = brightness;
        analogWrite(BLUE, Bstate);
        analogWrite(GREEN, Gstate);
        analogWrite(RED, Rstate);
    }
    void RGB::Magenta()
    {
        Bstate = brightness;
        Gstate = 0;
        Rstate = brightness;
        analogWrite(BLUE, Bstate);
        analogWrite(GREEN, Gstate);
        analogWrite(RED, Rstate);
    }
    void RGB::Cyan()
    {
        Bstate = brightness;
        Gstate = brightness;
        Rstate = 0;
        analogWrite(BLUE, Bstate);
        analogWrite(GREEN, Gstate);
        analogWrite(RED, Rstate);
    }
    void RGB::Raspberry()
    {
        Bstate = 125;
        Gstate = brightness;
        Rstate = brightness;
        analogWrite(BLUE, Bstate);
        analogWrite(GREEN, Gstate);
        analogWrite(RED, Rstate);
    }
   void RGB::begin(int baudRate)
   {
    Serial.begin(baudRate);
   }
    
// State changing for each colour including brightness.
     void RGB::changeBlue(int blue)
    {
        this->Bstate = constrain(blue, 0, this->brightness);
        analogWrite(BLUE, this->Bstate);
    }
    void RGB::changeGreen(int green)
    {
        this->Gstate = constrain(green, 0, this->brightness);
         analogWrite(GREEN, this->Gstate);
    }
    void RGB::changeRed(int red)
    {
        this->Rstate = constrain(red, 0, this->brightness);
        analogWrite(RED, this->Rstate);
    }
    void RGB::changeBrightness(int state)
    {
            this->brightness = state >= 0? state: 0;

    }
    // Setting all state to zero.
    void RGB::OFF()
    {
        Bstate = 0;
        Gstate = 0;
        Rstate = 0;
        analogWrite(BLUE, Bstate);
        analogWrite(GREEN, Gstate);
        analogWrite(RED, Rstate);
    }
    // Getting the pins for all colours.
    int RGB::getBluePin()
    {
        return BLUE;
    }
    int RGB::getRedPin()
    {
        return RED;
    }
    int RGB::getGreenPin()
    {
        return GREEN;
    }

    // getting the state for all pins and brightness
    int RGB::getBlueState()
    {
        return Bstate;
    }
    int RGB::getGreenState()
    {
        return Gstate;
    }
    int RGB::getRedState()
    {
        return Rstate;
    }
    int RGB::getBrightness()
    {
        return brightness;
    }

    // getting the state of all color charaters.
    int RGB::getState(char letter)
    {
        switch(letter)
        {
        case 'B':
           return getBlueState();
        case 'b':
            return getBlueState();
        case 'G':
            return getGreenState();
        case 'g':
            return getGreenState();
        case 'R':
            return getRedState();
        case 'r':
            return getRedState();
        default :
        Serial.print(letter);
        Serial.println(" is an invalid charaters in the RGB::getState().");
            break;

        }
        return 0;
    }

    // getting pins for all colour charaters.
    int RGB::getPin(char letter)
    {

            switch(letter)
        {
        case 'B':
           return getBluePin();
        case 'b':
            return getBluePin();
        case 'G':
            return getGreenPin();
        case 'g':
            return getGreenPin();
        case 'R':
            return getRedPin();
        case 'r':
            return getRedPin();
        default :
        Serial.print(letter);
        Serial.println(" is an invalid charaters in the RGB::getPin().");
            break;

        }
        return 0;
    }
    void RGB::returnState(char letter, int &state)
    {
        switch(letter)
        {
        case 'B':
           Bstate = state; // adjustState(state);
           break;
        case 'b':
            Bstate = state; // adjustState(state);
            break;
        case 'G':
            Gstate = state; // adjustState(state);
            break;
        case 'g':
            Gstate = state; // adjustState(state);
            break;
        case 'R':
            Rstate = state; // adjustState(state);
            break;
        case 'r':
            Rstate =  state; // adjustState(state);
            break;
        default:
        Serial.print(letter);
        Serial.println(" is an invalid charaters in the RGB::returnState().");
            break;
        }
    }

    // changing the delay time.
    void RGB::setTimer(int Time)
    {
        delayTime = Time;
    }

    // making transition to other colours.
    void RGB::transToRed()
    {
        transitionToPrimary('B', 'G', 'R');
    }
    void RGB::transToGreen()
    {
        transitionToPrimary('B', 'R', 'G');
    }
    void RGB::transToBlue()
    {
        transitionToPrimary('R', 'G', 'B');
    }

    // Transition to primary colours.
    void RGB::transitionToPrimary(char letter1, char letter2, char letter3)
    {
      // initiailizing the pins and states of the colour.
        int colour1 = getPin(letter1);
        int colour2 = getPin(letter2);
        int colour3 = getPin(letter3);
        int state1 = getState(letter1);
        int state2 = getState(letter2);
        int state3 = getState(letter3);


// This if statement is called most of the time when transition to primary is called.
        if(state1 > 0 && state2 > 0 && state3 > brightness)
            while(state1 > 0 || state2 > 0 || state3 > brightness)
        {
           
         if(state1 > 0 && state2 == 0 && state3 == brightness)
         {
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2);
                    analogWrite(colour3, state3);
                    delay(delayTime);
         }
         else if(state1 == 0 && state2 > 0 && state3 == brightness)
         {
                    analogWrite(colour1, state1);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3);
                    delay(delayTime);
         }
         else if(state1 == 0 && state2 == 0 && state3 > brightness)
         {
                    analogWrite(colour1, state1);
                    analogWrite(colour2, state2);
                    analogWrite(colour3, state3--);
                    delay(delayTime);
         }
         else if(state1 > 0 && state2 > 0 && state3 == brightness)
         {
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3);
                    delay(delayTime);
         }
         else if(state1 == 0 && state2 > 0 && state3 > brightness)
         {
                    analogWrite(colour1, state1);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3--);
                    delay(delayTime);
         }
         else if(state1 > 0 && state2 == 0 && state3 > brightness)
         {
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2);
                    analogWrite(colour3, state3--);
                    delay(delayTime);
         }
         else
         {
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3--);
                    delay(delayTime);
         }
         
        }
        
// This is also called but not as much as the dirst one.
        else if(state1 > 0 && state2 > 0 && state3 < brightness)
            while(state1 > 0 || state2 > 0 || state3 < brightness)
        {
           
         if(state1 > 0 && state2 == 0 && state3 == brightness)
         {
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2);
                    analogWrite(colour3, state3);
                    delay(delayTime);
         }
         else if(state1 == 0 && state2 > 0 && state3 == brightness)
         {
                    analogWrite(colour1, state1);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3);
                    delay(delayTime);
         }
         else if(state1 == 0 && state2 == 0 && state3 < brightness)
         {
                    analogWrite(colour1, state1);
                    analogWrite(colour2, state2);
                    analogWrite(colour3, state3++);
                    delay(delayTime);
         }
         else if(state1 > 0 && state2 > 0 && state3 == brightness)
         {
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3);
                    delay(delayTime);
         }
         else if(state1 == 0 && state2 > 0 && state3 < brightness)
         {
                    analogWrite(colour1, state1);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3++);
                    delay(delayTime);
         }
         else if(state1 > 0 && state2 == 0 && state3 < brightness)
         {
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2);
                    analogWrite(colour3, state3++);
                    delay(delayTime);
         }
         else
         {
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3++);
                    delay(delayTime);
         }
         
        }

            // if colour1 and colour2 are the same and colour3 is at brightness , then we decrement colour1 and colour2.
            if(state1 == state2 && state1 > 0 && state3 == brightness)
            {
                while(state1 > 0)
                {
                   
                    analogWrite(colour1, state1--);
                    analogWrite(colour2, state2--);
                    analogWrite(colour3, state3);
                    delay(delayTime);
                }

            }

            else if(state1 > 0 && state2 == 0 && state3 == brightness)
            {
                while(state1 > 0)
                {
                   
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
            }
            else if(state2 > 0 && state1 == 0 && state3 == brightness)
            {
                while(state2 > 0)
                {
                    
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
            }


             // if colour1 is greater than zero and colour2 is equal zero while colour3 is less than brightness
             // Then colour is decremented to 0 and colour2 stays the same way while colour3 gets incremented to brightness.
             else if(state1 > 0 && state2 == 0 && state3 < brightness)
             {
                 while(state1 > 0 || state3 < brightness)
                 {
                   
                     if(state1 == 0 && state3 < brightness)
                     {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3++);
                        delay(delayTime);
                     }
                     else if(state3 == brightness && state1 > 0)
                     {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                     }
                     else
                     {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3++);
                        delay(delayTime);
                     }
                 }
             }
             // if colour2  is greater than zero and colour1 is equals to zero while colour3 is less than brightness.
             //Then colour2 is decremented to zero and colour3 is incremented to brightnesss.
             else if(state2 > 0 && state1 == 0 && state3 < brightness)
             {
                 while(state2 > 0 || state3 < brightness)
                 {
                     
                     if(state2 == 0 && state3 < brightness)
                     {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3++);
                        delay(delayTime);
                     }
                     else if(state3 == brightness && state2 > 0)
                     {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                     }
                     else
                     {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3++);
                        delay(delayTime);
                     }
                     
                 }
             }
             // if both colour 1 and 2 are at zero but colour3 is less than brightness
             //Then we increment colour3 to brightness.
             else if(state2 == 0 && state1 == 0 && state3 < brightness)
             {
                 while(state3 < brightness)
                 {
                    
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3++);
                        delay(delayTime);
                        
                 }
             }


             else if( state1 == 0 && state2 > 0 && state3 > brightness)
             {
              while(state2 > 0 || state3 > brightness)
              {
                
                if(state2 == 0 && state3 > brightness)
                {

                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else if(state3 == brightness && state2 > 0)
                {

                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else
                {

                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
              }
             }
             else if(state2 == 0 && state1 > 0 && state3 > brightness)
             {
              while(state1 > 0 || state3 > brightness)
              {
                 // cout<<"1.10"<<endl;
                if(state1 == 0 && state3 > brightness)
                {

                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else if(state3 == brightness && state1 > 0)
                {

                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else
                {

                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }

              }
             }
             else if(state1 == 0 && state2 == 0 && state3 > brightness)
             {
              while(state3 > brightness)
              {
                  //cout<<"1.11"<<endl;

                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
              }
             }
             else if(state1 == 0 && state2 > 0 && state3 == brightness)
             {
              while(state2 > 0)
              {
                 // cout<<"1.12"<<endl;

                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
              }
             }
             else if(state1 > 0 && state2 == 0 && state3 == brightness)
             {
              while(state1 > 0)
              {
                 

                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
              }
             }
             // if all the colours are at the appropraite state then they remain the same way when called upon.
             else if(state1 == 0 && state2 == 0 && state3 == brightness)
            {
              
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
            }


        // returning all the state; to the appropraite colours.
        returnState(letter1, state1);
        returnState(letter2, state2);
        returnState(letter3, state3);

    }


    //This fuction activate two colours at the same time.
    void RGB::transitionToSecondary(char letter1, char letter2, char letter3)
    {
        //Assinging all the letters to the appropraite pins and appropraite states.
        int colour1 = getPin(letter1);
        int colour2 = getPin(letter2);
        int colour3 = getPin(letter3);
        int state1 = getState(letter1);
        int state2 = getState(letter2);
        int state3 = getState(letter3);

        //Note: when you see the word colour in comments it not talking about the colour pins
        // but rather the states it self but the state number is talking about which particular colour it affecting.

        if(state1 < brightness && state2 < brightness && state3 > 0)
            while(state1 < brightness || state2 < brightness || state3 > 0)
        {
           
            if(state1 == brightness && state2 < brightness && state3 > 0)
            {
                analogWrite(colour1, state1);
                analogWrite(colour2, state2++);
                analogWrite(colour3, state3--);
                delay(delayTime);
            }
            else if(state2 == brightness && state1 < brightness && state3 > 0)
            {
                analogWrite(colour1, state1++);
                analogWrite(colour2, state2);
                analogWrite(colour3, state3--);
                delay(delayTime);
            }
            else if( state3 == 0 && state1 < brightness && state2 < brightness)
            {
                analogWrite(colour1, state1++);
                analogWrite(colour2, state2++);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
            else if(state1 == brightness && state2 == brightness && state3 > 0)
            {
                analogWrite(colour1, state1);
                analogWrite(colour2, state2);
                analogWrite(colour3, state3--);
                delay(delayTime);
            }
            else if(state1 == brightness && state2 < brightness && state3 == 0)
            {
                analogWrite(colour1, state1);
                analogWrite(colour2, state2++);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
            else if(state1 < brightness && state2 == brightness && state3 == 0)
            {
                analogWrite(colour1, state1++);
                analogWrite(colour2, state2);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
            else
            {
                analogWrite(colour1, state1++);
                analogWrite(colour2, state2++);
                analogWrite(colour3, state3--);
                delay(delayTime);
            }
            
        }
        
        else if( state1 < brightness && state2 < brightness && state3 == 0)
            while(state1 < brightness || state2 < brightness)
        {
            
            if(state1 == brightness && state2 < brightness)
            {
                analogWrite(colour1, state1);
                analogWrite(colour2, state2++);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
            else if(state1 < brightness && state2 == brightness)
            {
                analogWrite(colour1, state1++);
                analogWrite(colour2, state2);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
            else
            {
                analogWrite(colour1, state1++);
                analogWrite(colour2, state2++);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
        }
        
        else if(state1 > brightness && state2 > brightness && state3 > 0)
            while(state1 > brightness || state2 > brightness || state3 > 0)
        {
           
            if(state1 > brightness && state2 == brightness && state3 == 0)
            {
                analogWrite(colour1, state1--);
                analogWrite(colour2, state2);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
            else if(state1 == brightness && state2 > brightness && state3 == 0)
            {
                analogWrite(colour1, state1);
                analogWrite(colour2, state2--);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
            else if(state1 == brightness && state2 == brightness && state3 > 0)
            {
                analogWrite(colour1, state1);
                analogWrite(colour2, state2);
                analogWrite(colour3, state3--);
                delay(delayTime);
            }
            else if(state1 > brightness && state2 > brightness && state3 == 0)
            {
                analogWrite(colour1, state1--);
                analogWrite(colour2, state2--);
                analogWrite(colour3, state3);
                delay(delayTime);
            }
            else if(state1 == brightness && state2 > brightness && state3 > 0)
            {
                analogWrite(colour1, state1);
                analogWrite(colour2, state2--);
                analogWrite(colour3, state3--);
                delay(delayTime);
            }
            else if(state1 > brightness && state2 == brightness && state3 > 0)
            {
                analogWrite(colour1, state1--);
                analogWrite(colour2, state2);
                analogWrite(colour3, state3--);
                delay(delayTime);
            }
            else
            {
                analogWrite(colour1, state1--);
                analogWrite(colour2, state2--);
                analogWrite(colour3, state3--);
                delay(delayTime);
            }
        }
        
        else if(state1 > brightness && state2 > brightness && state3 == 0)
            while(state1 > brightness || state2 > brightness)
            {
               
                if(state1 > brightness && state2 == brightness)
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state2 > brightness)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
            }
            
            else if(state1 > brightness && state2 < brightness && state3 > 0)
                while(state1 > brightness || state2 < brightness || state3 > 0)
            {
                
                if(state1 > brightness && state2 == brightness && state3 == 0)
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state2 < brightness && state3 == 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state2 == brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else if(state1 > brightness && state2 < brightness && state3 == 0)
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state2 < brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else if(state1 > brightness && state2 == brightness && state3 > 0 )
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
            }
            
            else if(state1 > brightness && state2 < brightness && state3 == 0)
                while(state1 > brightness || state2 < brightness)
            {
                
                if(state1 > brightness && state2 == brightness)
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if (state1 == brightness && state2 < brightness)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
            }
            
            else if(state1 < brightness && state2 > brightness && state3 > 0)
                while(state1 < brightness || state2 > brightness || state3  > 0)
            {
               
                if(state1 < brightness && state2 == brightness && state3 == 0)
                {
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state2 < brightness && state3 == 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state2 == brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else if(state1 < brightness && state2 > brightness && state3 == 0)
                {
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if (state1 == brightness && state2 > brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else if(state1 < brightness && state2 == brightness && state3 > 0 )
                {
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                
            }
            
            else if(state1 < brightness && state2 > brightness && state3 == 0)
                while(state1 < brightness || state2 > brightness)
            {
                
                if(state1 < brightness && state2 == brightness)
                {
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state2 > brightness)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                
            }
            
            else if(state1 > brightness && state2 == brightness && state3 > 0)
                while(state1 > brightness || state3 > 0)
            {
              
                if(state1 > brightness && state3 == 0)
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                
            }
            
            else if(state1 == brightness && state2 > brightness && state3 > 0)
                while(state2 > brightness || state3 > 0)
            {
                
                if(state2 > brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state2 == brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                
            }
            
            else if(state1 < brightness && state2 == brightness && state3 > 0)
                while(state1 < brightness || state3 > 0)
            {
                
                if(state1 < brightness && state3 == 0)
                {
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state1 == brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                
            }
            
            else if(state1 == brightness && state2 < brightness && state3 > 0)
                while(state2 < brightness || state3 > 0)
            {
               
                if(state2 < brightness && state3 == 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                }
                else if(state2 == brightness && state3 > 0)
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                else
                {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
            }


            else if(state1 == brightness && state2 == brightness && state3 > 0)
                while(state3 > 0)
                {
                   
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
                }
                  else if(state1 > brightness && state2 == brightness && state3 == 0)
                    while(state1 > brightness)
                  {
                     
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                  }
                  else if(state1 == brightness && state2 > brightness && state3 == 0)
                    while(state2 > brightness)
                  {
                     
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                  }
                  else if(state1 < brightness && state2 == brightness && state3 == 0)
                    while(state1 < brightness)
                  {
                    
                        analogWrite(colour1, state1++);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                  }
                  else if(state1 == brightness && state2 < brightness && state3 == 0 )
                    while(state2 < brightness)
                  {
                     
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2++);
                        analogWrite(colour3, state3);
                        delay(delayTime);
                  }

            else if(state1 == brightness && state2 == brightness && state3 == 0)
            {
               
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
            }

        else
        {

        }
        // returning all the state; to the appropraite colours.
        returnState(letter1, state1);
        returnState(letter2, state2);
        returnState(letter3, state3);

    }
    
     void RGB::transOff()
    {
        //Assinging all the letters to the appropraite pins and appropraite states.
        int colour1 = RED;
        int colour2 = GREEN;
        int colour3 = BLUE;
        int state1 = Rstate;
        int state2 = Gstate;
        int state3 = Bstate;


            while(state1 > 0 || state2 > 0 || state3 > 0)
        {
            if(state1 > 0 && state2 == 0 && state3 == 0)
            {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3);
                        delay(delayTime);
            }
            else if(state1 == 0 && state2 > 0 && state3 == 0)
            {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
            }
            else if(state1 == 0 && state2 == 0 && state3 > 0)
            {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
            }
            else if(state1 > 0 && state2 > 0 && state3 == 0)
            {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3);
                        delay(delayTime);
            }
            else if(state1 > 0 && state2 == 0 && state3 > 0)
            {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
            }
            else if(state1 == 0 && state2 > 0 && state3 > 0)
            {
                        analogWrite(colour1, state1);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
            }
            else
            {
                        analogWrite(colour1, state1--);
                        analogWrite(colour2, state2--);
                        analogWrite(colour3, state3--);
                        delay(delayTime);
            }
                
        }
        digitalWrite(colour1, LOW);
        digitalWrite(colour2, LOW);
        digitalWrite(colour3, LOW);

        //returning all the state to the appropraite colours.
        returnState('r', state1);
        returnState('g', state2);
        returnState('b', state3);

    }
