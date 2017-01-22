/* 
 MotorA was used for moving forward and was planted backwards thus needing negative power to move ahead. 
 MotorB was used to steer the car where positive power steered left and vice versa.
 MotorC acted as a drop-off mechanism.
*/

// Function for Begining and ending of program
void Start()
{
    eraseDisplay();
    nxtDisplayCenteredTextLine(4,"Press To Start");
    
    while(nNxtButtonPressed!=3){}
    while(nNxtButtonPressed==3){}     //wait until the released
    
    eraseDisplay();
}

void end()
{
	motor[motorA]=0;
    
	eraseDisplay();
	int a = time100[T1];
    
	nxtDisplayCenteredTextLine(3,"Time taken: %d", a/10);
	wait10Msec(500);
    
	nxtDisplayCenteredTextLine(3,"Thank You");
	wait10Msec(100);
    
	nxtDisplayCenteredTextLine(4,"For Watching");
	wait10Msec(100);
    
	nxtDisplayCenteredTextLine(6,"GENE 121 <3");
	
    while(nNxtButtonPressed!=3);
	while(nNxtButtonPressed==3);    //wait until the released
}

// Funtions for action after reaching house

void Tippy() //This function triggers the third motor to tip over luggage
{
	nMotorEncoder[motorC] = 0;
    motor[motorC] = 10;
    
    while(nMotorEncoder[motorC] <= 40);
    wait10Msec(100);
    
    motor[motorC] =-10;
    while(nMotorEncoder[motorC] >= 0);
    
    motor[motorC] = 0;
}

float fuelPrice() // Function used to calculate fuel price
{
	int a = nMotorEncoder[motorA]
    int rate = 0.5 // dollors per cm
	
    return 0.5*a/28.4; //28.4 is the encodercounts per cm covered
}

void printPrice(float fuelPrice, float package) // Function used to print costs
{
	eraseDisplay();
	nxtDisplayString(2,"Fuel Cost $%.2f",fuelPrice);
	nxtDisplayString(3,"Item Cost $%.2f",package);
	nxtDisplayString(5,"Total Cost $%.2f",fuelPrice+package);

	wait10Msec(500);

	eraseDisplay();
	wait10Msec(300);
}

// Function for tunring, steering and linefollowing to reach house

void traffic()
{
    while(SensorValue[S2]==2 && SensorValue[S3]<25) //waiting while light is blue(red) a no pedestrian ahead of the vehicle
        motor[motorA]=0;
    
    while(SensorValue[S2]!=3);
}


void juncTurn(char command) //function conducting turns at junctions
{
    traffic();
    
	if (command=='l')
	{
		motor[motorA]= -12;
		wait1Msec(1000);

		motor[motorB]= 30;
		wait1Msec(350);

		motor[motorB]=0;
		wait1Msec(3500);

		motor[motorB]= -30;
		wait1Msec(350);
		motor[motorB]= 0;
	}

	else if (command=='r')
	{
		motor[motorA]= -12;
		wait1Msec(1000);

		motor[motorB]= -30;
		wait1Msec(350);

		motor[motorB]=0;
		wait1Msec(3500);

		motor[motorB]= 30;
		wait1Msec(347);
		motor[motorB]= 0;
	}

	else if (command=='s')
	{
		motor[motorA]=-15;
		wait1Msec(4200);
	}
}

void steerLine(int color)
{
	if (color==6) //triggering of a left turn when sensing white
	{
		motor[motorB]=30;
		wait1Msec(310);

		motor[motorB]=0;

		while(SensorValue[S2]!=4 && Sensorvalue[S2]!=5); //waiting to sense red or yellow
		nxtDisplayClearTextLine(3);
		
        motor[motorB]=-30;
		wait1Msec(301);
	}


	else if (color==1) //triggering of a right turn when sensing black
	{
		motor[motorB]=-30;
		wait1Msec(310);

		motor[motorB]=0;

		while(SensorValue[S2]!=4 && Sensorvalue[S2]!=5); //waiting to sense red or yellow
        nxtDisplayClearTextLine(3);

        motor[motorB]=30;
		wait1Msec(290);

	}
    
	motor[motorB]=0;
}

void linefollowing(bool house)
{
    motor[motorA]= -10;

	while((SensorValue[S2]==4 || SensorValue[S2]==1 || SensorValue[S2]==6 || SensorValue[S2]==5)) //linefollowing continuing while sensing yellow, black, white
	{

		if(SensorValue[S2]==1)
		steerLine(1);          //moving right when black is sensed

		else if(SensorValue[S2]==6)
		steerLine(6);          //moving left when white is sensed

		wait10Msec(50);        //wait used to decrease stuttering of bot

		if(house==true)        //checking for the sensing of house for when the input bool is set to true
		{
			SensorType[S4]=sensorLightActive;
			if(SensorValue[S4]>35)
			{
                motor[motorA]=0;
				Tippy();      //execution of unloading of material
			}
		}
	}
}

// Function for selection and execution of house

int housepick()
{
	nxtDisplayCenteredTextLine(2,"Press Button:");
	nxtDisplayCenteredTextLine(3,"House 1: Right");
	nxtDisplayCenteredTextLine(4,"House 2: Left");
	nxtDisplayCenteredTextLine(5,"House 3: Orange");
    
	while(nNxtButtonPressed==-1);
    
	if(nNxtButtonPressed==3)
	{
		while (nNxtButtonPressed==3);
        eraseDisplay();
		return 3;
	}
    
	else if(nNxtButtonPressed==1)
	{
		while (nNxtButtonPressed==1);
        eraseDisplay();
		return 1;
	}
    
	else if(nNxtButtonPressed==2)
	{
		while (nNxtButtonPressed==2);
		eraseDisplay();
		return 2;
	}
    
    else
        return 0;
}

void house1(float package) //path to house one
{
    linefollowing(0);
    juncTurn('r');

    linefollowing(true);            //finding destination house2
    float a=fuelPrice();
    printPrice(a, package);

    Start();                        //waiting for user to trigger start
    linefollowing(true);            //finding home
    motor[motorA]=0;
    
    nxtDisplayString(3,"Welcome Home Fiona");
    wait10Msec(500);
    eraseDisplay();
}


void house2(float package) //path to house two
{
	linefollowing(0);
	juncturn('s');

	linefollowing(0);
	juncturn('r');

	linefollowing(true);        //checking for destination house2
    float a=fuelPrice()
	printPrice(a, package);
	
    Start();
	juncturn('r');
    
	linefollowing(true); // checking for home
	motor[motorA]=0;
    
	nxtDisplayString(3,"Welcome Home Fiona");
	wait10Msec(500);
	eraseDisplay();
}

void house3(float package)  //path to house three
{
	linefollowing(0);
	juncturn('s');

	linefollowing(0);
	juncturn('s');

	juncTurn('r');
	linefollowing(true);       //checking for destination house3
    
    float a = fuelPrice()
	printPrice(a, package);
	Start();

	linefollowing(true);   // checking for home
	motor[motorA]=0;

	nxtDisplayString(3,"Welcome Home Fiona");
	wait10Msec(500);
	eraseDisplay();
}

task main()
{
	time100[T1]=0;
	nMotorEncoder[motorA]=0;
	float package=10.00;

	SensorType[S2]=sensorCOLORFULL;
	SensorType[S3]=sensorSONAR;

	Start();

	int a = housepick(); //allowing used to chose house

	if(a==1)
	{
		nxtDisplayCenteredTextLine(4,"House 1");
     
		house1(package);
	}
    
	else if(a==2)
	{
		nxtDisplayCenteredTextLine(4,"House 2");
		house2(package);
	}
    
	else if(a==3)
	{
		nxtDisplayCenteredTextLine(4,"House 3");
		house3(package);
	}

    end();
}

