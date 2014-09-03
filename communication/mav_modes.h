/*******************************************************************************
 * Copyright (c) 2009-2014, MAV'RIC Development Team
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*******************************************************************************
 * \file mav_mode.h
 * 
 * \author MAV'RIC Team
 * \author Julien Lecoeur
 *   
 * \brief Place where the mav modes and flags are defined
 *
 ******************************************************************************/


#ifndef MAV_MODE_H
#define MAV_MODE_H

#include <stdint.h>
#include <stdbool.h>


typedef enum
{
	ARMED_OFF = 0,
	ARMED_ON  = 1,
} mode_flag_armed_t;


typedef enum
{
	MANUAL_OFF = 0,
	MANUAL_ON  = 1,
} mode_flag_manual_t;


typedef enum
{
	HIL_OFF = 0,			
	HIL_ON  = 1,
} mode_flag_hil_t;


typedef enum
{
	STABILISE_OFF = 0,
	STABILISE_ON  = 1,
} mode_flag_stabilise_t;


typedef enum
{
	GUIDED_OFF = 0,
	GUIDED_ON  = 1,
} mode_flag_guided_t;


typedef enum
{
	AUTO_OFF = 0,
	AUTO_ON  = 1,
} mode_flag_auto_t;


typedef enum
{
	TEST_OFF = 0,
	TEST_ON  = 1,
} mode_flag_test_t;


typedef enum
{
	CUSTOM_OFF = 0,
	CUSTOM_ON  = 1,
} mode_flag_custom_t;


typedef struct 
{
    mode_flag_armed_t 	  ARMED        : 1;
    mode_flag_manual_t 	  MANUAL       : 1;
    mode_flag_hil_t 	  HIL          : 1;
    mode_flag_stabilise_t STABILISE    : 1;
    mode_flag_guided_t 	  GUIDED       : 1;
    mode_flag_auto_t 	  AUTO         : 1;
    mode_flag_test_t 	  TEST         : 1;
    mode_flag_custom_t 	  CUSTOM       : 1;
} mav_mode_bitfield_t;


typedef union
{
	uint8_t byte;
	// unamed bitfield structure, use to access directly the flags
	struct 
	{
	    mode_flag_armed_t 	  ARMED        : 1;
	    mode_flag_manual_t 	  MANUAL       : 1;
	    mode_flag_hil_t 	  HIL          : 1;
	    mode_flag_stabilise_t STABILISE    : 1;
	    mode_flag_guided_t 	  GUIDED       : 1;
	    mode_flag_auto_t 	  AUTO         : 1;
	    mode_flag_test_t 	  TEST         : 1;
	    mode_flag_custom_t 	  CUSTOM       : 1;
	};
	// identical bitfield, but named (useful for initialisation)
	struct 
	{
	    mode_flag_armed_t 	  ARMED        : 1;
	    mode_flag_manual_t 	  MANUAL       : 1;
	    mode_flag_hil_t 	  HIL          : 1;
	    mode_flag_stabilise_t STABILISE    : 1;
	    mode_flag_guided_t 	  GUIDED       : 1;
	    mode_flag_auto_t 	  AUTO         : 1;
	    mode_flag_test_t 	  TEST         : 1;
	    mode_flag_custom_t 	  CUSTOM       : 1;
	} flags;
} mav_mode_t;


typedef enum
{
	MODE_FLAG_CUSTOM    = 0,
	MODE_FLAG_TEST      = 1,
	MODE_FLAG_AUTO      = 2,
	MODE_FLAG_GUIDED    = 3,
	MODE_FLAG_STABILISE = 4,
	MODE_FLAG_HIL       = 5,
	MODE_FLAG_MANUAL    = 6,
	MODE_FLAG_ARMED     = 7,
} mode_flags_t;


typedef enum MAV_MODE_FLAG mav_flag_mask_t;

typedef enum MAV_STATE mav_state_t;

typedef enum
{
	MAV_MODE_PRE = 0,
	MAV_MODE_SAFE = 64,
	MAV_MODE_ATTITUDE_CONTROL = 192,
	MAV_MODE_VELOCITY_CONTROL = 208,
	MAV_MODE_POSITION_HOLD = 216,
	MAV_MODE_GPS_NAVIGATION = 156
} mav_mode_predefined_t;


static inline bool mav_modes_is_armed(const mav_mode_t mav_mode)
{
	if ( mav_mode.ARMED == ARMED_ON )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_is_hil(const mav_mode_t mav_mode)
{
	if ( mav_mode.HIL == HIL_ON )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_is_manual(const mav_mode_t mav_mode)
{
	if ( mav_mode.MANUAL == MANUAL_ON )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_is_stabilise(const mav_mode_t mav_mode)
{
	if ( mav_mode.STABILISE == STABILISE_ON )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_is_guided(const mav_mode_t mav_mode)
{
	if ( mav_mode.GUIDED == GUIDED_ON )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_is_auto(const mav_mode_t mav_mode)
{
	if ( mav_mode.AUTO == AUTO_ON )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_is_test(const mav_mode_t mav_mode)
{
	if ( mav_mode.TEST == TEST_ON )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_is_custom(const mav_mode_t mav_mode)
{
	if ( mav_mode.CUSTOM == CUSTOM_ON )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_are_equal(const mav_mode_t mode1, const mav_mode_t mode2)
{
	if ( mode1.byte == mode2.byte )
	{
		return true;
	}
	else
	{
		return false;
	}
}


static inline bool mav_modes_are_equal_wo_hil(const mav_mode_t mode1, const mav_mode_t mode2)
{
	mav_mode_t mode1_ = mode1;
	mav_mode_t mode2_ = mode2;
	
	mode1_.HIL = HIL_OFF;
	mode2_.HIL = HIL_OFF;
	
	return mav_modes_are_equal(mode1_, mode2_);
}


static inline bool mav_modes_are_equal_wo_armed(const mav_mode_t mode1, const mav_mode_t mode2)
{
	mav_mode_t mode1_ = mode1;
	mav_mode_t mode2_ = mode2;
	
	mode1_.ARMED = ARMED_OFF;
	mode2_.ARMED = ARMED_OFF;
	
	return mav_modes_are_equal(mode1_, mode2_);
}


static inline bool mav_modes_are_equal_wo_hil_and_armed(const mav_mode_t mode1, const mav_mode_t mode2)
{
	mav_mode_t mode1_ = mode1;
	mav_mode_t mode2_ = mode2;
	
	mode1_.HIL = HIL_OFF;
	mode2_.HIL = HIL_OFF;
	mode1_.ARMED = ARMED_OFF;
	mode2_.ARMED = ARMED_OFF;
	
	return mav_modes_are_equal(mode1_, mode2_);
}


static inline mav_mode_t mav_modes_get_from_flags(const mode_flag_armed_t armed, const mode_flag_hil_t hil, const mode_flag_manual_t manual, const mode_flag_stabilise_t stabilise, const mode_flag_guided_t guided, const mode_flag_auto_t autoo, const mode_flag_test_t test, const mode_flag_custom_t custom)
{
	mav_mode_t mode;

	mode.ARMED     = armed;
	mode.HIL       = hil;
	mode.MANUAL    = manual;
	mode.STABILISE = stabilise;
	mode.GUIDED    = guided;
	mode.AUTO      = autoo;
	mode.TEST      = test;
	mode.CUSTOM    = custom;

	return mode;
}

#endif