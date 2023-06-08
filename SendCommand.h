/*This file received from to flight software to be compatible.*/
#ifndef SEND_COMMAND_H
#define SEND_COMMAND_H

#include "ReceiveCommand.h"


enum class SendType : int
{
    Info = 0,
    Settings
};

struct DebugValues
{
    DebugValues() = default;
    float altitude{};
    float desired_altitude{};
    float p_gain_alt{};
    float P_alt{};
    float I_alt{};
    float D_alt{};
    int countOfLoop{};
};

struct SendStatusInformations
{
    SendStatusInformations() = default;
    int altitude{};
    int satelliteCount{};
    Command status{};
    float roll{};
    float pitch{};
    float yaw{};
    float latitude{};
    float longtitude{};
    DebugValues debug{};
};

struct SendSettingsInformation
{
    float rollAndPitchP;
    float rollAndPitchI;
    float rollAndPitchD;
    float altitudeP;
    float altitudeI;
    float altitudeD;
};

union SendInformation
{
    SendSettingsInformation settings;
    SendStatusInformations status;
};

struct SendInformations
{
    SendType sendType{};
    SendInformation data{};
};




#endif
