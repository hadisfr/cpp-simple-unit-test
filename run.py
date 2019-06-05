#!/usr/bin/env python3

import csv
import codecs
import subprocess
import re
from sys import stderr

VERBOSE = True
sheet_addr = "./sheet.csv"
judge_addr = "./judge.sh"
submissions_addr = "./codes"


def get_sheet(addr):
    if VERBOSE:
        print("\x1b[32m$\x1b[0m reading %s..." % addr, file=stderr)
    with codecs.open(addr, "r", "utf-8-sig") as f:
        sheet = {row['Identifier']: row for row in list(csv.DictReader(f))}
    return sheet


def persist_sheet(addr, sheet, index=0):
    if VERBOSE:
        print("\x1b[32m$\x1b[0m writing %s..." % addr, file=stderr)
    sheet = list(sheet.values())
    with codecs.open(addr, "w", "utf-8-sig") as f:
        writer = csv.DictWriter(f, sheet[index].keys())
        writer.writeheader()
        writer.writerows(sheet)


def get_submission_list(addr):
    if VERBOSE:
        print("\x1b[32m$\x1b[0m indexing %s..." % addr, file=stderr)
    cmd = ["ls", addr]
    return subprocess.run(cmd, stdout=subprocess.PIPE).stdout.decode("utf-8").split("\n")[:-1]


def get_score(judge_addr, submission_addr):
    cmd = [judge_addr, submission_addr]
    if VERBOSE:
        print("\x1b[32m$\x1b[0m %s" % " ".join(cmd), file=stderr)
    raw_res = re.compile(
        r'(\x9B|\x1B\[)[0-?]*[ -\/]*[@-~]'
    ).sub(
        '',
        subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE).stdout.decode("utf-8")
    ).split("\n")
    log = "\n".join(raw_res[1:-5])
    overall_res = raw_res[-5]
    score = int(re.findall(
        r"Overall passed: ([0-9]+) of ([0-9]+) \([0-9.]+%\)",
        overall_res
    )[0][0])
    return (score, log)


def main():
    sheet = get_sheet(sheet_addr)
    submissions = get_submission_list(submissions_addr)
    for submission in submissions:
        (score, log) = get_score(judge_addr, "%s/%s" % (submissions_addr, submission))
        sheet['Participant %s' % submission]['Grade'] = score
        sheet['Participant %s' % submission]['Feedback comments'] = log
    persist_sheet(sheet_addr, sheet)


if __name__ == '__main__':
    main()
