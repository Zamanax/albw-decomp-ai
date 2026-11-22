#!/usr/bin/env python
"""Project dashboard data: one JSON document on stdout, for the Herdr `albw-dashboard` mod.

  python tools/dashboard.py            JSON (what the mod reads)
  python tools/dashboard.py --pretty   the same, indented

Sources (all read-only): functions.json, funcs.json, shared/{extra,not}_starts.txt, shared/parked.json,
shared/reopen.json, logs/campaign/{ledger.jsonl,plan.json}, logs/manual/<addr>/check_log.jsonl, git.
Function sizes are the gap to the next known start (the last one runs to the end of .text), so byte
figures are approximate. The matched-over-time history counts `"status"` lines added/removed in every
commit touching functions.json; it is cached in logs/dashboard_history.json keyed by HEAD.
"""
import collections
import datetime
import json
import os
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import campaign  # noqa: E402  (ledger, plan, check-log progress)

TA, TS = 0x100000, 5841180   # .text, as in fn.py (not imported: it needs code.bin and capstone)
TEXT_END = TA + TS
HISTORY_CACHE = os.path.join(ROOT, "logs", "dashboard_history.json")
SIZE_BUCKETS = (16, 64, 256, 1024, 4096)


def git(*args):
    r = subprocess.run(["git", "--no-optional-locks", *args], capture_output=True, text=True, cwd=ROOT,
                       encoding="utf-8", errors="replace")
    return r.stdout


def addr_lines(rel):
    p = os.path.join(ROOT, rel)
    if not os.path.exists(p):
        return set()
    out = set()
    for line in open(p):
        tok = line.split("#", 1)[0].split()
        if tok:
            out.add(int(tok[0], 16))
    return out


def function_sizes(status):
    starts = set(json.load(open(os.path.join(ROOT, "funcs.json")))["starts"])
    starts |= addr_lines("shared/extra_starts.txt")
    starts |= {int(k, 16) for k, v in status.items() if v.get("status") != "interior_address"}
    starts -= addr_lines("shared/not_starts.txt")
    starts -= {int(k, 16) for k, v in status.items() if v.get("status") == "interior_address"}
    order = sorted(a for a in starts if TA <= a < TEXT_END)
    ends = order[1:] + [TEXT_END]
    return {a: e - a for a, e in zip(order, ends)}


def bucket(size):
    for i, b in enumerate(SIZE_BUCKETS):
        if size <= b:
            return i
    return len(SIZE_BUCKETS)


def coverage(status):
    sizes = function_sizes(status)
    by = collections.Counter(v.get("status") for v in status.values())
    known = {int(k, 16): v.get("status") for k, v in status.items()}
    total_b = sum(sizes.values())
    bytes_by = collections.Counter()
    remaining = [[0, 0] for _ in range(len(SIZE_BUCKETS) + 1)]   # [functions, bytes] per size bucket
    for a, s in sizes.items():
        st = known.get(a)
        bytes_by[st or "unmatched"] += s
        if st is None:
            r = remaining[bucket(s)]
            r[0] += 1
            r[1] += s
    labels = ["≤%d" % b for b in SIZE_BUCKETS] + [">%d" % SIZE_BUCKETS[-1]]
    funcs = dict(by, total=len(sizes), unmatched=sum(1 for a in sizes if a not in known))
    return (funcs, dict(bytes_by, total=total_b),
            [dict(label=l, functions=r[0], bytes=r[1]) for l, r in zip(labels, remaining)])


def history():
    """[(unix time, honest delta, hack delta)] per commit touching functions.json, oldest first."""
    head = git("rev-parse", "HEAD").strip()
    if os.path.exists(HISTORY_CACHE):
        try:
            c = json.load(open(HISTORY_CACHE))
            if c.get("head") == head:
                return c["points"]
        except (ValueError, KeyError):
            pass
    out = git("log", "-p", "--reverse", "-U0", "--format=COMMIT %ct", "--", "functions.json")
    points, cur = [], None
    for line in out.splitlines():
        if line.startswith("COMMIT "):
            cur = [int(line[7:]), 0, 0]
            points.append(cur)
        elif cur and line[:1] in "+-" and line[1:].lstrip().startswith('"status"') and not line.startswith(("+++", "---")):
            d = 1 if line[0] == "+" else -1
            if '"honest"' in line:
                cur[1] += d
            elif '"hack"' in line:
                cur[2] += d
    os.makedirs(os.path.dirname(HISTORY_CACHE), exist_ok=True)
    json.dump(dict(head=head, points=points), open(HISTORY_CACHE, "w"))
    return points


def daily(points, days=120):
    """Honest + hack totals at the end of each of the last `days` days (local time), starting no earlier
    than the first commit (the initial import is a total, not a day's gain)."""
    by_day = collections.OrderedDict()
    h = k = 0
    for t, dh, dk in points:
        h += dh
        k += dk
        by_day[datetime.date.fromtimestamp(t)] = (h, k)
    today = datetime.date.today()
    out, last = [], (0, 0)
    first = max(today - datetime.timedelta(days=days - 1), min(by_day, default=today))
    for d, v in by_day.items():
        if d < first:
            last = v
    for i in range((today - first).days + 1):
        d = first + datetime.timedelta(days=i)
        last = by_day.get(d, last)
        out.append(dict(day=d.isoformat(), honest=last[0], hack=last[1]))
    return out


def campaign_data():
    led = campaign.ledger()
    c = collections.Counter((e["tier"], e["outcome"]) for e in led)
    tiers = [dict(tier=t, attempts=sum(v for (tt, _), v in c.items() if tt == t), match=c[(t, "MATCH")])
             for t in campaign.TIERS]
    rounds = collections.defaultdict(lambda: dict(attempts=0, **{t: 0 for t in campaign.TIERS}))
    for e in led:
        if e.get("round"):
            r = rounds[e["round"]]
            r["attempts"] += 1
            if e["outcome"] == "MATCH":
                r[e["tier"]] += 1
    rounds = [dict(round=n, **rounds[n]) for n in sorted(rounds)[-80:]]
    recent = [dict(addr=e["addr"], tier=e["tier"], round=e.get("round"), outcome=e["outcome"],
                   words=e.get("words", ""), t=e.get("t", "")) for e in led[-12:]][::-1]
    plan = None
    if os.path.exists(campaign.PLAN):
        p = json.load(open(campaign.PLAN))
        targets = []
        for task in p.get("tasks", []):
            for a in task["addrs"]:
                rep = campaign.reported(a)    # None, or MATCH / MISS / TIMEOUT / BAD ...
                n, b = campaign.progress(a, task.get("log_base", {}).get(a))
                targets.append(dict(addr=a, tier=task.get("tier"), checks=n,
                                    best=None if not b else ("MATCH" if b.get("match") else "%.1f%%" % b.get("pct", 0)),
                                    reported=rep))
        plan = dict(round=p.get("round"), created=p.get("created"), agents=len(p.get("tasks", [])),
                    harvested=bool(p.get("harvested")), targets=targets)
    return tiers, rounds, recent, plan


def count_doc(rel):
    p = os.path.join(ROOT, rel)
    if not os.path.exists(p):
        return 0
    return sum(1 for k in json.load(open(p)) if not k.startswith("_"))


def main():
    status = campaign.load_status()
    funcs, bytes_, remaining = coverage(status)
    reasons = collections.Counter(r for v in status.values() if v.get("status") == "hack"
                                  for r in v.get("hack_reasons", []))
    tiers, rounds, recent, plan = campaign_data()
    commits = [dict(zip(("hash", "time", "subject"), l.split("\x1f", 2)))
               for l in git("log", "-12", "--format=%h\x1f%ct\x1f%s").splitlines() if l]
    for c in commits:
        c["time"] = int(c["time"])
    dirty = [l for l in git("status", "--porcelain").splitlines() if l]
    doc = dict(
        generated=datetime.datetime.now().isoformat(timespec="seconds"),
        branch=git("rev-parse", "--abbrev-ref", "HEAD").strip(),
        functions=funcs, bytes=bytes_, remaining=remaining,
        hack_reasons=[dict(reason=r, n=n) for r, n in reasons.most_common(6)],
        parked=count_doc("shared/parked.json"), reopen_forms=count_doc("shared/reopen.json"),
        tiers=tiers, rounds=rounds, recent=recent, plan=plan,
        daily=daily(history()), commits=commits, dirty=len(dirty),
    )
    json.dump(doc, sys.stdout, indent=1 if "--pretty" in sys.argv else None)   # ASCII: safe on a cp1252 pipe


if __name__ == "__main__":
    main()
