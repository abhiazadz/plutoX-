// Do not remove the include below
#include  "PlutoPilot.h"
#include  "Control.h"
#include  "Motor.h"
#include  "Print.h"
#include  "Angle.h"
#include  "Led.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

int16_t roll_value;
int16_t pitch_value;
int16_t yaw_value;

int16_t throttle_value;
int16_t m1m2Value;
int16_t m3m4Value;

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
//Drift problem approach assuming no external input given to channge Roll/pitch/yaw
//otherwise we can add subtract the real time inputs by controller to find drifts in that case

//	roll_value=Flight.getAngle(ROLL);
//	pitch_value=Flight.getAngle(PITCH);
//	roll_value=Flight.getAngle(YAW);
//	Print.monitor(“Roll_drift”, roll_value);
//	Print.monitor(“Pitch_drift”, pitch_value);
//	Print.monitor(“Yaw_drift”, yaw_value);
//not using it as above functions values ranges 0-3600(as mentioned in booklet), so I would have to scale them between 1000-2000 further
	roll_value=Control.getRC(RC_ROLL);
	pitch_value=Control.getRC(RC_PITCH);
	yaw_value=Control.getRC(RC_YAW);

//printing drift values caused due to internal/external factors to the system
	Print.monitor(“Roll_drift”, roll_value-1500);
	Print.monitor(“Pitch_drift”, pitch_value-1500);
	Print.monitor(“Yaw_drift”, yaw_value-1500);

//assuming to avoid drift about neutral point i.e 1500 value
	roll_value=Control.getRC(RC_ROLL)+(1500-Control.getRC(RC_ROLL));
	pitch_value=Control.getRC(RC_PITCH)+(1500-Control.getRC(RC_PITCH));
	yaw_value=Control.getRC(RC_YAW)+(1500-Control.getRC(RC_YAW));


throttle_value=Control.getRC(RC_THROTTLE);
//correcting drifts
    Control.setRC(RC_ROLL, roll_value);
    Control.setRC(RC_PITCH, pitch_value);
    Control.setRC(RC_YAW, yaw_value);

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

