#ifndef _SCANPARAMETERS_H
#define _SCANPARAMETERS_H

#include <sstream>
#include <vector>

struct ShotParameters
{
    int Kv;                  // 80, 100, 120, 135
    int Ma;                  // 0 .. 400
    int Fss;                 // 0:small 1:large
    int ShotTime;            // msec
    int ScanTriggerMode;     // 0:time, 1:table, 2:angle, 3:ecg and 4:manual
    int ScanTriggerPosition; // ticks
    bool IsRelativePosition; // 0:absolute, 1:relattive
    int XrayOnTimeout;       // msec
    int Time2FirstView;      // msec
    int NumberOfViews;
    int IntegrationPulseSource; // 0:internal(mar), 1:external(gantry)
    int IntegrationPulsePeriod; // 4882.81:120rpm, 5859.38:100rpm, 7812.50:75rpm, 9765.63:60rpm
    int ECGStartDelay;
    bool WithDoseModulation; // TBD: ima table
    int NumberOfFocalSpots;  // 0: no fs toggle, 1, 2 ...: fs toggle (TBD),
    int CardiacPulmo;        // 0:none, 1:cardiac, 2:pulmo
    int ViewsPerRotation;
    int ShotIntervalMSec;
    int ShotIntervalRPulse;

    ShotParameters();
    std::string ToString();
    void Serialize(std::vector<char> &data);
    std::vector<char>::const_iterator Deserialize(const std::vector<char> &data);
    std::vector<char>::const_iterator Deserialize(const std::vector<char> &data, std::vector<char>::const_iterator iter);
};

struct PhaseParameters
{
    int PhaseEndCondition; // 0: NumberOfShots, 1: PhaseViewLimit, 2: PhaseTimeLimit
    int PhaseInterval;
    int NumberOfShots;
    int PhaseTimeLimit;
    int PhaseViewLimit;
    ShotParameters Shot;

    PhaseParameters();
    PhaseParameters(const PhaseParameters &phase_param);
    void operator=(const PhaseParameters &phase_param);
    std::string ToString();
    void Serialize(std::vector<char> &data);
    std::vector<char>::const_iterator Deserialize(const std::vector<char> &data);
    std::vector<char>::const_iterator Deserialize(const std::vector<char> &data, std::vector<char>::const_iterator iter);
};

struct ScanParameters
{
    bool IsEmergencyScan;
    std::vector<PhaseParameters> m_phases;

    ScanParameters();
    void operator=(const ScanParameters &scan_param);
    std::string ToString();
    void Serialize(std::vector<char> &data);
    void Deserialize(const std::vector<char> &data);
};
#endif