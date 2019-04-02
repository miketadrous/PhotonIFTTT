
int led = D6;
int boardLed = D7;
int photosensor = A0;

int sunValue;
int shadeValue;
int middleThreshold;

bool isInLight = false;

// We start with the setup function.

void setup() {
    // This part is mostly the same:
    pinMode(led,OUTPUT); // Our LED pin is output (lighting up the LED)
    pinMode(boardLed,OUTPUT); // Our on-board LED is output as well



    // Calibrate:
    // First, the D7 LED will go on to tell you to put the system in the shade.
    digitalWrite(boardLed,HIGH);
    delay(2000);

    // Then, the D7 LED will go off and the LED will turn on.
    digitalWrite(boardLed,LOW);
    digitalWrite(led,HIGH);
    delay(500);

    // Now we'll take some readings...
    int off_1 = analogRead(photosensor); // read photosensor
    delay(200); // wait 200 milliseconds
    int off_2 = analogRead(photosensor); // read photosensor
    delay(1000); // wait 1 second
    
    
    digitalWrite(led,LOW);
    delay(500);

    // Now flash to let us know that you've taken the readings...
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    delay(100);
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    delay(1000);

    // Now the D7 LED will go on to tell you to put the system in the sun.
    digitalWrite(boardLed,HIGH);
    delay(2000);

    // Then, the D7 LED will go off and the LED will turn on.
    digitalWrite(boardLed,LOW);
    digitalWrite(led,HIGH);
    delay(500);

    // ...And we will take two more readings.
    int on_1 = analogRead(photosensor); // read photosensor
    delay(200); // wait 200 milliseconds
    int on_2 = analogRead(photosensor); // read photosensor
    delay(300); // wait 300 milliseconds
    
    digitalWrite(led,LOW);
    delay(500); 

    // Now flash the D7 LED on and off three times to let us know that we're ready to go!
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    delay(100);
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    delay(100);
    digitalWrite(boardLed,HIGH);
    delay(100);
    digitalWrite(boardLed,LOW);
    


    sunValue = (on_1+on_2)/2;
    shadeValue = (off_1+off_2)/2;
    middleThreshold = (sunValue+shadeValue)/2;
    


}


void loop() {
    // This sends a publish when the reading exceeds the middleThreshold.
    if (analogRead(photosensor)>middleThreshold) {
        if (isInLight==true) {
            Particle.publish("In_Light","Yes");
            isInLight=false;
        }
    }
    // This sends a publish when the reading less than the middleThreshold.
    else {
        if (isInLight==false) {
            Particle.publish("In_Light","No");
            isInLight=true;
        }
    }
}

