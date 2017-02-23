import numpy   as np
import h5py    as h5
import Gnuplot as gp
import math    as mt
import sys
import os

# cutoff for cloudy and rainy grid cells
cutoff_cld = 0.01 # g/kg
cutoff_rin = 0.01 # g/kg

# left and right edges of bins for dry and wet radius
dry_edges = np.fromiter( (1e-6 * 10**(-3 + i * .1) for i in xrange(41)), dtype="float")
num_dry   = dry_edges.size - 1

# path to directory with data
dir_path = '../../../build/tests/chem_sandbox/'

# loop for case with and without aqueous chemistry
for case in ['case1', 'case_base', 'case3', 'case4', 'case5', 'case6']:
    
    # helper arrays for storing initial and cutoff dry radii
    n_dry_ini = np.zeros(num_dry)
    n_dry_dry = np.zeros(num_dry)
    n_dry_cld = np.zeros(num_dry)
    n_dry_rin = np.zeros(num_dry)
    
    # open hdf5 files with data
    h5f_ini  = h5.File(dir_path + 'out_' + case + '/timestep0000010000.h5', 'r')
    h5f_fin  = h5.File(dir_path + 'out_' + case + '/timestep0000011800.h5', 'r')

    # choose indexes of grid-cell with r_c and r_r > cutoff
    cld_mixr_fin = h5f_fin['rw_rng000_mom3'][:] * 4./3 * 3.14 * 1e3 * 1e3 #g/kg
    rin_mixr_fin = h5f_fin['rw_rng001_mom3'][:] * 4./3 * 3.14 * 1e3 * 1e3 #g/kg
            
    idx_dry = np.where(cld_mixr_fin <= cutoff_cld)
    idx_cld = np.where(cld_mixr_fin >  cutoff_cld)
    idx_rin = np.where(rin_mixr_fin >= cutoff_rin)
    
    # construct the size distribution based on the range of bins for mom0 
    for i in range(num_dry-1): # first bin id for total conc
        name_mom3 = "rw3ofrd_rng" + str(i+1).zfill(3) + "_mom3"
        name_mom0 =      "rd_rng" + str(i+1).zfill(3) + "_mom0"
        #idx_ini = np.where(h5f_ini[name_mom0][:] > 0)
        #idx_fin = np.where(h5f_fin[name_mom0][:] > 0) 
        tmp_ini  = (h5f_ini[name_mom3][:]) * 4.3 * mt.pi * 1e3 * 1e9 * 1e-6 # mean water mass [ug of water per mg of air per log dry radius size interval]
        tmp_fin  = (h5f_fin[name_mom3][:]) * 4.3 * mt.pi * 1e3 * 1e9 * 1e-6 # mean water mass [ug of water per mg of air per log dry radius size interval]
                                         # * volume      * rho_H2O * ug of water * mg of air
        #tmp_ini[idx_ini] = 0
        #tmp_fin[idx_fin] = 0

        n_dry_ini[i] += tmp_ini.sum()          / 76. / 76.       / (mt.log(dry_edges[i+1], 10) - mt.log(dry_edges[i], 10))
        #n_dry_dry[i] += tmp_fin[idx_dry].sum() / idx_dry[0].size / (mt.log(dry_edges[i+1], 10) - mt.log(dry_edges[i], 10))
        n_dry_cld[i] += tmp_fin[idx_cld].sum() / idx_cld[0].size / (mt.log(dry_edges[i+1], 10) - mt.log(dry_edges[i], 10))
        #n_dry_rin[i] += tmp_fin[idx_rin].sum() / idx_rin[0].size / (mt.log(dry_edges[i+1], 10) - mt.log(dry_edges[i], 10))
       
    # close hdf5 files
    h5f_ini.close()
    h5f_fin.close()
   
    # create directory for output (if it doesn't exist)
    output_dir = dir_path + 'plots_of_size_distr/'
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # plotting (part1)
    ymin = 1e-6
    ymax = 100
    xmin = 0.001
    xmax = 10

    g = gp.Gnuplot()
    g('reset')
    g('set term svg dynamic enhanced font "Verdana, 14"')
    g('set output "'+ output_dir + case + '_rw3ofrd.svg" ')
    g('set logscale xy')
    g('set key samplen 1.2')
    g('set xtics rotate by 65 right (.001, .01, .1, 1, 10)')
    #g('set ytics (.001, .01, .1, 1, 10, 100, 1000)')
    g('set xlabel "particle radius [um]"')
    g('set ylabel "dm/dlog_{10}(r) [ug mg^{-1} per log_{10}(size interval)]"')
    g('set xrange [' +  str(xmin) + ':' + str(xmax) + ']')
    g('set yrange [' +  str(ymin) + ':' + str(ymax) + ']')
    g('set grid')
    g('set nokey')
    
    plot_rd_ini  = gp.PlotItems.Data(dry_edges[:-1] * 1e6 , n_dry_ini,  with_="steps lw 4 lc rgb 'black'")
    #plot_rd_dry  = gp.PlotItems.Data(dry_edges[:-1] * 1e6 , n_dry_dry,  with_="steps lw 4 lc rgb 'red'")
    plot_rd_cld  = gp.PlotItems.Data(dry_edges[:-1] * 1e6 , n_dry_cld,  with_="steps lw 4 lc rgb 'green'")
    #plot_rd_rin  = gp.PlotItems.Data(dry_edges[:-1] * 1e6 , n_dry_rin,  with_="steps lw 4 lc rgb 'blue'")
 
    g.plot(plot_rd_ini, plot_rd_cld)
 
