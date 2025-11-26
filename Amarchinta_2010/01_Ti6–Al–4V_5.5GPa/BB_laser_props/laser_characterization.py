#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#=FILE DESCRIPTION======================================================
#
# Python script to visualize temporal and spatial laser-induced
# pressure intensity profiles for HiLASE lasers
#
# Conversion from laser power density to the ablation pressure is based
# on Scius-Bertrand et al. 2021
#

#=LICENSE===============================================================
#  laser_characterization_HiLASE.py
#
#  Copyright 2023 Martin Isoz <isozm@it.cas.cz>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#
#
#=======================================================================

# imports --------------------------------------------------------------
# -- file processing and I/O

# -- computations (general)
import numpy as np

# auxiliary functions  -------------------------------------------------
def pTime(t):
    """
    Pressure temporal evolution using piecewise linear points.
    t: array of times [ns]
    Returns pT (pressure at times t) and tZero (end of pulse)
    """

    # -- temporal table (t [ns], normalized pressure)
    t_points_ns = np.array([0, 3, 6, 15, 90, 169.9, 170, 200])
    p_points = np.array([0, 1, 1, 0.75, 0.3, 0.3, 0, 0])

    # -- convert t_points to seconds
    t_points = t_points_ns * 1e-9

    # -- linear interpolation
    pT = np.interp(t, t_points, p_points)

    # -- tZero = final pressure time
    tZero = t_points[-1]

    return pT, tZero
