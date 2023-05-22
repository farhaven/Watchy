#!/bin/bash

cat >/dev/null <<EOF
Use this tool to decode stack traces like the following (get them from pio run -t monitor and wait for a panic to be reported by the boot loader):

Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled.

Core  1 register dump:
PC      : 0x40092034  PS      : 0x00060e30  A0      : 0x800e8eb0  A1      : 0x3ffcd950
A2      : 0x00000005  A3      : 0x00000001  A4      : 0x000000ff  A5      : 0x0000ff00
A6      : 0x00ff0000  A7      : 0xff000000  A8      : 0x800e8ebe  A9      : 0x3ffcd920
A10     : 0x00000002  A11     : 0x3f418182  A12     : 0x3f418182  A13     : 0x3ffc4950
A14     : 0x00ff0000  A15     : 0xff000000  SAR     : 0x0000001b  EXCCAUSE: 0x0000001c
EXCVADDR: 0x00000005  LBEG    : 0x40092055  LEND    : 0x40092065  LCOUNT  : 0xffffffff


Backtrace: 0x40092031:0x3ffcd950 0x400e8ead:0x3ffcd960 0x400e8fa9:0x3ffcd980 0x400d3ee5:0x3ffcd9a0 0x400d4f85:0x3ffcda00 0x400d4755:0x3ffcda20 0x400d3015:0x3ffcda60 0x400ece6e:0x3ffcdab0
EOF

grep "^Backtrace: " | sed -e 's/ /\n/g' | tail -n +2 | while read addr; do
	xtensa-esp32-elf-addr2line -pfiaC -e .pio/build/esp32dev/firmware.elf -a $(echo $addr | cut -d':' -f1)
done

