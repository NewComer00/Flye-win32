#!/usr/bin/env python

#(c) 2019 by Authors
#This file is a part of the Flye package.
#Released under the BSD license (see LICENSE file)

"""
Runs simple toy test
"""


from __future__ import print_function

import os
import sys
import subprocess
import shutil
import multiprocessing
# from distutils.spawn import find_executable


def test_toy():
    # if not find_executable("flye"):
    #     sys.exit("flye is not installed!")

    print("Running toy test:\n")
    cpus = max(1, multiprocessing.cpu_count() // 2)
    script_dir = os.path.dirname(os.path.realpath(__file__))
    reads_file = os.path.join(script_dir, "data", "ecoli_500kb_reads_hifi.fastq.gz")
    out_dir = "flye_toy_test"
    cmd_test = ["python", "bin/flye", "--pacbio-corr", reads_file, "-g", "500k",
                           "-o", out_dir, "-t", str(cpus), "-m", "1000"]

    print("Running command:\n%s\n" % " ".join(cmd_test))
    subprocess.check_call(cmd_test)
    # shutil.rmtree(out_dir)
    print("\nTEST SUCCESSFUL")


def main():
    test_toy()
    return 0


if __name__ == "__main__":
    sys.exit(main())
