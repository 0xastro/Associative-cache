#pragma once

#include <stdint.h>

#include "arch.hpp"
#include "system/structures.h"

# define OP_READ 		false
# define OP_WRITE 		true


typedef struct block {
	addr_t 		addr;
	uint16_t	size;
	word_t		*data;
} block;


typedef block 	mem_unit;


typedef struct cache_message {
	bool 		op_type;
	mem_unit 	target;
	mem_unit 	victim;
} ass_cache_msg;


typedef struct message message;