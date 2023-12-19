import hashlib
import os
import time


def checksum_md5(filename):
    md5 = hashlib.md5()
    with open(filename, "rb") as f:
        for chunk in iter(lambda: f.read(8192), b""):
            md5.update(chunk)
    return md5.hexdigest()


def main():
    directory = os.getcwd()

    start = time.time()
    for filename in os.listdir(directory):
        hasher = hashlib.md5()
        if filename.endswith(".mov"):
            with open(filename, "rb") as open_file:
                content = open_file.read()  # Warning: will read the whole file.
                hasher.update(content)
            # print(hasher.hexdigest())

    print(f"First run: {time.time() - start}")

    start = time.time()
    for filename in os.listdir(directory):
        if filename.endswith(".mov"):
            # print(checksum_md5(filename))
            checksum_md5(filename)
            continue

    print(f"First run: {time.time() - start}")

    # To test if my C-code is giving the correct checksum on `main.c`:
    # `main.c` was: 05aaefae72afd3a95f686f6ed7702a4c. <- unless file updated.
    hex_string = checksum_md5("main.c")
    print(f"DBUGR: C-code checksum should be: {hex_string}")


if __name__ == "__main__":
    main()
