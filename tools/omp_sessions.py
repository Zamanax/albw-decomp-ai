"""omp sessions touched in the last day, the subagents each one spawned, and per-subagent details for
the recent ones, as JSON on stdout: {"sessions": [...], "subs": {name: {state, cost, started, mtime}}}.
Read every 5 s by the Herdr `albw-dashboard` mod (with tools/dashboard.py), on the machine of its space.

A session is ~/.omp/agent/sessions/<cwd>/<stamp>_<id>.jsonl; its first line is the title record.
Its subagents are the session files under the sibling folder <stamp>_<id>/ (nested ones in
subfolders). A subagent is finished once its file ends with a `session_exit` record; one without
it that was written in the last STALE seconds is running, older ones ended without the record.
Cost is omp's own estimate in USD: usage.cost.total of every `message` and `model_usage` record,
summed incrementally (byte offset per file, cached in the temp folder), so each scan only reads
what was appended since the last one. `subs` covers subagent files written in the last RECENT seconds,
keyed by file name (a campaign subagent's name is its plan task name), so the plan view can join them.
"""
import json
import os
import sys
import tempfile
import re
import time

ROOT = os.path.join(os.path.expanduser("~"), ".omp", "agent", "sessions")
SINCE = 24 * 3600
STALE = 600
RECENT = 6 * 3600
CAMPAIGN = re.compile(r"c\d{8}_")   # tools/campaign.py subagent names: c<MMDDHHMM>_<tier>_<addr>
TAIL = 2048
CACHE = os.path.join(tempfile.gettempdir(), "albw-dashboard-omp-cost.json")


def first_record(path):
    try:
        with open(path, "rb") as fh:
            return json.loads(fh.readline() or b"{}")
    except (OSError, ValueError):
        return {}


def finished(path, size):
    with open(path, "rb") as fh:
        fh.seek(max(0, size - TAIL))
        return b'"session_exit"' in fh.read()


def record_cost(line):
    try:
        r = json.loads(line)
        usage = (r.get("message") or {}).get("usage") if r.get("type") == "message" else r.get("usage")
        return float(((usage or {}).get("cost") or {}).get("total") or 0)
    except (ValueError, TypeError, AttributeError):
        return 0.0


def cost(path, size, cache):
    """USD so far; reads only the complete lines appended since the cached offset."""
    offset, total = cache.get(path, (0, 0.0))
    if size < offset:                         # rewritten: start over
        offset, total = 0, 0.0
    if size > offset:
        with open(path, "rb") as fh:
            fh.seek(offset)
            chunk = fh.read(size - offset)
        end = chunk.rfind(b"\n") + 1
        for line in chunk[:end].splitlines():
            if b'"cost"' in line:
                total += record_cost(line)
        offset += end
    cache[path] = (offset, total)
    return total


def subagents(folder, now, cache, subs):
    out = dict(spawned=0, nested=0, running=0, finished=0, ended=0, active=[], cost=0.0, running_cost=0.0,
               campaign=0)
    for root, _, files in os.walk(folder):
        for name in files:
            if not name.endswith(".jsonl"):
                continue
            path = os.path.join(root, name)
            if first_record(path).get("type") not in ("title", "session"):
                continue                      # changes.jsonl and other logs
            st = os.stat(path)
            c = cost(path, st.st_size, cache)
            out["spawned"] += 1
            out["campaign"] += bool(CAMPAIGN.match(name))
            out["nested"] += root != folder
            out["cost"] += c
            if finished(path, st.st_size):
                out["finished"] += 1
                state = "finished"
            elif now - st.st_mtime < STALE:
                out["running"] += 1
                out["running_cost"] += c
                out["active"].append(name[:-6])
                state = "running"
            else:
                out["ended"] += 1
                state = "ended"
            if now - st.st_mtime < RECENT:
                subs[name[:-6]] = dict(state=state, cost=c, mtime=st.st_mtime,
                                       started=getattr(st, "st_birthtime", st.st_ctime))
    out["active"].sort()
    return out


def main():
    now = time.time()
    try:
        cache = {k: tuple(v) for k, v in json.load(open(CACHE)).items()}
    except (OSError, ValueError):
        cache = {}
    sessions, subs = [], {}
    if os.path.isdir(ROOT):
        for proj in os.listdir(ROOT):
            pdir = os.path.join(ROOT, proj)
            if not os.path.isdir(pdir):
                continue
            for name in os.listdir(pdir):
                path = os.path.join(pdir, name)
                if not name.endswith(".jsonl") or not os.path.isfile(path):
                    continue
                folder = path[:-6]
                mtime = max(os.path.getmtime(path), os.path.getmtime(folder) if os.path.isdir(folder) else 0)
                if now - mtime > SINCE:
                    continue
                sub = subagents(folder if os.path.isdir(folder) else "", now, cache, subs)
                sessions.append(dict(file=path, title=first_record(path).get("title") or "", mtime=mtime, **sub))
    sessions.sort(key=lambda s: -s["mtime"])
    json.dump(dict(sessions=sessions, subs=subs), sys.stdout)
    with open(CACHE + ".tmp", "w") as fh:
        json.dump(cache, fh)
    os.replace(CACHE + ".tmp", CACHE)


if __name__ == "__main__":
    main()
