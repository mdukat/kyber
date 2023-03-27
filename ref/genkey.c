#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "kem.h"

int main(int argc, char* argv[])
{
	// TODO proper args handling
	if(argc != 2) {
		printf("usage: %s <keyname>\n", argv[0]);
		return 1;
	}

	uint8_t pk[CRYPTO_PUBLICKEYBYTES];
	uint8_t sk[CRYPTO_SECRETKEYBYTES];
	crypto_kem_keypair(pk, sk);

	FILE *f_pk, *f_sk;
	char pkfilename[strlen(filename)+5];

	// prepare public key filename
	strcpy(pkfilename, filename);
	strcat(pkfilename, ".pub");

	// TODO check if files exist
	
	// save public key
	f_pk = fopen(pkfilename, "w");
	if(!f_pk){
		printf("ERROR public key file stat\n");
		return;
	}

	if(!fwrite(pk, CRYPTO_PUBLICKEYBYTES, 1, f_pk)){
		printf("ERROR public key file write\n");
		return;
	}
	fclose(f_pk);

	// save secret key
	f_sk = fopen(filename, "w");
	if(!f_sk){
		printf("ERROR secret key file stat\n");
		return;
	}

	if(!fwrite(sk, CRYPTO_SECRETKEYBYTES, 1, f_sk)){
		printf("ERROR secret key file write\n");
		return;
	}
	fclose(f_sk);

	return 0;
}
