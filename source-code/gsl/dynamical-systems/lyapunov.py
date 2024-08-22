#!/usr/bin/env python3

from argparse import ArgumentParser
from math import fabs
import sys


def read_file(file_name):
    time = []
    theta = []
    omega = []
    with open(file_name, 'r') as in_file:
        for line in in_file:
            line = line.strip()
            if line.startswith('#'):
                continue
            if len(line) == 0:
                continue
            data = [float(x) for x in line.split()]
            time.append(data[0])
            theta.append(data[1])
            omega.append(data[2])
    return time, theta, omega


def compute_deviation(time1, theta1, time2, theta2, tol=1.0e-5,
                      verbose=False):
    nr_skipped = 0
    for t1, t2, th1, th2 in zip(time1, time2, theta1, theta2):
        if fabs(t1 - t2) < tol:
            print('{0} {1:.15f}'.format(t1, fabs(th1 - th2)))
        else:
            nr_skipped += 1
    if verbose:
        print('nr. skipped: {0}'.format(nr_skipped), file=sys.stderr)


if __name__ == '__main__':
    arg_parser = ArgumentParser(description='Given two oscillator output '
                                            'files, illustrate Lyapunov '
                                            'exponent')
    arg_parser.add_argument('input_1', help='first trajectory file')
    arg_parser.add_argument('input_2', help='second trajectory file')
    arg_parser.add_argument('--tol', type=float, default=1.0e-5,
                            help='tolerance to compare times')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='provide feedback')
    options = arg_parser.parse_args()
    time1, theta1, _ = read_file(options.input_1)
    time2, theta2, _ = read_file(options.input_2)
    if options.verbose:
        print('nr. data points: {0}'.format(len(time1)), file=sys.stderr)
    compute_deviation(time1, theta1, time2, theta2, options.tol,
                      options.verbose)
