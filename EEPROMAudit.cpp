#include "EEPROMAudit.h"

bool inspectCellHardware(uint16_t addr) {
    uint8_t backup = EEPROM.read(addr);

    EEPROM.write(addr, 0x55);
    if (EEPROM.read(addr) != 0x55) {
        EEPROM.update(addr, backup);
        return false;
    }

    EEPROM.write(addr, 0xAA);
    if (EEPROM.read(addr) != 0xAA) {
        EEPROM.update(addr, backup);
        return false;
    }

    EEPROM.update(addr, backup);
    return true;
}

AuditStats runFullActiveAudit() {
    uint16_t totalCells = EEPROM.length();
    uint16_t healthyCount = 0;
    uint16_t deadCount = 0;

    Serial.println(F("\n********************************************************"));
    Serial.print(F(" FULL ACTIVE EEPROM HARDWARE AUDIT ["));
    Serial.print(totalCells);
    Serial.println(F(" B]"));
    Serial.println(F("********************************************************"));
    Serial.println(F("SCANNING IN PROGRESS (Pattern test 0x55 / 0xAA)..."));

    for (uint16_t i = 0; i < totalCells; ++i) {
        bool status = inspectCellHardware(i);

        if (status) {
            healthyCount++;
        } else {
            deadCount++;
            Serial.print(F(" -> [PHYSICAL DAMAGE] Dec address: "));
            Serial.print(i);
            Serial.print(F(" | HEX: 0x"));
            if (i < 16) Serial.print(F("0"));
            Serial.println(i, HEX);
        }

        if (i % 64 == 0) {
            Serial.print(F("."));
        }
    }

    Serial.println(F("\n********************************************************"));
    
    AuditStats stats = {totalCells, healthyCount, deadCount};
    float healthPct = ((float)healthyCount / (float)totalCells) * 100.0f;

    Serial.println(F(" REPORT SUMMARY:"));
    Serial.print(F("  Total size:     ")); Serial.print(stats.total); Serial.println(F(" B"));
    Serial.print(F("  Healthy cells:  ")); Serial.print(stats.healthy); Serial.println(F(" B"));
    Serial.print(F("  Dead cells:     ")); Serial.print(stats.dead); Serial.println(F(" B"));
    Serial.print(F("  Health status:  ")); Serial.print(healthPct, 2); Serial.println(F(" %"));
    Serial.println(F("********************************************************\n"));

    return stats;
}
