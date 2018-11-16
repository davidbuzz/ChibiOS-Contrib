# List of all the MSP430X platform files.
PLATFORMSRC = ${CHIBIOS_CONTRIB}/os/hal/ports/ESP32/hal_lld.c \
              ${CHIBIOS_CONTRIB}/os/hal/ports/ESP32/hal_st_lld.c \
              ${CHIBIOS_CONTRIB}/os/hal/ports/ESP32/hal_serial_lld.c \
              ${CHIBIOS_CONTRIB}/os/hal/ports/ESP32/hal_pal_lld.c \
              ${CHIBIOS_CONTRIB}/os/hal/ports/ESP32/hal_dma_lld.c \
              ${CHIBIOS_CONTRIB}/os/hal/ports/ESP32/hal_spi_lld.c \
              ${CHIBIOS_CONTRIB}/os/hal/ports/ESP32/hal_adc_lld.c

# Required include directories
PLATFORMINC = ${CHIBIOS_CONTRIB}/os/hal/ports/ESP32
