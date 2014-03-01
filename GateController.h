#ifndef gate_controller_h
#define gate_controller_h
#include <Servo.h>
class GateController {
public:
    GateController();
    void step(unsigned long now);
    void open(unsigned long now);
    void close(unsigned long now);
    int busy();

private:
    int state;
    unsigned long magnetsActivationTime;
    unsigned long transitionStartTime;
    int magnetsActive;
    Servo servo;

    void activateMagnets(unsigned long now);
    void deactivateMagnets();
};

#endif