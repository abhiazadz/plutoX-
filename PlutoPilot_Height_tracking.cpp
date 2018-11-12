#include  "PlutoPilot.h"
#include  "Control.h"
#include  "Althold.h"
#include  "Motor.h"
#include  "Print.h"
#include  "Angle.h"
#include  "Led.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

int16_t H[15];
int16_t n;
int16_t i;
int32_t alt;
int16_t roll_value;
int16_t throttle_value;

bool isArmed=false;

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
}



//The function is called once before plutoFly when you activate UserCode
void onPilotStart()
{
  // do your one time stuffs here


	roll_value=0;
	throttle_value=0;
	Control.disableFlightStatus(true);
	ledOp(L_MID, OFF);
	ledOp(L_LEFT, OFF);
	ledOp(L_RIGHT, OFF);



}



// The loop function is called in an endless loop
void plutoPilot()
{
	if(!isArmed)
				{

					isArmed=Control.arm();

					Althold.setRelativeAltholdHeight(100);



				}

//Add your repeated code here
	alt=Althold.getAltholdHeight();
//hardcoded matrix H[] for vertical height tracking, with n= no of track points
	i=0
	n=14;
	H[10]=(10,100,50,200,150,300,200,500,250,300,100,50,10);

	Althold.activateAlthold;
	if(i<=n)
	{
		if(i=0)
			Althold.setAltholdHeight(H[i]);

		else if(Althold.getAltholdHeight()==H[i-1])
											  Althold.setAltholdHeight(H[i]);
		i++;
	}


}

//The function is called once after plutoFly when you deactivate UserCode
void onPilotFinish()
{

	 // do your cleanup stuffs here

	isArmed=false;
	Control.disableFlightStatus(false);
	  Motor.set(M1, 1000);
	  Motor.set(M2, 1000);
	  Motor.set(M3, 1000);
	  Motor.set(M4, 1000);


}



