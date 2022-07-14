# toy-AES
About
This is a rudimentary AES implementation in C++ and the different encryption sections could be substituted for more sophisticated algorithms. As it stands, this implementation is to test my understanding of the AES components and is not at all secure.<br>

This project was completed as an assignment in my cybersecurity course on November 12, 2021. I also used skills I learned from my cryptography course.

## Plan
Input files need to be turned into single strings
- Read files by character
- Add characters to the on going string (if not whitespace)

We read the key file first, then read do the preprocessing and substitution at the same time.
- This project called for Vigenere cipher subsitution.

Using a block struct, then we block-ify the input string and pad any empty blocks
- We shift rows in the way AES is structured to do so, but once

Check for an odd number of 1's and correct parity
- The best way I found to do this was using the hamming weight when I completed this project (https://en.wikipedia.org/wiki/Hamming_weight)
- We then do an XOR with 1 if the number from the hamming weight is odd

We use Rijndael's Galois fields to multiply and complete the encryption process
- rgfMul(c0,2) ⊕ rgfMul(c1,3)  ⊕ c2  ⊕ c3 =  a0
- c0 ⊕ rgfMul(c1,2)  ⊕ rgfMul(c2,3)  ⊕ c3 =  a1
- c0 ⊕ c1 ⊕ rgfMul(c2,2)  ⊕ rgfMul(c3,3)  =  a2
- rgfMul(c0,3) ⊕ c1  ⊕ c2  ⊕ rgfMul(c3,2)  =  a3
