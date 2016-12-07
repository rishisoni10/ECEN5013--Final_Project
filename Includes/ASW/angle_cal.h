
#ifndef Angle_H_
#define Angle_H_

#define NUM_MUESTRAS_MEDIANA 8

struct tipo_mediana
  {
 unsigned char   ap_muestras;
 int buffer_muestras[NUM_MUESTRAS_MEDIANA];
  };


/*Acceleration  RAM */
extern signed int X_acc;
extern signed int Y_acc;
extern signed int Z_acc;

extern unsigned int xy_mag;
extern unsigned int xz_mag;
extern unsigned int yz_mag;

extern signed  int xy_angle;
extern signed  int xz_angle;
extern signed  int yz_angle;

extern unsigned char fall_input;

extern void angle_calculation(void);
void detect_fall_detection(void);

#endif
