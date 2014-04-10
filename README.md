Floating Point Inspector
========================

This application reads in numerical input and displays floating point information for given input.

## How to Compile

    gcc -m32 -std=gnu99 -Wall -g floating-point-inspector.c -o floating-point-inspector

## Example Output

    Floating Point Inspector

    byte order: little-endian

    > FFFFFFFF
    0xFFFFFFFF
    signBit 1, expBits 255, fractBits 0x007FFFFF
    QNaN

    > 3
    0x00000003
    signBit 0, expBits   0, fractBits 0x00000003
    denormalized: exp = -126

    > DEADBEEF
    0xDEADBEEF
    signBit 1, expBits 189, fractBits 0x002DBEEF
    normalized:   exp =  62

    > deadbeef
    0xDEADBEEF
    signBit 1, expBits 189, fractBits 0x002DBEEF
    normalized:   exp =  62

    > 0
    0x00000000
    signBit 0, expBits   0, fractBits 0x00000000
    +zero

## Notes

- See LICENSE file for license information.
