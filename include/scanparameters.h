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

    ShotParameters()
    {
        Kv = 80;
        Ma = 20;
        Fss = 0;
        ShotTime = 1000;
        ScanTriggerMode = 0;
        ScanTriggerPosition = 0;
        IsRelativePosition = 0;
        XrayOnTimeout = 1000;
        Time2FirstView = 0;
        NumberOfViews = 0;
        IntegrationPulseSource = 0;
        IntegrationPulsePeriod = 9766;
        ECGStartDelay = 0;
        WithDoseModulation = 0;
        NumberOfFocalSpots = 0;
        CardiacPulmo = 0;
        ViewsPerRotation = 1024;
        ShotIntervalMSec = 0;
        ShotIntervalRPulse = 0;
    }

    std::string ToString()
    {
        std::ostringstream oss;
        oss << "\tKv = " << Kv << "\n";
        oss << "\tMa = " << Ma << "\n";
        oss << "\tFss = " << Fss << " (0:small 1:large)\n";
        oss << "\tShotTime = " << ShotTime << " msec\n";
        oss << "\tScanTriggerMode = " << ScanTriggerMode << " (0:time, 1:table, 2:angle, 3:ecg and 4:manual)\n";
        oss << "\tScanTriggerPosition = " << ScanTriggerPosition << " ticks\n";
        oss << "\tIsRelativePosition = " << IsRelativePosition << " (0:absolute, 1:relattive)\n";
        oss << "\tXrayOnTimeout = " << XrayOnTimeout << " msec\n";
        oss << "\tTime2FirstView = " << Time2FirstView << " msec\n";
        oss << "\tNumberOfViews = " << NumberOfViews << "\n";
        oss << "\tIntegrationPulseSource = " << IntegrationPulseSource << " (0:internal-mar, 1:external-gantry)\n";
        oss << "\tIntegrationPulsePeriod = " << IntegrationPulsePeriod << "\n";
        oss << "\tECGStartDelay = " << ECGStartDelay << "msec\n";
        oss << "\tWithDoseModulation = " << WithDoseModulation << "\n";
        oss << "\tNumberOfFocalSpots = " << NumberOfFocalSpots << "\n";
        oss << "\tCardiacPulmo = " << CardiacPulmo << " (0:none, 1:cardiac, 2:pulmo)\n";
        oss << "\tViewsPerRotation = " << ViewsPerRotation << "\n";
        oss << "\tShotIntervalMSec = " << ShotIntervalMSec << "\n";
        oss << "\tShotIntervalRPulse = " << ShotIntervalRPulse << "\n";

        return oss.str();
    }
};

struct PhaseParameters
{
    int PhaseEndCondition; // 0: NumberOfShots, 1: PhaseViewLimit, 2: PhaseTimeLimit
    int PhaseInterval;
    int NumberOfShots;
    ShotParameters Shot;
    int PhaseTimeLimit;
    int PhaseViewLimit;

    PhaseParameters()
    {
        PhaseEndCondition = 0;
        PhaseInterval = 0;
        NumberOfShots = 1;
        PhaseTimeLimit = 0;
        PhaseViewLimit = 0;
    }

    PhaseParameters(const PhaseParameters &phase_param)
    {
        *this = phase_param;
    }

    void operator=(const PhaseParameters &phase_param)
    {
        this->PhaseEndCondition = phase_param.PhaseEndCondition;
        this->PhaseInterval = phase_param.PhaseInterval;
        this->NumberOfShots = phase_param.NumberOfShots;
        this->Shot = phase_param.Shot;
        this->PhaseTimeLimit = phase_param.PhaseTimeLimit;
        this->PhaseViewLimit = phase_param.PhaseViewLimit;
    }

    std::string ToString()
    {
        std::ostringstream oss;

        oss << Shot.ToString();
        oss << "NumberOfShots = " << NumberOfShots << "\n";
        oss << "PhaseEndCondition = " << PhaseEndCondition << " (0:NumberOfShots, 1:PhaseViewLimit, 2:PhaseTimeLimit)\n";
        oss << "PhaseInterval = " << PhaseInterval << " msec\n";
        oss << "PhaseTimeLimit = " << PhaseTimeLimit << " msec\n";
        oss << "PhaseViewLimit = " << PhaseViewLimit << "\n";

        return oss.str();
    }
};

struct ScanParameters
{
    bool IsEmergencyScan;
    std::vector<PhaseParameters> m_phases;

    ScanParameters()
    {
        IsEmergencyScan = false;
    }

    void operator=(const ScanParameters &scan_param)
    {
        this->IsEmergencyScan = scan_param.IsEmergencyScan;
        this->m_phases = scan_param.m_phases;
    }

    std::string ToString()
    {
        std::ostringstream oss;

        oss << "<<< Scan Parameters " << (IsEmergencyScan ? "(Emergency)" : "") << ">>>\n";

        int phase_no = 0;
        for (auto &phase : m_phases)
        {
            oss << "[Phase-" << phase_no++ << "]\n";
            oss << phase.ToString();
        }
        oss << "========= End Scan Parameters ==========\n";

        return oss.str();
    }
};
#endif