#!/usr/bin/env python

from argparse import ArgumentParser
import numpy as np
import sys


def add_defaults(name, values, nr_sines, default, is_verbose):
    if len(values) < nr_sines:
        if is_verbose:
            print('### warning: adding default values to {0}'.format(name),
                  file=sys.stderr)
        values.extend([default]*(nr_sines - len(values)))


def dump_param(name, params):
    print('# {0}: {1}'.format(name, ', '.join(str(x) for x in params)))


def compute_signal(t, noise, freqs, ampls, phis):
    if noise > 0.0:
        signal = np.random.normal(0.0, noise, len(t))
    else:
        signal = np.zeros(len(t))
    for f, A, phi in zip(freqs, ampls, phis):
        signal += A*np.sin(2.0*np.pi*f*t + phi)
    return signal


def compute_sweep(t, min_freq, max_freq, freq_time):
    delta, _ = np.modf(t/freq_time)
    f = min_freq + delta*(max_freq - min_freq)
    theta = 2.0*np.pi*f*t
    return np.sin(theta)


if __name__ == '__main__':
    param_names = ['f', 'A', 'phi']
    param_defaults = [440.0, 1.0, 0.0]
    arg_parser = ArgumentParser(description='create signals')
    arg_parser.add_argument('--t', type=float, default=1.0,
                            help='total time for the signal (s)')
    arg_parser.add_argument('--sample_rate', type=int, default=65536,
                            help='number of samples per second')
    arg_parser.add_argument('--f', type=float, nargs='*',
                            default=[param_defaults[0]],
                            help='frequencies for sine waves (Hz)')
    arg_parser.add_argument('--A', type=float, nargs='*',
                            default=[param_defaults[1]],
                            help='amplitudes for sine waves')
    arg_parser.add_argument('--phi', type=float, nargs='*',
                            default=[param_defaults[2]],
                            help='phase of sine waves in pi radians')
    arg_parser.add_argument('--noise', type=float, default=0.0,
                            help='amplitude of Gaussian noise')
    arg_parser.add_argument('--sweep', type=float, nargs=3,
                            help='linear sweep between minimum and '
                                 'maximum frequency in specified time')
    arg_parser.add_argument('--header', action='store_true',
                            help='show headers')
    arg_parser.add_argument('--sep', default=' ', help='column separator')
    arg_parser.add_argument('--verbose', action='store_true',
                            help='show verbose output')
    options = arg_parser.parse_args()
    time_steps = np.linspace(0.0, options.t,
                             int(options.t*options.sample_rate))
    if options.sweep:
        if options.header:
            print('# min. freq: {:.3f}'.format(options.sweep[0]))
            print('# max. freq: {:.3f}'.format(options.sweep[1]))
            print('# sweep time: {:.3f}'.format(options.sweep[2]))
        signal = compute_sweep(time_steps, options.sweep[0],
                               options.sweep[1], options.sweep[2])
    else:
        param_values = [list(options.f), list(options.A), list(options.phi)]
        nr_sines = max(map(len, param_values))
        for name, values, default in zip(param_names, param_values,
                                         param_defaults):
            add_defaults(name, values, nr_sines, default, options.verbose)
        if options.header:
            for name, param in zip(param_names, param_values):
                dump_param(name, param)
        signal = compute_signal(time_steps, options.noise, *param_values)
    if options.header:
        print('# sample rate: {0}'.format(options.sample_rate))
        print('# t: {0}'.format(options.t))
        print('t{0}signal'.format(options.sep))
    for i in range(len(time_steps)):
        print('{0:.5f}{1}{2:.15f}'.format(time_steps[i], options.sep,
                                          signal[i]))
