# BinaryArincToAsciiConverter
This project converts binary recorded 32-Bit ARINC 429 data to ASCII

ARINC 429 data consists of 32 bit words. Within those words, different data is stored. Depending on the ARINC label this data is decoded differently.
This projects converts the binary stored ARINC 429 data into a ASCII text file. This binary data consists of 32-bit words and 32-bit time tags indicating the recording time of that word based on the clock of the interface card.
The program is a console application. It is called with the input file and output file as parameters

BinaryArincToAscii.exe <inputfile> <outputfile>
