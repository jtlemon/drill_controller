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

#define SOLENOID_TEST_DELAY_MS 1000

//Homing Interfaces.

#define LIMIT_SW_LEN 5

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
#define DIGITAL_OUT2 23 //D23k

//On-Board Solenoid Drivers

#define SLND_11 45 //D45
#define SLND_12 47 //D47

#define SOLENOID_LEN 11

#define SERVO_X_DIR 55//A1 = D55
#define SERVO_X_STEP 54//A0 = D54
#define SERVO_X_EN 38
#define SERVO_X_AUX -1//NC
#define SERVO_X_PED 67//A13 = D67
#define SERVO_X_ALARM 21
 
#define SERVO_Y_DIR  //A7 = 
#define SERVO_Y_STEP //A6 = 
#define SERVO_Y_EN  //A2 = 
#define SERVO_Y_AUX -1//NC
#define SERVO_Y_PED  //A14 = 
#define SERVO_Y_ALARM 20//D20

#define SERVO_Z_DIR //D48
#define SERVO_Z_STEP //D46
#define SERVO_Z_EN //A8 = 
#define SERVO_Z_AUX -1//NC
#define SERVO_Z_PED 13//D13
#define SERVO_Z_ALARM 19//D19

#define SERVO_A_DIR //D28
#define SERVO_A_STEP //D26
#define SERVO_A_EN //D24
#define SERVO_A_AUX -1//NC
#define SERVO_A_PED //D50
#define SERVO_A_ALARM //D11

#define SERVO_B_DIR //D34
#define SERVO_B_STEP //D36
#define SERVO_B_EN //D30
#define SERVO_B_AUX -1//NC
#define SERVO_B_PED //D52
#define SERVO_B_ALARM //D12


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

enum menu_options{
  MENU_OPT_ALL_AUTOMATIC = 1,
  MENU_OPT_SOLENOID = 2,
  MENU_OPT_DIGITAL_OUT = 3,
  MENU_OPT_DIGITAL_IN = 4,
  MENU_OPT_SPINDLE = 5,
  MENU_OPT_SERVO = 6,
  MENU_OPT_INVALID,
};

typedef struct test_state{
  bool initialized;
  uint8_t test_mode;
  uint8_t last_run_test_id;
}test_state_t;

typedef struct limit_switch{
  homing_interfaces_t axis;
  char axis_letter;
  uint8_t max_pin;
  uint8_t min_pin;
  bool max_is_triggered;
  bool min_is_triggered;
}limit_switch_t;

typedef struct servo_output_pins{
  uint8_t enable_pin;
  uint8_t direction_pin;
  uint8_t step_pin;
  uint8_t aux_pin;
}servo_output_pins_t;

typedef struct servo_input_pins{
  uint8_t ped;
  uint8_t alarm;
}servo_input_pins_t;

typedef struct servo_interface{
  bool is_enabled; //tracking of state, useful in mocked tests for future usage.
  servo_output_pins_t output_pins;
  servo_input_pins_t input_pins;
}servo_interface_t;



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

limit_switch_t limit_switches[] = {
  {
    X_AXIS,
    'X',
    HOMING_X_MAX,
    HOMING_X_MIN,
    false,
    false,
  },
  {
    Y_AXIS,
    'Y',
    HOMING_Y_MAX,
    HOMING_Y_MIN,
    false,
    false,
  },
  {
    Z_AXIS,
    'Z',
    HOMING_Z_MAX,
    HOMING_Z_MIN,
    false,
    false,
  },
  {
    A_AXIS,
    'A',
    HOMING_A_MAX,
    HOMING_A_MIN,
    false,
    false,
  },
  {
    B_AXIS,
    'B',
    HOMING_B_MAX,
    HOMING_B_MIN,
    false,
    false,
  },
  {
    A_AXIS,
    'A',
    HOMING_A_MAX,
    HOMING_A_MIN,
    false,
    false,
  }
};

test_state_t tstate = {
  false,
  MODE_INVALID,
  0,
};

// Function Prototypes

void print_intro(void);
void print_menu(void);
void print_help(void);

void wait_for_input(void);

static void solenoid_init(void);

bool is_valid_solenoid(uint8_t pin);
bool solenoid_enable(uint8_t pin);
bool solenoid_disable(uint8_t pin);
bool solenoid_cycle_all(unsigned long delay_ms);


void limit_switch_init(void);
void limit_switch_tests();
bool check_limit_switch(limit_switch_t* sw);
bool check_homing_interface(homing_interfaces_t axis, bool *min, bool* max);

void probe_init(void);
bool check_probe_interface(uint8_t pin);

void digital_output_tests(void);
void digital_output_init(void);
void digital_output_set(uint8_t pin);

void digital_input_init(void);
bool digital_input_get(uint8_t pin);

void spindle_init(void);
void spindle_tests(void);
void spindle_enable();
void spindle_disable();
void spindle_set_pwm();

void servo_init(void);
void servo_tests();
void servo_set_all_high(servo_interface_t* servo);
void servo_set_all_low(servo_interface_t* servo);


// Function Definitions

void print_intro(void)
{
  //Exit function early if coms isn't setup.
  if(tstate.test_mode == MODE_NO_CONNECTIONS ||
    tstate.test_mode >= MODE_INVALID)
  {
    return;
  }
  Serial.println("Mega Shield Tester:");
  Serial.print("Version: ");
  Serial.println(PGRM_VERSION);

  Serial.print("\r\n");
}

void print_menu(void)
{
  //Exit function early if coms isn't setup.
  if(tstate.test_mode == MODE_NO_CONNECTIONS ||
    tstate.test_mode >= MODE_INVALID)
  {
    return;
  }

  Serial.println("Test Menu:");
  Serial.println("\t1. Run All Automatic Tests.");
  Serial.println("\t2. Run Only Solenoid Tests.");
  Serial.println("\t3. Run Digital Output Tests."); 
  Serial.println("\t4. Run Digital Input Tests."); 
  Serial.println("\t5. Run Spindle Tests.");
  Serial.println("\t6. Run Servo Tests.");
}

void print_help(void)
{
  //Exit function early if coms isn't setup.
  if(tstate.test_mode == MODE_NO_CONNECTIONS ||
    tstate.test_mode >= MODE_INVALID)
  {
    return;
  }

  Serial.println("Program Usage:");
  Serial.println("Work in progress.");
}

void wait_for_input(void)
{
  Serial.println("Press Enter to continue:");
  while(Serial.available() > 0)
  {
    Serial.read();
  }
  while(Serial.available() == 0)
  {
    //do nothing.
  }
  while(Serial.available() > 0)
  {
    Serial.read();
  }
}

static void solenoid_init(void)
{
  for(uint8_t i = 0; i < SOLENOID_LEN; i++)
  {
    pinMode(solenoid_pins_arr[i], OUTPUT);
    digitalWrite(solenoid_pins_arr[i], LOW);
  }

}

void solenoid_tests(void)
{
  Serial.println("Calling: solenoid_tets()");
  Serial.println("Disabling all solenoids...");
  for(uint8_t i = 0; i < SOLENOID_LEN; i++)
  {
    solenoid_disable(solenoid_pins_arr[i]);
  }

  solenoid_cycle_all(SOLENOID_TEST_DELAY_MS);
}

bool is_valid_solenoid(uint8_t pin)
{
  for(uint8_t i = 0; i < SOLENOID_LEN; i++)
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
    Serial.print("Invalid pin number:");
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
    Serial.print("Invalid pin number:");
    Serial.println(pin);
    return false;
  }

  digitalWrite(pin, LOW);
  return true;
}

bool solenoid_cycle_all(unsigned long delay_ms)
{
  bool result = true;

  //First ensure all of them are disabled.
  for(uint8_t i = 0; i < SOLENOID_LEN; i++)
  {
    result = solenoid_disable(solenoid_pins_arr[i]);
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
    Serial.print("enabled solenoid on pin ");
    Serial.println(solenoid_pins_arr[i]);
    delay(delay_ms);

    result = solenoid_disable(solenoid_pins_arr[i]);
    if(result == false)
    {
      return result;
    }
    Serial.print("disabled solenoid on pin ");
    Serial.println(solenoid_pins_arr[i]);
    delay(delay_ms);
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
    Serial.println("Err: check_homing_interface()");
    Serial.println("Invalid axis passed.");
    return false;
  }
  else if(min == NULL || max == NULL)
  {
    Serial.println("Err: check_homing_interface()");
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
      Serial.println("Err: check_homing_interface()");
      Serial.println("Invalid axis passed.");
      return false;
  }

  *max = digitalRead(max_pin) == HIGH;
  *min = digitalRead(min_pin) == HIGH;

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

void digital_output_tests(void)
{
  Serial.println("Calling: digital_output_tests()");
  Serial.println("Setting digital outputs low.");
  digital_output_set(DIGITAL_OUT1, false);
  digital_output_set(DIGITAL_OUT2, false);
  Serial.println("Triggering output 1 for 1S");
  wait_for_input();
  digital_output_set(DIGITAL_OUT1, true);
  delay(1000);
  digital_output_set(DIGITAL_OUT1, false);

  Serial.println("Triggering output 2 for 1S");
  wait_for_input();
  digital_output_set(DIGITAL_OUT2, true);
  delay(1000);
  digital_output_set(DIGITAL_OUT2, false);
}

void digital_output_set(uint8_t pin, bool enable)
{
  if(pin != DIGITAL_OUT1 && pin != DIGITAL_OUT2)
  {
    Serial.println("Error: digital_output_set(), invalid pin.");
  }
  digitalWrite(pin, enable);
  return;
}


void digital_input_init(void)
{
  pinMode(DIGITAL_IN1, INPUT);
  pinMode(DIGITAL_IN2, INPUT);
}

void digital_input_tests(void)
{
  Serial.println("Calling: digital_input_tests()");
  Serial.println("Getting digital inputs inital states...");

  bool in1 = digital_input_get(DIGITAL_IN1);
  bool in2 = digital_input_get(DIGITAL_IN2);
  Serial.print("Digital input1 = ");
  Serial.println(in1);

  Serial.print("Digital input2 = ");
  Serial.println(in2);

  wait_for_input();
  in1 = digital_input_get(DIGITAL_IN1);
  in2 = digital_input_get(DIGITAL_IN2);

  Serial.print("Digital input1 = ");
  Serial.println(in1);

  Serial.print("Digital input2 = ");
  Serial.println(in2);

}

bool digital_input_get(uint8_t pin)
{
  if(pin != DIGITAL_IN1 && pin != DIGITAL_IN2)
  {
    Serial.println("Error: digital_input_get(), invalid pin param.");
    return false;
  }

  return digitalRead(pin) > 0;
}

void spindle_init(void)
{
  pinMode(SPINDLE_EN, OUTPUT);
  pinMode(SPINDLE_DIR, OUTPUT);
  pinMode(SPINDLE_PWM, OUTPUT);
}

//TODO: Add pwm test using frequencies the actual machine uses.
void spindle_tests(void)
{
  Serial.println("Calling spindle_tests()");

  Serial.println("Setting all spindle pins low.");
  //spindle_disable();
  digitalWrite(SPINDLE_EN, LOW);
  digitalWrite(SPINDLE_DIR, LOW);
  digitalWrite(SPINDLE_PWM, LOW);

  Serial.println("waiting 1s");
  delay(1000);

  Serial.println("Setting all spindle pins high for 1S");
  //spindle_enable();
  digitalWrite(SPINDLE_EN, LOW);
  digitalWrite(SPINDLE_DIR, HIGH);
  digitalWrite(SPINDLE_PWM, HIGH);

  digitalWrite(SPINDLE_EN, LOW);
  digitalWrite(SPINDLE_DIR, LOW);
  digitalWrite(SPINDLE_PWM, LOW);

}

//TODO: Use these helper functions with struct to hold data.
void spindle_enable()
{
  
}

void spindle_disable()
{

}

void spindle_set_pwm()
{

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
  {
    tstate.test_mode = MODE_NO_CONNECTIONS;
  }
  else{
    tstate.test_mode = MODE_SERIAL_OVER_USB;
  }

  print_intro();

  solenoid_init();
  digital_output_init();
  digital_input_init();
  spindle_init();

  tstate.initialized = true;
}

void loop() {
  if(Serial.available() > 0)
  {
    print_menu();
    int input = Serial.parseInt();

    switch(input)
    {
      case(MENU_OPT_ALL_AUTOMATIC):
        Serial.println("All automated tests selected.");
        break;
      case(MENU_OPT_SOLENOID):
        Serial.println("Solenoid tests selected.");
        solenoid_tests();
        break;
      case(MENU_OPT_DIGITAL_OUT):
        Serial.println("Digital output test selected.");
        digital_output_tests();
        break;
      case(MENU_OPT_DIGITAL_IN):
        Serial.println("Digital input test selected.");
        digital_input_tests();
        break;
      case(MENU_OPT_SPINDLE):
        Serial.println("Spindle interface tests selected.");
        spindle_tests();
        break;
      case(MENU_OPT_SERVO):
        Serial.println("Servo motor tests selected.");
        servo_tests();
        break;
      default:
        Serial.println("Invalid Option.");
        break;
    };
  }
}





