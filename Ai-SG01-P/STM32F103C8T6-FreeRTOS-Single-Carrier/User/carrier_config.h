#ifndef __CARRIER_CONFIG_H
#define __CARRIER_CONFIG_H

/* ---------------------------------------------------------------------
 * AI-SG-01 single-carrier (CARRIER) firmware build
 * ---------------------------------------------------------------------
 * CARRIER_AUTO_ON_BOOT = 1 : after power-up initialisation the firmware
 *                            enters the unmodulated single-carrier (CW)
 *                            transmit mode, i.e. exactly the state that
 *                            AT+ENTERCARRIER produces, and keeps it.
 * CARRIER_AUTO_ON_BOOT = 0 : original behaviour (power-up PingPong start
 *                            with the role taken from the role config).
 * ------------------------------------------------------------------- */
#ifndef CARRIER_AUTO_ON_BOOT
#define CARRIER_AUTO_ON_BOOT   1
#endif

#endif /* __CARRIER_CONFIG_H */
