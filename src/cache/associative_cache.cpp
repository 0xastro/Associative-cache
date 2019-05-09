#include <cstring>
#include <iostream>

#include "associative_cache.hpp"


cache_message * AssociativeCache::craft_ass_cache_msg(bool op, mem_unit tgt, mem_unit vcm)
{
	cache_message *msg = new cache_message();
	
	msg->op_type = op;
	msg->target = tgt;
	msg->victim = vcm;

	return msg;
}


message * AssociativeCache::craft_msg(char *dest, void *content)
{
	message *msg = new message();
	
	msg->valid = 1;
	msg->timestamp = getTime();
	strncpy(msg->source, getName().c_str(), 10);
	strncpy(msg->dest, dest, 10);
	msg->magic_struct = content;
	
	return msg;
}


AssociativeCache::AssociativeCache(System& sys, string name, string prev_name, string next_name,
			unsigned n_ways, unsigned cache_size, unsigned block_size, unsigned mem_unit_size,
			bool write_policy, bool allocate_policy, int priority)
	: module(name, priority),
	  prev_name(prev_name),
	  next_name(next_name),
	  n_ways(n_ways),
	  cache_size(cache_size),
	  block_size(block_size),
	  mem_unit_size(mem_unit_size),
	  write_policy(write_policy),
	  allocate_policy(allocate_policy)
{
	std::cout << getName() << ": building associative cache" << std::endl;	// DEBUG
	for (unsigned i = 0; i < n_ways; ++i) {
		DirectCache *dcache = new DirectCache(name + "_" + std::to_string(i));
		ways.push_back(dcache);
		sys.addModule(dcache);
	}
}


void AssociativeCache::onNotify(message* m)
{
	std::cout << getName() << ": was notified" << std::endl;	// DEBUG
	
	// Check if this is the recipient of the message (if not, exit)
	if (getName() != m->dest)
		return;

	
	// Check the message type (LOAD, STORE or RESPONSE)
	// If LOAD or STORE, forward the request to the inner direct caches 
	// If RESPONSE, check if HIT/MISS/ACK and handle it accordingly
	// Send a message to previous/next level
}
