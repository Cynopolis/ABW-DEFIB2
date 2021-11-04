/*
* Code Written by Quinn Henthorne: quinn.henthorne@gmail.com
* 10/7/2021
*
* Pinout List
* Dac0 - Waveform output
* Dac1 - Amplitude output
* D2 - Synch Pin Output (For debugging purposes)
* D22 - Ampltidue Encoder Input
* D23 - Amplitude Encoder Input
* D24 - Period Encoder Input
* D25 - Period Encoder Input
* D26 - Nothing
* D27 - Single pulse armed pin. toggles the armed state when it recieves a falling signal
* D28 - Single pulse enable pin (A FALLING signal toggles single pulse mode)
* D29 - Single pulse trigger. (LOW will cause the arduino to send 1 waveform pulse)
* D30 - Slow pulse flag (LOW enables a pulse rate of 3 pulses/second)
* D31 - Armed state indicator light output
* D32 - Fired state indicator light output
*/


// Define pinouts
#define waveform_pin DAC0
#define amplitude_pin DAC1
#define sync_pin 2
#define single_pulse_arm_pin 27
#define single_pulse_enable_pin 28
#define single_pulse_trig_pin 29
#define slow_pulse_flag_pin 30
#define armed_indicator_pin 31
#define fired_indicator_pin 32

//Include necessary libraries
#include <Arduino.h>
#include <Encoder.h>
#include <LiquidCrystal_I2C.h>


//uncomment to enable serial output for debugging
#define enable_serial_debug
//uncomment to enable lcd output
#define enable_lcd

/* Changes the number of array points to sample. If 1, it will sample every point. 
*  If 2, it will sample every other point,. If four it will sample every 4 points, etc.
*/
#define sample_resolution 4

// Number of waveforms available. Change this if you add or remove waveforms
#define waveform_num 4
// Array of waveform arrays. Currently holds four waveforms with 600 samples each.
int default_waveform[600] = {2048,4093,4091,4088,4085,4083,4080,4077,4075,4072,4069,4066,4064,4061,4058,4055,4052,4050,4047,4044,4041,4038,4036,4033,4030,4027,4024,4021,4018,4015,4012,4009,4007,4004,4001,3998,3995,3992,3989,3986,3983,3980,3977,3973,3970,3967,3964,3961,3958,3955,3952,3949,3946,3942,3939,3936,3933,3930,3926,3923,3920,3917,3913,3910,3907,3904,3900,3897,3894,3890,3887,3884,3880,3877,3874,3870,3867,3863,3860,3856,3853,3850,3846,3843,3839,3836,3832,3829,3825,3821,3818,3814,3811,3807,3803,3800,3796,3792,3789,3785,3781,3778,3774,3770,3767,3763,3759,3755,3751,3748,3744,3740,3736,3732,3728,3725,3721,3717,3713,3709,3705,3701,3697,3693,3689,3685,3681,3677,3673,3669,3665,3661,3657,3652,3648,3644,3640,3636,3632,3627,3623,3619,3615,3610,3606,3602,3598,3593,3589,3585,3580,3576,3571,3567,3563,3558,3554,3549,3545,3540,3536,3531,3527,3522,3518,3513,3508,3504,3499,3494,3490,3485,3480,3476,3471,3466,3462,3457,3452,3447,3442,3437,3433,3428,3423,3418,3413,3408,3403,3398,3393,3388,3383,3378,3373,3368,3363,3358,3353,3348,3342,3337,3332,3327,3322,3316,3311,3306,3301,3295,3290,3285,3279,3274,3268,3263,3258,3252,3247,3241,3236,3230,3225,3219,3213,3208,3202,3197,3191,3185,3180,3174,3168,3162,3157,3151,3145,3139,3133,3127,3122,3116,3110,3104,3098,3092,3086,3080,3074,3068,3062,3055,3049,3043,3037,3031,3025,3018,3012,3006,3000,2993,2987,2981,2974,2968,2961,2955,2948,2942,2935,2929,2922,2916,2909,2903,2896,2889,2883,2876,2869,2862,2856,2849,2842,2835,2828,2821,2815,2808,2801,2794,2787,2780,2773,2766,2758,2751,2744,2737,2048,0,3,5,8,11,13,16,19,22,24,27,30,33,35,38,41,44,47,49,52,55,58,61,64,66,69,72,75,78,81,84,87,90,93,96,99,102,105,108,111,114,117,120,123,126,129,132,135,138,142,145,148,151,154,157,161,164,167,170,173,177,180,183,186,190,193,196,200,203,206,210,213,216,220,223,227,230,233,237,240,244,247,251,254,258,261,265,268,272,276,279,283,286,290,294,297,301,305,308,312,316,319,323,327,331,334,338,342,346,350,353,357,361,365,369,373,377,381,384,388,392,396,400,404,408,412,416,420,425,429,433,437,441,445,449,453,458,462,466,470,474,479,483,487,491,496,500,504,509,513,518,522,526,531,535,540,544,549,553,558,562,567,571,576,580,585,590,594,599,604,608,613,618,622,627,632,637,641,646,651,656,661,666,670,675,680,685,690,695,700,705,710,715,720,725,730,735,741,746,751,756,761,766,772,777,782,787,793,798,803,809,814,819,825,830,836,841,847,852,858,863,869,874,880,885,891,897,902,908,914,919,925,931,937,943,948,954,960,966,972,978,984,990,996,1002,1008,1014,1020,1026,1032,1038,1044,1050,1056,1063,1069,1075,1081,1087,1094,1100,1106,1113,1119,1126,1132,1138,1145,1151,1158,1164,1171,1178,1184,1191,1197,1204,1211,1217,1224,1231,1238,1244,1251,1258,1265,1272,1279,1286,1293,1300,1307,1314,1321,1328,1335,1342,1349,2048
};

// A dynamic waveform that can change its values based on some scalar. This gets initialized at the start of the program
int dynamic_waveform[600];

//Waveform values
float waveform_vals[] = {1,2,3,4,5,6,7,8,9,10};

//Setup encoders and their corresponding variables
Encoder amp_encoder(22, 23);
long new_amp = 10;
long old_amp = 10;
Encoder period_encoder(24, 25);
long new_period = 4;
long old_period = 4;

//Create LCD object
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

//Setup values for arming and firing system
boolean single_fire_is_enabled = true; // is true when single fire mode is enabled
boolean single_fire_is_disabled = false; // is false when single fire mode is disabled. Used to keep track of state changes
boolean is_armed = false; // is true when single fire mode is armed
unsigned long fire_debounce = 0; // A timer to debounce the firing pin
unsigned long armed_debounce = 0; //A time to deboucne the arming pin


/* Cycle through the waveform samples over a given period of time
* The time scalar argument changes how many samples it will skip. 
* A value of 1 will not skip any samples, a value of 2 will use every 2nd sammple, and a value of 5 will use every 5th sample. 
* This allows you to sacrifice resolution for speed. A value of 2 will take half the time to create a waveform pulse
*/
void generate_waveform(int time_scalar){
  // The period of time each sample in the array should take in microseconds
  // The 1000 converts from milliseconds to microseconds, and the 600 deivides by the number of samples in the array
  // The -3 offset compensates for a 3 millisecond overhead created by the time it takes to do all of the calculations
  unsigned int sample_period = (new_period-3)*1000/600;

  // Timer to regulate the step width
  int timer = 0;

  //Loop through all of the samples in the array and output them to Dac 0
  for(int i = 0; i < 600; i=i+time_scalar){
    while(micros()-timer < sample_period);
    analogWrite(waveform_pin, dynamic_waveform[i]);
    timer = micros();
  }
}



// Recalculates the waveform given a new amplitude percentage
void recalc_waveform(float percent_amplitude){
  float amp_scalar = float(percent_amplitude)/10; // Create ampltidue scalar between 0.1 and 1
  float offset = 2048 - 2048*amp_scalar; //Generate offset to keep the waveform DC offset the same

  // Scale the array and give it its new offset
  for(int i = 0; i < 600; i++){
    dynamic_waveform[i] = (int)(default_waveform[i]*amp_scalar + offset);
  }
}

//Changes the LCD screen to the continuous firing status screen
void continuous_output_lcd(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Period:");
  lcd.print((float)(new_period)/sample_resolution);
  lcd.setCursor(0, 1);
  lcd.print("Amplitude:");
  lcd.print(waveform_vals[new_amp-1]);
}

//Change the LCD screen to the single fire status screen
void single_fire_lcd(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Single Fire Mode");
  lcd.setCursor(0,1);
  lcd.print("Armed: ");
  if(is_armed){
    lcd.print("Yes");
  }
  else lcd.print("No");
}

void setup() {
  //Immediately set the analog output to the mid point
  analogWrite(waveform_pin, 2048);
  //The sync pin can be run into an oscilliscope's trig channel to easiy find the waveform
  pinMode(sync_pin, OUTPUT);
  // Setup the rest of the IO pins
  pinMode(single_pulse_enable_pin, INPUT_PULLUP);
  pinMode(single_pulse_arm_pin, INPUT_PULLUP);
  pinMode(single_pulse_trig_pin, INPUT_PULLUP);
  pinMode(slow_pulse_flag_pin, INPUT_PULLUP);
  pinMode(armed_indicator_pin, OUTPUT);
  pinMode(fired_indicator_pin, OUTPUT);

  //Set up interrupts to simplify single fire mode:
  // This will call the arm_single_fire() function whenever it detects a falling signal on this pin
  //attachInterrupt(digitalPinToInterrupt(single_pulse_arm_pin), arm_single_fire, FALLING);

  //Change the resolution of the analog ourput to its maximum (12 bit res)
  analogWriteResolution(12);
  
  // Initialize timers and encoders
  amp_encoder.write(new_amp*4);
  period_encoder.write(new_period*4);

  // Check single pulse status
  single_fire_is_enabled = !digitalRead(single_pulse_enable_pin);
  single_fire_is_disabled = !single_fire_is_enabled;

  // Only executes this block of code if serial debug is enabled
  #ifdef enable_serial_debug
    Serial.begin(115200);
    Serial.print("Ampltidue: ");
    Serial.println(waveform_vals[new_amp-1]);
    Serial.print("Period: ");
    Serial.println(new_period/sample_resolution);
  #endif

  // Loads currently selected waveform into the dynamic waveform
  for(int i = 0; i < 600; i++) dynamic_waveform[i] = default_waveform[i];

  //Init LCD
  #ifdef enable_lcd
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    if(single_fire_is_enabled){
      single_fire_lcd();
    }
    else{
      continuous_output_lcd();
    }
  #endif
}



void loop() {
  // Read in encoder values
  new_amp = amp_encoder.read()/4;
  new_period = period_encoder.read()/4;

  // Check to see if any of the encoder values have changed. If they have, update their values.
  //Handles ampltidue encoder
  if(new_amp != old_amp){
    // Make sure the value is within a valid range
    if(new_amp > 10){
      //128 ampltidue steps should be enough granularity
      new_amp = 10;
      amp_encoder.write(new_amp*4);
    }
    if(new_amp < 1){
      new_amp = 1;
      amp_encoder.write(new_amp*4);
    }
    old_amp = new_amp;
    //If serial is enabled, output some serial data
    #ifdef enable_serial_debug
      Serial.print("Ampltidue: ");
      Serial.println(waveform_vals[new_amp-1]);
    #endif

    // If LCD output is enabled output to LCD
    #ifdef enable_lcd
      if(single_fire_is_enabled == false){
        lcd.setCursor(10,1);
        lcd.print(waveform_vals[new_amp-1]);
      }
    #endif

    recalc_waveform(new_amp);
  }

  //Handles period encoder
  if(new_period != old_period){
    // Make sure the value is within a valid range
    if(new_period > 100){
      new_period = 100;
      period_encoder.write(new_period*4);
    }
    //Anything less than three will cause errors
    if(new_period < 4){
      new_period = 4;
      period_encoder.write(new_period*4);
    }
    old_period = new_period;
    //If serial is enabled, output some serial data
    #ifdef enable_serial_debug
      Serial.print("Period (ms): ");
      Serial.println((float)(new_period)/sample_resolution);
    #endif

    // If LCD output is enabled output to LCD
    #ifdef enable_lcd
      if(single_fire_is_enabled == false){
        lcd.setCursor(7,0);
        lcd.print((float)(new_period)/sample_resolution);
      }
    #endif
  }


  // Creates a synch signal so an oscilliscope can more easily read irregular pulses
  digitalWrite(sync_pin, !digitalRead(sync_pin));

  //Reads the state of the single pulse enable pin
  single_fire_is_enabled = !digitalRead(single_pulse_enable_pin);



  //Check to see if the single fire state has changed
  #ifdef enable_lcd
    if(single_fire_is_enabled == single_fire_is_disabled){
      if(single_fire_is_enabled){
        single_fire_lcd();
      }
      else{
        continuous_output_lcd();
      }
      
    }
  #endif
  single_fire_is_disabled = !single_fire_is_enabled;

  // Check to see if the single pulse pin has been pulled LOW
  if(single_fire_is_enabled){

    //Heavy-duty debounce routine for arming pin
    if(!digitalRead(single_pulse_arm_pin)){
      // Reset the debounce timer
      if(millis()-armed_debounce > 3000) armed_debounce = millis();

      //Once the debounce timer reaches 250ms toggle the armed state.
      if(millis()-armed_debounce > 200 && millis()-armed_debounce < 300){
        // Toggle the armed state
        is_armed = !is_armed;
        // Output the armed state to the lcd
        lcd.setCursor(7,1);
        if(is_armed){
          lcd.print("Yes");
        }
        else lcd.print("No ");
        //Output the armed state to the arm pin
        digitalWrite(armed_indicator_pin, is_armed);
        //Set the timer so this if statement doesn't run again
        armed_debounce = millis()-301;
      }
    }

    // Heavy duty debounce routine for firing pin
    if(!digitalRead(single_pulse_trig_pin) && is_armed){
      // Reset the debounce timer
      if(millis()-fire_debounce > 2500) fire_debounce = millis();

      //Once the debounce timer reaches 250ms toggle the armed state.
      if(millis()-fire_debounce > 200 && millis()-fire_debounce < 300){
        
        digitalWrite(fired_indicator_pin, HIGH);
        //Send out pulse
        generate_waveform(sample_resolution);
        // Toggle the armed state
        is_armed = false;
        // Output the armed state to the lcd
        lcd.setCursor(7,1);
        lcd.print("No ");
        //Output the state to the indicator lights
        digitalWrite(armed_indicator_pin, LOW);
        //Set the timer so this if statement doesn't run again
        fire_debounce = millis()-301;
        armed_debounce = millis();
      }
    }

    // Turn off the fire indicator pin after a half of a second
    if(millis()-fire_debounce>300+500){
        digitalWrite(fired_indicator_pin, LOW);
    }
  }

  else{
    generate_waveform(sample_resolution);
    // Slows down the output pulse if the slow pulse pin is pulled LOW
    if(!digitalRead(slow_pulse_flag_pin)) delay(500);
  }

}