/* includes */

#include "vxWorks.h"
#include <stdio.h>
#include "DspLoader.h"

void dsp_loader_start(void) 
{
    DspLoader_init();
    DspLoader_startCore();
    DspLoader_deinit();
}
