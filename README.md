# README

This is a simple C and Python program that serves as a reference for how to use
MD5 on a string and a file (in C).

## Warning

Since this is purely experimental, one of the calls in the Python scripts does
an `f.read()`, reading the whole file in Memory. The function `checksum_md5()`
reads the file bytes to a buffer.

## Requirements

- Linux
- For C `apt install libssl-dev`

## Tests

Not designed to be efficient so the tests aren't accurate but with 24 files
(~2GB) each it took the Python script:

- ~80 seconds first run.
- ~73 seconds second run.

## Useful Links

- https://www.openssl.org/docs/man1.1.1/man3/EVP_DigestInit_ex.html
