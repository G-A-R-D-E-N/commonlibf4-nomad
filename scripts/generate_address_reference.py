#!/usr/bin/env python3

# Generates a deterministic, human-searchable Markdown reference from an Address Library binary.
# Where possible, Address Library IDs are labeled from the CommonLib declarations in include/.

import argparse
import hashlib
import re
import struct
from collections import defaultdict
from pathlib import Path

PAIR = struct.Struct("<QQ")
COUNT = struct.Struct("<Q")
NUMBER_RE = re.compile(r"(?<![A-Za-z0-9_])(?:0[xX][0-9A-Fa-f]+|\d+)(?![A-Za-z0-9_])")
BLOCK_COMMENT_RE = re.compile(r"/\*.*?\*/", re.S)
NAMESPACE_RE = re.compile(r"\bnamespace\s+([A-Za-z_]\w*(?:::[A-Za-z_]\w*)*)\s*\{")
SIMPLE_RE = re.compile(
    r"\b(?:inline\s+)?constexpr\s+REL::(VariantID|ID)\s+([A-Za-z_]\w*)\s*\{(.*?)\}\s*;",
    re.S,
)
ARRAY_RE = re.compile(
    r"\b(?:inline\s+)?constexpr\s+std::array\s*<\s*REL::(VariantID|ID)\s*,\s*\d+\s*>\s+"
    r"([A-Za-z_]\w*)\s*\{(.*?)\}\s*;",
    re.S,
)
INNER_ID_RE = re.compile(r"REL::(?:VariantID|ID)\s*[\(\{](.*?)[\)\}]", re.S)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate a Markdown ID -> RVA reference from an F4SE Address Library .bin file."
    )
    parser.add_argument("input", type=Path, help="Address Library .bin file")
    parser.add_argument("output", type=Path, help="Markdown output file")
    parser.add_argument("--version", required=True, help="Fallout 4 version label, e.g. 1.11.240.0")
    parser.add_argument(
        "--include-root",
        type=Path,
        default=Path("include"),
        help="CommonLib include tree used to attach known symbolic names",
    )
    return parser.parse_args()


def runtime_slot(version: str) -> int:
    parts = [int(x) for x in version.split(".") if x.isdigit()]
    if len(parts) < 3:
        raise SystemExit(f"cannot infer runtime slot from version {version!r}")
    major, minor, patch = parts[:3]
    if (major, minor) == (1, 10) and patch <= 163:
        return 0  # OG
    if (major, minor) == (1, 10):
        return 1  # NG
    if (major, minor) >= (1, 11):
        return 2  # AE
    raise SystemExit(f"unsupported Fallout 4 version {version!r}")


def parse_numbers(text: str) -> list[int]:
    return [int(token, 0) for token in NUMBER_RE.findall(text)]


def select_runtime_id(values: list[int], slot: int) -> int | None:
    if not values:
        return None
    if len(values) == 1:
        value = values[0]
    elif slot == 0:
        value = values[0]
    elif slot == 1:
        value = values[1] if len(values) >= 3 else values[-1]
    else:
        value = values[2] if len(values) >= 3 else values[-1]
    return value or None


def namespace_at_positions(text: str) -> list[tuple[int, tuple[str, ...]]]:
    """Return declaration-friendly namespace snapshots keyed by character position."""
    snapshots: list[tuple[int, tuple[str, ...]]] = []
    stack: list[tuple[int, tuple[str, ...]]] = []
    depth = 0
    i = 0
    while i < len(text):
        match = NAMESPACE_RE.match(text, i)
        if match:
            parts = tuple(match.group(1).split("::"))
            depth += 1
            stack.append((depth, parts))
            i = match.end()
            continue
        ch = text[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
            while stack and depth < stack[-1][0]:
                stack.pop()
        if ch == "\n":
            flattened: list[str] = []
            for _, parts in stack:
                flattened.extend(parts)
            snapshots.append((i + 1, tuple(flattened)))
        i += 1
    return snapshots


def namespace_for(pos: int, snapshots: list[tuple[int, tuple[str, ...]]]) -> tuple[str, ...]:
    lo, hi = 0, len(snapshots)
    while lo < hi:
        mid = (lo + hi) // 2
        if snapshots[mid][0] <= pos:
            lo = mid + 1
        else:
            hi = mid
    return snapshots[lo - 1][1] if lo else ()


def collect_symbol_names(include_root: Path, slot: int) -> dict[int, list[str]]:
    names: dict[int, set[str]] = defaultdict(set)
    if not include_root.exists():
        return {}

    for path in sorted(p for p in include_root.rglob("*") if p.suffix.lower() in {".h", ".hpp", ".inl"}):
        try:
            source = path.read_text(encoding="utf-8", errors="ignore")
        except OSError:
            continue
        source = BLOCK_COMMENT_RE.sub("", source)
        source = "\n".join(line.split("//", 1)[0] for line in source.splitlines())
        snapshots = namespace_at_positions(source)

        for match in SIMPLE_RE.finditer(source):
            _, symbol, initializer = match.groups()
            address_id = select_runtime_id(parse_numbers(initializer), slot)
            if address_id is None:
                continue
            ns = namespace_for(match.start(), snapshots)
            full = "::".join((*ns, symbol)) if ns else symbol
            names[address_id].add(full)

        for match in ARRAY_RE.finditer(source):
            _, symbol, initializer = match.groups()
            ns = namespace_for(match.start(), snapshots)
            entries = list(INNER_ID_RE.finditer(initializer))
            for index, entry in enumerate(entries):
                address_id = select_runtime_id(parse_numbers(entry.group(1)), slot)
                if address_id is None:
                    continue
                indexed = f"{symbol}[{index}]"
                full = "::".join((*ns, indexed)) if ns else indexed
                names[address_id].add(full)

    return {address_id: sorted(symbols) for address_id, symbols in names.items()}


def main() -> None:
    args = parse_args()
    raw = args.input.read_bytes()
    if len(raw) < COUNT.size:
        raise SystemExit(f"{args.input}: file is too small")

    (count,) = COUNT.unpack_from(raw, 0)
    expected = COUNT.size + count * PAIR.size
    if len(raw) != expected:
        raise SystemExit(
            f"{args.input}: size mismatch: header says {count:,} entries, "
            f"expected {expected:,} bytes, got {len(raw):,}"
        )

    slot = runtime_slot(args.version)
    symbol_names = collect_symbol_names(args.include_root, slot)
    present_ids = set()
    offset = COUNT.size
    for _ in range(count):
        address_id, _ = PAIR.unpack_from(raw, offset)
        present_ids.add(address_id)
        offset += PAIR.size
    named_count = sum(1 for address_id in present_ids if address_id in symbol_names)

    sha256 = hashlib.sha256(raw).hexdigest()
    args.output.parent.mkdir(parents=True, exist_ok=True)

    with args.output.open("w", encoding="utf-8", newline="\n") as out:
        out.write(f"# Fallout 4 Address Library {args.version}\n\n")
        out.write(f"Source: `{args.input.as_posix()}`  \n")
        out.write(f"Entries: **{count:,}**  \n")
        out.write(f"Named by this CommonLib checkout: **{named_count:,}**  \n")
        out.write(f"SHA-256: `{sha256}`\n\n")
        out.write(
            "Each line is `Address Library ID  RVA  CommonLib symbol(s)`. "
            "RVAs are relative to the Fallout4.exe module base. `-` means the binary contains "
            "the ID but this CommonLib checkout has no symbolic declaration for it. Names are "
            "derived from the checked-out CommonLib headers, not guessed from the binary.\n\n"
        )
        out.write("```text\n")
        offset = COUNT.size
        previous_id = None
        for index in range(count):
            address_id, rva = PAIR.unpack_from(raw, offset)
            offset += PAIR.size
            if previous_id is not None and address_id <= previous_id:
                raise SystemExit(
                    f"{args.input}: IDs are not strictly increasing at entry {index}: "
                    f"{previous_id} -> {address_id}"
                )
            previous_id = address_id
            labels = symbol_names.get(address_id)
            label = "; ".join(labels) if labels else "-"
            out.write(f"{address_id} 0x{rva:08X} {label}\n")
        out.write("```\n")

    print(
        f"wrote {count:,} entries to {args.output}; "
        f"{named_count:,} IDs labeled from CommonLib; sha256={sha256}"
    )


if __name__ == "__main__":
    main()
