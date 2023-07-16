

#define NOZZLE_D_MODE_CYCLE 0       //Functions similar to the official firmware, each press of the encoder will increase size by step size.
#define NOZZLE_D_MODE_ENCODER 1     //Adjust nozzle diameter with the encoder

#define NOZZLE_D_MODE NOZZLE_D_MODE_ENCODER

#define NOZZLE_DEF_DIAMETER 40      //0.4mm
#define NOZZLE_DEF_DIAMETER_uM NOZZLE_DEF_DIAMETER * 10
#define NOZZLE_MIN_DIAMETER_uM 100  //0.1mm
#define NOZZLE_MAX_DIAMETER_uM 1000 //1.0mm Warning: Max size is 2500 (2.5mm), for larger values you will need to change "oNozzleDiameter" to uint16_t, and "EEPROM_NOZZLE_DIAMETER" which would mess with most of your EEPROM addresses.
#define NOZZLE_DIAMETER_STEPS_uM 50 //0.05mm


#if NOZZLE_D_MODE < 0 || NOZZLE_D_MODE > 1
#error NOZZLE_D_MODE is invalid
#endif

#if NOZZLE_DEF_DIAMETER_uM > NOZZLE_MAX_DIAMETER_uM || NOZZLE_DEF_DIAMETER_uM < NOZZLE_MIN_DIAMETER_uM
#error NOZZLE_DEF_DIAMETER_uM cannot be smaller or larger than the min and max.
#endif

#if NOZZLE_MIN_DIAMETER_uM % NOZZLE_DIAMETER_STEPS_uM != 0
#error NOZZLE_MIN_DIAMETER_uM must be divisible by NOZZLE_DIAMETER_STEPS_uM
#endif

#if NOZZLE_MAX_DIAMETER_uM % NOZZLE_DIAMETER_STEPS_uM != 0
#error NOZZLE_MAX_DIAMETER_uM must be divisible by NOZZLE_DIAMETER_STEPS_uM
#endif

