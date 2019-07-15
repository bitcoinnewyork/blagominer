#include "stdafx.h"
#include "shabal.h"

// context for 1-dimensional shabal (32bit)
sph_shabal_context global_32;
// context for 4-dimensional shabal (128bit)
mshabal_context global_128;
mshabal_context_fast global_128_fast;
// context for 8-dimensional shabal (256bit)
mshabal256_context global_256;
mshabal256_context_fast global_256_fast;
// context for 16-dimensional shabal (512bit)
mshabal512_context global_512;
mshabal512_context_fast global_512_fast;

//ALL CPUs
void procscoop_sph(std::shared_ptr<t_coin_info> coin, const unsigned long long nonce, const unsigned long long n, char const *const data, const size_t acc, const std::string &file_name) {
	char const *cache;
	char sig[32 + 128];
	cache = data;
	char res[32];
	memcpy_s(sig, sizeof(sig), coin->mining->currentSignature, sizeof(char) * 32);
	
	sph_shabal_context x;
	for (unsigned long long v = 0; v < n; v++)
	{
		memcpy_s(&sig[32], sizeof(sig) - 32, &cache[v * 64], sizeof(char) * 64);

		memcpy(&x, &global_32, sizeof(global_32)); // optimization: sph_shabal256_init(&x);
		sph_shabal256(&x, (const unsigned char*)sig, 64 + 32);
		sph_shabal256_close(&x, res);

		unsigned long long *wertung = (unsigned long long*)res;
		
		unsigned long long deadline = *wertung / coin->mining->currentBaseTarget;
		if (deadline <= coin->mining->bests[acc].targetDeadline)
		{
			if (*wertung < coin->mining->bests[acc].best)
			{
				Log(L"SPH-: found deadline=%llu scoop=%lu nonce=%llu base=%llu height=%llu for account: %llu file: %S", deadline, coin->mining->scoop, nonce + v, coin->mining->baseTarget, coin->mining->height, coin->mining->bests[acc].account_id, file_name.c_str());
				Log(L"SIG: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					coin->mining->currentSignature[ 0], coin->mining->currentSignature[ 1], coin->mining->currentSignature[ 2], coin->mining->currentSignature[ 3], coin->mining->currentSignature[ 4], coin->mining->currentSignature[ 5], coin->mining->currentSignature[ 6], coin->mining->currentSignature[ 7], coin->mining->currentSignature[ 8], coin->mining->currentSignature[ 9],
					coin->mining->currentSignature[10], coin->mining->currentSignature[11], coin->mining->currentSignature[12], coin->mining->currentSignature[13], coin->mining->currentSignature[14], coin->mining->currentSignature[15], coin->mining->currentSignature[16], coin->mining->currentSignature[17], coin->mining->currentSignature[18], coin->mining->currentSignature[19],
					coin->mining->currentSignature[20], coin->mining->currentSignature[21], coin->mining->currentSignature[22], coin->mining->currentSignature[23], coin->mining->currentSignature[24], coin->mining->currentSignature[25], coin->mining->currentSignature[26], coin->mining->currentSignature[27], coin->mining->currentSignature[28], coin->mining->currentSignature[29],
					coin->mining->currentSignature[30], coin->mining->currentSignature[31]);
				Log(L"SCP: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					cache[v * 64 +  0], cache[v * 64 +  1], cache[v * 64 +  2], cache[v * 64 +  3], cache[v * 64 +  4], cache[v * 64 +  5], cache[v * 64 +  6], cache[v * 64 +  7], cache[v * 64 +  8], cache[v * 64 +  9],
					cache[v * 64 + 10], cache[v * 64 + 11], cache[v * 64 + 12], cache[v * 64 + 13], cache[v * 64 + 14], cache[v * 64 + 15], cache[v * 64 + 16], cache[v * 64 + 17], cache[v * 64 + 18], cache[v * 64 + 19],
					cache[v * 64 + 20], cache[v * 64 + 21], cache[v * 64 + 22], cache[v * 64 + 23], cache[v * 64 + 24], cache[v * 64 + 25], cache[v * 64 + 26], cache[v * 64 + 27], cache[v * 64 + 28], cache[v * 64 + 29],
					cache[v * 64 + 30], cache[v * 64 + 31], cache[v * 64 + 32], cache[v * 64 + 33], cache[v * 64 + 34], cache[v * 64 + 35], cache[v * 64 + 36], cache[v * 64 + 37], cache[v * 64 + 38], cache[v * 64 + 39],
					cache[v * 64 + 40], cache[v * 64 + 41], cache[v * 64 + 42], cache[v * 64 + 43], cache[v * 64 + 44], cache[v * 64 + 45], cache[v * 64 + 46], cache[v * 64 + 47], cache[v * 64 + 48], cache[v * 64 + 49],
					cache[v * 64 + 50], cache[v * 64 + 51], cache[v * 64 + 52], cache[v * 64 + 53], cache[v * 64 + 54], cache[v * 64 + 55], cache[v * 64 + 56], cache[v * 64 + 57], cache[v * 64 + 58], cache[v * 64 + 59],
					cache[v * 64 + 60], cache[v * 64 + 61], cache[v * 64 + 62], cache[v * 64 + 63]);

				EnterCriticalSection(&coin->locks->bestsLock);
				coin->mining->bests[acc].best = *wertung;
				coin->mining->bests[acc].nonce = nonce + v;
				coin->mining->bests[acc].DL = deadline;
				LeaveCriticalSection(&coin->locks->bestsLock);
				EnterCriticalSection(&coin->locks->sharesLock);
				coin->mining->shares.push_back(std::make_shared<t_shares>(
					file_name, 
					coin->mining->bests[acc].account_id, 
					coin->mining->bests[acc].best,
					coin->mining->bests[acc].nonce,
					coin->mining->bests[acc].DL,
					coin->mining->currentHeight,
					coin->mining->currentBaseTarget));
				LeaveCriticalSection(&coin->locks->sharesLock);
				printToConsole(2, true, false, true, false, L"[%20llu|%-10s|Worker] DL found     : %s",
					coin->mining->bests[acc].account_id, coin->coinname.c_str(), toWStr(coin->mining->bests[acc].DL, 11).c_str());
			}
		}
	}
}

//SSE fast
void procscoop_sse_fast(std::shared_ptr<t_coin_info> coin, unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name) {
	char const *cache;
	char sig0[32];
	char end0[32];
	char res0[32];
	char res1[32];
	char res2[32];
	char res3[32];
	cache = data;
	unsigned long long v;

	memmove(sig0, coin->mining->currentSignature, 32);
	end0[0] = -128;
	memset(&end0[1], 0, 31);

	mshabal_context_fast z, z2;
	memcpy(&z2, &global_128_fast, sizeof(global_128_fast)); // local copy of global fast context

    //prepare shabal inputs
	union {
		mshabal_u32 words[64];
		__m128i data[16];
	} u1, u2;

	for (int j = 0; j < 64 / 2; j += 4 ) {
		size_t o = j ;
		u1.words[j + 0] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 1] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 2] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 3] = *(mshabal_u32 *)(sig0 + o);
		u2.words[j + 0 + 32] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 1 + 32] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 2 + 32] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 3 + 32] = *(mshabal_u32 *)(end0 + o);
	}

	for (v = 0; v<n; v += 4) {
		// initialise shaba^l
		memcpy(&z, &z2, sizeof(z2)); // optimization: mshabal256_init(&x, 256);

		// load and shuffle data 
		// NB: this can be further optimised by preshuffling plot files depending on SIMD length and use avx2 memcpy
		// did not find a away yet to completely avoid memcpys

		for (int j = 0; j < 64 / 2; j += 4) {
			size_t o = j;
			u1.words[j + 0 + 32] = *(mshabal_u32 *)(&cache[(v + 0) * 64] + o);
			u1.words[j + 1 + 32] = *(mshabal_u32 *)(&cache[(v + 1) * 64] + o);
			u1.words[j + 2 + 32] = *(mshabal_u32 *)(&cache[(v + 2) * 64] + o);
			u1.words[j + 3 + 32] = *(mshabal_u32 *)(&cache[(v + 3) * 64] + o);
			u2.words[j + 0] = *(mshabal_u32 *)(&cache[(v + 0) * 64 + 32] + o);
			u2.words[j + 1] = *(mshabal_u32 *)(&cache[(v + 1) * 64 + 32] + o);
			u2.words[j + 2] = *(mshabal_u32 *)(&cache[(v + 2) * 64 + 32] + o);
			u2.words[j + 3] = *(mshabal_u32 *)(&cache[(v + 3) * 64 + 32] + o);
		}

		simd128_mshabal_openclose_fast(&z, &u1, &u2, res0, res1, res2, res3, 0);

		unsigned long long *wertung = (unsigned long long*)res0;
		unsigned long long *wertung1 = (unsigned long long*)res1;
		unsigned long long *wertung2 = (unsigned long long*)res2;
		unsigned long long *wertung3 = (unsigned long long*)res3;
		unsigned posn = 0;
		if (*wertung1 < *wertung)
		{
			*wertung = *wertung1;
			posn = 1;
		}
		if (*wertung2 < *wertung)
		{
			*wertung = *wertung2;
			posn = 2;
		}
		if (*wertung3 < *wertung)
		{
			*wertung = *wertung3;
			posn = 3;
		}

		unsigned long long deadline = *wertung / coin->mining->currentBaseTarget;
		if (deadline <= coin->mining->bests[acc].targetDeadline)
		{
			if (*wertung < coin->mining->bests[acc].best)
			{
				Log(L"SSEF: found deadline=%llu scoop=%lu nonce=%llu base=%llu height=%llu for account: %llu file: %S", deadline, coin->mining->scoop, nonce + v + posn, coin->mining->baseTarget, coin->mining->height, coin->mining->bests[acc].account_id, file_name.c_str());
				Log(L"SIG: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					coin->mining->currentSignature[ 0], coin->mining->currentSignature[ 1], coin->mining->currentSignature[ 2], coin->mining->currentSignature[ 3], coin->mining->currentSignature[ 4], coin->mining->currentSignature[ 5], coin->mining->currentSignature[ 6], coin->mining->currentSignature[ 7], coin->mining->currentSignature[ 8], coin->mining->currentSignature[ 9],
					coin->mining->currentSignature[10], coin->mining->currentSignature[11], coin->mining->currentSignature[12], coin->mining->currentSignature[13], coin->mining->currentSignature[14], coin->mining->currentSignature[15], coin->mining->currentSignature[16], coin->mining->currentSignature[17], coin->mining->currentSignature[18], coin->mining->currentSignature[19],
					coin->mining->currentSignature[20], coin->mining->currentSignature[21], coin->mining->currentSignature[22], coin->mining->currentSignature[23], coin->mining->currentSignature[24], coin->mining->currentSignature[25], coin->mining->currentSignature[26], coin->mining->currentSignature[27], coin->mining->currentSignature[28], coin->mining->currentSignature[29],
					coin->mining->currentSignature[30], coin->mining->currentSignature[31]);
				Log(L"SCP: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					cache[(v + posn) * 64 +  0], cache[(v + posn) * 64 +  1], cache[(v + posn) * 64 +  2], cache[(v + posn) * 64 +  3], cache[(v + posn) * 64 +  4], cache[(v + posn) * 64 +  5], cache[(v + posn) * 64 +  6], cache[(v + posn) * 64 +  7], cache[(v + posn) * 64 +  8], cache[(v + posn) * 64 +  9],
					cache[(v + posn) * 64 + 10], cache[(v + posn) * 64 + 11], cache[(v + posn) * 64 + 12], cache[(v + posn) * 64 + 13], cache[(v + posn) * 64 + 14], cache[(v + posn) * 64 + 15], cache[(v + posn) * 64 + 16], cache[(v + posn) * 64 + 17], cache[(v + posn) * 64 + 18], cache[(v + posn) * 64 + 19],
					cache[(v + posn) * 64 + 20], cache[(v + posn) * 64 + 21], cache[(v + posn) * 64 + 22], cache[(v + posn) * 64 + 23], cache[(v + posn) * 64 + 24], cache[(v + posn) * 64 + 25], cache[(v + posn) * 64 + 26], cache[(v + posn) * 64 + 27], cache[(v + posn) * 64 + 28], cache[(v + posn) * 64 + 29],
					cache[(v + posn) * 64 + 30], cache[(v + posn) * 64 + 31], cache[(v + posn) * 64 + 32], cache[(v + posn) * 64 + 33], cache[(v + posn) * 64 + 34], cache[(v + posn) * 64 + 35], cache[(v + posn) * 64 + 36], cache[(v + posn) * 64 + 37], cache[(v + posn) * 64 + 38], cache[(v + posn) * 64 + 39],
					cache[(v + posn) * 64 + 40], cache[(v + posn) * 64 + 41], cache[(v + posn) * 64 + 42], cache[(v + posn) * 64 + 43], cache[(v + posn) * 64 + 44], cache[(v + posn) * 64 + 45], cache[(v + posn) * 64 + 46], cache[(v + posn) * 64 + 47], cache[(v + posn) * 64 + 48], cache[(v + posn) * 64 + 49],
					cache[(v + posn) * 64 + 50], cache[(v + posn) * 64 + 51], cache[(v + posn) * 64 + 52], cache[(v + posn) * 64 + 53], cache[(v + posn) * 64 + 54], cache[(v + posn) * 64 + 55], cache[(v + posn) * 64 + 56], cache[(v + posn) * 64 + 57], cache[(v + posn) * 64 + 58], cache[(v + posn) * 64 + 59],
					cache[(v + posn) * 64 + 60], cache[(v + posn) * 64 + 61], cache[(v + posn) * 64 + 62], cache[(v + posn) * 64 + 63]);

				EnterCriticalSection(&coin->locks->bestsLock);
				coin->mining->bests[acc].best = *wertung;
				coin->mining->bests[acc].nonce = nonce + v + posn;
				coin->mining->bests[acc].DL = deadline;
				LeaveCriticalSection(&coin->locks->bestsLock);
				EnterCriticalSection(&coin->locks->sharesLock);
				coin->mining->shares.push_back(std::make_shared<t_shares>(
					file_name,
					coin->mining->bests[acc].account_id,
					coin->mining->bests[acc].best,
					coin->mining->bests[acc].nonce,
					coin->mining->bests[acc].DL,
					coin->mining->currentHeight,
					coin->mining->currentBaseTarget));
				LeaveCriticalSection(&coin->locks->sharesLock);
				printToConsole(2, true, false, true, false, L"[%20llu|%-10s|Worker] DL found     : %s",
					coin->mining->bests[acc].account_id, coin->coinname.c_str(), toWStr(coin->mining->bests[acc].DL, 11).c_str());
			}
		}
	}
}

//AVX fast
void procscoop_avx_fast(std::shared_ptr<t_coin_info> coin, unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name) {
	char const *cache;
	char sig0[32];
	char end0[32];
	char res0[32];
	char res1[32];
	char res2[32];
	char res3[32];
	cache = data;
	unsigned long long v;

	memmove(sig0, coin->mining->currentSignature, 32);
	end0[0] = -128;
	memset(&end0[1], 0, 31);

	mshabal_context_fast z, z2;
	memcpy(&z2, &global_128_fast, sizeof(global_128_fast)); // local copy of global fast context

															//prepare shabal inputs
	union {
		mshabal_u32 words[64];
		__m128i data[16];
	} u1, u2;

	for (int j = 0; j < 64 / 2; j += 4) {
		size_t o = j;
		u1.words[j + 0] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 1] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 2] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 3] = *(mshabal_u32 *)(sig0 + o);
		u2.words[j + 0 + 32] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 1 + 32] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 2 + 32] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 3 + 32] = *(mshabal_u32 *)(end0 + o);
	}

	for (v = 0; v<n; v += 4) {
		// initialise shaba^l
		memcpy(&z, &z2, sizeof(z2)); // optimization: mshabal256_init(&x, 256);

									 // load and shuffle data 
									 // NB: this can be further optimised by preshuffling plot files depending on SIMD length and use avx2 memcpy
									 // did not find a away yet to completely avoid memcpys

		for (int j = 0; j < 64 / 2; j += 4) {
			size_t o = j;
			u1.words[j + 0 + 32] = *(mshabal_u32 *)(&cache[(v + 0) * 64] + o);
			u1.words[j + 1 + 32] = *(mshabal_u32 *)(&cache[(v + 1) * 64] + o);
			u1.words[j + 2 + 32] = *(mshabal_u32 *)(&cache[(v + 2) * 64] + o);
			u1.words[j + 3 + 32] = *(mshabal_u32 *)(&cache[(v + 3) * 64] + o);
			u2.words[j + 0] = *(mshabal_u32 *)(&cache[(v + 0) * 64 + 32] + o);
			u2.words[j + 1] = *(mshabal_u32 *)(&cache[(v + 1) * 64 + 32] + o);
			u2.words[j + 2] = *(mshabal_u32 *)(&cache[(v + 2) * 64 + 32] + o);
			u2.words[j + 3] = *(mshabal_u32 *)(&cache[(v + 3) * 64 + 32] + o);
		}

		simd128_mshabal_openclose_fast(&z, &u1, &u2, res0, res1, res2, res3, 0);

		unsigned long long *wertung = (unsigned long long*)res0;
		unsigned long long *wertung1 = (unsigned long long*)res1;
		unsigned long long *wertung2 = (unsigned long long*)res2;
		unsigned long long *wertung3 = (unsigned long long*)res3;
		unsigned posn = 0;
		if (*wertung1 < *wertung)
		{
			*wertung = *wertung1;
			posn = 1;
		}
		if (*wertung2 < *wertung)
		{
			*wertung = *wertung2;
			posn = 2;
		}
		if (*wertung3 < *wertung)
		{
			*wertung = *wertung3;
			posn = 3;
		}

		unsigned long long deadline = *wertung / coin->mining->currentBaseTarget;
		if (deadline <= coin->mining->bests[acc].targetDeadline)
		{
			if (*wertung < coin->mining->bests[acc].best)
			{
				Log(L"AVX0: found deadline=%llu scoop=%lu nonce=%llu base=%llu height=%llu for account: %llu file: %S", deadline, coin->mining->scoop, nonce + v + posn, coin->mining->baseTarget, coin->mining->height, coin->mining->bests[acc].account_id, file_name.c_str());
				Log(L"SIG: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					coin->mining->currentSignature[ 0], coin->mining->currentSignature[ 1], coin->mining->currentSignature[ 2], coin->mining->currentSignature[ 3], coin->mining->currentSignature[ 4], coin->mining->currentSignature[ 5], coin->mining->currentSignature[ 6], coin->mining->currentSignature[ 7], coin->mining->currentSignature[ 8], coin->mining->currentSignature[ 9],
					coin->mining->currentSignature[10], coin->mining->currentSignature[11], coin->mining->currentSignature[12], coin->mining->currentSignature[13], coin->mining->currentSignature[14], coin->mining->currentSignature[15], coin->mining->currentSignature[16], coin->mining->currentSignature[17], coin->mining->currentSignature[18], coin->mining->currentSignature[19],
					coin->mining->currentSignature[20], coin->mining->currentSignature[21], coin->mining->currentSignature[22], coin->mining->currentSignature[23], coin->mining->currentSignature[24], coin->mining->currentSignature[25], coin->mining->currentSignature[26], coin->mining->currentSignature[27], coin->mining->currentSignature[28], coin->mining->currentSignature[29],
					coin->mining->currentSignature[30], coin->mining->currentSignature[31]);
				Log(L"SCP: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					cache[(v + posn) * 64 +  0], cache[(v + posn) * 64 +  1], cache[(v + posn) * 64 +  2], cache[(v + posn) * 64 +  3], cache[(v + posn) * 64 +  4], cache[(v + posn) * 64 +  5], cache[(v + posn) * 64 +  6], cache[(v + posn) * 64 +  7], cache[(v + posn) * 64 +  8], cache[(v + posn) * 64 +  9],
					cache[(v + posn) * 64 + 10], cache[(v + posn) * 64 + 11], cache[(v + posn) * 64 + 12], cache[(v + posn) * 64 + 13], cache[(v + posn) * 64 + 14], cache[(v + posn) * 64 + 15], cache[(v + posn) * 64 + 16], cache[(v + posn) * 64 + 17], cache[(v + posn) * 64 + 18], cache[(v + posn) * 64 + 19],
					cache[(v + posn) * 64 + 20], cache[(v + posn) * 64 + 21], cache[(v + posn) * 64 + 22], cache[(v + posn) * 64 + 23], cache[(v + posn) * 64 + 24], cache[(v + posn) * 64 + 25], cache[(v + posn) * 64 + 26], cache[(v + posn) * 64 + 27], cache[(v + posn) * 64 + 28], cache[(v + posn) * 64 + 29],
					cache[(v + posn) * 64 + 30], cache[(v + posn) * 64 + 31], cache[(v + posn) * 64 + 32], cache[(v + posn) * 64 + 33], cache[(v + posn) * 64 + 34], cache[(v + posn) * 64 + 35], cache[(v + posn) * 64 + 36], cache[(v + posn) * 64 + 37], cache[(v + posn) * 64 + 38], cache[(v + posn) * 64 + 39],
					cache[(v + posn) * 64 + 40], cache[(v + posn) * 64 + 41], cache[(v + posn) * 64 + 42], cache[(v + posn) * 64 + 43], cache[(v + posn) * 64 + 44], cache[(v + posn) * 64 + 45], cache[(v + posn) * 64 + 46], cache[(v + posn) * 64 + 47], cache[(v + posn) * 64 + 48], cache[(v + posn) * 64 + 49],
					cache[(v + posn) * 64 + 50], cache[(v + posn) * 64 + 51], cache[(v + posn) * 64 + 52], cache[(v + posn) * 64 + 53], cache[(v + posn) * 64 + 54], cache[(v + posn) * 64 + 55], cache[(v + posn) * 64 + 56], cache[(v + posn) * 64 + 57], cache[(v + posn) * 64 + 58], cache[(v + posn) * 64 + 59],
					cache[(v + posn) * 64 + 60], cache[(v + posn) * 64 + 61], cache[(v + posn) * 64 + 62], cache[(v + posn) * 64 + 63]);

				EnterCriticalSection(&coin->locks->bestsLock);
				coin->mining->bests[acc].best = *wertung;
				coin->mining->bests[acc].nonce = nonce + v + posn;
				coin->mining->bests[acc].DL = deadline;
				LeaveCriticalSection(&coin->locks->bestsLock);
				EnterCriticalSection(&coin->locks->sharesLock);
				coin->mining->shares.push_back(std::make_shared<t_shares>(
					file_name,
					coin->mining->bests[acc].account_id,
					coin->mining->bests[acc].best, 
					coin->mining->bests[acc].nonce,
					coin->mining->bests[acc].DL,
					coin->mining->currentHeight,
					coin->mining->currentBaseTarget));
				LeaveCriticalSection(&coin->locks->sharesLock);
				printToConsole(2, true, false, true, false, L"[%20llu|%-10s|Worker] DL found     : %s",
					coin->mining->bests[acc].account_id, coin->coinname.c_str(), toWStr(coin->mining->bests[acc].DL, 11).c_str());
			}
		}
	}
}

//AVX2 fast
void procscoop_avx2_fast(std::shared_ptr<t_coin_info> coin, unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name) {
	char const *cache;
	char sig0[32];
	char end0[32];
	char res0[32];
	char res1[32];
	char res2[32];
	char res3[32];
	char res4[32];
	char res5[32];
	char res6[32];
	char res7[32];
	cache = data;
	unsigned long long v;

	memmove(sig0, coin->mining->currentSignature, 32);
	end0[0] = -128;
	memset(&end0[1], 0, 31);

	mshabal256_context_fast x;
	mshabal256_context_fast x2;
	memcpy(&x2, &global_256_fast, sizeof(global_256_fast)); // local copy of global fast contex

															//prepare shabal inputs
	union {
		mshabal_u32 words[64 * MSHABAL256_FACTOR];
		__m256i data[16];
	} u1, u2;

	for (int j = 0; j < 64 * MSHABAL256_FACTOR / 2; j += 4 * MSHABAL256_FACTOR) {
		size_t o = j / MSHABAL256_FACTOR;
		u1.words[j + 0] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 1] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 2] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 3] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 4] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 5] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 6] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 7] = *(mshabal_u32 *)(sig0 + o);
		u2.words[j + 0 + 64] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 1 + 64] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 2 + 64] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 3 + 64] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 4 + 64] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 5 + 64] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 6 + 64] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 7 + 64] = *(mshabal_u32 *)(end0 + o);
	}

	for (v = 0; v<n; v += 8) {
		//Inititialise Shabal
		memcpy(&x, &x2, sizeof(x2)); // optimization: mshabal256_init(&x, 256);

									 //Load and shuffle data 
									 //NB: this can be further optimised by preshuffling plot files depending on SIMD length and use avx2 memcpy
									 //Did not find a away yet to completely avoid memcpys

		for (int j = 0; j < 64 * MSHABAL256_FACTOR / 2; j += 4 * MSHABAL256_FACTOR) {
			size_t o = j / MSHABAL256_FACTOR;
			u1.words[j + 0 + 64] = *(mshabal_u32 *)(&cache[(v + 0) * 64] + o);
			u1.words[j + 1 + 64] = *(mshabal_u32 *)(&cache[(v + 1) * 64] + o);
			u1.words[j + 2 + 64] = *(mshabal_u32 *)(&cache[(v + 2) * 64] + o);
			u1.words[j + 3 + 64] = *(mshabal_u32 *)(&cache[(v + 3) * 64] + o);
			u1.words[j + 4 + 64] = *(mshabal_u32 *)(&cache[(v + 4) * 64] + o);
			u1.words[j + 5 + 64] = *(mshabal_u32 *)(&cache[(v + 5) * 64] + o);
			u1.words[j + 6 + 64] = *(mshabal_u32 *)(&cache[(v + 6) * 64] + o);
			u1.words[j + 7 + 64] = *(mshabal_u32 *)(&cache[(v + 7) * 64] + o);
			u2.words[j + 0] = *(mshabal_u32 *)(&cache[(v + 0) * 64 + 32] + o);
			u2.words[j + 1] = *(mshabal_u32 *)(&cache[(v + 1) * 64 + 32] + o);
			u2.words[j + 2] = *(mshabal_u32 *)(&cache[(v + 2) * 64 + 32] + o);
			u2.words[j + 3] = *(mshabal_u32 *)(&cache[(v + 3) * 64 + 32] + o);
			u2.words[j + 4] = *(mshabal_u32 *)(&cache[(v + 4) * 64 + 32] + o);
			u2.words[j + 5] = *(mshabal_u32 *)(&cache[(v + 5) * 64 + 32] + o);
			u2.words[j + 6] = *(mshabal_u32 *)(&cache[(v + 6) * 64 + 32] + o);
			u2.words[j + 7] = *(mshabal_u32 *)(&cache[(v + 7) * 64 + 32] + o);
		}

		simd256_mshabal_openclose_fast(&x, &u1, &u2, res0, res1, res2, res3, res4, res5, res6, res7, 0);

		unsigned long long *wertung = (unsigned long long*)res0;
		unsigned long long *wertung1 = (unsigned long long*)res1;
		unsigned long long *wertung2 = (unsigned long long*)res2;
		unsigned long long *wertung3 = (unsigned long long*)res3;
		unsigned long long *wertung4 = (unsigned long long*)res4;
		unsigned long long *wertung5 = (unsigned long long*)res5;
		unsigned long long *wertung6 = (unsigned long long*)res6;
		unsigned long long *wertung7 = (unsigned long long*)res7;
		unsigned posn = 0;
		if (*wertung1 < *wertung)
		{
			*wertung = *wertung1;
			posn = 1;
		}
		if (*wertung2 < *wertung)
		{
			*wertung = *wertung2;
			posn = 2;
		}
		if (*wertung3 < *wertung)
		{
			*wertung = *wertung3;
			posn = 3;
		}
		if (*wertung4 < *wertung)
		{
			*wertung = *wertung4;
			posn = 4;
		}
		if (*wertung5 < *wertung)
		{
			*wertung = *wertung5;
			posn = 5;
		}
		if (*wertung6 < *wertung)
		{
			*wertung = *wertung6;
			posn = 6;
		}
		if (*wertung7 < *wertung)
		{
			*wertung = *wertung7;
			posn = 7;
		}

		unsigned long long deadline = *wertung / coin->mining->currentBaseTarget;
		if (deadline <= coin->mining->bests[acc].targetDeadline)
		{
			if (*wertung < coin->mining->bests[acc].best)
			{
				Log(L"AVX2: found deadline=%llu scoop=%lu nonce=%llu base=%llu height=%llu for account: %llu file: %S", deadline, coin->mining->scoop, nonce + v + posn, coin->mining->baseTarget, coin->mining->height, coin->mining->bests[acc].account_id, file_name.c_str());
				Log(L"SIG: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					coin->mining->currentSignature[ 0], coin->mining->currentSignature[ 1], coin->mining->currentSignature[ 2], coin->mining->currentSignature[ 3], coin->mining->currentSignature[ 4], coin->mining->currentSignature[ 5], coin->mining->currentSignature[ 6], coin->mining->currentSignature[ 7], coin->mining->currentSignature[ 8], coin->mining->currentSignature[ 9],
					coin->mining->currentSignature[10], coin->mining->currentSignature[11], coin->mining->currentSignature[12], coin->mining->currentSignature[13], coin->mining->currentSignature[14], coin->mining->currentSignature[15], coin->mining->currentSignature[16], coin->mining->currentSignature[17], coin->mining->currentSignature[18], coin->mining->currentSignature[19],
					coin->mining->currentSignature[20], coin->mining->currentSignature[21], coin->mining->currentSignature[22], coin->mining->currentSignature[23], coin->mining->currentSignature[24], coin->mining->currentSignature[25], coin->mining->currentSignature[26], coin->mining->currentSignature[27], coin->mining->currentSignature[28], coin->mining->currentSignature[29],
					coin->mining->currentSignature[30], coin->mining->currentSignature[31]);
				Log(L"SCP: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					cache[(v + posn) * 64 +  0], cache[(v + posn) * 64 +  1], cache[(v + posn) * 64 +  2], cache[(v + posn) * 64 +  3], cache[(v + posn) * 64 +  4], cache[(v + posn) * 64 +  5], cache[(v + posn) * 64 +  6], cache[(v + posn) * 64 +  7], cache[(v + posn) * 64 +  8], cache[(v + posn) * 64 +  9],
					cache[(v + posn) * 64 + 10], cache[(v + posn) * 64 + 11], cache[(v + posn) * 64 + 12], cache[(v + posn) * 64 + 13], cache[(v + posn) * 64 + 14], cache[(v + posn) * 64 + 15], cache[(v + posn) * 64 + 16], cache[(v + posn) * 64 + 17], cache[(v + posn) * 64 + 18], cache[(v + posn) * 64 + 19],
					cache[(v + posn) * 64 + 20], cache[(v + posn) * 64 + 21], cache[(v + posn) * 64 + 22], cache[(v + posn) * 64 + 23], cache[(v + posn) * 64 + 24], cache[(v + posn) * 64 + 25], cache[(v + posn) * 64 + 26], cache[(v + posn) * 64 + 27], cache[(v + posn) * 64 + 28], cache[(v + posn) * 64 + 29],
					cache[(v + posn) * 64 + 30], cache[(v + posn) * 64 + 31], cache[(v + posn) * 64 + 32], cache[(v + posn) * 64 + 33], cache[(v + posn) * 64 + 34], cache[(v + posn) * 64 + 35], cache[(v + posn) * 64 + 36], cache[(v + posn) * 64 + 37], cache[(v + posn) * 64 + 38], cache[(v + posn) * 64 + 39],
					cache[(v + posn) * 64 + 40], cache[(v + posn) * 64 + 41], cache[(v + posn) * 64 + 42], cache[(v + posn) * 64 + 43], cache[(v + posn) * 64 + 44], cache[(v + posn) * 64 + 45], cache[(v + posn) * 64 + 46], cache[(v + posn) * 64 + 47], cache[(v + posn) * 64 + 48], cache[(v + posn) * 64 + 49],
					cache[(v + posn) * 64 + 50], cache[(v + posn) * 64 + 51], cache[(v + posn) * 64 + 52], cache[(v + posn) * 64 + 53], cache[(v + posn) * 64 + 54], cache[(v + posn) * 64 + 55], cache[(v + posn) * 64 + 56], cache[(v + posn) * 64 + 57], cache[(v + posn) * 64 + 58], cache[(v + posn) * 64 + 59],
					cache[(v + posn) * 64 + 60], cache[(v + posn) * 64 + 61], cache[(v + posn) * 64 + 62], cache[(v + posn) * 64 + 63]);

				EnterCriticalSection(&coin->locks->bestsLock);
				coin->mining->bests[acc].best = *wertung;
				coin->mining->bests[acc].nonce = nonce + v + posn;
				coin->mining->bests[acc].DL = deadline;
				LeaveCriticalSection(&coin->locks->bestsLock);
				EnterCriticalSection(&coin->locks->sharesLock);
				coin->mining->shares.push_back(std::make_shared<t_shares>(
					file_name,
					coin->mining->bests[acc].account_id,
					coin->mining->bests[acc].best,
					coin->mining->bests[acc].nonce,
					coin->mining->bests[acc].DL,
					coin->mining->currentHeight,
					coin->mining->currentBaseTarget));
				LeaveCriticalSection(&coin->locks->sharesLock);
				printToConsole(2, true, false, true, false, L"[%20llu|%-10s|Worker] DL found     : %s",
					coin->mining->bests[acc].account_id, coin->coinname.c_str(), toWStr(coin->mining->bests[acc].DL, 11).c_str());
			}
		}
	}
}

//AVX512 fast
void procscoop_avx512_fast(std::shared_ptr<t_coin_info> coin, unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name) {
	char const *cache;
	char sig0[32];
	char end0[32];
	char res0[32];
	char res1[32];
	char res2[32];
	char res3[32];
	char res4[32];
	char res5[32];
	char res6[32];
	char res7[32];
	char res8[32];
	char res9[32];
	char res10[32];
	char res11[32];
	char res12[32];
	char res13[32];
	char res14[32];
	char res15[32];
	cache = data;
	unsigned long long v;

	memmove(sig0, coin->mining->currentSignature, 32);
	end0[0] = -128;
	memset(&end0[1], 0, 31);

	mshabal512_context_fast x;
	mshabal512_context_fast x2;
	memcpy(&x2, &global_512_fast, sizeof(global_512_fast)); // local copy of global fast contex

															//prepare shabal inputs
	union {
		mshabal_u32 words[64 * MSHABAL512_FACTOR];
		__m512i data[16];
	} u1, u2;

	for (int j = 0; j < 64 * MSHABAL512_FACTOR / 2; j += 4 * MSHABAL512_FACTOR) {
		size_t o = j / MSHABAL512_FACTOR;
		u1.words[j + 0] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 1] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 2] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 3] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 4] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 5] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 6] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 7] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 8] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 9] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 10] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 11] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 12] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 13] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 14] = *(mshabal_u32 *)(sig0 + o);
		u1.words[j + 15] = *(mshabal_u32 *)(sig0 + o);
		u2.words[j + 0 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 1 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 2 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 3 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 4 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 5 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 6 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 7 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 8 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 9 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 10 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 11 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 12 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 13 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 14 + 128] = *(mshabal_u32 *)(end0 + o);
		u2.words[j + 15 + 128] = *(mshabal_u32 *)(end0 + o);
	}

	for (v = 0; v<n; v += 16) {
		//Inititialise Shabal
		memcpy(&x, &x2, sizeof(x2)); // optimization: mshabal512_init(&x, 256);

									 //Load and shuffle data 
									 //NB: this can be further optimised by preshuffling plot files depending on SIMD length and use avx2 memcpy
									 //Did not find a away yet to completely avoid memcpys

		for (int j = 0; j < 64 * MSHABAL512_FACTOR / 2; j += 4 * MSHABAL512_FACTOR) {
			size_t o = j / MSHABAL512_FACTOR;
			u1.words[j + 0 + 128] = *(mshabal_u32 *)(&cache[(v + 0) * 64] + o);
			u1.words[j + 1 + 128] = *(mshabal_u32 *)(&cache[(v + 1) * 64] + o);
			u1.words[j + 2 + 128] = *(mshabal_u32 *)(&cache[(v + 2) * 64] + o);
			u1.words[j + 3 + 128] = *(mshabal_u32 *)(&cache[(v + 3) * 64] + o);
			u1.words[j + 4 + 128] = *(mshabal_u32 *)(&cache[(v + 4) * 64] + o);
			u1.words[j + 5 + 128] = *(mshabal_u32 *)(&cache[(v + 5) * 64] + o);
			u1.words[j + 6 + 128] = *(mshabal_u32 *)(&cache[(v + 6) * 64] + o);
			u1.words[j + 7 + 128] = *(mshabal_u32 *)(&cache[(v + 7) * 64] + o);
			u1.words[j + 8 + 128] = *(mshabal_u32 *)(&cache[(v + 8) * 64] + o);
			u1.words[j + 9 + 128] = *(mshabal_u32 *)(&cache[(v + 9) * 64] + o);
			u1.words[j + 10 + 128] = *(mshabal_u32 *)(&cache[(v + 10) * 64] + o);
			u1.words[j + 11 + 128] = *(mshabal_u32 *)(&cache[(v + 11) * 64] + o);
			u1.words[j + 12 + 128] = *(mshabal_u32 *)(&cache[(v + 12) * 64] + o);
			u1.words[j + 13 + 128] = *(mshabal_u32 *)(&cache[(v + 13) * 64] + o);
			u1.words[j + 14 + 128] = *(mshabal_u32 *)(&cache[(v + 14) * 64] + o);
			u1.words[j + 15 + 128] = *(mshabal_u32 *)(&cache[(v + 15) * 64] + o);
			u2.words[j + 0] = *(mshabal_u32 *)(&cache[(v + 0) * 64 + 32] + o);
			u2.words[j + 1] = *(mshabal_u32 *)(&cache[(v + 1) * 64 + 32] + o);
			u2.words[j + 2] = *(mshabal_u32 *)(&cache[(v + 2) * 64 + 32] + o);
			u2.words[j + 3] = *(mshabal_u32 *)(&cache[(v + 3) * 64 + 32] + o);
			u2.words[j + 4] = *(mshabal_u32 *)(&cache[(v + 4) * 64 + 32] + o);
			u2.words[j + 5] = *(mshabal_u32 *)(&cache[(v + 5) * 64 + 32] + o);
			u2.words[j + 6] = *(mshabal_u32 *)(&cache[(v + 6) * 64 + 32] + o);
			u2.words[j + 7] = *(mshabal_u32 *)(&cache[(v + 7) * 64 + 32] + o);
			u2.words[j + 8] = *(mshabal_u32 *)(&cache[(v + 8) * 64 + 32] + o);
			u2.words[j + 9] = *(mshabal_u32 *)(&cache[(v + 9) * 64 + 32] + o);
			u2.words[j + 10] = *(mshabal_u32 *)(&cache[(v + 10) * 64 + 32] + o);
			u2.words[j + 11] = *(mshabal_u32 *)(&cache[(v + 11) * 64 + 32] + o);
			u2.words[j + 12] = *(mshabal_u32 *)(&cache[(v + 12) * 64 + 32] + o);
			u2.words[j + 13] = *(mshabal_u32 *)(&cache[(v + 13) * 64 + 32] + o);
			u2.words[j + 14] = *(mshabal_u32 *)(&cache[(v + 14) * 64 + 32] + o);
			u2.words[j + 15] = *(mshabal_u32 *)(&cache[(v + 15) * 64 + 32] + o);
		}

		simd512_mshabal_openclose_fast(&x, &u1, &u2, res0, res1, res2, res3, res4, res5, res6, res7, res8, res9, res10, res11, res12, res13, res14, res15, 0);

		unsigned long long *wertung = (unsigned long long*)res0;
		unsigned long long *wertung1 = (unsigned long long*)res1;
		unsigned long long *wertung2 = (unsigned long long*)res2;
		unsigned long long *wertung3 = (unsigned long long*)res3;
		unsigned long long *wertung4 = (unsigned long long*)res4;
		unsigned long long *wertung5 = (unsigned long long*)res5;
		unsigned long long *wertung6 = (unsigned long long*)res6;
		unsigned long long *wertung7 = (unsigned long long*)res7;
		unsigned long long *wertung8 = (unsigned long long*)res8;
		unsigned long long *wertung9 = (unsigned long long*)res9;
		unsigned long long *wertung10 = (unsigned long long*)res10;
		unsigned long long *wertung11 = (unsigned long long*)res11;
		unsigned long long *wertung12 = (unsigned long long*)res12;
		unsigned long long *wertung13 = (unsigned long long*)res13;
		unsigned long long *wertung14 = (unsigned long long*)res14;
		unsigned long long *wertung15 = (unsigned long long*)res15;
		unsigned posn = 0;
		if (*wertung1 < *wertung)
		{
			*wertung = *wertung1;
			posn = 1;
		}
		if (*wertung2 < *wertung)
		{
			*wertung = *wertung2;
			posn = 2;
		}
		if (*wertung3 < *wertung)
		{
			*wertung = *wertung3;
			posn = 3;
		}
		if (*wertung4 < *wertung)
		{
			*wertung = *wertung4;
			posn = 4;
		}
		if (*wertung5 < *wertung)
		{
			*wertung = *wertung5;
			posn = 5;
		}
		if (*wertung6 < *wertung)
		{
			*wertung = *wertung6;
			posn = 6;
		}
		if (*wertung7 < *wertung)
		{
			*wertung = *wertung7;
			posn = 7;
		}
		if (*wertung8 < *wertung)
		{
			*wertung = *wertung8;
			posn = 8;
		}
		if (*wertung9 < *wertung)
		{
			*wertung = *wertung9;
			posn = 9;
		}
		if (*wertung10 < *wertung)
		{
			*wertung = *wertung10;
			posn = 10;
		}
		if (*wertung11 < *wertung)
		{
			*wertung = *wertung11;
			posn = 11;
		}
		if (*wertung12 < *wertung)
		{
			*wertung = *wertung12;
			posn = 12;
		}
		if (*wertung13 < *wertung)
		{
			*wertung = *wertung13;
			posn = 13;
		}
		if (*wertung14 < *wertung)
		{
			*wertung = *wertung14;
			posn = 14;
		}
		if (*wertung15 < *wertung)
		{
			*wertung = *wertung15;
			posn = 15;
		}

		unsigned long long deadline = *wertung / coin->mining->currentBaseTarget;
		if (deadline <= coin->mining->bests[acc].targetDeadline)
		{
			if (*wertung < coin->mining->bests[acc].best)
			{
				Log(L"AVX5: found deadline=%llu scoop=%lu nonce=%llu base=%llu height=%llu for account: %llu file: %S", deadline, coin->mining->scoop, nonce + v + posn, coin->mining->baseTarget, coin->mining->height, coin->mining->bests[acc].account_id, file_name.c_str());
				Log(L"SIG: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					coin->mining->currentSignature[ 0], coin->mining->currentSignature[ 1], coin->mining->currentSignature[ 2], coin->mining->currentSignature[ 3], coin->mining->currentSignature[ 4], coin->mining->currentSignature[ 5], coin->mining->currentSignature[ 6], coin->mining->currentSignature[ 7], coin->mining->currentSignature[ 8], coin->mining->currentSignature[ 9],
					coin->mining->currentSignature[10], coin->mining->currentSignature[11], coin->mining->currentSignature[12], coin->mining->currentSignature[13], coin->mining->currentSignature[14], coin->mining->currentSignature[15], coin->mining->currentSignature[16], coin->mining->currentSignature[17], coin->mining->currentSignature[18], coin->mining->currentSignature[19],
					coin->mining->currentSignature[20], coin->mining->currentSignature[21], coin->mining->currentSignature[22], coin->mining->currentSignature[23], coin->mining->currentSignature[24], coin->mining->currentSignature[25], coin->mining->currentSignature[26], coin->mining->currentSignature[27], coin->mining->currentSignature[28], coin->mining->currentSignature[29],
					coin->mining->currentSignature[30], coin->mining->currentSignature[31]);
				Log(L"SCP: %llu <= %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx %02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", deadline,
					cache[(v + posn) * 64 +  0], cache[(v + posn) * 64 +  1], cache[(v + posn) * 64 +  2], cache[(v + posn) * 64 +  3], cache[(v + posn) * 64 +  4], cache[(v + posn) * 64 +  5], cache[(v + posn) * 64 +  6], cache[(v + posn) * 64 +  7], cache[(v + posn) * 64 +  8], cache[(v + posn) * 64 +  9],
					cache[(v + posn) * 64 + 10], cache[(v + posn) * 64 + 11], cache[(v + posn) * 64 + 12], cache[(v + posn) * 64 + 13], cache[(v + posn) * 64 + 14], cache[(v + posn) * 64 + 15], cache[(v + posn) * 64 + 16], cache[(v + posn) * 64 + 17], cache[(v + posn) * 64 + 18], cache[(v + posn) * 64 + 19],
					cache[(v + posn) * 64 + 20], cache[(v + posn) * 64 + 21], cache[(v + posn) * 64 + 22], cache[(v + posn) * 64 + 23], cache[(v + posn) * 64 + 24], cache[(v + posn) * 64 + 25], cache[(v + posn) * 64 + 26], cache[(v + posn) * 64 + 27], cache[(v + posn) * 64 + 28], cache[(v + posn) * 64 + 29],
					cache[(v + posn) * 64 + 30], cache[(v + posn) * 64 + 31], cache[(v + posn) * 64 + 32], cache[(v + posn) * 64 + 33], cache[(v + posn) * 64 + 34], cache[(v + posn) * 64 + 35], cache[(v + posn) * 64 + 36], cache[(v + posn) * 64 + 37], cache[(v + posn) * 64 + 38], cache[(v + posn) * 64 + 39],
					cache[(v + posn) * 64 + 40], cache[(v + posn) * 64 + 41], cache[(v + posn) * 64 + 42], cache[(v + posn) * 64 + 43], cache[(v + posn) * 64 + 44], cache[(v + posn) * 64 + 45], cache[(v + posn) * 64 + 46], cache[(v + posn) * 64 + 47], cache[(v + posn) * 64 + 48], cache[(v + posn) * 64 + 49],
					cache[(v + posn) * 64 + 50], cache[(v + posn) * 64 + 51], cache[(v + posn) * 64 + 52], cache[(v + posn) * 64 + 53], cache[(v + posn) * 64 + 54], cache[(v + posn) * 64 + 55], cache[(v + posn) * 64 + 56], cache[(v + posn) * 64 + 57], cache[(v + posn) * 64 + 58], cache[(v + posn) * 64 + 59],
					cache[(v + posn) * 64 + 60], cache[(v + posn) * 64 + 61], cache[(v + posn) * 64 + 62], cache[(v + posn) * 64 + 63]);

				EnterCriticalSection(&coin->locks->bestsLock);
				coin->mining->bests[acc].best = *wertung;
				coin->mining->bests[acc].nonce = nonce + v + posn;
				coin->mining->bests[acc].DL = deadline;
				LeaveCriticalSection(&coin->locks->bestsLock);
				EnterCriticalSection(&coin->locks->sharesLock);
				coin->mining->shares.push_back(std::make_shared<t_shares>(
					file_name,
					coin->mining->bests[acc].account_id, 
					coin->mining->bests[acc].best,
					coin->mining->bests[acc].nonce,
					coin->mining->bests[acc].DL,
					coin->mining->currentHeight,
					coin->mining->currentBaseTarget));
				LeaveCriticalSection(&coin->locks->sharesLock);
				printToConsole(2, true, false, true, false, L"[%20llu|%-10s|Worker] DL found     : %s",
					coin->mining->bests[acc].account_id, coin->coinname.c_str(), toWStr(coin->mining->bests[acc].DL, 11).c_str());
			}
		}
	}
}
