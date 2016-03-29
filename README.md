# chaotic-rngs
Random number generators based on chaotic functions. The main works inspiring present code are:

1. T. Stojanovski, L. Kocarev, "Chaos-Based Random Number Generators - Part I: Analysis", IEEE Trans. on CAS - part I, Vol. 48, No. 3, pp. 281-288, Mar. 2001. 
2. T. Stojanovski, J. Pihl, L. Kocarev, "Chaos-Based Random Number Generators - Part II: Practical Realization", IEEE Trans. on CAS - part I, Vol. 48, No. 3, pp. 382-385, Mar. 2001.
3. Von Neumann, John. "13. Various Techniques Used in Connection With Random Digits.", 1951.

## rng01-vhdl

Preliminary version of the chaotic random number generator in VHDL code. 

*newCaoticGen* is the main circuit, performing iterations of a chaotic map belonging to the maps family described in [1]. *variable_Caos* is a package with constants definitions, and *test* is the testbench.

## rng02-vhdl

*CaosAlAl* is the second version of previous circuit. It does not require external files, and all configuration parameters are hardcoded into the vhdl file in binary encoding. *testCaosAlAl* is the test bench for present circuit, and tells to the simulator to write a file "Test.out" the sequence of outputs produced by the rng. The implemented map is:

if x(k)<0 : x(k+1) = 1.875*x(k) + 1;
else : x(k+1) = 1.875*x(k) - 1;

The random number generator output is only the sign of map output. This circuit is interesting because one can vary the number of bits used to represent the system states (x(i)) and to test possible random number generator sequence variations.

## rng03-matlab

Matlab implementation of the previous circuit.

## rng04-cpp

C++ implementation of the following map:
if x(k)<0 : x(k+1) = a*x(k) + 1;
else : x(k+1) = b*x(k) - 1;

## rng05-vhdl

This code includes a C++ program able to write VHDL random number generators.
Starting from file *template.vhd*, the C++ program *main.cpp* produces rngs implementing chaotic maps like:

if x(k)<0 : x(k+1) = 1.875*x(k) + 1;
else : x(k+1) = 1.875*x(k) - 1;

but different features including number of bytes to reperent map state, and number of outputs to ignore between valid rng outputs.

## rng06-vhdl

Project of a chaotic map rng analog to previous ones, but including a von neumann corrector useful to force the probabilities of 0 and 1 to 0.5 [3].

## rng07-vhdl

Same as previous project, but the file *randgen_package.vhd* is created by a c++ code useful to specify in a programmatic way the number of bits of the chaotic map state, and the number of map putputs to skip.

## rng08-vhdl

VHDL code implementing the map:
if x(k)<0 : x(k+1) = 1.875*x(k) + 1;
else : x(k+1) = 1.875*x(k) - 1;

but present circuit is combinatorial, the propagation time and the number of map iterations are given by FPGA place&route phase. The test bench takes the output every 10 ns.

## rng09-cpp

C++ code implementig chaotic maps similar to previous circuits. The representation of the map state is in fixed precision (custom implementation). It is possible to specify the total number of bits of the state, and the number of bits ised to represent the decimal part. It is specified also a number of map outputs to skip. 

## rng10-cpp

C++ code implementig chaotic maps similar to previous circuits. The representation of the map state is in fixed precision (custom implementation). It is possible to specify the total number of bits of the state, and the number of bits ised to represent the decimal part. It is specified also a number of map outputs to skip. Such implementations includes a von neumann corrector stadium.