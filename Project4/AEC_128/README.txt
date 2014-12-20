Implementing the Advanced Encryption Standard (AES) in software.

-Write software that implements AES.
- Identify hotspots in software using profiling and analysis techniques
- Apply software optimization techniques in an iterative fashion to generate performance reports
- Use source code manipulation techniques to improve the software performance
- Understand different design strategies and implementation techniques for AES

1. In this project we will reuse the hardware platform created in project #3, so as the first step copy the entire content of the directory where project #3 is contained into a new location. Then, launch the SDK with the correct workspace (the hardware architecture should be recognized).
2. Be sure to experiment with and measure the performance for the following processor configurations:
MB, external SDRAM memory, no cache
MB, external SDRAM memory, cache 64Kb
a. Compare the profiling results using both gprof (stage 1) and hardware counters (stage 2).
b. Develop code for AES-128 decryption. Verify it with tests provided in FIPS-197 document. Use explicit GF(2^8) operations to calculate Sbox elements