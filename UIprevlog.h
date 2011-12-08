#include "globaltypes.h"
class set_reset_ui{
public:
    bool Fire;
    bool Security;
    bool Exit;
public:
    bool setFire(bool);
    bool setSecurity(bool);
    bool setexit(bool);
}zone1,zone2,zone3,zone4,zone5,zone6,zone7,zone8;

bool set_reset_ui::setFire(bool fire){
    Fire=fire;
    return Fire;
}
bool set_reset_ui::setSecurity(bool security){
    Security=security;
    return Security;
}
bool set_reset_ui::setexit(bool exit){
    Exit=exit;
    return exit;
}
