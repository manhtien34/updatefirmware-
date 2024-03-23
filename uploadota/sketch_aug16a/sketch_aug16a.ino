#include "dowloadfile.h"
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println(file_hex);
}
typedef enum{
OTA_IDLE_STATE,
OTA_START_STATE,
OTA_HEADER_STATE,
OTA_DATA_STATE,
OTA_END_STATE
}OTA_State;

void min_application_handler(uint8_t min_id, uint8_t const *min_payload, uint8_t len_payload, uint8_t port)(
switch()

)
void loop() {
  // put your main code here, to run repeatedly:

}
