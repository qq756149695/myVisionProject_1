#ifndef SETTING_H
#define SETTING_H

#include<QString>


namespace Device {
extern QString hostName;
extern int port;
extern QString serialName;
}


namespace GlobalV {
extern int screenWidth;
extern int screenHeight;
extern bool PLCSTATE;
}


#endif // SETTING_H
