#pragma once

#ifdef __cplusplus
extern "C" {

#include <sys/param.h>
#include <sys/systm.h>

uint32_t
calculate_crc32c(uint32_t crc32c,
    const unsigned char *buffer,
    unsigned int length);


#ifdef __cplusplus
}
#endif