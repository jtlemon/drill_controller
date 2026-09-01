/**
 * @author: Jake Goodwin
 * @date: 2026-08-27
 * @description: Testing program for mega shield.
 * @version: 0.1.0
 */

// Constantants

//Uses semantic versioning.
static const char PGRM_VERSION[] = "0.1.0";

//The 9600 baud rate is reasonable and shouldn't be error prone
// even over longer wires.
#ifndef SERIAL_BUAD
#define SERIAL_BUAD 9600
#endif

#define SERIAL_SETUP_TIMEOUT_MS 1000 

//Homing Interfaces.
#define HOMING_X_MAX 2 //D2
#define HOMING_X_MIN 3 //D3

#define HOMING_Y_MAX 15 //D15
#define HOMING_Y_MIN 14 //D14

#define HOMING_Z_MAX 32 //D32
#define HOMING_Z_MIN 18 //D18

#define HOMING_A_MAX 40 //D40
#define HOMING_A_MIN 42 //D42

#define HOMING_B_MAX 5 //A5
#define HOMING_B_MIN 44 //D44

//Servo Interface(s)



//Probe Interface

#define PROBE 15 //A15

//10CH Solenoid Interface

#define SLND_2 6 //D6
#define SLND_3 35 //D35
#define SLND_4 7 //D7
#define SLND_5 16 //D16
#define SLND_6 17 //D17
#define SLND_7 39 //D39
#define SLND_8 33 //D33
#define SLND_9 41 //D41
#define SLND_10 43 //D43

//Spindle Interface

#define SPINDLE_EN 4 //D4
#define SPINDLE_DIR 5 //D5
#define SPINDLE_PWM 8 //D8

//Digital Inputs

#define DIGITAL_IN1 25 //D25
#define DIGITAL_IN2 27 //D27

//Digital Outputs

#define DIGITAL_OUT1 22 //D22
#define DIGITAL_OUT2 23 //D23

//On-Board Solenoid Drivers

#define SLND_11 45 //D45
#define SLND_12 47 //D47

#define SOLENOID_LEN 11

// Structures, classes and globals.
enum test_modes{
  MODE_NO_CONNECTIONS,
  MODE_SERIAL_OVER_USB,
  MODE_INVALID //Anything equal to or greater is an error.
};

enum test_ids{
  TEST_ID_INVALID,
};

typedef enum{
  X_AXIS,
  Y_AXIS,
  Z_AXIS,
  A_AXIS,
  B_AXIS,
  INVALID_AXIS,
}homing_interfaces_t;

typedef struct test_state{
  bool initialized;
  uint8_t test_mode;
  uint8_t last_run_test_id;
}test_state_t;

test_state_t tstate = {
  false,
  MODE_INVALID,
  0,
};

uint8_t solenoid_pins_arr[SOLENOID_LEN] = {
  SLND_2,
  SLND_3,
  SLND_4,
  SLND_5,
  SLND_6,
  SLND_7,
  SLND_8,
  SLND_9,
  SLND_10,
  SLND_11,
  SLND_12,
};


// Function Prototypes

void print_intro(void);
void print_menu(void);
void print_help(void);

void solenoid_init(void);

bool is_valid_solenoid(uint8_t pin);
bool solenoid_enable(uint8_t pin);
bool solenoid_disable(uint8_t pin);
bool solenoid_cycle_all(delay_us);


void homing_init(void);
bool check_homing_interface(homing_interfaces_t axis, bool *min, bool* max);

void probe_init(void);
bool check_probe_interface(uint8_t pin);

void digital_output_init(void);
void digital_output_set(uint8_t pin);

void digital_input_init(void);
bool digital_input_get(uint8_t pin)

void spindle_enable();
void spindle_disable();
void spindle_set_pwm();


// Function Definitions

void print_intro(void)
{
  //Exit function early if coms isn't setup.
  if(tstate.test_mode == MODE_NO_CONNECTIONS ||
    tstate.testing >= MODE_INVALID)
  {
    return;
  }
  Serial.println("Mega Shield Tester:");
  Serial.print("Version: ");
  Serial.print(PGRM_VERSION);

  Serial.print("\r\n");
}


void print_menu(void)
{
  //Exit function early if coms isn't setup.
  if(tstate.test_mode == MODE_NO_CONNECTIONS ||
    tstate.testing >= MODE_INVALID)
  {
    return;
  }

  println("Test Menu:")
  println("\t1. Run All Automatic Tests.");
  println("\t2. Run Only Solenoid Tests.");
  println("\t3. Run Digital Output Tets."); 
  println("\t4. Run Digital Input Tests."); 
  println("\t5. Run Spindle Tests.");
  println("\t6. Run Servo Tests.");
}

void print_help(void)
{
  //Exit function early if coms isn't setup.
  if(tstate.test_mode == MODE_NO_CONNECTIONS ||
    tstate.testing >= MODE_INVALID)
  {
    return;
  }

  Serial.println("Program Usage:");
  Serial.println("Work in progress.");
}

static void solenoid_init(void)
{
  for(uint8_t i = 0; i < SOLENOID_LEN; i++)
  {
    pinMode(solenoid_pins_arr[i], OUTPUT);
    digitalWrite(solenoid_pins_arr[i], LOW);
  }

}

bool is_valid_solenoid(uint8_t pin)
{
  for(i = 0; i < SOLENOID_LEN; i++)
  {
    if(pin == solenoid_pins_arr[i])
    {
      return true;
    }
  }
  return false;
}

bool solenoid_enable(uint8_t pin)
{
  if(!is_valid_solenoid(pin))
  {
    Serial.println("ERR: solenoid_enable()");
    Serial.print("Invalid pin number:")
    Serial.println(pin);
    return false;
  }
  digitalWrite(pin, HIGH);
  return true;
}

bool solenoid_disable(uint8_t pin)
{
  if(!is_valid_solenoid(pin))
  {
    Serial.println("ERR: solenoid_enable()");
    Serial.print("Invalid pin number:")
    Serial.println(pin);
    return false
  }

  digitalWrite(pin, LOW);
  return true;
}

bool solenoid_cycle_all(delay_us)
{
  bool result = true;

  //First ensure all of them are disabled.
  for(uint8_t i = 0; i < SOLENOID_LEN; i++)
  {
    result = solenoid_disable(i);
    if(result == false)
    {
      return result; 
    }
  }

  for(uint8_t i = 0; i < SOLENOID_LEN; i++)
  {
    result = solenoid_enable(solenoid_pins_arr[i]);
    if(result == false)
    {
      return result;
    }
    delay(delay_us);

    result = solenoid_disable(solenoid_pins_arr[i]);
    if(result == false)
    {
      return result;
    }

    delay(delay_us);
  }

  return result;
}


void homing_init(void)
{
  pinMode(HOMING_X_MAX, INPUT);
  pinMode(HOMING_X_MIN, INPUT);

  pinMode(HOMING_Y_MAX, INPUT);
  pinMode(HOMING_Y_MIN, INPUT);

  pinMode(HOMING_Z_MAX, INPUT);
  pinMode(HOMING_Z_MIN, INPUT);

  pinMode(HOMING_A_MAX, INPUT);
  pinMode(HOMING_A_MIN, INPUT);

  pinMode(HOMING_B_MAX, INPUT);
  pinMode(HOMING_B_MIN, INPUT);
}

bool check_homing_interface(
homing_interfaces_t axis, bool *min, bool* max)
{
  if(axis >= INVALID_AXIS)
  {
    Serial.println("Err: check_probe_interface()");
    Serial.println("Invalid axis passed.");
    return false;
  }
  else if(out == NULL)
  {
    Serial.println("Err: check_probe_interface()");
    Serial.println("Passed null ptr.");
    return false;
  }

  uint8_t max_pin = 0;
  uint8_t min_pin = 0;

  switch(axis)
  {
    case X_AXIS:
      max_pin = HOMING_X_MAX;
      min_pin = HOMING_X_MIN;
      break;
    case Y_AXIS:
      max_pin = HOMING_Y_MAX;
      min_pin = HOMING_Y_MIN;
      break;
    case Z_AXIS:
      max_pin = HOMING_Z_MAX;
      min_pin = HOMING_Z_MIN;
      break;
    case A_AXIS:
      max_pin = HOMING_A_MAX;
      min_pin = HOMING_A_MIN;
      break;
    case B_AXIS:
      max_pin = HOMING_B_MAX;
      min_pin = HOMING_B_MIN;
      break;
    default:
      Serial.println("Err: check_probe_interface()");
      Serial.println("Invalid axis passed.");
      return false;
  }

  *max == digitalRead(max_pin)
  *min == digitalRead(min_pin)

  return true;
}

void probe_init(void)
{
  pinMode(PROBE, INPUT);
}

bool check_probe_interface(void)
{
  return digitalRead(PROBE);
}


void digital_output_init(void)
{
  pinMode(DIGITAL_OUT1, OUTPUT);
  pinMode(DIGITAL_OUT2, OUTPUT);
}

void digital_output_set(uint8_t pin)
{
  return;
}


void digital_input_init(void)
{
  pinMode(DIGITAL_IN1, INPUT);
  pinMode(DIGITAL_IN2, INPUT);
}

bool digital_input_get(uint8_t pin)
{
  if(pin > 2)
  {
    return false;
  }

  return digitalRead(pin);
}


void setup() {
  // put your setup code here, to run once:
  
  //Setup the serial connection over the USB->serial IC.
  Serial.begin(SERIAL_BUAD);

  //Wait until serial connection established.
  for(uint16_t t = 0; !Serial && t < SERIAL_SETUP_TIMEOUT_MS; t++)
  {
    delay(1);
  }

  if(!Serial)
    tstate.test_mode = MODE_NO_CONNECTIONS;
  }
  else{
    tstate.test_mode = MODE_SERIAL_OVER_USB;
  }

  print_intro();

  solenoid_init();

  tstate.initialized = true;
}

void loop() {
  // put your main code here, to run repeatedly:

}





