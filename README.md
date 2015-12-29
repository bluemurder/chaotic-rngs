# chaotic-rngs
Random number generators based on chaotic functions. The main works inspiring present code are:

1. T. Stojanovski, L. Kocarev, "Chaos-Based Random Number Generators - Part I: Analysis", IEEE Trans. on CAS - part I, Vol. 48, No. 3, pp. 281-288, Mar. 2001. 
2. T. Stojanovski, J. Pihl, L. Kocarev, "Chaos-Based Random Number Generators - Part II: Practical Realization", IEEE Trans. on CAS - part I, Vol. 48, No. 3, pp. 382-385, Mar. 2001.

## rng01-vhdl

Preliminary version of the chaotic random number generator in VHDL code. 

*newCaoticGen* is the main circuit, performing an iteration a chaotic map described in [1]. The package with constants definitions is *variable_Caos*, and *test* is the testbench.

## rng02-vhdl

*CaosAlAl* is the second version of previous circuit. It does not require external files, and all configuration parameters are hardcoded into the vhdl file in binary encoding. *testCaosAlAl* is the test bench for present circuit, and tells to the simulator to write a file "Test.out" the sequance of outputs produced by the rng.

## rng03-matlab

## rng04-cpp

## rng05-vhdl

## rng06-vhdl

## rng07-vhdl

## rng08-vhdl

## rng09-cpp

## rng10-cpp

