# Toy AES
This is a rudimentary and very insecure implementation of
AES in C++. The reason for the insecurity comes from the
assignments description, since this project was developed
in my undergraduate experience.

The goal was to show an understanding of the different
parts of AES's encryption algorithm. Different sections of my
implementation could be subsituted for more sophisticated algorithms
(as is intended by the AES manual and standards).

This project was completed in my cybersecurity course on November 12, 2021.
I also used skills that I learned in my cryptography course from the
semester prior to complete this assignment.

## Plan
Input files need to be turned into single strings
- Read files by character
- Add characters to the on going string (if not whitespace)

We read the key file first, then read do the preprocessing and substitution at the same time.
- This project called for Vigenere cipher subsitution.

Using a block struct, then we block-ify the input string and pad any empty blocks
- We shift rows in the way AES is structured to do so, but once

Check for an odd number of 1's and correct parity
- The best way I found to do this was using the [hamming weight](https://en.wikipedia.org/wiki/Hamming_weight) when I completed this project
- We then do an XOR with 1 if the number from the hamming weight is odd

We use Rijndael's Galois fields to multiply and complete the encryption process
- rgfMul(c0,2) ⊕ rgfMul(c1,3)  ⊕ c2  ⊕ c3 =  a0
- c0 ⊕ rgfMul(c1,2)  ⊕ rgfMul(c2,3)  ⊕ c3 =  a1
- c0 ⊕ c1 ⊕ rgfMul(c2,2)  ⊕ rgfMul(c3,3)  =  a2
- rgfMul(c0,3) ⊕ c1  ⊕ c2  ⊕ rgfMul(c3,2)  =  a3
