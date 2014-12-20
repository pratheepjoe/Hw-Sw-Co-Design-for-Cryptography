1. Write software function that implements Galois field multiplier GF(2^128) with the following irreducible polynomial f(x) = x^128+x^7+x^2+x+1.
2. Use the baseline AES software and the multiplier developed in step 1 to implement simplified version of the AES GCM (assume that initialization vectors will always consist of 96 bits)
3. Verify the functionality of the AES-GCM using just one platform of your choice and test cases #3 and 4.

GCM mode of operation for AES-128, Implementation Comments from Chris Wood
1. Encryption is done with the existing AES 128-bit cipher.
2. GCM is for both encryption of data and authentication of such data.
3. The hash key, H, is simply the result of encrypting a string of 128 0’s (0^128) with the private key, K.
4. The most efficient implementations for GCM use IVs that have a length of 96 bits. This avoids having to use the GHASH function to create a 128-bit string from the IV and counter.
5. The increment function only operates on the rightmost (least significant) 32 bits of its argument, which is the counter (denoted as Y).
6. The GHASH function returns a set of 128 bit blocks of data of size (m + n + 2). This is because X_0 is always initialized to 0 and X_(m+n+1) is the 128-bit block used to generate the authentication tag.
7. The result of len(A) || len(C) is a 128-bit string. The len() function returns a 64-bit integer representing the size of its argument, so len(A) || len(C) just concatenates these two 64-bit numbers together to get a 128-bit string.
8. The additional authentication data can be greater than 128 bits. This should be taken into account in the GHASH function where it is used to generate the final X block used for the authentication tag.
9. The labeled diagram below is a representation of the algorithm for a case where we have 1 block of additional authenticated data and two blocks of plaintext. Note the clear distinction between the initialization, encryption, and authentications.