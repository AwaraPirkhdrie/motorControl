
#ifndef TEMP_H_
#define TEMP_H_

#include <inttypes.h>

void regulator_init(void);
uint8_t getpotvalue(void);
uint16_t getrawvalue(void);

#endif /* TEMP_H_ */