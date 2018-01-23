#ifndef ICPHANDLER_H
#define ICPHANDLER_H

#define ICP1  1
#define ICP3  3
#define ICP4  4
#define ICP5  5

void attachICPInterrupt(uint8_t ICPChannel, void (*userFunc)(void), int triggerEdge);
void detachICPInterrupt(uint8_t ICPChannel);

#endif // ICPHANDLER_H
