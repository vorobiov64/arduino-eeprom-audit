# Arduino Active EEPROM Hardware Audit 

An active hardware diagnostic tool for checking the PHYSICAL HEALTH of EEPROM memory cells on AVR-based Arduino microcontrollers (Uno, Nano, Mega etc).

> ⚠️ **CRITICAL DISCLAIMER & WARNING!**
> 
> **THIS IS A DESTRUCTIVE/ACTIVE HARDWARE TEST.**
> * **Data Loss Risk:** While the script attempts to back up and restore each byte in RAM, **any power loss or reset during the audit will permanently corrupt the byte currently being tested**. Do NOT use this on production boards containing critical EEPROM data without backing it up first!
> * **Hardware Wear:** Running this test performs multiple write cycles per cell. **Do NOT run this continuously or in a loop!**
> * **AVR Only:** Designed specifically for AVR microcontrollers with real physical EEPROM. Do NOT run this on ESP32, ESP8266, STM32, or RP2040, as emulated EEPROM on Flash memory will wear out significantly faster.

---

## How It Works:

This utility inspects every single byte of the onboard EEPROM using a **bit-flipping pattern test**:

1. **Backup:** Reads the original byte value at address $N$ and holds it in SRAM.
2. **Pattern 1 (`0x55` / `0b01010101`):** Writes alternating bits to verify each cell bit can hold `0` and `1`.
3. **Pattern 2 (`0xAA` / `0b10101010`):** Inverts all bits to ensure no adjacent bits are shorted or stuck.
4. **Verification:** Reads back the cell state after each pattern write.
5. **Restore:** Writes the original `backup` byte back to the EEPROM address.

If any pattern readback fails to match the expected pattern, the address is marked as **PHYSICAL DAMAGE** and reported via Serial.

---

## How to Use

1. Clone or download this repository.
2. Open `arduino_eeprom_audit.ino` in the Arduino IDE/PlatformIO.
3. Open the **Serial Monitor** at **9600 baud**.
3. Upload the sketch and watch the live hardware report.

---

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.

PS. developed with assistance from Gemini
