#ifndef EEPROM_AUDIT_H
#define EEPROM_AUDIT_H

#include <Arduino.h>
#include <EEPROM.h>

struct AuditStats {
    uint16_t total;
    uint16_t healthy;
    uint16_t dead;
};

bool inspectCellHardware(uint16_t addr);
AuditStats runFullActiveAudit();

#endif
