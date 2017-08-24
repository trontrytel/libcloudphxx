#include <cstdlib> // system()
#include <set>
#include <string>
#include <sstream> // std::ostringstream

#include <fstream>
#include <iostream>

#include "../common.hpp"
#include "bins.hpp"

using std::ostringstream;
using std::set;
using std::string;

int main(int ac, char** av)
{
  if (ac != 2) error_macro("expecting one argument - CMAKE_BINARY_DIR");

  string bins_wet_str, bins_dry_str, bins_wet_str_2;
/*
  {
    ostringstream tmp;
    vector<quantity<si::length>> left_edges = bins_dry();
    for (int i = 0; i < left_edges.size()-1; ++i)
      tmp << float(left_edges[i] / si::metres) << ":" << float(left_edges[i + 1] / si::metres) << "|0;";
    bins_dry_str = tmp.str();
  }

  {
    ostringstream tmp;
    vector<quantity<si::length>> left_edges = bins_wet();
    for (int i = 0; i < left_edges.size()-1; ++i)
      tmp << float(left_edges[i] / si::metres) << ":" << float(left_edges[i + 1] / si::metres) << "|0;";
    bins_wet_str = tmp.str();
  }
*/
  {
    ostringstream tmp;
    vector<quantity<si::length>> left_edges = bins_wet();
    for (int i = 0; i < left_edges.size()-1; ++i)
      tmp << float(left_edges[i] / si::metres) << ":" << float(left_edges[i + 1] / si::metres) << "|0,3,6;";
    bins_wet_str_2 = tmp.str();
  }

  {
    string cmn = 
      "--outfreq=100 --dt=1 --nt=11800 --spinup=7200 --nx=76 --nz=76 --relax_th_rv=false "
      "--backend=CUDA --adv_serial=false --sd_conc=256 --sstp_cond=10 --coal=true --sedi=true "
      "--adve=true --adve_scheme=pred_corr --async=true --rcyc=true "
      "--w_max=1.2 --terminal_velocity=beard77fast "
      "--micro=lgrngn --kernel=onishi_hall --rng_seed=42 ";

    string stats =         
        " --out_wet=\""
          "1.e-6:25e-6|0,1,2,3,6;"   // "cloud"
          "25e-6:1|0,3,6;"           // "rain"
          "1.e-6:1|6;"               // "all liquid 6th moment"
//          + bins_wet_str_2 +       // aerosol spectrum (wet)
        "\""
        " --out_dry=\""
          "0.:1.|0,1,3;"
        "\"";

    string size1 = "--mean_rd1=0.05e-6 --sdev_rd1=1.8 --n1_stp=50e6  --mean_rd2=0.1e-6 --sdev_rd2=1.5 --n2_stp=0 ";
    string size2 = "--mean_rd1=0.05e-6 --sdev_rd1=1.8 --n1_stp=150e6 --mean_rd2=0.1e-6 --sdev_rd2=1.5 --n2_stp=0 ";
    string size3 = "--mean_rd1=0.05e-6 --sdev_rd1=1.8 --n1_stp=0     --mean_rd2=0.1e-6 --sdev_rd2=1.5 --n2_stp=50e6 ";
    string size4 = "--mean_rd1=0.05e-6 --sdev_rd1=1.8 --n1_stp=0     --mean_rd2=0.1e-6 --sdev_rd2=1.5 --n2_stp=150e6 ";

    string case1 = "--outdir=out_size1 ";
    string case2 = "--outdir=out_size2 ";
    string case3 = "--outdir=out_size3 ";
    string case4 = "--outdir=out_size4 ";

    set<string> opts_micro({
        cmn + " " + case1 + " " + stats + " " + size1,
        //cmn + " " + case2 + " " + stats + " " + size2,
        cmn + " " + case3 + " " + stats + " " + size3
        //cmn + " " + case4 + " " + stats + " " + size4 
    });

    // run the above simulation cases
    for (auto &opts_m : opts_micro)
    {
      ostringstream cmd;
      cmd << av[1] << "/src/icicle " << opts_m;  
      notice_macro("about to call: " << cmd.str())

      std::ofstream log;
      log.open("command_log", std::ios::app);
      log << cmd.str() << "\n";
      log.close();  

      if (EXIT_SUCCESS != system(cmd.str().c_str()))
        error_macro("model run failed: " << cmd.str())
    }
  }
}
