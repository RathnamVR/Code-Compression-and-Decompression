# Code-Compression-and-Decompression
In this project, you need to implement both code compression and decompression using C, C++ or Java.
Assume that the dictionary can have eight entries (index 3 bits) and the eight entries are selected based on
frequency (the most frequent instruction should have index 000). If two entries have the same frequency,
the priority should be given to the one that appears first in the original program order. The original
code consists of 32-bit binaries. You are allowed to use only the following seven possible formats for
compression. Note that if one entry (32-bit binary) can be compressed in more than one way, choose the
most beneficial one i.e., the one that provides the shortest compressed pattern. If two formats produce
exactly the same compression, choose the one that appears earlier in the following listing (e.g., run-length
encoding appears earlier than direct matching). Also, if there is a scenario where you have two possible
ways of applying bitmasks to a 32-bit binary, always give preference to the scenario where the leftmost bit
‘1’ for the bitmask pattern (e.g., 11 is preferred over 01). Please count the starting location of a mismatch
from the leftmost (MSB) bit of the pattern – If the mismatch is at the MSB, Mismatch Location should
be 00000.<br/> 

![alt text](https://github.com/RathnamVR/Code-Compression-and-Decompression/blob/main/images/compression%20format.PNG?raw=true)

Run-Length Encoding (RLE) can be used when there is consecutive repetition of the same instruction. The first instruction of the repeated sequence will be compressed (or kept uncompressed if it
is not part of the dictionary) as usual. The remaining ones will be compressed using RLE format shown
above. The two bits in the RLE indicates the number of occurrences (00, 01, 10 and 11 imply 1, 2, 3
and 4 occurrences, respectively), excluding the first one. A single application of RLE can encode up to
4 instructions. Assume that the longest sequence can be at most 5 repeating instructions (the first one
using other formats and the last 4 using RLE). Note that, RLE should be used when it is profitable
compared to other available options.<br/> 

A working prototype that will take any 32-bit binary (0/1 text) file and compress it to
produce an output file that shows compressed patterns arranged in a sequential manner (32-bit in each
line, last line padded with 1’s, if needed), a separation marker “xxxx”, followed by eight dictionary entries is implemented.<br/> 

The program is alos able to accept a compressed file (in the above format) and decompress to
generate the decompressed (original) patterns.<br/> 

# Command Line and Input/Output Formats:
The simulator is executed with the following command line. Parameters “1” and “2” are used
to indicate compression, and decompression, respectively.<br/> 
• ./SIM 1 for compression<br/> 
• ./SIM 2 for decompression<br/> 
