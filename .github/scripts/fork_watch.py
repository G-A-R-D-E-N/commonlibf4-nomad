"""Report recently active CommonLib forks with their own commits that are not in UPSTREAM_SYNC_SOURCES."""
import json
import os
import subprocess
from datetime import datetime, timedelta, timezone

REPO = os.environ["REPO"]
BASE = os.environ["BASE"]
DAYS = int(os.environ.get("FORK_WATCH_DAYS") or 120)
since = datetime.now(timezone.utc) - timedelta(days=DAYS)
sources = json.loads(os.environ.get("SOURCES") or "[]")


def gh(*args):
    r = subprocess.run(["gh", *args], capture_output=True, text=True)
    return r.stdout.strip() if r.returncode == 0 else ""


def forks_of(full):
    out = gh("api", "--paginate", f"repos/{full}/forks?per_page=100", "--jq", ".[] | @json")
    return [json.loads(line) for line in out.splitlines() if line]


def counts(base_repo, base_branch, fork, branch):
    out = gh("api", f"repos/{base_repo}/compare/{base_branch}...{fork.split('/')[0]}:{fork.split('/')[1]}:{branch}", "--jq", "[.ahead_by,.behind_by]")
    return tuple(json.loads(out)) if out else None


roots = [r.strip() for r in (os.environ.get("NETWORK_ROOT") or gh("api", f"repos/{REPO}", "--jq", ".source.full_name // empty")).split(",") if r.strip()]
root = ", ".join(roots)
known = {s["url"].lower().removesuffix(".git").split("github.com/")[-1] for s in sources if "github.com/" in s.get("url", "")}
parent_of_repo = gh("api", f"repos/{REPO}", "--jq", ".parent.full_name // empty").lower()
if any(s.get("url") == "parent" for s in sources) and parent_of_repo:
    known.add(parent_of_repo)

seen, queue, parents, repos = set(roots), list(roots), {}, {}
for r in roots:
    info = json.loads(gh("api", f"repos/{r}") or "{}")
    if info.get("parent"):
        parents[r], repos[r] = info["parent"]["full_name"], info
while queue:
    full = queue.pop(0)
    for f in forks_of(full):
        name = f["full_name"]
        if name in seen:
            continue
        seen.add(name)
        parents[name], repos[name] = full, f
        if f.get("forks_count"):
            queue.append(name)

rows = []
for name, f in repos.items():
    if name.split("/")[0].lower() == REPO.split("/")[0].lower() or name.lower() in known:
        continue
    if datetime.fromisoformat(f["pushed_at"].replace("Z", "+00:00")) < since:
        continue
    parent = parents[name]
    parent_branch = (repos.get(parent) or {}).get("default_branch") or gh("api", f"repos/{parent}", "--jq", ".default_branch") or "main"
    own = counts(parent, parent_branch, name, f["default_branch"])
    if not own or own[0] == 0:
        continue
    vs_us = counts(REPO, BASE, name, f["default_branch"])
    rows.append((f["pushed_at"][:10], name, f["default_branch"], parent, own[0], vs_us, f.get("stargazers_count", 0)))

rows.sort(reverse=True)
lines = [
    f"Recently active forks under `{root}` (pushed in the last {DAYS} days) with commits of their own that `upstream-sync` does not track yet.",
    "",
    "To track one, add `{\"name\": ..., \"url\": \"https://github.com/<owner>/<repo>.git\", \"ref\": ..., \"build\": ...}` to the `UPSTREAM_SYNC_SOURCES` repo variable after checking the fork is a real CommonLib fork.",
    "",
    "| Last push | Fork | Branch | Fork of | Own commits | vs this repo (+ahead / -behind) | Stars |",
    "|---|---|---|---|---|---|---|",
]
for pushed, name, branch, parent, own, vs, stars in rows:
    vs_text = f"+{vs[0]} / -{vs[1]}" if vs else "different network"
    lines.append(f"| {pushed} | [{name}](https://github.com/{name}) | `{branch}` | {parent} | {own} | {vs_text} | {stars} |")
if not rows:
    lines.append("| - | none | | | | | |")
open("fork-watch.md", "w", encoding="utf-8").write("\n".join(lines) + "\n")
print(f"{len(rows)} untracked active forks")
