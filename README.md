# CPP-hashing-function
In this project, I created a program that can test out all the hashing functions, at a very optimal rate.

For each of the possible hash functions my program:

- Creates a vector<int> hashes of size 65,536
- Processes the list of words, and for each word, compute its hash h
- Increments the entry in the table for that hash: hashes.at(h)++
- When finished, uses Pearson’s X2 test to determine the probability that the resulting distribution is uniformly distributed. 
  
Hash functions to test:

- String length (modulo 216)
- First character
- Additive checksum (add all characters together), modulo 216
- Remainder (use a modulo of 65413, this is the first prime that is smaller than the table size). Remember that you cannot just add up all the characters and then take the mod of the result; you have to thread the modulo through the loop that computes the sum.
- Multiplicative (using the scheme described in class/in the lecture notes). Again, remember that you can’t just use the final sum; you have to incorporate the multiplicative calculation into hashing loop.
