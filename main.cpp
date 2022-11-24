#include "mbed.h"
#include "H3LIS331DL.h"
 
H3LIS331DL h3lis(D4, D7);
I2C i2c0(D14, D15);
const int addr = 0x9E;
extern int* ReadDS1621(void);
DigitalOut ledTemp(D10);
DigitalOut ledAccel(D11);
Serial pc(SERIAL_TX, SERIAL_RX);
AnalogIn AccelX(A0);
AnalogIn AccelY(A1);
AnalogIn AccelZ(A2);

int tempWarning = 26;
int accelWarning = 2;
int accelWarning2 = -2;

int i;
int x;
int y;
int z;



int* ReadDS1621(void)
{
    char cmd[2];
    static int data[2] = {0,0};
    cmd[0] = 0xAC;
    i2c0.write(addr, cmd, 1, false);
    cmd[0] = 0x02;
    i2c0.write(addr, cmd, 1, false);
    thread_sleep_for(20);
    cmd[0] = 0xEE;
    i2c0.write(addr, cmd, 1, false);
    thread_sleep_for(20);
    cmd[0] = 0xAA;
    i2c0.write(addr, cmd, 1, false);
    i2c0.read(addr, cmd, 2, false);
    data[0] = (int)cmd[0]; data[1] = (int)cmd[1];
    return (int*)data;
    }
    

    int main(void)
    {
        int*temp;
       // h3lis.init();
        
        while(1)
        {
            temp = ReadDS1621();
            if (temp[1] == 0)
            {
                temp[1] = 0;
            }
            else{
                
                temp[1] = 5;
                }
            pc.printf("%d : %d \r\n", temp[0], temp[1]);
            thread_sleep_for(1000);
            if (temp[0] >=tempWarning)
            { 
            ledTemp = 1;
            }
            else
            {
            ledTemp = 0;
            }

           /* double accel[3] = {0.0, 0.0, 0.0};
        
            h3lis.getAcceleration(accel);
            pc.printf("acceleration = x = %f\t y = %f\t z = %f\r\n" , ((accel[0]-0.5)*6), ((accel[1])-0.5)*6), ((accel[2]-0.5)*6) );
            thread_sleep_for(1000);

            x = ((accel[0]-0.5)*6);
            y = ((accel[1]-0.5)*6);
            z = ((accel[2]-0.5)*6);
            if (x >= accelWarning || y >= accelWarning || z >= accelWarning || x <= accelWarning2 || y <= accelWarning2 || z <= accelWarning2) {

                pc.printf(" !!! CRASH DETECTED !!! \r\n");
                pc.printf(" !!! POSSIBLE INJURY !!! \r\n");
                pc.printf("acceleration = x = %f\t y = %f\t z = %f\r\n" , ((accel[0]-0.5)*6), ((accel[1])-0.5)*6), ((accel[2]-0.5)*6) );
                ledAccel = 1;
                */

            pc.printf("acceleration = x = %f\t y = %f\t z = %f\r\n" , ((AccelX.read()-0.5)*6), ((AccelY.read()-0.5)*6), ((AccelZ.read()-0.5)*6) );
            thread_sleep_for(1000);

            x = ((AccelX.read()-0.5)*6);
            y = ((AccelY.read()-0.5)*6);
            z = ((AccelZ.read()-0.5)*6);

            if (x >= accelWarning || y >= accelWarning || z >= accelWarning || x <= accelWarning2 || y <= accelWarning2 || z <= accelWarning2) {

                pc.printf(" !!! CRASH DETECTED !!! \r\n");
                pc.printf(" !!! POSSIBLE INJURY !!! \r\n");
                pc.printf("acceleration = x = %f\t y = %f\t z = %f\r\n" , ((AccelX.read()-0.5)*6), ((AccelY.read()-0.5)*6), ((AccelZ.read()-0.5)*6) );
                ledAccel = 1;


            }


        }

    }   


