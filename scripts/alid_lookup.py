#!/usr/bin/env python3
"""F4SE Address Library .bin lookup.

Bin format (validated against AddressBins/F4SE/Plugins/*): u64 entry count,
then count * <QQ> = (address_id, rva), ids strictly increasing.

Usage:
  alid_lookup.py <bin> --id 195462            # id -> rva
  alid_lookup.py <bin> --rva 0x23670          # rva -> id
"""
import argparse
import bisect
import struct
import sys


def load(path):
    raw = open(path, 'rb').read()
    (count,) = struct.unpack_from('<Q', raw, 0)
    if len(raw) != 8 + count * 16:
        raise SystemExit(f'{path}: size mismatch ({len(raw)} vs {8 + count * 16})')
    ids = []
    rvs = []
    off = 8
    for _ in range(count):
        i, r = struct.unpack_from('<QQ', raw, off)
        off += 16
        ids.append(i)
        rvs.append(r)
    return ids, rvs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('bin')
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument('--id', type=lambda x: int(x, 0))
    g.add_argument('--rva', type=lambda x: int(x, 0))
    a = ap.parse_args()
    ids, rvs = load(a.bin)
    if a.id is not None:
        k = bisect.bisect_left(ids, a.id)
        if k < len(ids) and ids[k] == a.id:
            print(f'id {a.id} -> RVA 0x{rvs[k]:X}')
        else:
            print(f'id {a.id} absent')
    else:
        k = bisect.bisect_left(rvs, a.rva)
        hits = [ids[i] for i in range(k, len(ids)) if rvs[i] == a.rva]
        if hits:
            print(f'RVA 0x{a.rva:X} -> ids {hits}')
        else:
            print(f'RVA 0x{a.rva:X} absent')


if __name__ == '__main__':
    main()
