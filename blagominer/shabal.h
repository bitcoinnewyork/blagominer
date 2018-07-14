#pragma once

#include "blagominer.h"
#include "sph_shabal.h"
#include "mshabal.h"
#include "mshabal256.h"


//gobal shabal contexts, just created once
extern sph_shabal_context global_y, local_y;
extern mshabal_context global_z;
extern mshabal256_context_fast global_x_fast;
extern mshabal256_context global_x;



//hashing routines
void procscoop_sph(const unsigned long long nonce, const unsigned long long n, char const *const data, const size_t acc, const std::string &file_name);
void procscoop_m_4(unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name);
void procscoop_m256_8(unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name);
//fast hashing routines by Johnny
void procscoop_m256_8_fast(unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name);

