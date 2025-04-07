#ifndef SWSYS_ENV_UEFI_DISPCTRL_H
#define SWSYS_ENV_UEFI_DISPCTRL_H

#include "../swsys_env.h"
#include <stdbool.h>

bool swsys_init_dispctrl_uefi();
bool swsys_dispctrl_off_uefi();
bool swsys_dispctrl_on_uefi();
#endif // SWSYS_ENV_UEFI_DISPCTRL_H
